// http://www.roroid.ro/termometru-cu-ceas-bazat-pe-arduino-si-esp8266/
// adapted by niq_ro from http://nicuflorica.blogspot.ro/
// and http://arduinotehniq.blogspot.com/

#include <TextFinder.h>
#include <Time.h>  
#include "Timer.h"  

TextFinder  finder(Serial2);  
long pctime;                            //variable that stores time readed by ES8266
Timer t;                               //instantiate the timer object

double tmp;
String tmpl,tmpld;

void setup()
{
  Serial2.begin(9600);//connection to ESP8266
 Serial2.setTimeout(2000);
  Serial.begin(9600); //serial debug


  //Set mode for ES8266 wifi board
 Serial2.println("AT+RST");
 Serial.println("AT+RST");
 Serial2.println("AT+CWMODE=1");
  delay(500);//delay after mode change
  Serial2.println("AT+RST");
  //connect to wifi network
  
  delay(2000);
  boolean b=false;
  while (b!=true){
    Serial2.println("AT+CWJAP=\"SSID\",\"password\"");
    Serial.println("AT+CWJAP=\"SSID\",\"password\"");
    if(Serial2.find("OK")){
      Serial.println("OK WIFI");     
      b=true;
    }  
    else
    { 
      Serial.println("NOK WIFI");
      b=false;
    }
  }


  setSyncProvider(requestSync);//defines the function responsabel for the time sincronization
//delay(500);
  setSyncInterval(20);//sync interval

  ClockSYNC();//initial sincroization of the clock

  t.every(500, digitalClockDisplay);//evry 500ms display the clock

//digitalClockDisplay();

}

void loop(){

  t.update();
//delay(300);


}

time_t requestSync()
{
  ClockSYNC();  
  delay(100);
  return 0; // the time will be sent later in response to serial mesg
}

void ClockSYNC(){

  //create start command
  String startcommand = "AT+CIPSTART=\"TCP\",\"www.roroid.ro\", 80"; //443 is HTTPS, still to do

  Serial2.println(startcommand);

  //test for a start error
  if(Serial2.find("Error")){
    Serial.println("Error on start");
    return;
  }

  //create the request command
  String sendcommand = "GET http://www.roroid.ro/php/ceas.php HTTP/1.0\r\n\r\n\r\n";//works for most cases
Serial.println("http://www.roroid.ro/php/ceas.php");
  //send 
  Serial2.print("AT+CIPSEND=");
  Serial2.println(sendcommand.length());
 Serial.println(sendcommand.length());
  if(Serial2.find(">"))
  {
 //   delay(1000);
 Serial.println("...");
  }
  else
  {
    Serial2.println("AT+CIPCLOSE");
    Serial.println("Timeout");
    return;
  }



  Serial2.print(sendcommand); 
Serial.print(sendcommand); 

  if(Serial2.find("SEND OK")){
    finder.find("TIME=");
    pctime=finder.getValue();
    pctime=pctime+7200;
    setTime(pctime);
    Serial.println(pctime);
    return;  
  }

}


void digitalClockDisplay(){
  // digital clock display of the time
  String timp,data;
//timp="*";
  if (hour()<10)
    timp=timp+"0";
  timp=timp+String(hour());
  timp=timp+":";
  if (minute()<10)
    timp=timp+"0";
  timp=timp + String(minute());
  timp=timp+":";
  if (second()<10)
    timp=timp+"0";

  timp=timp + String(second());

  char charBuf[12];
  if(tmpl!=timp){  
    tmpl.toCharArray(charBuf, 12) ;
    Serial.println(charBuf);
    timp.toCharArray(charBuf, 12) ;
    Serial.println(charBuf);
    tmpl=timp;
 }

  data=String(day())+"/"+String(month())+"/"+String(year());
  if (tmpld!=data){
    tmpld.toCharArray(charBuf, 12) ;
    Serial.println(charBuf);
    data.toCharArray(charBuf, 12) ;
 Serial.println(charBuf);
    tmpld=data;
  }
}

