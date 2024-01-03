![Before](/images/Screenshot_2023-12-21-06-11-07~2(1).png)


# Webserver-SD-buffered-Image-pico



### Original Based code 

https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/SD-card-web-server-image/

# 

### Added buffer accelerate code in Webserver SD Image for Arduino IDE

Ex) Image webpage loading performance of about 39KB size in old microSD card
 
 - Previous Original code - ± 11 sec  (per One Byte fileLoad, IO bottleneck)
 
 - This buffered code - ± 1.5 sec (per 2KiByte fileLoad in ImgBF.ino)

# 

### Optimazed support device
 
 Raspberry Pi Pico RP2040 + Wiznet HAT W5100S

# 

### Based board manager

 - Setup URLs : https://github.com/WIZnet-ArduinoEthernet/arduino-pico/releases/download/global/package_rp2040-ethernet_index.json

 - Library : https://github.com/WIZnet-ArduinoEthernet/arduino-pico

# 

### About files

 - ImgBF.ino : When Running, sync to same size as W5100s with 2KiB memory per socket. (Released)

 - ImgBB.ino : Each device running with it's own a different memory size (Nightly :

_____Now, same speed as Release over 100KB~)

 - pins_arduino.h : When the SD card is connected to another SPI,

    replace it in /variants/rpipico in the BoardManager lib folder.

