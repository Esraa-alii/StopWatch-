# StopWatch Project






<!-- <p align="center"><img src=" src/assets/DroopyHome.jpg" alt="Droopy" width="500" align="center"/></p> -->

A stopwatch is a timepiece designed to measure the amount of time that elapses between its activation and deactivation.
<br>
<img  src="https://drive.google.com/file/d/1ySD8_vzP40Tc5dyWH-rZOksP7r-S1qKU/view?usp=sharing"  alt="stopwatcOFF"  height="300" width="800" align="center"/>

<img  src="https://drive.google.com/file/d/1INTsuJM0Ik6OkqCZQAfIwWZI32hmxgtr/view?usp=sharing"  alt="stopwatcOFF"  height="300" width="800" align="center"/>

## Table of contents

* [Structure](#structure)
* [Features](#features)
* [Development](#development)
* [UpComing](#upcoming)


## Structure

   <br>
            <li>ATmega32 Microcontroller with frequency 1Mhz</li> 
            <li>Timer1 in ATmega32 with CTC mode to count the Stop Watch time.</li>
            <li>six Common Anode 7-segments.</li>
            <li>one 7447 decoder for all 7-segments and control the enable/disable for each 7-segement using a NPN BJT transistor connect to one of the MCU pins</li>
            <li>3 push Buttons</li> 
            <br><br>

## Features
* **Reset your stop watch**

 Configure External Interrupt INT0 with falling edge. Connect a push button with the
internal pull-up resistor. If a falling edge detected the Stop Watch time should be
reset. 


* **Pause your stop watch**

Configure External Interrupt INT1 with raising edge. Connect a push button with the
external pull-down resistor. If a raising edge detected the Stop Watch time should be
paused.

* **Resume your stop watch**

Configure External Interrupt INT2 with falling edge. Connect a push button with the
internal pull-up resistor. If a falling edge detected the Stop Watch time should be
resumed.

## Development

Clone the repository and install all the necessary dependencies (eclipse is highly recommended)

```sh
 git clone https://github.com/Esraa-alii/StopWatch-
 
```


## UpComing 
* **🛠 Upcoming Features**
count down for your input time using keypad.




