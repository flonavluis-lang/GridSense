#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// ========================================
// FLEX
// ========================================
const int flexDerPin = 34;
const int flexIzqPin = 35;
const int flexPin32 = 32; 
const int flexPin33 = 33; 

const char* ssid = "Galaxy";
const char* password = "parangaricutirimicuaro";

String scriptURL =
"https://script.google.com/macros/s/AKfycbzewHevecC4D11mBoVNSa_ibbohmU8GuMh_Ehb6020j9hIHo4jEdMzNjuLsBoRuJDnrDQ/exec";

// ========================================
// FILTRO
// ========================================
float alpha = 0.15;

float flexIzq = 0;
float flexDer = 0;
float flex32 = 0;          
float flex33 = 0;          

const int numSamples = 10;

// ========================================
// UMBRALES
// ========================================
int umbralRecto = 450;
int umbralRiesgo = 4000;

int margen = 100;

// ========================================
// ESTADOS
// ========================================
String estadoIzq = "Recto";
String estadoDer = "Recto";
String estado32 = "Recto";  
String estado33 = "Recto";  

String estadoIzqAnt = "";
String estadoDerAnt = "";
String estado32Ant = "";
String estado33Ant = "";

void enviarDatos() {

    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;

    String eIzq = estadoIzq;
    String eDer = estadoDer;
    String e32  = estado32;
    String e33  = estado33;

    eIzq.replace(" ", "%20");
    eDer.replace(" ", "%20");
    e32.replace(" ", "%20");
    e33.replace(" ", "%20");

    String url = scriptURL +
        "?tipo=FLEX" +
        "&flexIzq=" + String((int)flexIzq) +
        "&estadoIzq=" + eIzq +
        "&flex32=" + String((int)flex32) +
        "&estado32=" + e32 +
        "&flexDer=" + String((int)flexDer) +
        "&estadoDer=" + eDer +
        "&flex33=" + String((int)flex33) +
        "&estado33=" + e33;

    Serial.println("================================");
    Serial.println("URL ENVIADA:");
    Serial.println(url);

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("HTTP=");
    Serial.println(httpCode);

    String payload = http.getString();

    Serial.print("RESPUESTA=");
    Serial.println(payload);

    http.end();
}
// ========================================
// SETUP
// ========================================
void setup() {

    Serial.begin(115200);

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

    pinMode(flexIzqPin, INPUT);
    pinMode(flexDerPin, INPUT);
    pinMode(flexPin32, INPUT);
    pinMode(flexPin33, INPUT);

    // =========================
    // CALIBRACIÓN INICIAL
    // =========================
    long sumaIzq = 0;
    long sumaDer = 0;
    long suma32 = 0;
    long suma33 = 0;

    for (int i = 0; i < 50; i++) {
        // lectura para estabilizar ADC en calibración
        analogRead(flexIzqPin); delayMicroseconds(5);
        sumaIzq += analogRead(flexIzqPin);

        analogRead(flexDerPin); delayMicroseconds(5);
        sumaDer += analogRead(flexDerPin);

        analogRead(flexPin32); delayMicroseconds(5);
        suma32  += analogRead(flexPin32);

        analogRead(flexPin33); delayMicroseconds(5);
        suma33  += analogRead(flexPin33);

        delay(10);
    }

    flexIzq = sumaIzq / 50.0;
    flexDer = sumaDer / 50.0;
    flex32  = suma32 / 50.0;
    flex33  = suma33 / 50.0;

    Serial.println("Sistema iniciado con 4 sensores");
}

// ========================================
// ESTADO FLEX
// ========================================
String obtenerEstado(float valor, String estadoActual) {
    if (estadoActual == "Recto") {
        if (valor > umbralRecto + margen) {
            estadoActual = "Flexion";
        }
    }
    else if (estadoActual == "Flexion") {
        if (valor < umbralRecto - margen) {
            estadoActual = "Recto";
        }
        else if (valor > umbralRiesgo + margen) {
            estadoActual = "Riesgo";
        }
    }
    else if (estadoActual == "Riesgo") {
        if (valor < umbralRiesgo - margen) {
            estadoActual = "Flexion";
        }
    }
    return estadoActual;
}

// ========================================
// LOOP
// ========================================
void loop() {

    // ====================================
    // FLEX IZQUIERDO
    // ====================================
    long sumaIzq = 0;
    for (int i = 0; i < numSamples; i++) {
        analogRead(flexIzqPin); // Lectura fantasma para limpiar el ADC
        delayMicroseconds(5);
        sumaIzq += analogRead(flexIzqPin);
        delay(2);
    }
    float adcIzq = sumaIzq / (float)numSamples;
    flexIzq = alpha * adcIzq + (1 - alpha) * flexIzq;

    // ====================================
    // FLEX DERECHO
    // ====================================
    long sumaDer = 0;
    for (int i = 0; i < numSamples; i++) {
        analogRead(flexDerPin); // Lectura fantasma
        delayMicroseconds(5);
        sumaDer += analogRead(flexDerPin);
        delay(2);
    }
    float adcDer = sumaDer / (float)numSamples;
    flexDer = alpha * adcDer + (1 - alpha) * flexDer;

    // ====================================
    // FLEX PIN 32
    // ====================================
    long suma32 = 0;
    for (int i = 0; i < numSamples; i++) {
        analogRead(flexPin32); // Lectura fantasma
        delayMicroseconds(5);
        suma32 += analogRead(flexPin32);
        delay(2);
    }
    float adc32 = suma32 / (float)numSamples;
    flex32 = alpha * adc32 + (1 - alpha) * flex32;

    // ====================================
    // FLEX PIN 33
    // ====================================
    long suma33 = 0;
    for (int i = 0; i < numSamples; i++) {
        analogRead(flexPin33); // Lectura fantasma
        delayMicroseconds(5);
        suma33 += analogRead(flexPin33);
        delay(2);
    }
    float adc33 = suma33 / (float)numSamples;
    flex33 = alpha * adc33 + (1 - alpha) * flex33;

    // ====================================
    // ESTADOS INDIVIDUALES
    // ====================================
    estadoIzq = obtenerEstado(flexIzq, estadoIzq);
    estadoDer = obtenerEstado(flexDer, estadoDer);
    estado32  = obtenerEstado(flex32, estado32);
    estado33  = obtenerEstado(flex33, estado33);
    
    if (
    estadoIzq != estadoIzqAnt ||
    estadoDer != estadoDerAnt ||
    estado32  != estado32Ant  ||
    estado33  != estado33Ant
) {

    enviarDatos();

    estadoIzqAnt = estadoIzq;
    estadoDerAnt = estadoDer;
    estado32Ant  = estado32;
    estado33Ant  = estado33;
}

    // ====================================
    // Pruebas en el SERIAL
    // ====================================
    Serial.print("Izq: ");
    Serial.print(flexIzq);
    Serial.print(" -> ");
    Serial.print(estadoIzq);

    Serial.print(" | Der: ");
    Serial.print(flexDer);
    Serial.print(" -> ");
    Serial.print(estadoDer);

    Serial.print(" | P32: ");
    Serial.print(flex32);
    Serial.print(" -> ");
    Serial.print(estado32);

    Serial.print(" | P33: ");
    Serial.print(flex33);
    Serial.print(" -> ");
    Serial.println(estado33);
  
    delay(50);
}