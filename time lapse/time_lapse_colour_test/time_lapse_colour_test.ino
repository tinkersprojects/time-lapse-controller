#define S0 3
#define S1 2
#define S2 5
#define S3 6
#define sensorOut 4
#define enpin 13
#define buttonpin 16
#define runningLEDpin 14
#define powerLEDpin 15

long R = 0;
long G = 0;
long B = 0;

void setup() 
{
  
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop() 
{
  getcolor();
}

void getcolor()
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  R = pulseIn(sensorOut, LOW);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  G = pulseIn(sensorOut, LOW);

  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  B = pulseIn(sensorOut, LOW); 

  long total = R+G+B;
  Serial.print((double)R/total*100);
  Serial.print(",");
  Serial.print((double)G/total*100);
  Serial.print(",");
  Serial.println((double)B/total*100);
}


  
