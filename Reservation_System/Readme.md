## 🏥 Hospital Booking System

---

### 🔸 Overview
The **Smart Login and Reservation System** is a secure hospital management module developed in **C**, designed to authenticate users (Doctors, Patients, IT Admins) and manage appointment reservations with enhanced security features.

---

### 🔸 System Features

| Feature                                | Description                                                                 |
|----------------------------------------|-----------------------------------------------------------------------------|
| 🔐 Secure Login                        | Unique IDs and passwords for all user roles                                |
| 🧑‍⚕️ Role-Based Access                 | Doctor, Patient, and Admin functionalities are separated                    |
| 📅 Reservation Management              | Schedule and cancel appointments securely                                  |
| 🛡️ Intrusion Detection                 | Detects unauthorized app access via fake interfaces                        |
| 🌐 IP Tracking                         | Stores usage IP address of every connected PC                              |
| 🧪 Fake Application Redirection        | Forwards suspicious access attempts to a decoy app for data collection     |

---

### 🔸 User Roles

#### 👨‍⚕️ Doctors
- View upcoming appointments
- Access patient records (if implemented)
- Modify availability schedule

#### 👨‍💻 IT Admin
- Monitor user activity
- View access logs and IP tracking
- Manage fake interface system

---

### 🔸 Security Mechanisms

| Mechanism                   | Description                                               |
|-----------------------------|-----------------------------------------------------------|
| 🔑 Unique ID Authentication | Each user type has a unique identifier-password pair      |
| 🧩 Encapsulation            | Sensitive logic is modularized for code security          |
| 🕵️‍♂️ Fake Interface Trap    | Misused apps redirect to decoy environment                |
| 🌍 IP Logger                | Logs each access point's IP to flag potential threats     |

---

### 🔸 Application Architecture

- **Language:** C (Console-based UI)
- **Design Pattern:** Modular with layered security functions
- **Input/Output:** Keyboard + Terminal screen
- **Data Handling:** File-based record system (can be upgraded to database)

---


### 🧠 Future Improvements

- 🔄 Integration with hospital database (e.g., SQLite or MySQL)
- 📱 GUI version using GTK or a web-based frontend
- 🧩 Multi-factor authentication (MFA) system
- 🌐 Online appointment access via ESP8266 + web server

---

> ## 💡 **Note:** This system is designed for educational and prototype-level use. Security should be upgraded for production deployment.

---


