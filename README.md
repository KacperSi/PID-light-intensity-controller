# Light-intensity-controller-PID-
Implementation of light intensity control using STM32 microcontroller, PID controller and user application written in C++.

ENG

The system's task is to automatically adjust the light intensity.
The circuit is built on the NUCLEO-F746ZG development board based on the STM32 microcontroller.

A dedicated application written in C++ language is used to operate the regulator.

Used programming environment:
- STM32CubeIDE
- Qt
The CMSIS-DSP package was used to implement the PID controller according to: https://www.keil.com/pack/doc/CMSIS/DSP/html/group__PID.html

QserialPort library was used to support serial communication.

Detailed discussion: https://youtu.be/Pf2mL_dkMzg

PL

Zadaniem układu jest automatyczna regulacja natężenia światła.
Układ zbudowany jest na płytce rozwojowej NUCLEO-F746ZG opartej na mikrokontrolerze STM32.

Do obsługi regulatora służy dedykowana aplikacja napisana w języku C++.

Wykorzystane środowiska programistyczne:
- STM32CubeIDE
- Qt

Do implementacji regulatora PID wykorzystano pakiet CMSIS-DSP zgodnie z : https://www.keil.com/pack/doc/CMSIS/DSP/html/group__PID.html

Do obsługi komunikacji szeregowej wykorzystano bibliotekę QserialPort.

Szczegółowe omówienie: https://youtu.be/Pf2mL_dkMzg
