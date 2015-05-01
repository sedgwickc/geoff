/*
 *Charles Sedgwick
 *geoff v .1
 *This program runs geoff, the (eventually) object avoiding robot
 */
 
#include <Servo.h>


#define ABACKWARD 5
#define AFORWARD 3
#define BFORWARD 6
#define BBACKWARD 11

#define RANGEPIN A0
#define MOTIONPIN 7
#define BUZPIN 9
#define TOUCHPIN 8
#define LINEPIN 10

#define WHITE 1
#define BLACK 0
#define ONTIME 1000

int range_value = 0;
int posTilt = 0;
int posPan = 0;
int object = 0;
int time = ONTIME;

//Function prototypes
int get_gp2d12 (int value);
void scan();
void stopMotors();
void backward();
void forward();
void turnRight();
void turnLeft();
void LineFollow();

Servo pan;
Servo tilt;

void setup(){
   Serial.begin (9600);
   pinMode(AFORWARD, OUTPUT);
   pinMode(ABACKWARD, OUTPUT);
   pinMode(BFORWARD, OUTPUT);
   pinMode(BBACKWARD, OUTPUT);
   
   pinMode(RANGEPIN, INPUT);
   pinMode(MOTIONPIN, INPUT);
   pinMode(TOUCHPIN, INPUT);
   pinMode(BUZPIN, OUTPUT);
   
   pan.attach(4);
   tilt.attach(2);
   int pp = 90;
   int pt = 0;
   
   tilt.write(pt);
   pan.write(pp);
}

/*************Main Loop*********************/
void loop(){
   //LineFollow();

  range_value = analogRead(RANGEPIN);
  while(range_value < 16 )
  {
    forward();
    //turnRight();
    range_value = analogRead(RANGEPIN);
  }
}

//Function Definitions
int get_gp2d12 (int value) {
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}
 
void get_touch(){   
  //byte state = digitalRead(MOTIONPIN);
  
  if(digitalRead(TOUCHPIN) == HIGH){
    analogWrite(BUZPIN,254);
  }else if(digitalRead(TOUCHPIN) == LOW){
    digitalWrite(BUZPIN, LOW);
  }
}
 
 /* stopMotors()
  * args: none
  * stops both motors by sending LOW along bnoth pins for each motor.
  */
void stopMotors(){
   digitalWrite(ABACKWARD, LOW);
   digitalWrite(AFORWARD, LOW);
   digitalWrite(BBACKWARD, LOW);
   digitalWrite(BFORWARD, LOW);
}
 
 /* backward(...)
  * args: 
  * sets both motors to reverse for a given length of time
  */
void backward(){
   digitalWrite(AFORWARD, LOW);
   digitalWrite(ABACKWARD, HIGH);
   
   digitalWrite(BFORWARD, LOW);
   digitalWrite(BBACKWARD, HIGH);
 }
 

   /* forward(...)
  * args: 
  * sets both motors to move forward for the given time
  */
void forward(){
   digitalWrite(AFORWARD, HIGH);
   digitalWrite(ABACKWARD, LOW);
   
   digitalWrite(BFORWARD, HIGH);
   digitalWrite(BBACKWARD, LOW);   
}

/* Using PWM allows you to slow your motors down via software 
pulsing commands. Leave one pin high (or low), and pulse the other to 
vary the speed. Learn about this feature by using the Arduino command
AnalogWrite. Check out the Arduino IDE example code “0.3Analog -> 
Fading” sketch to help you out.
*/

void turnRight(){
   digitalWrite(AFORWARD, LOW);
   digitalWrite(ABACKWARD, LOW);
   
   digitalWrite(BFORWARD, HIGH);
   digitalWrite(BBACKWARD, LOW);
}

void turnLeft(){
   digitalWrite(AFORWARD, HIGH);
   digitalWrite(ABACKWARD, LOW);
   
   digitalWrite(BFORWARD, LOW);
   digitalWrite(BBACKWARD, LOW);
}
 
 void LineFollow(){
   if(digitalRead(LINEPIN) == WHITE)
   {
     turnLeft();
   }
   else if(digitalRead(LINEPIN) == BLACK)
   {
     turnRight();
   }  
}

 
