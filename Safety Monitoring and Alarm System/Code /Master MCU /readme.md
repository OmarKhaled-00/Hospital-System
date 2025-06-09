📂 **Section: Master MCU Firmware – Safety and Monitoring System**

---

### 🔸 Overview
The **Master MCU (ATmega32)** plays a central role in environmental sensing, data processing, and coordination with a Slave MCU and a WiFi communication module (ESP8266).

---

### 🔸 Sensors Integration

| **Sensor**     | **Purpose**             | **Signal Type** | **Interface**     |
|----------------|--------------------------|------------------|-------------------|
| Flame Sensor   | Fire detection            | Digital          | INT0, INT1        |
| Gas Sensor     | Gas leakage detection     | Digital          | DIO - PINB2       |
| LM35           | Temperature monitoring    | Analog           | ADC               |
| LDR            | Light level monitoring    | Analog           | ADC               |

---

### 🔸 Communication Flow
- **SPI:** Sends control/status data to Slave MCU.
- **USART:** Sends environment alerts to ESP8266 for IoT-based real-time monitoring.

---

### 🔸 Interrupt Usage

| **Interrupt** | **Trigger Source** | **Purpose**            |
|---------------|--------------------|-------------------------|
| INT0          | Flame Sensor 1     | Fire alert (channel 1)  |
| INT1          | Flame Sensor 2     | Fire alert (channel 2)  |

---

### 🔸 System States & Actions

| **Condition**           | **SPI Code** | **ESP Code** | **Actuator Action**    |
|-------------------------|--------------|--------------|-------------------------|
| Fire Detected (Ch1)     | `f`          | `f`          | Alarm on               |
| Fire Ended (Ch1)        | `n`          | `n`          | Alarm off              |
| Fire Detected (Ch2)     | `F`          | `F`          | Alarm on               |
| Fire Ended (Ch2)        | `N`          | `N`          | Alarm off              |
| Gas Detected            | `G`          | `G`          | Fan/warning on         |
| Gas Cleared             | `g`          | `g`          | Fan/warning off        |
| Temp > 25°C             | `H`          | `H`          | Activate fan           |
| Temp ≤ 25°C             | `L`          | `L`          | Deactivate fan         |
| Light < 49              | `D`          | `D`          | Turn light on          |

---


