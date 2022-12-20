#include <SoftwareSerial.h>

/*
1 - pin where you should connected sensor for room / area no 1 
3 - pin where you should connected sensor for room / area no 2 
4 - pin where you should connected sensor for room / area no 4
6 - pin where you should connected sensor for room / area no 6
8 - pin where you should connected sensor for room / area no 7
9 - pin where you should connected sensor for room / area no 9
10 - pin where you should connected sensor for room / area no 11
13 - pin where you should connected sensor for room / area no 12
*/

SoftwareSerial mySerial(12, 11); //SIM800L Tx & Rx is connected to Arduino #7->TX & #8->RX
String incoming_string="";
String alramTestAnswer = "content of the response - when you send questions about status";
String motionDetected = "content of the response -  when system detect motion";
char incoming_char=0;

String trunOnAlarm = "command - with activate system"; 
String trunOffAlarm = "command - with will turn off system";
String alarmTest = "command - with will send system status ";
String alrmaStatusOnAnswer = "content of the response - where system will be turn on";
String alrmaStatusOffAnswer = "content of the response - where system will be turn off";

// choose the input pin (for PIR sensor)
int inputPinForPIRSensorFirst = 2; 
int inputPinForPIRSensorNextOneSecond = 5;
int inputPinForPIRSensorNextOneThird = 3;
int inputPinForPIRSensorNextOneThirdFourth = 4;
int inputPinForPIRSensorNextOneThirdFifth = 6;
int inputPinForPIRSensorNextOneThirdSixth = 8;
int inputPinForPIRSensorNextOneThirdSeventh = 9;
int inputPinForPIRSensorNextOneThirdEighth =10;
int inputPinForPIRSensorNextOneThirdTenth = 13;             

// we start, assuming no motion detected
int state = LOW;             

// variable for reading the pin status
int valInputPinForPIRSensorFirst = LOW; 
int valInputPinForPIRSensorNextOneSecond = LOW;
int valInputPinForPIRSensorNextOneThird = LOW;
int valInputPinForPIRSensorNextOneThirdFourth = LOW;
int valInputPinForPIRSensorNextOneThirdFifth = LOW;
int valInputPinForPIRSensorNextOneThirdSixth = LOW;
int valInputPinForPIRSensorNextOneThirdSeventh = LOW;
int valInputPinForPIRSensorNextOneThirdEighth =LOW;
int valInputPinForPIRSensorNextOneThirdTenth = LOW;        

//alarm setting 
int alarmSetting = 0;

//
String messageMotionPIRSensorFirst = "message";
String messageMotionPIRSensorSecond = "message";
String messageMotionPIRSensorThird = "message";
String messageMotionPIRSensorFourth = "message";
String messageMotionPIRSensorFifth = "message";
String messageMotionPIRSensorSixth = "message";
String messageMotionPIRSensorSeventh = "message";
String messageMotionPIRSensorEighth = "message";
String messageMotionPIRSensorTenth = "message";

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  Serial.println("Initializing...");
  delay(100);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(100);
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  delay(100);
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  delay(100);
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  delay(100);
  mySerial.print("AT+CMGF=1\r");
  updateSerial();
  delay(100);
  mySerial.print("AT+CNMI=2,2,0,0,0\r");
  updateSerial();

  // declare sensor as input
  pinMode(inputPinForPIRSensorFirst, INPUT); 
  pinMode(inputPinForPIRSensorNextOneSecond, INPUT);
  pinMode(inputPinForPIRSensorNextOneThird, INPUT);
  pinMode(inputPinForPIRSensorNextOneThirdFourth, INPUT);
  pinMode(inputPinForPIRSensorNextOneThirdFifth, INPUT);
  pinMode(inputPinForPIRSensorNextOneThirdSixth, INPUT);
  pinMode(inputPinForPIRSensorNextOneThirdSeventh, INPUT);
  pinMode(inputPinForPIRSensorNextOneThirdEighth, INPUT);
  
  delay(200);  

  sendSMS("Setup is on");

    valInputPinForPIRSensorFirst = LOW;
    valInputPinForPIRSensorNextOneSecond = LOW;
    valInputPinForPIRSensorNextOneThird = LOW;
    valInputPinForPIRSensorNextOneThirdFourth = LOW;
    valInputPinForPIRSensorNextOneThirdFifth = LOW;
    valInputPinForPIRSensorNextOneThirdSixth = LOW;
    valInputPinForPIRSensorNextOneThirdSeventh = LOW;
    valInputPinForPIRSensorNextOneThirdEighth = LOW;
    valInputPinForPIRSensorNextOneThirdTenth = LOW;
}

