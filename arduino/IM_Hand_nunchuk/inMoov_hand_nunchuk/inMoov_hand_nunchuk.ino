//Librairies indispensables
#include <Nunchuk.h>
#include <Servo.h>
#include <Wire.h>

//Construction des objets Servo => fonctions de la main => index dans le tableau
Servo thumb; //le pouce => 0
Servo index; //l'index => 1
Servo major; //le majeur => 2
Servo medium;//l'annulaire => 3
Servo rikiki;//l'auriculaire => 4
Servo wrist;//le poignet => pas d'index, il est géré par X

//String fingers[5] = {"thumb","index","major","medium","rikiki"};
String finger_name[5] = {"pouce","index","majeur","annulaire","auriculaire"};
//Définitions des valeurs initiales
///////////////////////////////////
int finger_min[5] = {10,0,0,0,0};
int finger_max[5] = {170,180,180,180,180};
int finger_rest[5] = {90,90,90,90,90};
//sens de fonctionnement des servos 0=normal 1=reverse
int finger_rev[5] = {0,0,0,0,0};

//gestion du 'rotateur' pour les doigts : à chaque appui sur Z on change de doigt
int finger = 0; //le pouce est le doigt activé au démarrage
int reAct = 1 ; //on positionne le reAct prêt à détecter un passage de Z à 1

//le poignet est au repos à mi-course
int wrist_rest = 90;
int wrist_min = 0;
int wrist_max = 180;
int wrist_rev = 0;

// SETUP ********************
void setup() {
// attacher les servos 
thumb.attach(3);
//index.attach(5);
//major.attach(6);
//medium.attach(9);
//rikiki.attach(10);
//wrist.attach(11);

////position de repos
thumb.write(finger_rest[0]);
//index.write(index_rest);
//major.write(major_rest);
//medium.write(medium_rest);
//rikiki.write(rikiki_rest);
//wrist.write(wrist_rest);

  
Serial.begin(9600);
Wire.begin();
nunchuk_init();


delay(1);
}

// LOOP *********************************
void loop() {
  //lecture des infos du nunchuk
  if (nunchuk_read()){
        int x = nunchuk_joystickX();    //joystick X position
        int y = nunchuk_joystickY();    //joystick Y position
         boolean z = nunchuk_buttonZ();  //z button status
         boolean c = nunchuk_buttonC();  //c button status
        delay(1);
        rotator(c,z); //écoute Z et C pour rotation de doigts
        int activeFinger = getActiveFinger(finger); //doigt actif
        //on travaille sur Y pour ouvrir ou fermer un doigt
        if (y > 40 || y < -40) {
          int rest = moveFinger (activeFinger,
                   finger_rest[activeFinger],
                   finger_max[activeFinger],
                   finger_min[activeFinger],
                   finger_rev[activeFinger],y);

          finger_rest[activeFinger] = rest;
        }
        //on travaille sur X pour tourner le poignet
//        if (x > 40 || x < -40) {
//          setMove (5, wrist_rest, wrist_max, wrist_min, wrist_rev, x);
//        }
            
        }
  }
 
int moveFinger (int finger, int action_rest, int action_max, int action_min, int action_rev, int value){
  if (value > 0) {
    action_rest += 1;
    if (action_rest > action_max) {action_rest = action_max ;}
    switch (finger){
        case 0:
        Serial.println(String(finger) + "->" + String(action_rest));
        thumb.write(action_rest);
        break;
        case 1:
        index.write(action_rest);
        break;
        case 2:
        major.write(action_rest);
        break;
        case 3:
        medium.write(action_rest);
        break;
        case 4:
        rikiki.write(action_rest);
        break;
        case 5:
        wrist.write(action_rest);
        break;
    }
  }
  if (value < 0) {
    action_rest -= 1;
    if (action_rest < action_min) {action_rest = action_min ;}
    switch (finger){
        case 0:
        Serial.println(String(finger) + "->" + String(action_rest));
        thumb.write(action_rest);
        break;
        case 1:
        index.write(action_rest);
        break;
        case 2:
        major.write(action_rest);
        break;
        case 3:
        medium.write(action_rest);
        break;
        case 4:
        rikiki.write(action_rest);
        break;
        case 5:
        wrist.write(action_rest);
        break;
    }
  }
  return action_rest;
}


void printActiveFinger(int param){ //envoi un message sur serial précisant le doigt actif
  switch (param) {
    case 0:
      Serial.println("Pouce est actif");
    break;
    case 1:
      Serial.println("Index est actif");
    break;
    case 2:
      Serial.println("Majeur est actif");
    break;
    case 3:
      Serial.println("Annulaire est actif");
    break;
    case 4:
      Serial.println("Auriculaire est actif");
    break;
        }
}



void rotator(boolean c, boolean z){//gestion du rotateur de doigt, activé par Z
            if ( z == 1 && reAct == 0){
              //Serial.println(z);
              printActiveFinger(finger);
              delay(1);
              reAct = 1;
            }
            if ( z == 0 && reAct == 1){
              reAct = 0;
              finger += 1;
                  if (finger > 4)
                  {finger = 0;}
              Serial.print("rotateur activé -> ");
              Serial.println(finger_name[finger]);
            }
            if ( c == 1 && reAct == 0 ) {
              int active_finger = getActiveFinger(finger);
              printActiveFinger(active_finger);
              delay(1);}
}

int getActiveFinger (int finger){
  int active_finger = (finger - 1) ;
  if (active_finger < 0) {active_finger = 4;} 
  return active_finger;
}
