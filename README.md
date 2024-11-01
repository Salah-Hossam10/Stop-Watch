Digital Clock with Button-Controlled Timer Adjustments
This project is a Digital Clock built using embedded C, featuring button-controlled adjustments for hours, minutes, and resetting the time. It utilizes an ATmega microcontroller, 7-segment displays, and digital inputs to control time settings and display. The clock maintains time in hours, minutes, and seconds and allows users to adjust time with dedicated buttons.

Features
Time Display: Shows time in hours, minutes, and seconds on 7-segment displays.
Time Adjustments: Buttons allow users to increment or decrement hours and minutes independently.
Pause/Resume Functionality: Toggle button to pause/resume the timer.
Reset Function: Reset button to set hours, minutes, and seconds back to zero.
System Overview
Components Used
Microcontroller: ATmega series
7-Segment Display: Six digits for hours, minutes, and seconds
Buttons:
Increment/Decrement Hours
Increment/Decrement Minutes
Pause/Resume
Reset
Additional Libraries:
DIO for Digital Input/Output
Timer for clock functionality
Interrupts for handling timing and button inputs
Functionality
Time Counting: The clock uses Timer0 for precise counting of seconds, incrementing minutes and hours accordingly.
Button Control:
Increment/Decrement buttons update hours and minutes by checking the button's state and then delaying to avoid repeated actions.
Pause/Resume button toggles the timer, pausing or continuing the clock without resetting.
Reset button sets the time back to zero.
Code Structure
Header Files
STD_TYPES_GCC.h and BIT_MATH_GCC.h: Contain type definitions and bit manipulation macros.
DIO_interface.h: Handles digital I/O functions for reading/writing pins.
TIMER0_interface.h: Sets up Timer0 for clock functionality.
LCD_interface.h and KEYPAD_interface.h: Interfaces for LCD and keypad, included for optional input/output expansions.
GI_interface.h and EXTI_interface.h: Manage global and external interrupts.
Key Code Sections
Time Control Logic:

Func(): Incrementing seconds, minutes, and hours with overflow handling.
Button-activated adjustments use MDIO_voidGetPinValue() to read button states and control time.
Display Logic:

SEG[]: Segment values to display each digit.
Port Manipulation: Manages display multiplexing to show each digit separately with microsecond delays.
Button State Management:

Detects button states for increment/decrement and toggles functions based on digital input.
Constants and Macros
F_CPU: Clock speed (8 MHz)
KEY_PRESSED: Macro for detecting a pressed button.
Digit Macros (ZERO, ONE, etc.): Represent each digit for the 7-segment display.
How to Use
Compile and Flash: Compile the code using an AVR compiler and flash to the ATmega microcontroller.
Connect Components: Attach buttons and 7-segment displays as per the pin configurations in the code.
Button Operations:
Adjust the clock with increment/decrement buttons.
Use the pause/resume button to control time counting.
Reset the clock with the reset button.
Future Improvements
Add an LCD for a clearer display and additional functionalities.
User Interface Expansion: Implement a keypad interface for more advanced time-setting options.
Alarm/Timer Functions: Add alarms and countdown timers.
