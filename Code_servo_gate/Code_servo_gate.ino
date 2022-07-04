#include <Wire.h> 
#include <Servo.h> 

Servo myservo1;

int IR1 = 2;
int IR2 = 4;

int Slot = 4;           //enter Total number of parking Slots

int flag1 = 0;
int flag2 = 0;

void setup() {
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(3);
  myservo1.write(100);
}

void loop(){ 

  //
  if(digitalRead (IR1) == LOW && flag1==0) {
    if(Slot>0){ 
      flag1=1;
      if(flag2==0) {
        myservo1.write(0); 
        Slot = Slot-1;
      }
    } 
  }

  //car is out and add more slot 
  if(digitalRead (IR2) == LOW && flag2==0) {
    flag2=1;
    if(flag1==0) {
      myservo1.write(0); 
      Slot = Slot+1;
    }
  }

  if(flag1==1 && flag2==1) {
    delay (1000);
    myservo1.write(100);
    flag1=0, 
    flag2=0;
  }
}
