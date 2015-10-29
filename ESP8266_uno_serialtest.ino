// original sketch: http://shin-ajaran.blogspot.ro/2014/12/noobs-guide-to-esp8266-with-arduino.html
// rewrite after phote by niq_ro from http://nicuflorica.blogspot.com/
// and http://arduinotehniq.blogspot.com/

#include <SoftwareSerial.h> 
const int  RX=10;     
const int  TX=11;  
const long COM_BAUD = 57600;    
SoftwareSerial esp8266(RX, TX); // RX, TX 

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  esp8266.begin(9600);
}

void loop() {
 while(esp8266.available()) Serial.write(esp8266.read());
 
while(Serial.available()) esp8266.write(Serial.read());
}
