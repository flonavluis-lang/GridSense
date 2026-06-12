<p align="center">
  <img width="800" height="300" alt="rodillera_sensores" src="https://github.com/user-attachments/assets/5482916b-51fa-4c35-9f2b-732d1afd1791" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Status-Work%20In%20Progress-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Platform-ESP32-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Sensors-4%20Flex%20%7C%205%20Piezo-green?style=for-the-badge">
</p>

# GridSense

GridSense is a wearable smart knee brace designed to monitor knee flexion and detect impact events during physical activity. The system combines flex sensors, piezoelectric sensors, and ESP32 microcontrollers to acquire, process, and transmit real-time biomechanical data for movement analysis and injury prevention.

## Features

- 4 flex sensors for knee movement monitoring
- 5 piezoelectric sensors for impact detection
- 2 ESP32 microcontrollers
- Real-time data acquisition
- Wi-Fi communication
- Google Sheets integration
- Impact classification
- Movement analysis and monitoring

## Team

- Luis Manuel Flores Navarrete
- Elizabeth Amigón Domínguez

## Advisor

- Hugo Gustavo González Hernández

## Project Overview

GridSense was developed as a wearable monitoring system capable of measuring knee flexion and detecting impacts during physical activity. The prototype integrates four flex sensors positioned around the knee joint and five piezoelectric sensors distributed throughout the knee brace.

The acquired data is processed by two ESP32 microcontrollers and transmitted wirelessly to Google Sheets, where measurements can be visualized and analyzed in real time.

The main objective of the project is to provide quantitative information about knee movement and impact events that may contribute to injury prevention, biomechanical analysis, and future sports monitoring applications.

---

## System Architecture

The GridSense architecture is divided into four main stages:

1. Data acquisition through flex and piezoelectric sensors.
2. Signal processing using ESP32 microcontrollers.
3. Wireless communication through Wi-Fi.
4. Storage and visualization using Google Sheets.

The architecture allows real-time monitoring of knee movement and impact events during physical activity.

---

## Prototype
<img width="500" height="600" alt="Prototipo_final" src="https://github.com/user-attachments/assets/44cbdc75-9696-4833-aa47-3a3bfc552cb7" />

---

## Circuit Connections

### Flex Sensors
<img width="700" height="400" alt="flex_esp32" src="https://github.com/user-attachments/assets/566e5422-63fd-4570-b4e4-f5f71186dded" />

### Piezoelectric Sensors
<img width="700" height="400" alt="piezos_esp32" src="https://github.com/user-attachments/assets/62fd697a-8c49-4f3c-b31a-6535f29c76cd" />

---

## Technologies Used

- ESP32
- Arduino IDE
- Flex Sensors
- Piezoelectric Sensors
- Wi-Fi Communication
- Google Sheets
- C++

---

## Experimental Results

The system was experimentally validated through:

- Flex sensor calibration tests.
- Controlled impact tests using known masses and drop heights.
- Real-time monitoring tests.
- Field tests with athletes performing movement and acceleration exercises.

---

## Demonstration Videos

The following videos show the operation of GridSense during laboratory tests, calibration procedures, and real-world athletic activities.

<p align="center">
  <a href="https://drive.google.com/drive/folders/1wFj4c-nhccjZuyiRole_q-78-rgM8UrX?usp=sharing">
    <img src="https://img.shields.io/badge/Watch%20Project%20Videos-Google%20Drive-red?style=for-the-badge&logo=google-drive">
  </a>
</p>

---

### Real-Time Monitoring
<img width="840" height="438" alt="GoogleSheets" src="https://github.com/user-attachments/assets/8ce296b9-034b-4df5-845e-f335612ada0a" />

---

## Repository Contents

- Source code for flex sensor acquisition.
- Source code for piezoelectric sensor acquisition.
---

## Future Improvements

- Improve flex sensor stability and calibration.
- Implement pattern recognition algorithms.
- Develop injury risk alert systems.
- Design a mobile application.
- Improve cable management and electronics integration.
- Develop a more compact and ergonomic version.
- Incorporate machine learning for movement analysis.

---

## Documentation
The complete technical report, methodology, experimental results, and project conclusions are available in the following document: [Reporte_Final_Jackpot.pdf](https://github.com/user-attachments/files/28885320/Reporte_Final_Jackpot.pdf).

---

## Institution

Instituto de Estudios Superiores de Monterrey – Campus Puebla
