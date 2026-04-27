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

### 🔐 System Credentials (For Testing)

#### 🛡️ IT Administrator
- **ID:** `ITAD001`  
- **Password:** `admin123`

👉 When the IT Administrator successfully logs in:
- The system unlocks full access control
- A generated list of **User and Doctor credentials** is displayed
- The administrator can use these credentials to test system roles

---

#### 👨‍⚕️ Sample Doctor Account
- **ID:** `DOC021`  
- **Password:** `$@zc-u`

---

#### 🧑‍💻 Sample User Account
- **ID:** `USR001`  
- **Password:** `m!Tr)F`

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
- Must login first before any system access is allowed  
- Generates and displays all user and doctor credentials  
- Monitors login attempts and system security  
- Handles intrusion detection and system protection  

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

### 🚀 How to Use the System

The system follows a **secure hierarchical login flow**.

---

### 🔐 ⚠️ IMPORTANT LOGIN RULE

👉 The system **CANNOT be accessed by Doctors or Users unless the IT Administrator logs in first.**

- IT Admin must log in first (`ITAD001 / admin123`)
- After successful login:
  - System displays all generated credentials
  - Doctors and Users can then log in using provided accounts

---

### 🪜 Step-by-Step Flow

#### 1️⃣ Start the Application
- Run the compiled `.exe` file
- System performs IP & hostname verification

---

#### 2️⃣ IT Administrator Login (MANDATORY FIRST STEP)
- Enter:
  - ID: `ITAD001`
  - Password: `admin123`

✔ If successful:
- System unlocks full functionality
- Displays all User & Doctor credentials

---

#### 3️⃣ User / Doctor Login
After IT Admin authentication:
- Doctors access operation schedules
- Users access:
  - Reservations
  - Appointment information

---


### 🌐 System Startup Security Requirement

Before compiling and running the system, you MUST configure:

```c
const char *desired_ip = "YOUR_IP_HERE";
const char *desired_hostname = "YOUR_HOSTNAME_HERE";
