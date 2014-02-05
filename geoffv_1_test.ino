/*
 *Charles Sedgwick
 *geoff v .1
 *This program runs geoff, the (eventually) object avoiding robot
 */
 
 #include <Servo.h>
 #define ABACKWARD 3
 #define AFORWARD 5
 #define BFORWARD 6
 #define BBACKWARD 11
 #define ONTIME 1500
 
 Servo pan;
 Servo tilt;
 int rangePin = A0;
 int rangeValue = 0;
 int posTilt = 0;
 int posPan = 0;
 int object = 0;
 int time = ONTIME;

 
 void setup(){
   pan.attach(4);
   tilt.attach(2);
   pinMode(AFORWARD, OUTPUT);
   pinMode(ABACKWARD, OUTPUT);
   pinMode(BFORWARD, OUTPUT);
   pinMode(BBACKWARD, OUTPUT);
   pinMode(rangePin, OUTPUT);
 }
 
 void loop(){
   //scan();
   test();
   /*object = scan();
   
   if(object == 0){ //no object so clear to move forward
   
   }
   else if(object == 1){ // object so attempt to avoid
     backup();
   } else { // error
   }
     */
 
 }
 
 /* Perception
  * scans the environment for objects and returns 0 for object and 1 for no object
  * pans side to side and tilts when sensor facing forward to check for objects. 
  */
 int scan(){
   int pp = 90;
   int pt = 0;
   
   tilt.write(pt);
         /*
   for(pp = 40; pp < 120 ; pp++){
     pan.write(pp);
     rangeValue = analogRead(rangePin);
     while(rangeValue < 16 ){
       backward(500);
       rangeValue = analogRead(rangePin);
     }
     delay(20);
   }
   for(pp = 120; pp >= 1; pp--){
     pan.write(pp);
     rangeValue = analogRead(rangePin);
     while(rangeValue < 16 ){
       backward(500);
       rangeValue = analogRead(rangePin);
     }
     delay(20);
   }

   for(pt = 0; pp < 40 ; pp++){
     tilt.write(pt);
     delay(20);
   }
      for(pt = 40; pp >= 1; pp--){
     tilt.write(pt);
     delay(20);
   }
   */
   
   rangeValue = analogRead(rangePin);
   
   if(!(rangeValue > 6)){
     while(rangeValue < 16 ){
       backward(500);
       rangeValue = analogRead(rangePin);
     }
   }
   
   if(rangeValue > 6 && rangeValue <= 12){
     while(rangeValue < 12){
       turn(500);
       rangeValue = analogRead(rangePin);
     }
   }
        
   pt = 0;
   pp = 90;
   tilt.write(pt);
   pan.write(pp);
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
 
 /* turn(...)
  * args: int time -> lenght of time in ms that it move forward
  * sets both motors to move forward for the given time
  */
 void turn(int t){
   
   stopMotors();
   
   digitalWrite(AFORWARD, HIGH);
   digitalWrite(ABACKWARD, LOW);
   
   digitalWrite(BFORWARD, HIGH);
   digitalWrite(BBACKWARD, LOW);
   delay(long(t));
   stopMotors();
 }
 
 /* backward(...)
  * args: int time-> length of time in ms
  * sets both motors to reverse for a given length of time
  */
  void forward(int t){
   
   stopMotors();
   
   digitalWrite(AFORWARD, LOW);
   digitalWrite(ABACKWARD, HIGH);
   
   digitalWrite(BFORWARD, LOW);
   digitalWrite(BBACKWARD, HIGH);
   delay(long(t));
   stopMotors();
 }

 /* backward(...)
  * args: int time-> length of time in ms
  * sets both motors to reverse for a given length of time
  */
  void backward(int t){
   
   stopMotors();
   
   digitalWrite(AFORWARD, HIGH);
   digitalWrite(ABACKWARD, LOW);
   
   digitalWrite(BFORWARD, HIGH);
   digitalWrite(BBACKWARD, LOW);
   delay(long(t));
   stopMotors();
 }
 
 void test(){
   forward(ONTIME);
   scan();
 }
 
