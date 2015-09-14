/*
 Project: Androiduino
 Who done it: Samwise
 samuel barnum at gmail dot com
 DATE: April 19, 2015
*/
#include <SoftwareSerial.h> //use pins other than 0,1
SoftwareSerial HM10Serial(2, 3); // RX, TX
//#include <MeetAndroid.h>
//
//MeetAndroid meetAndroid;

String readSerialString()
{
  String content = "";
  char character;

  while (Serial.available()) {
    character = Serial.read();
    content.concat(character);
    delayMicroseconds(998); //needed to avoid the printing of single characters. SerialRead is quite slow. //delay(1) also works
  }

  return content;
}
String readSoftSerialString(SoftwareSerial &mySerial)
{

  String content = "";
  char character;
  mySerial.peek(); //For some reason nothing was working, I added this in, and everything worked. Commented it out, and still works. No idea why..??
  while (mySerial.available()) {
    character = mySerial.read();
    content.concat(character);
    delayMicroseconds(998); //needed to avoid the printing of single characters. SerialRead is quite slow. //delay(1) also works
  }

  return content;
}

//String inStream = "";
//String outStream = "";

int A = (int)"A";
void setup() {
  Serial.begin(9600); //communication via USB
  HM10Serial.begin(9600); //communication via Bluetooth
  HM10Serial.flush();
}

void loop()
{
  //write the Bluetooth stream to the Serial Monitor
  if (HM10Serial.available())

  {
    int b = HM10Serial.peek();
    String inStream = readSoftSerialString(HM10Serial);
    inStream.trim();
    Serial.println(inStream);

    if (b != 79) //If it is an "OK" Reply, print it out

    {
 
      HM10Serial.print("AT"); //turn off connection to device to allow AT commands
      delay(100); //allow time to shut off
      HM10Serial.print(inStream);
      
    }
 //HM10Serial.flush(); //not sure if this is needed
  }
  //write the Serial Monitor stream to Bluetooth
  if (Serial.available() && Serial.peek() != 79)
  {
    String outStream = readSerialString();
    outStream.trim(); //remove whitespaces that interfere with AT commands
    HM10Serial.print(outStream); //println will not work because of whitespace
  }

}
