#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

void motormove(int, int, float);//foward, backward pin and rotation speed.

void travel(float, float);//moves motors foward at a given float speed for a given time
//**BACKWARDS IF SPEED INPUT IS NEGATIVE

void turn(float,float,float);
//Motor Enable pins *powering through VRegulator.

void emit(float);//activate emitters for a given time

int Receive();

// Motor PWM pins
const int mL_forward = 4;//left
const int mL_reverse = 3;
const int mR_forward = 5;//right
const int mR_reverse = 6;

// Encoder digital pins
const int encoder_mL_A = 9;
const int encoder_mL_B = 10;
const int encoder_mR_A = 12;
const int encoder_mR_B = 11;

// Encoder objects
Encoder encoder_mL(encoder_mL_A, encoder_mL_B);
Encoder encoder_mR(encoder_mR_A, encoder_mR_B);

// Emitter digital pins
const int emitters[4]={23,22,21,20};
const int emit1 = 23;
const int emit2 = 22;
const int emit3 = 21;
const int emit4 = 20;

// Reciever analog pins
const int receivers[4]={19,18,17,16};
int reading[4]={0,0,0,0};
const int reciev1 = 19;
const int reciev2 = 18;
const int reciev3 = 17;
const int reciev4 = 16;

void setup() 
{
  // Built-in led
  pinMode(13, OUTPUT);
  
  // Motor pin setup
  pinMode(mL_forward, OUTPUT);
  pinMode(mL_reverse, OUTPUT);
  pinMode(mR_forward, OUTPUT);
  pinMode(mR_reverse, OUTPUT);

  // Emitter pin setup
  pinMode(emit1, OUTPUT);
  pinMode(emit2, OUTPUT);
  pinMode(emit3, OUTPUT);
  pinMode(emit4, OUTPUT);

  // Reciever pin setup
  pinMode(reciev1, INPUT);
  pinMode(reciev2, INPUT);
  pinMode(reciev3, INPUT);
  pinMode(reciev4, INPUT);

  // Serial Monitor
  Serial.begin(9600);
  Serial.println("Micromouse: Team Kavianpour");
}

void loop()
{
  float i;
  for (i=0;i<=255;i+=50)
  {
    travel(i, 1000);//moves motors foward at a given float speed for a given time
    long leftread, rightread;
    leftread= encoder_mL.read();
    rightread = encoder_mR.read(); 
    Serial.print("Left = ");
    Serial.println(leftread);
    Serial.print(", Right = ");
    Serial.println(rightread);
  }
}


void onLight()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}

void travel (float motorSpeed, float t)//moves  at speed s for time s
{
  //*** speed  must be between 0 and 255;
  if (motorSpeed>255 || motorSpeed<-255)
  {
    motorSpeed=constrain(motorSpeed,-255,255);
    Serial.println("ERROR: SPEED OUT OF RANGE.");
  }
  motormove(mL_forward,mL_reverse,motorSpeed);
  motormove(mR_forward,mR_reverse,motorSpeed);
  delay(t);
}

/*
float Receive()//get reading from receivers
{
static int i;
int result
for (i=0;i<4;i++)
{
analogRead(receivers[i]);
}
return
}
*/

void emit(float t)//flash LED's for a given time t
{
  int i;
  for (i=0;i<4;i++)
  {
    digitalWrite(emitters[i],HIGH);
    delay(t);//stay on for time t in ms 
    digitalWrite(emitters[i],LOW);
    delay(t);
  }
}

void turn(float rightspeed,float leftspeed, float t)//turns by spinning motors at different speeds.
{
  motormove(mL_forward,mL_reverse,rightspeed);
  motormove(mR_forward,mR_reverse,leftspeed);
  delay(t);//in milliseconds
}  

void motormove (int pinforward,int pinbackward ,float velocity)//velocity for a single motor
{
  if (velocity>=0)
  {
    analogWrite(pinforward,velocity);
    digitalWrite(pinbackward,LOW);
  }
  if (velocity<0)//reverse if motorvelocity is negative
  {
    analogWrite(pinbackward,-velocity);//makes value positive
    digitalWrite(pinforward,LOW);
  }
}
