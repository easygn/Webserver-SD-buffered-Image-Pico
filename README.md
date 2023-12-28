# Webserver-SD-buffered-Image-pico


![Before](/images/Screenshot_2023-05-15-19-50-04_3-1.png)


### Original Based code : 

https://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/SD-card-web-server-image/



### Added buffer accelerate code in Webserver SD Image for Arduino IDE

Ex) Image webpage loading performance of about 32KB based old micro SD
 
 - Previous Original code - ± 11 sec  (per one Byte fileLoad, bottleneck)
 
 - This buffered code - ± 1.5 sec (per 2KiByte fileLoad in ImgBF.ino)



### Optimazed support device :
 
 Raspberry Pi Pico RP2040 + Wiznet HAT W5100S
 
