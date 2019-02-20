/*******************************************************************************************************
  Vicky Duarte
  Line-following Robot code
  The robot follows a black line. When faced with the end of the track on a double black line,
  the robot captures a golf ball that is positioned on top of a golf tee, using an arm connected
  to a servo. It then turns around, and when it gets back to where it started, the robot drops the
  golf ball at the start position.

*******************************************************************************************************/
//import servo library
#include <Servo.h> 
//set varibales that will be used throughout the code
Servo myservo;
int pos = 0;
int count=0;
int lightsensor1 = A0;
int lightsensor2 = A1;
int lvalue = 0;
int rvalue = 0;
int L1 = 2;
int L2 = 3;
int R1 = 4;
int R2 = 5;

void setup() {
   Serial.begin(9600);
   //initialize servo and declare pins
   pinMode(L1, OUTPUT);
   pinMode(L2, OUTPUT);
   pinMode(R1, OUTPUT);
   pinMode(R2, OUTPUT);
   myservo.attach(6);
   //drive forward for 2000 milliseconds without reading in values
   digitalWrite(L1, HIGH);
   digitalWrite(L2, LOW);
   digitalWrite(R1, HIGH);
   digitalWrite(R2, LOW);
   myservo.write(pos);
   delay(1000);
   }
void loop(){ 
  //read in values from light sensors
 lvalue = analogRead(lightsensor1);
 rvalue = analogRead(lightsensor2);
 Serial.print("left  ");
 Serial.print(lvalue);
 Serial.print("  right  ");
 Serial.print(rvalue);
  Serial.print("  count  ");
 Serial.println(count);
 //w&w 
 if (lvalue < 600 && rvalue < 600)
 { //drive forward
   digitalWrite(L1, HIGH);
   digitalWrite(L2, LOW);
   digitalWrite(R1, HIGH);
   digitalWrite(R2, LOW);
  }
  //w&b
  else if (lvalue > 600 && rvalue < 600)
  { //stop left wheel, and go forward with the right wheel
    digitalWrite(R1, HIGH);
    digitalWrite(R2, LOW);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, HIGH);
  }
  //b&w 
  else if (lvalue < 600 && rvalue > 600)
  { //stop right wheel and go forward with the left wheel
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
  } 
//b&b
  else if (lvalue > 600 && rvalue > 600) {
    //add 1 to the count variable
    count+=1; 
    //position arm to capture ball
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(L1, HIGH);
    digitalWrite(L2, LOW);
    delay(125);
    //capture the ball
    myservo.write(80); 
    //drive forward with the rigt wheel, and drive back with the left wheel
    digitalWrite(L1, HIGH); 
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    //if this is the second time reaching a double black line, drop the ball
    if (count>=2){
      myservo.write(pos);
    }  
    //stay in reverse for 2000 milliseconds so that robot can get back on track
    delay(2500);
  }
  
  delay(1);
}
