#include <AccelStepper.h>

#define S0 3
#define S1 2
#define S2 5
#define S3 6
#define sensorOut 4
#define enpin 13
#define buttonpin 16
#define runningLEDpin 14
#define powerLEDpin 15

#define tolrents 10

int R = 0;
int G = 0;
int B = 0;

AccelStepper rotatorstepper;
AccelStepper movingstepper;
AccelStepper tiltstepper;

void setup() 
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(runningLEDpin, OUTPUT);
  pinMode(powerLEDpin, OUTPUT);
  pinMode(enpin, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(buttonpin, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(enpin,LOW);
  digitalWrite(powerLEDpin,HIGH);
  digitalWrite(runningLEDpin,HIGH);
  
  rotatorstepper = AccelStepper(1,7,8);
  rotatorstepper.setMaxSpeed(100);
  rotatorstepper.setAcceleration(100.0);
  rotatorstepper.move(1000);
  
  movingstepper = AccelStepper(1,9,10);
  movingstepper.setMaxSpeed(100);
  movingstepper.setAcceleration(100.0);
  movingstepper.move(1000);
  
  tiltstepper = AccelStepper(1,11,12);
  tiltstepper.setMaxSpeed(100);
  tiltstepper.setAcceleration(100.0);
  tiltstepper.move(1000);
}

void loop() 
{
  
  rotatorstepper.move(1000);
  movingstepper.move(1000);
  tiltstepper.move(1000);
  rotatorstepper.run();
  movingstepper.run();
  tiltstepper.run();
}

