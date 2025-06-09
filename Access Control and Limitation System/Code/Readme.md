# 🧾 Code Description: Access Control & Limitation System (main.c)
## ✅ System Overview:
### This embedded C program controls:

- A gate motor using IR sensors to detect people.

- An elevator motor using external interrupt buttons.
- Both systems are powered by the ATmega32 microcontroller and use PWM for motor control, with logic and control handled in real-time based on sensor inputs.

### 🧩 Modules and Functions:
- Initialization (main):
- PORT_voidInit(), Timer0_voidInit(), Timer1_voidInit(), EXTI_VoidInit()
- Initialize all required ports, timers, and external interrupt modules.

### Startup LED blink sequence:

- Toggles PORTC PIN5 (likely an indicator LED) to show the system is initializing.

### 🚪 Gate Control Logic (main while loop):
#### IR Sensors Input:
- PIN0 and PIN7 on Port A detect if a person is present.

- If both are HIGH → No person → Close gate.

- If either is LOW → Person detected → Open gate.

### Motor Direction Pins:
#### PORTC PIN0 and PIN1 control the gate motor via L298N:

- One HIGH, one LOW = move in one direction.

- Both LOW = stop.

#### Door States:
- Local_u8Reading: IR sensor status (1 = person detected, 0 = no person).

- Local_u8DoorState: gate status (1 = closed, 0 = open).

#### Depending on the current and desired door states:

- Motor spins to open or close the gate for 1.5 seconds using PWM at 50% (CompareMatchValue = 128).

- If already in the correct position, motor stays off.

### 🛗 Elevator Control Using Interrupts:
#### INT0_Func (Triggered by INT0):
- Controls elevator upward movement.

#### If Local_u8LiftState == 0 (elevator down):

- Sets Local_u8LiftState = 0, stops motor.

##### Else:

##### Moves elevator up by:

- Activating motor via PORTC PIN3 and PIN4.

- Sets PWM value with TIMER1_voidSetComValB(65535).

- Delays to simulate lift movement (6s + 3.7s).

- Stops motor afterward.

#### INT1_Func (Triggered by INT1):
- Controls elevator downward movement (similar to INT0 but opposite direction).

- Uses same motor pins with reversed polarity.

### 🧠 Hardware Connections Summary:
- Peripheral	Pin/Port	Description
- IR Sensors	PINA0, PINA7	Detect person for gate
- Gate Motor	PORTC0, PORTC1	Controlled via L298N (door)
- Elevator Motor	PORTC3, PORTC4	Controlled via L298N (lift)
- Indicator LED	PORTC5	Startup/status indicator
- UP Button	INT0 (PD2)	External interrupt 0
- DOWN Button	INT1 (PD3)	External interrupt 1

### 🧪 Key Concepts Used:
- External Interrupts (INT0, INT1)

- PWM Motor Control (Timer0 & Timer1)

- Digital I/O with sensors and buttons

- System state management (door and lift states)

- Delay functions for real-time simulation

