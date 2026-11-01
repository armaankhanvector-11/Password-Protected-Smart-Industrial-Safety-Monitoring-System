# Password Protected Smart Industrial Safety Monitoring and Alert System Using ARM7 LPC2129

📌 Project Overview

This project is an embedded-based industrial safety monitoring system developed using the ARM7 LPC2129 microcontroller. It provides password-based authentication and monitors industrial safety conditions using temperature, PIR and flame sensors.

The monitoring system starts only after successful password authentication. If the password is entered incorrectly three times, the system asks for a backup password. After successful backup authentication, the user can set a new password.

🚀 Features
Password-based system authentication through UART.
Three password attempts.
Backup password authentication.
Option to change the password.
Temperature monitoring using LM35.
Worker detection using PIR sensor.
Fire detection using flame sensor.
Real-time status indication through LCD.
UART-based serial communication.
SAFE / NOT SAFE status indication.
🛠️ Hardware Components
ARM7 LPC2129 Microcontroller
LM35 Temperature Sensor
PIR Motion Sensor
Flame Sensor
16x2 LCD Display
UART Serial Communication
Power Supply
💻 Software Requirements
Keil µVision IDE
Flash Magic
Embedded C
ARM7 LPC2129 Header Files
⚙️ Working Principle
Initially, the LCD displays an ENTER PASSWORD message.
The user enters a five-character password through UART.
If the password is correct, the monitoring system starts.
If the password is incorrect three times, the system requests a backup password.
If the backup password is correct, the user can enter a new password.
If the backup password is incorrect, the system displays UNAUTHORIZED and stops.
After successful authentication, the LM35 monitors temperature, the PIR sensor detects worker presence, and the flame sensor detects fire.
The ADC converts the analog temperature sensor output into a digital value.
If the temperature exceeds 35°C, a worker is detected, or fire is detected, the system displays NOT SAFE.
If none of these conditions occur, the system displays SAFE.
🔐 Password Details
Default Password: hello
Backup Password: mango
Password Length: 5 Characters

The new password is stored in RAM and is not retained after a power reset.

📟 Output

The LCD displays:

ENTER PASSWORD
PASSWORD CORRECT
PASSWORD WRONG
BACKUP PASSWORD
SYSTEM STARTED
TEMP
STATUS: SAFE
STATUS: NOT SAFE
UNAUTHORIZED

UART displays temperature, worker detection, fire detection and overall safety status.

🎯 Applications
Industrial safety monitoring
Factory environment monitoring
Worker presence monitoring
Fire detection systems
Industrial access control
📚 Conclusion

This project combines password-based authentication with industrial safety monitoring using the ARM7 LPC2129 microcontroller. It provides a simple approach to monitoring temperature, worker presence and fire conditions, helping identify potentially unsafe industrial environments.
