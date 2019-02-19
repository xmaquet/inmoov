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
Servo wrist;//le poignet => 5 et géré par X

String finger_name[5] = {"pouce","index","majeur","annulaire","auriculaire"};
//Définitions des valeurs initiales
///////////////////////////////////
int finger_min[5] = {5,10,10,10,25};
int finger_max[5] = {180,170,170,170,165};
int finger_rest[5] = {90,90,90,90,90};
//sens de fonctionnement des servos 0=normal 1=reverse
int finger_rev[5] = {1,1,1,1,1};

//vitesse des servos : entre 1 (lent) à 10 (rapide) ; 3 est une bonne valeur à priori
int servo_speed = 1 ;

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
index.attach(5);
major.attach(6);
medium.attach(9);
rikiki.attach(10);
wrist.attach(11);

////position de repos
thumb.write(finger_rest[0]);
index.write(finger_rest[1]);
major.write(finger_rest[2]);
medium.write(finger_rest[3]);
rikiki.write(finger_rest[4]);
wrist.write(wrist_rest);

  
Serial.begin(9600);
Wire.begin();
nunchuk_init();
}

// LOOP *********************************
void loop() {
  //lecture des infos du nunchuk
  if (nunchuk_read()){
        int x = nunchuk_joystickX();    //joystick X position
        int y = nunchuk_joystickY();    //joystick Y position
         boolean z = nunchuk_buttonZ();  //z button status
         boolean c = nunchuk_buttonC();  //c button status
        delay(10);
        rotator(c,z); //écoute Z et C pour rotation de doigts
        int activeFinger = getActiveFinger(finger); //doigt actif
        //on travaille sur Y pour ouvrir ou fermer un doigt
        if (y > 40 || y < -40) {
          int rest = moveDevice (activeFinger,
                   finger_rest[activeFinger],
                   finger_max[activeFinger],
                   finger_min[activeFinger],
                   finger_rev[activeFinger],
                   servo_speed,
                   y);

          finger_rest[activeFinger] = rest;
        }
        //on travaille sur X pour tourner le poignet
        if (x > 40 || x < -40) {
          int rest = moveDevice (5,
                   finger_rest[wrist_rest],
                   finger_max[wrist_max],
                   finger_min[wrist_min],
                   finger_rev[wrist_rev],
                   servo_speed,
                   x);

          wrist_rest = rest ;
        }
            
        }
  }
 
int moveDevice (int device, int dev_rest, int dev_max, int dev_min, int dev_rev, int servo_speed, int value){
  if (value > 0) {
    
    if (dev_rev == 0) { //si le device est inversé on décrémente
      dev_rest += servo_speed;
    }
    else {
      dev_rest -= servo_speed;
    }
    
    
    if (dev_rest > dev_max) {dev_rest = dev_max ;} // ne pas dépasser les valeurs limites !!
    else if (dev_rest < dev_min) {dev_rest = dev_min ;}

    
    switch (device){
        case 0:
        Serial.println(String(device) + "->" + String(dev_rest));
        thumb.write(dev_rest);
        break;
        case 1:
        Serial.println(String(device) + "->" + String(dev_rest));
        index.write(dev_rest);
        break;
        case 2:
        Serial.println(String(device) + "->" + String(dev_rest));
        major.write(dev_rest);
        break;
        case 3:
        Serial.println(String(device) + "->" + String(dev_rest));
        medium.write(dev_rest);
        break;
        case 4:
        Serial.println(String(device) + "->" + String(dev_rest));
        rikiki.write(dev_rest);
        break;
        case 5:
        Serial.println(String(device) + "->" + String(dev_rest));
        wrist.write(dev_rest);
        break;
    }
  }
  if (value < 0) {

        if (dev_rev == 0) { //si le device est inversé on incrémente
      dev_rest -= servo_speed;
    }
    else {
      dev_rest += servo_speed;
    }
    
    if (dev_rest > dev_max) {dev_rest = dev_max ;} // ne pas dépasser les valeurs limites !!
    else if (dev_rest < dev_min) {dev_rest = dev_min ;}
    
    switch (device){
        case 0:
        Serial.println(String(device) + "->" + String(dev_rest));
        thumb.write(dev_rest);
        break;
        case 1:
        Serial.println(String(device) + "->" + String(dev_rest));
        index.write(dev_rest);
        break;
        case 2:
        Serial.println(String(device) + "->" + String(dev_rest));
        major.write(dev_rest);
        break;
        case 3:
        Serial.println(String(device) + "->" + String(dev_rest));
        medium.write(dev_rest);
        break;
        case 4:
        Serial.println(String(device) + "->" + String(dev_rest));
        rikiki.write(dev_rest);
        break;
        case 5:
        Serial.println(String(device) + "->" + String(dev_rest));
        wrist.write(dev_rest);
        break;
    }
  }
  return dev_rest;
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
              delay(10);
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
              delay(10);}
}

int getActiveFinger (int finger){
  int active_finger = (finger - 1) ;
  if (active_finger < 0) {active_finger = 4;} 
  return active_finger;
}
