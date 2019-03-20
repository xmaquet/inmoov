#include <ArduinoJson.h>

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
String incoming = "";
int start = 0;


void setup() {
  Serial.begin(9600); //instanciation de Serial
  while (!Serial) continue;
  for (int i = 0; i<8; i++){ // affectation du mode OUTPUT à chaque broche/relay
    pinMode(relay[i], OUTPUT);
    digitalWrite(relay[i],relayState[i]);
  }

}

void loop() {
  while (Serial.available()) {
    char inc = Serial.read();
    if (inc == '[' && incoming == ""){
      start = 1;
    }
    if (start == 1){
      incoming += inc;
    }
    if (inc == ']' && start == 1){
        //Serial.println (incoming);
        parseIncoming (incoming);
        start = 0;
        incoming = "";
    }
    delay(1);
  }
  
}

void parseIncoming(String text){//interprétation de la chaîne reçue entre [] = deserialize JSON
  text.replace("[","");//retirer les [
  text.replace("]","");//retirer les ]
  Serial.println (text);
      DynamicJsonDocument doc(512);
      DeserializationError err = deserializeJson(doc, text);
      if (err) {
              Serial.print(F("deserializeJson() failed with code "));
              Serial.println(err.c_str());
              }
      JsonObject obj = doc.as<JsonObject>();
      // Loop through all the key-value pairs in obj
        for (JsonPair p : obj) {
        p.key() ;// is a JsonString
        p.value() ;// is a JsonVariant
        }
        
      //obj est l'objet qui contient la représentation du json reçu
      if (obj.containsKey("order")&& obj.containsKey("params")){
        f_returnMsg(0);
        if (obj.containsKey("servo")){
          f_returnMsg(5);
        }
        if (obj.containsKey("sensor")){
          f_returnMsg(6);
        }
        if (obj.containsKey("ledRing")){
          f_returnMsg(7);
        }
        if (obj.containsKey("relay")){
          int value = obj["params"]["value"];
          int index = obj["params"]["index"];
          int closeLevel = obj["relay"]["closeLevel"];
          f_actionRelay (value, index, closeLevel);
        }
      }
          
}

void f_actionRelay(int val, int relayIndex, int level){//action sur le relais indexé
  switch (val) {
    case 0:
      digitalWrite(relay[relayIndex],!level);
      break;
    case 1:
    digitalWrite(relay[relayIndex],level);
      break;    
  }
  
}

void f_returnMsg (int indexMsg) {
  Serial.println (returnMsg [indexMsg]);
}
