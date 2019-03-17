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
String returnMsg [5] ={ //messages à renvoyer selon les cas 
  "Order received in a correct format", //l'ordre reçu est correctement formaté
  "Bad pin number in order", // la broche évoquée n'est pas correcte
  "Controler not accept action order", // les ordres d'action ne sont pas acceptés par ce controleur
  "Controler not accept query order", // les ordres de requête ne sont pas acceptés par ce controleur
  "Value is not correct" // la valeur indiquée est incorrecte
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
  char escapeCar = '"';
  String car = "" ;
  car += "\\" ;
  car += escapeCar ;
  text.replace("\"",car);//échapper les guillements
  const char* text2char = string2char(text);
  Serial.println (text);

  DynamicJsonDocument doc(1024);
  //StaticJsonDocument<2048> doc;
  Serial.println(doc.capacity());
  //deserializeJson(doc, text2char);
  DeserializationError err = deserializeJson(doc, text);
  if (err) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(err.c_str());
    }
  JsonObject obj = doc.as<JsonObject>();
  for (JsonPair p : obj) {
    p.key(); // is a JsonString
    p.value(); // is a JsonVariant
    }
  if (obj.containsKey("params")) {Serial.println("order OK");}
}

void actionRelay(int relayIndex, String level){//action sur le relais indexé
  
}
char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
}
