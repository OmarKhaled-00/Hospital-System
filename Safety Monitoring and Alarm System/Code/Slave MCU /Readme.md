## 📂 Section: Slave MCU Firmware – Actuation & Response System

### 🔸 Overview
The Slave MCU (ATmega32) handles all actuator control operations based on commands received via SPI from the Master MCU. It provides a fast and deterministic response to critical safety and environment-related signals.

---

### 🔸 SPI Command Handling

| Received Code | Function               | Description                       |
|---------------|------------------------|---------------------------------|
| f             | Fire_Alarm_OnCh1()     | Turn ON Buzzer + Pump1 + Red LED|
| n             | Fire_Alarm_OffCh1()    | Turn OFF Buzzer + Pump1 + Restore LEDs |
| K             | Fire_Alarm_OnCh2()     | Turn ON Buzzer + Pump2 + Red LED|
| k             | Fire_Alarm_OffCh2()    | Turn OFF Buzzer + Pump2 + Restore LEDs |
| G             | Gas_Alarm_On()         | Activate Buzzer, Yellow LED, 2 Fans |
| g             | Gas_Alarm_Off()        | Deactivate Buzzer, Fans, Restore LEDs |
| H             | Fan High               | Set Fan pin HIGH                |
| L             | Fan Low                | Set Fan pin LOW                 |
| D             | Case_Dark()            | PWM = 100% (Brightest)          |
| I             | Case_Mid()             | PWM = ~40% (Medium Brightness)  |
| S             | Case_Light()           | PWM = ~5% (Dim Light)            |

---

### 🔸 PWM-Based Light Intensity Control

| Function      | PWM Compare Match | Light Level         |
|---------------|-------------------|---------------------|
| Case_Dark()   | 255               | Maximum brightness  |
| Case_Mid()    | 100               | Medium brightness   |
| Case_Light()  | 10                | Minimum brightness  |

---

### 🔸 Actuator Components

| Component         | Port/Pin           | Role                           |
|-------------------|--------------------|--------------------------------|
| Buzzer            | PORTA, PIN0        | Audio alert                   |
| Fan 1 & Fan 2     | PORTC, PIN2 & PIN3 | Ventilation                   |
| Water Pump 1      | PORTC, PIN0        | Fire suppression (Ch1)        |
| Water Pump 2      | PORTC, PIN1        | Fire suppression (Ch2)        |
| RGB LEDs (Red/Green) | PORTC, PIN4/PIN5 | Fire/Gas/Normal indication     |
| Fan Control       | PORTB, PIN0        | Temp-based ventilation        |
| Indicator LED     | PORTA, PIN7        | SPI reception status          |

---

### 🔸 System Logic Features
- **Status Acknowledgment:** LED toggle (PORTA, PIN7) confirms command receipt.
- **State Machines:** Counters prevent PWM value overwrite unless the state changes.
- **Non-blocking SPI Receive:** Uses polling and `_delay_ms(25)` for stability.
- **Failsafe Behavior:** Defaults all actuators OFF on unrecognized input.

---


