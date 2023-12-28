/*--------------------------------------------------------------
  Program:      eth_websrv_SD_image

  Description:  Arduino web server that serves up a basic web
                page that displays an image.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                2Gb micro SD card formatted FAT16
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +
                
                Requires index.htm, page2.htm and pic.jpg to be
                on the micro SD card in the Ethernet shield
                micro SD card socket.
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD

  Date:         7 March 2013
  Modified:     17 June 2013
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/


/*
  SD card basic file example

  This example shows how to create and destroy an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
   ** MISO - pin 0
   ** MOSI - pin 3
   ** CS   - pin 1
   ** SCK  - pin 2

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  added file buffer &
  combined 19 Dec 2023
  by Easygn

*/


#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>

#define Pin_CSn_SD   PIN_SPI1_SS 
#define Pin_CSn_ETH  PIN_SPI0_SS
#define Port_WEB     80  // (port 80 is default for HTTP):


// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   20
#define F_BUF_SZ    2048  // 16384 +0.5s  4096,8192 +0.1~.2s  overhead canceled   
#define WZ_BUF_SZ   2048  // for File, W5100s buffer by Easygn

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 52, 121);
IPAddress gateway(192, 168, 52, 254);
IPAddress myDns(192, 168, 52, 254);
IPAddress subnet(255, 255, 255, 0);
EthernetServer server(Port_WEB);  // create a server at port 80
File webFile;
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

void setup()
{
    // disable Ethernet chip
   // pinMode(10, OUTPUT);  deActivate 2023
   // digitalWrite(10, HIGH);
    
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(Pin_CSn_SD, 655360, SPI1)) {  // Added 2023
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
    

   // start the Ethernet connection and the server:
    Ethernet.init(Pin_CSn_ETH);

    Ethernet.begin(mac, ip, myDns, gateway, subnet);
    Serial.println(Ethernet.localIP());

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  
  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // print HTTP request character to serial monitor
                Serial.print(c);
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // open requested web page file
                    if (StrContains(HTTP_req, "GET / ")
                                 || StrContains(HTTP_req, "GET /index.htm")) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connnection: close");
                        client.println();
                        webFile = SD.open("index.htm");        // open web page file
                    }
                    else if (StrContains(HTTP_req, "GET /page2.htm")) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connnection: close");
                        client.println();
                        webFile = SD.open("page2.htm");        // open web page file
                    }
                    else if (StrContains(HTTP_req, "GET /pic.jpg")) {
                        webFile = SD.open("pic.jpg");
                        if (webFile) {
                            client.println("HTTP/1.1 200 OK");
                            client.println();
                        }
                    }
                    if (webFile) {                    
//                      while(webFile.available()) {
                        unsigned short int fSz
                          = (unsigned short int)webFile.available();
                        unsigned char fBuf[F_BUF_SZ];
                        // unsigned short int wSz, av_wSz;
                        while(fSz) {
                          if (fSz > F_BUF_SZ) fSz = F_BUF_SZ;
                          webFile.read(fBuf, fSz); /*
                          wSz = 0;
                          while (fSz > wSz) {
                            av_wSz = fSz-wSz;
                            client.write(&fBuf[0+wSz], av_wSz > WZ_BUF_SZ ? 
                                        WZ_BUF_SZ : av_wSz); // send buffered page to client by Easygn
                            wSz += WZ_BUF_SZ;
                          } */
                          client.write(fBuf, fSz);    // send buffered page to client by Easygn
                          fSz = (unsigned short int)webFile.available();
                          //client.write(webFile.read()); // send web page to client
                        }  
                        webFile.close();
                    }
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}
