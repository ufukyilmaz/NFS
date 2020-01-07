# CmpE443 Car Project
## NFS
<p align="center">
    <img src="https://github.com/ufukyilmaz/NFS/blob/master/Assets/NFS.jpeg" width="50%" height="auto" align="center">
</p>

### We were 2nd place in the race.

#### Team Members

- [Gürkan Demir(Team Leader)](https://www.github.com/gurkandemir)
- [Ufuk Yılmaz](https://www.github.com/ufukyilmaz)
- [Burak İkan Yıldız](https://www.github.com/burakikanyildiz)
- [Enes Turan Özcan](https://www.github.com/enozcan)

## Links
- [Final Project Description](https://github.com/ufukyilmaz/NFS/blob/master/Description/Term_Project.pdf) (given)
- [Final Project Report](https://github.com/ufukyilmaz/NFS/blob/master/Report/NFS.pdf)

## Description
We are expected to build a toy car that will follow along a wall. For the car, we use 1 Motor Controller, 
2 LDRs, 4 LEDs, 1 potentiometer, 1 speedometer and 1 Ultrasonic sensor. The car will have two separate operating modes. 
One of them is Test mode which will be used to test the car using serial communication. The other one is Autonomous mode which car follow along a wall itself.

### Flowcharts
* Initializations
<p align="center">
    <img src="https://github.com/ufukyilmaz/NFS/blob/master/Assets/flowchartInit.png" width="50%" height="auto" align="center">
</p>

* Test Mode
<p align="center">
    <img src="https://github.com/ufukyilmaz/NFS/blob/master/Assets/flowchartTest.png" width="50%" height="auto" align="center">
</p>

* Auto Mode
<p align="center">
    <img src="https://github.com/ufukyilmaz/NFS/blob/master/Assets/flowchartAuto.png" width="50%" height="auto" align="center">
</p>

### Circuit Schema
<p align="center">
    <img src="https://github.com/ufukyilmaz/NFS/blob/master/Assets/Circuit-Schematic.png" width="50%" height="auto" align="center">
</p>

### Pins
| LPC4088 pin | Connection | Function | Purpose |
|:-----------:|:----------:|:--------:|:-------:|
|P1.24|P5|GPIO|BR LED|
|P1.23|P6|GPIO|BL LED|
|P1.20|P7|PWM1[2]|LED Blinking|
|P0.21|P8|GPIO|FR LED|
|P0.0|P9|UART3 TX|Bluetooth RX|
|P0.1|P10|UART3 RX|Bluetooth TX|
|P0.9|P11|T2_MAT_3|Ultrasonic Trigger|
|P0.23|P15|T3_CAP_0|Ultrasonic Echo|
|P0.24|P16|ADC0[1]|Potentiometer|
|P0.25|P17|ADC0[2]|LDR Right|
|P0.26|P18|ADC0[3]|LDR Left|
|P1.30|P19|GPIO|IN1 - Left Motor|
|P1.31|P20|GPIO|IN2 - Right Motor|
|P2.10|P23|EINT0|Speedometer|
|P1.6|P27|GPIO|FL LED|
|P1.6|P29|PWM0[2]|ENB - Right Motor|
|P1.6|P30|PWM0[1]|ENA - Left Motor|
|P0.5|P33|GPIO|IN4 - Right Motors|
|P0.4|P34|GPIO|IN3 - Right Motors|