void loop()
{
    if(mySerial.available()>0) {
    //Get the character from the cellular serial port
    incoming_string=mySerial.readString(); 
    //Print the incoming character to the terminal
    Serial.print(incoming_char);
    delay(100);
    }
    
    if(incoming_string.indexOf(trunOnAlarm)>=0)
    {
    // Turn off relay and save current state
    Serial.println(alrmaStatusOnAnswer);
    sendSMS(alrmaStatusOnAnswer);
    incoming_char= ""; 
    alarmSetting=1;
    }

    if(incoming_string.indexOf(trunOffAlarm)>=0)
    {
    // Turn off relay and save current state
    Serial.println(alrmaStatusOffAnswer);
    sendSMS(alrmaStatusOffAnswer);
    incoming_char= "";
    alarmSetting=0; 
    }

    if(incoming_string.indexOf(alarmTest)>=0)
    {
    // Turn off relay and save current state
    Serial.println(alramTestAnswer);
    sendSMS(alramTestAnswer);
    incoming_char= ""; 
    }
    
      // read input value
      valInputPinForPIRSensorFirst = digitalRead(inputPinForPIRSensorFirst);
      valInputPinForPIRSensorNextOneSecond = digitalRead(inputPinForPIRSensorNextOneSecond);
      valInputPinForPIRSensorNextOneThird = digitalRead(inputPinForPIRSensorNextOneThird);
      valInputPinForPIRSensorNextOneThirdFourth = digitalRead(inputPinForPIRSensorNextOneThirdFourth);
      valInputPinForPIRSensorNextOneThirdFifth = digitalRead(inputPinForPIRSensorNextOneThirdFifth);
      valInputPinForPIRSensorNextOneThirdSixth = digitalRead(inputPinForPIRSensorNextOneThirdSixth);
      valInputPinForPIRSensorNextOneThirdSeventh = digitalRead(inputPinForPIRSensorNextOneThirdSeventh);
      valInputPinForPIRSensorNextOneThirdEighth = digitalRead(inputPinForPIRSensorNextOneThirdEighth);
      valInputPinForPIRSensorNextOneThirdTenth = digitalRead(inputPinForPIRSensorNextOneThirdTenth);
      
    if(alarmSetting==1)
    {
      if(valInputPinForPIRSensorFirst == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorFirst);
        sendSMS(messageMotionPIRSensorFirst);
        delay(200);
        
        if (valInputPinForPIRSensorFirst == LOW) { 
          valInputPinForPIRSensorFirst = HIGH;       
          }        
        }
        
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorFirst == HIGH){ 
          valInputPinForPIRSensorFirst = LOW;   
        }
       }
        
        if (valInputPinForPIRSensorNextOneSecond == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorSecond);
        sendSMS(messageMotionPIRSensorSecond);
        delay(200);
        
        if (valInputPinForPIRSensorNextOneSecond == LOW) { 
          valInputPinForPIRSensorNextOneSecond = HIGH;       
          }
        }
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorNextOneSecond == HIGH){ 
          valInputPinForPIRSensorNextOneSecond = LOW;   
        }
       }

        if (valInputPinForPIRSensorNextOneThird == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorThird);
        sendSMS(messageMotionPIRSensorThird);
        delay(200);
        
        if (valInputPinForPIRSensorNextOneThird == LOW) { 
          valInputPinForPIRSensorNextOneThird = HIGH;       
          }
        }
        
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorNextOneThird == HIGH){ 
          valInputPinForPIRSensorNextOneThird = LOW;   
        }
       }

        if (valInputPinForPIRSensorNextOneThirdFourth == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorFourth);
        sendSMS(messageMotionPIRSensorFourth);
        delay(200);
        
        if (valInputPinForPIRSensorNextOneThirdFourth == LOW) { 
          valInputPinForPIRSensorNextOneThirdFourth = HIGH;       
          }
        
        }
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorNextOneThirdFourth == HIGH){ 
          valInputPinForPIRSensorNextOneThirdFourth = LOW;   
        }
       }

        if (valInputPinForPIRSensorNextOneThirdFifth == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorFourth);
        sendSMS(messageMotionPIRSensorFourth);
        delay(200);
        
        if (valInputPinForPIRSensorNextOneThirdFifth == LOW) { 
          valInputPinForPIRSensorNextOneThirdFifth = HIGH;       
          }
        }
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorNextOneThirdFifth == HIGH){ 
          valInputPinForPIRSensorNextOneThirdFifth = LOW;   
        }
       }
        
        if (valInputPinForPIRSensorNextOneThirdSixth == HIGH){
        // what hapen wehne alarm hapen
        Serial.println(messageMotionPIRSensorSixth);
        sendSMS(messageMotionPIRSensorSixth);
        delay(200);
        
        if (valInputPinForPIRSensorNextOneThirdSixth == LOW) { 
          valInputPinForPIRSensorNextOneThirdSixth = HIGH;       
          }         
        }
        
        else {
        //what hapen when alarm shows 0
        Serial.println("message on terminal");
        delay(200);
          if (valInputPinForPIRSensorNextOneThirdSixth == HIGH){ 
          valInputPinForPIRSensorNextOneThirdSixth = LOW;   
        }
       }     
       delay(10000);
     }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

void  alarmSensorDetection (int sensorValue){
        if (sensorValue == HIGH){
        // what hapen wehne alarm hapen
        Serial.println("Motion");
        sendSMS(motionDetected);
        delay(200); 
        }
      }

void sendSMS (String message){
    mySerial.print("AT+CMGF=1\r");
    delay(1000);
  mySerial.println("AT+CMGS=\"+48123123123\"\r "); //phone number
      delay(1000);
  mySerial.println(message);
    delay(1000);  
  mySerial.println((char)26);
    delay(1000);
  mySerial.println();
    delay(1000);
  }
