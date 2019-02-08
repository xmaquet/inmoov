
//Include libraries
#include <Nunchuk.h>
#include <Wire.h>
#include <Servo.h>

//define variables
Servo base; //servo 1
Servo armH; //bras horizontal
Servo armV; //bras vertical
Servo grip; //pince


//define starting angle for each servo
//choose a safe position to start from
//it will try to move instantaniously to that position when powered up!
//those angles will depend on the angle of each servo during the assemble
int base_rest = 90; //servo 1 current angle
int base_speed = 1; //servo 1 speed
int armH_rest = 100;
int armH_speed = 1;
int armV_rest = 90;
int armV_speed = 1;
int grip_rest = 90;
int grip_speed = 1;

//define restrictions for each servo
//those angles will depend on the angle of each servo during the assemble
int base_min = 0;   
int base_max = 180; 
int armV_min = 45;   
int armV_max = 100; 
int armH_min = 75;   
int armH_max = 140; 
int grip_min = 0;
int grip_max = 120;



//SETUP
void setup() {
    //attach each servo to a pin and start its position
    base.attach(3);
    base.write(base_rest);
    armH.attach(5);
    armH.write(armH_rest);
    armV.attach(6);
    armV.write(armV_rest);
    grip.attach(9);
    grip.write(grip_rest);
    

    //start serial communication
    Serial.begin(9600);

    //start Nunchuk
    Wire.begin();
    nunchuk_init();
}

void loop() {
    //read Nunchuk sensors
    if (nunchuk_read()) {
        
        int x = nunchuk_joystickX();    //joystick X position
        int y = nunchuk_joystickY();    //joystick Y position
        boolean z = nunchuk_buttonZ();  //z button status
        boolean c = nunchuk_buttonC();  //c button status
        float pitch = nunchuk_pitch();  //pitch angle
        float roll = nunchuk_roll();    //roll angle

        if (x>40) {
          base_speed = map(x,40,100,1,3);
          base_rest += base_speed ;
          if (base_rest > base_max){
            base_rest = base_max;
          }
          base.write(base_rest);
        }
        if (x<-40) {
          base_speed = map(x,-40,-100,1,3);
          base_rest -= base_speed ;
          if (base_rest < base_min){
            base_rest = base_min;
          }
          base.write(base_rest);
        }
//        Serial.print("X:");
//        Serial.print(x);
//        Serial.print("-");
//        Serial.println(base_rest);

        if (y>20 && c==0) {
          armH_speed = map (y,20,100,1,2);
          armH_rest += armH_speed;
          if (armH_rest > armH_max){
            armH_rest = armH_max;
          }
          armH.write(armH_rest);
        }
        if (y<-20 && c==0) {
          armH_speed = map(y,-20,-100,1,2);
          armH_rest -= armH_speed ;
          if (armH_rest < armH_min){
            armH_rest = armH_min ; 
          }
          armH.write(armH_rest);
          }
        Serial.print("Y:");
        Serial.print(y);
        Serial.print("-");
        Serial.println(armH_rest);

      if (y>20 && c==1){
        armV_speed = map(y,20,100,1,2);
        armV_rest+=armV_speed;
        if (armV_rest > armV_max){
          armV_rest = armV_max;
        }
        armV.write(armV_rest);
      }
      if (y<-20 && c==1){
        armV_speed = map(y,-20,-100,1,2);
        armV_rest-=armV_speed;
        if (armV_rest < armV_min){
          armV_rest = armV_min;
        }
        armV.write(armV_rest);
      }
          Serial.print("C:");
          Serial.print(c);
          Serial.print("-");
          Serial.println(armV_rest);
          

    }

 
}
