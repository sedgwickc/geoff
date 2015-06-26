/*
 *Charles Sedgwick
 *This program combines panning with distance sensing
 * Hardware:
 * - Arduino Uno R3
 * - cmdr shield by solarbotics
 * - dfrobot URM37 V4.0 Ultrasonic Sensor
 * - rover 5 robot platform 
 * - 5 AA battery pack
 * - 1 servo
 */
 
#include <Servo.h>

#define ABACKWARD 5
#define AFORWARD 3
#define BFORWARD 6
#define BBACKWARD 11

#define MOTIONPIN 7
#define BUZPIN 9
#define TOUCHPIN 8
#define LINEPIN 10
#define PANPIN 4
#define TILTPIN 2
#define DELAY 100

int posTilt = 5;
int posPan = 90;
int object = 0;
int numTones = 3;

uint8_t EnDistCmd[4]={0x22, 0x00, 0x00, 0x22};    // Distance measure command
uint8_t DistData[4];
unsigned int DistValue=0;

//Function prototypes
uint16_t get_gp2d12 (uint16_t value);
void stopMotors();
void backward();
void forward();
void turnRight();
void turnLeft();

Servo pan;
Servo tilt;

void setup(){    
  
   Serial.begin (9600);
   pinMode(AFORWARD, OUTPUT);
   pinMode(ABACKWARD, OUTPUT);
   pinMode(BFORWARD, OUTPUT);
   pinMode(BBACKWARD, OUTPUT);

   pan.attach(PANPIN);
   tilt.attach(TILTPIN);
   
   tilt.write(posTilt);
   pan.write(posPan);
   
   delay(DELAY);
}

/*************Main Loop*********************/
void loop(){
  int dist = 0;
  int i;

  for( i = 50; i < 140; i+=3 )
  {
    pan.write( i );
    dist = SerialCmd(); 
    while ( dist > 0 && dist <= 15)
    {
      dist = SerialCmd(); 
      backward();
      delay(500);
      turnRight();
      delay(500);
    }
    forward();
  }
  
  for( ; i >= 50; i-=3 )
  {
    pan.write( i );
    dist = SerialCmd();
    while ( dist > 0 && dist <= 15 )
    {
      dist = SerialCmd();
      backward();
      delay(500);
      turnRight();
      delay(500);
    }
    forward();
  }
}

//Helper Definitions
 
uint16_t get_gp2d12 (uint16_t value) {
    if (value < 10) value = 10;
    return ((6787.0 / (value - 3.0)) - 4.0);
}

int SerialCmd()
{
   int i;
   for(i = 0;i < 4;i++){
    Serial.write(EnDistCmd[i]);
   }
   
   if (Serial.available() == 0 )
   {
     Serial.println( "no data" );
     delay( DELAY );
     return 0;
   }
   
  while (Serial.available() > 0)  //if serial receive any data
  {
     for(i = 0;i < 4;i++){
       DistData[i] = Serial.read();
     }
     DistValue = DistData[1]<<8;
     DistValue = DistValue+DistData[2];
     if(DistValue>=45000){              // the reading is invalid.
       Serial.println("Invalid");
       delay( DELAY );
       return 0;
     }
     else{
      Serial.print("Distance=");
      Serial.print(DistValue);
      Serial.println("cm");
      delay( DELAY );
      return DistValue;
     }
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
