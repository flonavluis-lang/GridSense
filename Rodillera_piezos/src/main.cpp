#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ============================
// WIFI
// ============================
const char* ssid = "Galaxy";
const char* password = "parangaricutirimicuaro";

String scriptURL =
"https://script.google.com/macros/s/AKfycbzewHevecC4D11mBoVNSa_ibbohmU8GuMh_Ehb6020j9hIHo4jEdMzNjuLsBoRuJDnrDQ/exec";

// ============================
// PIEZOS
// ============================
const int piezo1Pin = 34;
const int piezo2Pin = 35;
const int piezo3Pin = 32;
const int piezo4Pin = 33;
const int piezo5Pin = 36;

// ============================
// UMBRALES
// ============================
const int umbralMedio = 550;
const int umbralFuerte = 900;

// ============================
// MAXIMOS
// ============================
int max1 = 0;
int max2 = 0;
int max3 = 0;
int max4 = 0;
int max5 = 0;

unsigned long ultimoReporte = 0;

// ============================
// ENVIO GOOGLE SHEETS
// ============================
void enviarImpactos(
    int p1, String e1,
    int p2, String e2,
    int p3, String e3,
    int p4, String e4,
    int p5, String e5
) {

    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;

    String url = scriptURL +
        "?tipo=PIEZO" +
        "&p1=" + String(p1) +
        "&e1=" + e1 +
        "&p2=" + String(p2) +
        "&e2=" + e2 +
        "&p3=" + String(p3) +
        "&e3=" + e3 +
        "&p4=" + String(p4) +
        "&e4=" + e4 +
        "&p5=" + String(p5) +
        "&e5=" + e5;

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("HTTP=");
    Serial.println(httpCode);

    http.end();
}

// ============================
// CLASIFICACION
// ============================
String clasificarImpacto(int valor) {

    if (valor >= umbralFuerte) {
        return "FUERTE";
    }

    if (valor >= umbralMedio) {
        return "MEDIO";
    }

    return "";
}

// ============================
// SETUP
// ============================
void setup() {

    Serial.begin(115200);

    analogReadResolution(12);

    WiFi.begin(ssid, password);

    Serial.print("Conectando WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("Prueba de 5 piezos");
}

// ============================
// LOOP
// ============================
void loop() {

    int lectura1 = analogRead(piezo1Pin);
    if (lectura1 > max1) max1 = lectura1;

    int lectura2 = analogRead(piezo2Pin);
    if (lectura2 > max2) max2 = lectura2;

    int lectura3 = analogRead(piezo3Pin);
    if (lectura3 > max3) max3 = lectura3;

    int lectura4 = analogRead(piezo4Pin);
    if (lectura4 > max4) max4 = lectura4;

    int lectura5 = analogRead(piezo5Pin);
    if (lectura5 > max5) max5 = lectura5;

    if (millis() - ultimoReporte >= 1000) {

        String estado1 = clasificarImpacto(max1);
        String estado2 = clasificarImpacto(max2);
        String estado3 = clasificarImpacto(max3);
        String estado4 = clasificarImpacto(max4);
        String estado5 = clasificarImpacto(max5);

        bool huboImpacto = false;

        if (estado1 != "") {
            Serial.print("P1: ");
            Serial.print(max1);
            Serial.print(" -> ");
            Serial.println(estado1);
            huboImpacto = true;
        }

        if (estado2 != "") {
            Serial.print("P2: ");
            Serial.print(max2);
            Serial.print(" -> ");
            Serial.println(estado2);
            huboImpacto = true;
        }

        if (estado3 != "") {
            Serial.print("P3: ");
            Serial.print(max3);
            Serial.print(" -> ");
            Serial.println(estado3);
            huboImpacto = true;
        }

        if (estado4 != "") {
            Serial.print("P4: ");
            Serial.print(max4);
            Serial.print(" -> ");
            Serial.println(estado4);
            huboImpacto = true;
        }

        if (estado5 != "") {
            Serial.print("P5: ");
            Serial.print(max5);
            Serial.print(" -> ");
            Serial.println(estado5);
            huboImpacto = true;
        }

        if (huboImpacto) {

            enviarImpactos(
                estado1 != "" ? max1 : 0, estado1,
                estado2 != "" ? max2 : 0, estado2,
                estado3 != "" ? max3 : 0, estado3,
                estado4 != "" ? max4 : 0, estado4,
                estado5 != "" ? max5 : 0, estado5
            );

            Serial.println("----------------------");
        }

        max1 = 0;
        max2 = 0;
        max3 = 0;
        max4 = 0;
        max5 = 0;

        ultimoReporte = millis();
    }
}