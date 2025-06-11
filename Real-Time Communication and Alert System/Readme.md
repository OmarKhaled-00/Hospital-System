## 📡 Real-Time Communication and Alert System

---

### 🔸 Overview
The **Real-Time Communication and Alert System** enables the **Master MCU (ATmega32)** to transmit environmental alerts to a remote monitoring interface using the **ESP8266 WiFi module**. This system supports real-time data broadcasting and IoT-based remote supervision.

---

### 🔸 Communication Protocol

- **Interface:** USART (Asynchronous Serial Communication)
- **Baud Rate:** `9600`
- **Data Format:** `8 data bits`, `no parity`, `1 stop bit` (`SWSERIAL_8N1`)
- **Driver Used:** `USART.c` – Custom-built for stable transmission

---

### 🔸 ESP8266 Transmission Codes

| Condition               | Code Sent | Server Action                     |
|------------------------|-----------|-----------------------------------|
| Gas Detected           | `G`       | Show gas leak alert               |
| Gas Cleared            | `g`       | Clear gas alert                   |
| Temperature > 25°C     | `H`       | Display high temperature warning  |
| Temperature ≤ 25°C     | `L`       | Clear temperature warning         |
| Light Intensity < 49   | `D`       | Show low ambient light alert      |

---

### 🔸 Communication Logic

- ✅ **Efficient State Tracking:** Data is sent only on condition/state changes to reduce unnecessary traffic.
- 🔁 **Super Loop Execution:** Periodically checks flags from ADC and digital sensors.
- ✉️ **USART Output:** Transmits 1-byte ASCII characters representing specific alerts.

---

### 🔸 ESP8266 Configuration

| Parameter               | Value                    |
|------------------------|--------------------------|
| Baud Rate              | `9600`                   |
| Mode                   | Station (STA)            |
| Protocol Format        | ASCII                    |
| WiFi Platform          | Blynk / Custom Web App   |
| Connected Pins         | `espSerial` (SoftwareSerial) |

---

### 🔸 Reliability Features

- ⚠️ **Error Prevention:** Optional timeout mechanism to detect transmission failure.
- 🧩 **Layer Separation:** Communication logic is isolated from sensor processing.
- ⚡ **Optimized Output:** Single-character codes for lightweight, fast network parsing.

---

### 🔸 Use Cases

- 🔥 Fire/Gas alert notification to web/mobile dashboards
- 🏥 Real-time hospital room condition monitoring
- 📲 Integration with cloud-based alert systems (e.g., Blynk, ThingSpeak, custom dashboards)

---

### Video [Here](https://drive.google.com/file/d/1cIK4LhfvrbY6V4GstkTynaeZuTq_GgB2/view)



