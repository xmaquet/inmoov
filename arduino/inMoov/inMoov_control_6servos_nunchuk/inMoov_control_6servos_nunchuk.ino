//Librairies indispensables
#include <Nunchuk.h>
#include <Servo.h>
#include <Wire.h>

//Construction des objets Servo => fonctions  => index dans le tableau
Servo S0; //servo => 0
Servo S1; //servo => 1
Servo S2; //servo => 2
Servo S3;//servo => 3
Servo S4;//servo => 4
Servo S5;//servo => 5 et géré par X

String servo_name[5] = {"servo#0","servo#1","servo#2","servo#3","servo#4"};
//Définitions des valeurs initiales
//---------------------------------
int servo_min[5] = {67,80,80,80,80};
int servo_max[5] = {143,100,100,100,100};
int servo_rest[5] = {90,90,90,90,90}; //position à la mise sous tension
int servo_rev[5] = {0,0,0,0,0}; //sens de fonctionnement des servos 0=normal 1=reverse


int servo_speed = 1 ;//vitesse des servos : entre 1 (lent) à 10 (rapide) ; 3 est une bonne valeur à priori

//gestion du 'rotateur' pour les servos : à chaque appui sur Z on change de servo (en réalité on détecte le relachement du bouton, qui est unique dans une série de cycles loop)
int servo = 0; //servo#0 est le servo activé au démarrage
int reAct = 1 ; //on positionne le reAct prêt à détecter un passage Z de 1 à 0

//le servo#5 est au repos à mi-course
int S5_rest = 90;
int S5_min = 0;
int S5_max = 180;
int S5_rev = 0;

// SETUP ********************
void setup() {
// attacher les servos 
S0.attach(3);
S1.attach(5);
S2.attach(6);
S3.attach(9);
S4.attach(10);
S5.attach(11);

////position de repos
S0.write(servo_rest[0]);
S1.write(servo_rest[1]);
S2.write(servo_rest[2]);
S3.write(servo_rest[3]);
S4.write(servo_rest[4]);
S5.write(S5_rest);

  
Serial.begin(9600); //ouverture du port Série
Wire.begin(); //début de la liaison I2C
nunchuk_init(); //init de la lib du Nunchuk
}
// endof SETUP
// LOOP *********************************
void loop() {
  //lecture des infos du nunchuk
  if (nunchuk_read()){
        int x = nunchuk_joystickX();    //joystick X position
        int y = nunchuk_joystickY();    //joystick Y position
         boolean z = nunchuk_buttonZ();  //z button status
         boolean c = nunchuk_buttonC();  //c button status
        delay(10);
        rotator(c,z); //écoute Z et C pour rotation de servos
        int activeServo = getActiveServo(servo); //servo actif
        //on travaille sur Y pour ouvrir ou fermer un servo
        if (y > 40 || y < -40) {
          int rest = moveDevice (activeServo,
                   servo_rest[activeServo],
                   servo_max[activeServo],
                   servo_min[activeServo],
                   servo_rev[activeServo],
                   servo_speed,
                   y);

          servo_rest[activeServo] = rest;
        }
        //on travaille sur X pour tourner le S5
        if (x > 40 || x < -40) {
          int rest = moveDevice (5,
                   servo_rest[S5_rest],
                   servo_max[S5_max],
                   servo_min[S5_min],
                   servo_rev[S5_rev],
                   servo_speed,
                   x);

          S5_rest = rest ;
        }
            
        }
  }
//endof LOOP
//fonctions--------------------------------------------------------------------------------------------------------

// moveDevice reçoit les paramètres d'un servo à actionner ; l'incrément servoSpeed détermine le pas et donc la vitesse
// device : n°d'index du servo concerné
// dev_rest : position instantanée
// dev_max et dev_min : extrêmes à ne pas dépasser
// dev_rev : indicateur de reverse, indique si le servo doit fonctionner à l'envers (auquel cas on calcule le pas différemment)
// value : valeur de l'axe du Nunchuk ; dans ce sketch cette valeur donne uniquement le sens de fonctionnementet n'entre pas en compte dans le calcul de la position à atteindre
int moveDevice (int device, int dev_rest, int dev_max, int dev_min, int dev_rev, int servo_speed, int value){
  if (value > 0) { // sens "positif"
    
    if (dev_rev == 0) { //si le device est inversé on décrémente
      dev_rest += servo_speed;
    }
    else {
      dev_rest -= servo_speed;
    }
     
    if (dev_rest > dev_max) {dev_rest = dev_max ;} // ne pas dépasser les valeurs limites !!
    else if (dev_rest < dev_min) {dev_rest = dev_min ;}

//on actionne le servo concerné uniquement
    switch (device){
        case 0:
        Serial.println(String(device) + "->" + String(dev_rest));
        S0.write(dev_rest);
        break;
        case 1:
        Serial.println(String(device) + "->" + String(dev_rest));
        S1.write(dev_rest);
        break;
        case 2:
        Serial.println(String(device) + "->" + String(dev_rest));
        S2.write(dev_rest);
        break;
        case 3:
        Serial.println(String(device) + "->" + String(dev_rest));
        S3.write(dev_rest);
        break;
        case 4:
        Serial.println(String(device) + "->" + String(dev_rest));
        S4.write(dev_rest);
        break;
        case 5:
        Serial.println(String(device) + "->" + String(dev_rest));
        S5.write(dev_rest);
        break;
    }
  }
  if (value < 0) { //sens "négatif"

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
        S0.write(dev_rest);
        break;
        case 1:
        Serial.println(String(device) + "->" + String(dev_rest));
        S1.write(dev_rest);
        break;
        case 2:
        Serial.println(String(device) + "->" + String(dev_rest));
        S2.write(dev_rest);
        break;
        case 3:
        Serial.println(String(device) + "->" + String(dev_rest));
        S3.write(dev_rest);
        break;
        case 4:
        Serial.println(String(device) + "->" + String(dev_rest));
        S4.write(dev_rest);
        break;
        case 5:
        Serial.println(String(device) + "->" + String(dev_rest));
        S5.write(dev_rest);
        break;
    }
  }
  return dev_rest;
}


void printActiveServo(int param){ //envoi un message sur serial précisant le doigt actif
  switch (param) {
    case 0:
      Serial.println("servo#0 est actif");
    break;
    case 1:
      Serial.println("servo#1 est actif");
    break;
    case 2:
      Serial.println("servo2 est actif");
    break;
    case 3:
      Serial.println("servo#3 est actif");
    break;
    case 4:
      Serial.println("servo#4 est actif");
    break;
        }
}



void rotator(boolean c, boolean z){//gestion du rotateur de servo, activé par Z
            if ( z == 1 && reAct == 0){ //détection du Z et armement de reAct
              //Serial.println(z);
              printActiveServo(servo);
              delay(10);
              reAct = 1;
            }
            if ( z == 0 && reAct == 1){ //détection du relachement du Z et contrôle de reAct ; si reAct est armé on change de servo (+1)
              reAct = 0;
              servo += 1;
                  if (servo > 4)
                  {servo = 0;}
              Serial.print("rotateur activé -> ");
              Serial.println(servo_name[servo]);
            }
            if ( c == 1 && reAct == 0 ) { //détection de C et affiche le servo actif
              int active_servo = getActiveServo(servo);
              printActiveServo(active_servo);
              delay(10);}
}

int getActiveServo (int servo){ //renvoie le rang du servo actif 
  int active_servo = (servo - 1) ;
  if (active_servo < 0) {active_servo = 4;} 
  return active_servo;
}
