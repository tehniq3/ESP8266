// original sketch: http://shin-ajaran.blogspot.ro/2014/12/noobs-guide-to-esp8266-with-arduino.html
// rewrite after phote by niq_ro from http://nicuflorica.blogspot.com/
// and http://arduinotehniq.blogspot.com/

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial2.begin(9600);
}

void loop() {
 while(Serial2.available()) Serial.write(Serial2.read());
 
while(Serial.available()) Serial2.write(Serial.read());
}
