/**************************************************************

Name:		  Gizwits + ArduinoUnoWiFi Library 
Author:		bing@arduino.org.cn / tli@gizwits.com
Version:	V1.0
Init:		  2016-12-23
Modify:   2016-12-23
****************************************************************/
#include <Gizwits.h>
#include <Wire.h>
#include<Servo.h>

unsigned long temp_SteeringEngine;
unsigned long temp_Motor2;
int initialAngle = 90;
int tempAngle=0;
bool temp_Motor1=false;

Gizwits myGizwits;
Servo myServo;

void setup() {
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  myGizwits.begin();
  myServo.attach(9);
  myServo.write(initialAngle);
  if(LOW==digitalRead(7))
    myGizwits.setBindMode(0x02);
  if(LOW==digitalRead(8))
    myGizwits.setBindMode(0x00);
}

void loop() {  
  if(myGizwits.hasBeenSet(EVENT_STEERINGENGINE)){
    myGizwits.read(EVENT_STEERINGENGINE,&temp_SteeringEngine);
    
  if(temp_SteeringEngine==0){
    tempAngle = initialAngle+45;
    myServo.write(tempAngle);
    for(int i=0;i<8;i++){
      tempAngle = tempAngle-i*5;
      delay(500);
      myServo.write(tempAngle);
      }
    myServo.write(initialAngle);
    }
  else if(temp_SteeringEngine==1){
    tempAngle = initialAngle-45;
    myServo.write(tempAngle);
    for(int i=0;i<8;i++){
      tempAngle = tempAngle+i*5;
      delay(500);
      myServo.write(tempAngle);
      }
      myServo.write(initialAngle);
    }
     
  }
  
  
  if(myGizwits.hasBeenSet(EVENT_MOTOR1)){
    myGizwits.read(EVENT_MOTOR1,&temp_Motor1);  
    if(temp_Motor1){
      analogWrite(3,180);
      digitalWrite(6,LOW);
    }
    else{
      analogWrite(3,0);
      analogWrite(6,0);
    }
}

  if(myGizwits.hasBeenSet(EVENT_MOTOR2)){
    myGizwits.read(EVENT_MOTOR2,&temp_Motor2);
    if(temp_Motor2==0){
      digitalWrite(5,HIGH);
      digitalWrite(10,LOW);
    }
    else if(temp_Motor2==1){
      digitalWrite(5,LOW);
      digitalWrite(10,HIGH);
    }
  }
  else{
  analogWrite(5,0);
  analogWrite(10,0);
  }
      

  myGizwits.wifiProcess();
}
