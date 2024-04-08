

### The installation steps are the same as the Micropython installation video blow :

https://www.raspberrypi.com/documentation/microcontrollers/images/MicroPython-640x360-v2.gif

#

### Last compiled Profile 

BF : CPU (forgot : 100 or 133)Mhz, Flash Sketch 1MB / FS 1MB, small -Os 

BB, BF_RC2, BFv2 : CPU 120Mhz, Flash Sketch 1MB / FS 1MB, small -Os 

BFv2MT_16 : ... + Stack Protector Enable

BFv2Fn : CPU 100Mhz ( SD,Eth SPI 12.5Mhz ), others same as above

#

### V2.0 ~ options

BFv2_8L : SPI FiFo 8byte block - fast, stable

BFv2_12L : " per 12byte block - 5~10% more faster, unstable

BFv2MT : V2.2 Support Multithread
