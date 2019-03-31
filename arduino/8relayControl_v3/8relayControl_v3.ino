#include <aJSON.h>
//ce sketch permet de contrôler un board de 8 relays à travers la liaison série
//format d'un ordre {order{orderType}{value}{index}{code}}
//{orderType:action||query||ping}
//{value:number} valeur associée à l'ordre
//{index:integer} rang dans le tableau des équipements gérés par le contrôleur
//{code:string} string identifiant l'équipement

String controlerTitle = "Contrôleur de commande 8 relais" ;
String sketchName = "8relayControl" ; 
int relay[8] = {2,3,4,5,6,7,8,9}; //affectation d'un relay à chaque broche digitale
boolean relayState[8] = {1,1,1,1,1,1,1,1}; //état initial de chaque relais
String returnMsg [8] ={ //messages à renvoyer selon les cas 
  "Order received in a correct format", //l'ordre reçu est correctement formaté
  "Bad pin number in order", // la broche évoquée n'est pas correcte
  "Controler not accept action order", // les ordres d'action ne sont pas acceptés par ce controleur
  "Controler not accept query order", // les ordres de requête ne sont pas acceptés par ce controleur
  "Value is not correct" // la valeur indiquée est incorrecte
  "Controler not manage servo" // le contrôleur ne contrôle pas de servo
  "Controler not manage sensor" //le controleur ne controle pas de senseur
  "Controler not manage ledRing" // le controleur ne controle pas d'anneau de leds
};
unsigned long last_print = 0;
aJsonStream serial_stream(&Serial);

void setup() {
  Serial.begin(9600); //instanciation de Serial
  while (!Serial) continue;
  for (int i = 0; i<8; i++){ // affectation du mode OUTPUT à chaque broche/relay
    pinMode(relay[i], OUTPUT);
    digitalWrite(relay[i],relayState[i]);
  }

}
void processMessage(aJsonObject *msg)
{
  aJsonObject *pwm = aJson.getObjectItem(msg, "pwm");
  if (!pwm) {
    Serial.println("no pwm data");
    return;
  }

  const static int pins[] = { 8, 9 };
  const static int pins_n = 2;
  for (int i = 0; i < pins_n; i++) {
    char pinstr[3];
    snprintf(pinstr, sizeof(pinstr), "%d", pins[i]);

    aJsonObject *pwmval = aJson.getObjectItem(pwm, pinstr);
    if (!pwmval) continue; /* Value not provided, ok. */
    if (pwmval->type != aJson_Int) {
      Serial.print("invalid data type ");
      Serial.print(pwmval->type, DEC);
      Serial.print(" for pin ");
      Serial.println(pins[i], DEC);
      continue;
    }

    Serial.print("setting pin ");
    Serial.print(pins[i], DEC);
    Serial.print(" to value ");
    Serial.println(pwmval->valueint, DEC);
    analogWrite(pins[i], pwmval->valueint);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 if (serial_stream.available()) {
    /* First, skip any accidental whitespace like newlines. */
    serial_stream.skip();
  }

  if (serial_stream.available()) {
    /* Something real on input, let's take a look. */
    aJsonObject *msg = aJson.parse(&serial_stream);
    processMessage(msg);
    aJson.deleteItem(msg);
  }
}
