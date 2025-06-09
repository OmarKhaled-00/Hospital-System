## 🛡️ Access Control & Limitation System
- The Access Control & Limitation System is an embedded solution designed to manage and automate secure entry and movement within sensitive areas of a hospital or facility. It ensures that only authorized personnel can access restricted zones, while also controlling physical mechanisms like gates and elevators.

### ⚙️ Key Features:
#### ATmega32 Microcontroller:
- Acts as the central controller, handling all logic, input/output processing, and motor control.

### Dual Motor Control:
#### Utilizes two DC motors:

- One for gate automation

- One for elevator movement
 - Controlled via the L298N motor driver, with PWM signals at 50% duty cycle for smooth operation.

- IR Sensors for Entry/Exit Detection:
- Two infrared sensors detect the presence and direction of movement, ensuring accurate control of door and elevator activity.

### Manual Elevator Buttons:
- Includes UP and DOWN control buttons, allowing authorized users to move between floors.

### Reset Mechanism:
- A dedicated reset button is provided to safely restart the microcontroller if needed.

### 🔐 Security Logic:
- The system restricts access based on sensor input and user interaction:

- The gate operates only when the IR sensor detects entry authorization.

- The elevator can only be activated by authorized personnel using the control buttons.

- Each motor receives PWM signals for controlled speed and direction, ensuring safe operation within a hospital environment.

### 🧠 Purpose:
- This module is intended for hospital access automation, helping secure restricted zones like ICUs, operating rooms, or staff-only areas. It enhances physical security, ensures controlled movement, and adds a layer of automation and reliability to facility management.

### Circuit video on proteus [Here](https://www.linkedin.com/posts/omar-khaled-4a85aa271_engineering-mechatronics-embeddedsystems-activity-7201962067405205508-o1Rw/?utm_source=share&utm_medium=member_desktop&rcm=ACoAAEJ5PEABloBk-I_pPlzgtOS0jw7eBO_Uh7Y)
### Circuit video in Real-World [Here](https://www.linkedin.com/posts/omar-khaled-4a85aa271_engineering-mechatronics-embeddedsystems-activity-7201962434155147265-VC7S/?utm_source=share&utm_medium=member_desktop&rcm=ACoAAEJ5PEABloBk-I_pPlzgtOS0jw7eBO_Uh7Y)


