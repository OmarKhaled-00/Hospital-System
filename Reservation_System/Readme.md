## 🏥 Hospital Management System (C Language Project)

---

### 🔸 Overview
The **Hospital Management System** is a secure, role-based console application developed in **C programming language**, designed to simulate real hospital operations including patient management, appointment scheduling, operation room allocation, and multi-level authentication.

The system also integrates **basic security mechanisms such as IP/hostname verification, intrusion detection simulation, and fake interface redirection** to demonstrate cybersecurity concepts in embedded-style software design.

---

### 🔸 System Features

| Feature                                | Description                                                                 |
|----------------------------------------|-----------------------------------------------------------------------------|
| 🔐 Secure Authentication System        | Auto-generated IDs and passwords for Users, Doctors, and IT Admins         |
| 🧑‍⚕️ Role-Based Access Control         | Separate functionalities for Patients, Doctors, and IT Administrators      |
| 📅 Patient Reservation System          | Add, edit, cancel, and view hospital appointments                          |
| 🏨 Operation Room Management           | Reserve and monitor operation rooms with full patient & doctor details     |
| 🌐 IP & Hostname Verification          | Validates system access based on machine identity                          |
| 🛡️ Intrusion Detection System          | Detects suspicious login attempts and triggers security response           |
| 🧪 Fake Security Page                   | Redirects unauthorized access to a decoy interface                         |
| 📊 Access Limitation Mechanism         | Blocks system after multiple failed login attempts                         |

---

### 🔸 User Roles

#### 👨‍⚕️ Doctor Module
- View assigned operations and schedules  
- Access patient operation details  
- Check personal operation timetable  

---

#### 👩‍💻 Patient / User Module
- View reservation information  
- Check appointment schedules  
- Access hospital services menu  

---

#### 🛡️ IT Administrator Module
- Generate and manage system credentials  
- Monitor login attempts and system security  
- Handle intrusion detection responses  
- Control system-wide access permissions  

---

### 🔸 Security Mechanisms

| Mechanism                     | Description                                                                 |
|------------------------------|-----------------------------------------------------------------------------|
| 🔑 Role-Based Authentication | Each user type has unique ID & password validation                         |
| 🌍 IP & Hostname Check       | Ensures system runs only on authorized machine                             |
| 🚨 Login Attempt Limiter     | Locks system after 3 failed login attempts                                 |
| 🧠 Fake System Redirection   | Sends attackers to decoy interface for simulation purposes                 |
| 🕵️ Malware Simulation       | Simulates security scanning and blocking behavior                          |

---

### 🔸 System Architecture

- **Language:** C (Structured Programming)
- **Platform:** Windows (MinGW / GCC Compiler)
- **Networking API:** Winsock2 (IP & Hostname detection)
- **Design Style:**
  - Modular functions
  - Struct-based data modeling
  - Role-based system flow
- **Data Handling:** In-memory storage using arrays (upgradeable to database)

---

### 🔸 Core Functional Modules

- Patient Information Management  
- Appointment Scheduling System  
- Operation Room Booking System  
- Login & Verification System  
- Security Monitoring System  
- Doctor Schedule Tracking  

---

### 🧠 Future Improvements

- 🗄️ Database integration (MySQL / SQLite)
- 🌐 Web-based dashboard for remote access
- 📱 GUI version using Qt or web frontend (React)
- 🔐 Password encryption (hashing + salting)
- 📡 Real-time hospital network communication (IoT/ESP8266)
- 👨‍⚕️ Advanced role permissions (RBAC system upgrade)

---


### 🚀 How to Use the System

The system follows a **secure hierarchical login flow**, meaning access is controlled in stages to ensure maximum security.

---

### 🔐 ⚠️ IMPORTANT LOGIN RULE

👉 The system **CANNOT be accessed by Doctors or Users unless the IT Administrator logs in first.**

This means:
- The **IT Admin must log in first**
- Only after IT authentication, the system allows access to:
  - 👨‍⚕️ Doctors
  - 🧑‍💻 Users (Patients)

---

### 🪜 Step-by-Step Usage Flow

#### 1️⃣ Start the Application
- Run the compiled `.exe` file
- The system will perform an **IP & hostname verification**

---

#### 2️⃣ IT Administrator Login (MANDATORY FIRST STEP)
- Enter:
  - IT Admin ID
  - Password
- If login is successful:
  - System permissions are activated
  - User and Doctor accounts become accessible
  - Access control system is initialized

⚠️ If IT Admin does NOT log in:
- System will remain restricted
- Other users cannot access the system

---

#### 3️⃣ User / Doctor Login
After IT Admin authentication:
- Doctors can log in to view operations and schedules
- Users can access:
  - Patient reservation system
  - Appointment details

---

### 🛡️ Security Behavior Summary

| Condition | System Behavior |
|----------|----------------|
| IT Admin not logged in | ❌ Access blocked for all users |
| Wrong login attempts | 🚨 Security counter activated |
| Multiple failures | 🔒 System locks and triggers security mode |
| Valid IT Admin login | ✅ System unlocks role-based access |

---

### 🧠 System Logic Concept

This design follows a **hierarchical security model**:


### 📌 Note
This project is developed for **educational and academic purposes**, demonstrating:
- Embedded-style C programming
- System-level thinking
- Basic cybersecurity simulation
- Real-world hospital workflow modeling

---

### 🔗 Code Repository
👉 [View Full Source Code](https://github.com/OmarKhaled-00/Hospital-System/tree/main/Reservation_System/Code)

---
