
# 🏥 Hospital Management System – Embedded & Software Integration
- This project is a comprehensive Hospital Management System built using Embedded Systems and C-based Software Development. It is designed to enhance patient safety, streamline operations, and enable real-time monitoring and communication across hospital facilities.
---
## 🔧 Embedded Systems Modules:
### Autonomous Power and Voltage Control System:
- Designed to monitor voltage levels and manage power source switching between renewable and backup sources, ensuring energy efficiency and hospital equipment safety.
  
### Access Control and Limitation System
- Controls gate and elevator access using IR sensors, ATmega32, DC motors, and PWM — ensures only authorized personnel can enter specific hospital areas.

### Safety Monitoring and Alarm System
- Monitors critical environmental parameters using flame sensors, MQ2, LDR, and LM35. Triggers actuators (fan, water pump, alarms) for immediate response to fire, gas, or high temperature. Communication between MCUs is handled using UART and SPI protocols.

### Real-time Communication & Alert System
- Uses ESP8266 for Wi-Fi-based alerts and remote updates. Critical events are reported to a central system or dashboard for faster emergency response.
---
## 💻 Software Application – Reservation System
A terminal-based application built in C that handles:

- Patient reservations and data records

- Doctor/IT Admin login with unique ID & password

- IP address tracking for connected PCs

- Redirection of unauthorized access to a fake application for security tracking
---
