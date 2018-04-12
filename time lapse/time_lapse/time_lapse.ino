#include <AccelStepper.h>

#define S0 3
#define S1 2
#define S2 5
#define S3 4
#define sensorOut 6
#define enpin 13
#define buttonpin 16
#define runningLEDpin 14
#define powerLEDpin 15

#define tolrents 2

double R = 0;
double G = 0;
double B = 0;

double ProgramedArray[5][9] = {
  //R,G,B,MovDir,MovSpeed,RotDir,RotSpeed,TilDir,TilSpeed
 {43,25,31,0,200,0,0,0,0},    // green
 {34,35,30,0,200,0,200,0,0},    // White
 {23,31,44,0,100,0,100,0,0},    // Yellow
 {15,47,36,0,0,0,0,0,0}, // Red
 {50,33,15,0,100,0,100,0,0}     // Blue
};

AccelStepper rotatorstepper;
AccelStepper movingstepper;
AccelStepper tiltstepper;

void setup() 
{
  Serial.begin(115200);
  getcolor();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(runningLEDpin, OUTPUT);
  pinMode(powerLEDpin, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(buttonpin, INPUT);
  pinMode(enpin, INPUT);

  digitalWrite(enpin,LOW);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  digitalWrite(powerLEDpin,HIGH);
  digitalWrite(runningLEDpin,HIGH);
  
  rotatorstepper = AccelStepper(1,7,8);
  rotatorstepper.setMaxSpeed(200/60);
  rotatorstepper.setAcceleration(100000.0);
  rotatorstepper.move(0);
  
  movingstepper = AccelStepper(1,9,10);
  movingstepper.setMaxSpeed(200/60);
  movingstepper.setAcceleration(100000.0);
  movingstepper.move(0);
  
  tiltstepper = AccelStepper(1,11,12);
  tiltstepper.setMaxSpeed(200/60);
  tiltstepper.setAcceleration(100000.0);
  tiltstepper.move(0);
}

void loop() 
{
  getcolor();

  for(int i =0;i<sizeof(ProgramedArray);i++)
  {
    runsteps();
    if(isColor(ProgramedArray[i][0],ProgramedArray[i][1],ProgramedArray[i][2]))
    {
      movingstepper.setMaxSpeed(ProgramedArray[i][4]);
      movingstepper.setSpeed(ProgramedArray[i][4]);
      movingstepper.setPinsInverted(ProgramedArray[i][3],0,1);

      rotatorstepper.setMaxSpeed(ProgramedArray[i][6]);
      rotatorstepper.setSpeed(ProgramedArray[i][6]);
      rotatorstepper.setPinsInverted(ProgramedArray[i][5],0,1);

      tiltstepper.setMaxSpeed(ProgramedArray[i][8]);
      tiltstepper.setSpeed(ProgramedArray[i][8]);
      tiltstepper.setPinsInverted(ProgramedArray[i][7],0,1);

      runsteps();
  
      if(ProgramedArray[i][4] == 0 && ProgramedArray[i][6] == 0 && ProgramedArray[i][8] == 0)
      {
        movingstepper.stop();
        rotatorstepper.stop();
        tiltstepper.stop();
        movingstepper.disableOutputs();
        rotatorstepper.disableOutputs();
        tiltstepper.disableOutputs();
      }
      break;
    }
  }
  runsteps();
}

void runsteps()
{
  rotatorstepper.move(100);
  movingstepper.move(100);
  tiltstepper.move(100);

  rotatorstepper.run();
  movingstepper.run();
  tiltstepper.run();
}

void getcolor()
{
  R = pulseIn(sensorOut, LOW);
  G = pulseIn(sensorOut, LOW);
  B = pulseIn(sensorOut, LOW); 

  long total = R+G+B;
  R = R/total*100;
  G = G/total*100;
  B = B/total*100;
}

boolean isColor(int r,int g, int b)
{
  if(R+tolrents>r && R-tolrents<r) return false;
  if(G+tolrents>g && G-tolrents<g) return false;
  if(B+tolrents>b && B-tolrents<b) return false;
  return true;
}
  
