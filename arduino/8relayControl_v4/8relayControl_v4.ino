// This is a sample file from the book "Mastering ArduinoJson"
// https://arduinojson.org/book/
// Copyright 2017-2019 Benoit Blanchon
//
// This example shows how to recursively analyze the content of an unknown
// JSON document.
//
// Paste a JSON document in the Serial Monitor, and the program will display
// everything it knows about this document

#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
  while (!Serial)
    continue;

  Serial.setTimeout(5000);
}

void loop() {
  Serial.println(F("Flushing Serial input buffer..."));
  while (Serial.available())
    Serial.read();

  Serial.println(F("Waiting for a JSON document in Serial..."));
  while (!Serial.available())
    delay(50);

  Serial.println(F("Parsing..."));
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, Serial);

  Serial.print(F("Parsing... "));
  Serial.println(error.c_str());

  if (!error) {
    dump(doc.as<JsonVariant>(), 0);
  }

  Serial.println();
}

void indent(int nesting) {
  for (int i = 0; i < nesting; i++)
    Serial.print("  ");
}

void dump(JsonVariant variant, int nesting) {
  if (variant.is<bool>())
    dump(variant.as<bool>(), nesting);
  else if (variant.is<long>())
    dump(variant.as<long>(), nesting);
  else if (variant.is<double>())
    dump(variant.as<double>(), nesting);
  else if (variant.is<char *>())
    dump(variant.as<char *>(), nesting);
  else if (variant.is<JsonObject>())
    dump(variant.as<JsonObject>(), nesting);
  else if (variant.is<JsonArray>())
    dump(variant.as<JsonArray>(), nesting);
  else {
    indent(nesting);
    Serial.println(F("null"));
  }
}

void dump(bool value, int nesting) {
  indent(nesting);
  Serial.print(F("Bool: "));
  Serial.print(value);
  Serial.println('"');
}

void dump(long value, int nesting) {
  indent(nesting);
  Serial.print(F("Integer: "));
  Serial.println(value);
}

void dump(double value, int nesting) {
  indent(nesting);
  Serial.print(F("Float: "));
  Serial.println(value);
}

void dump(const char *str, int nesting) {
  indent(nesting);
  Serial.print(F("String: \""));
  Serial.print(str);
  Serial.println('"');
}

void dump(JsonObject obj, int nesting) {
  indent(nesting);
  Serial.print(F("Object (size = "));
  Serial.print(obj.size());
  Serial.println("):");

  // Iterate though all key-value pairs
  for (JsonPair kvp : obj) {
    // Print the key
    indent(nesting + 1);
    Serial.print("[\"");
    Serial.print(kvp.key().c_str());
    Serial.println("\"]");

    // Print the value
    dump(kvp.value(), nesting + 2); // <- RECURSION
  }
}

void dump(JsonArray arr, int nesting) {
  indent(nesting);
  Serial.print(F("Array (size = "));
  Serial.print(arr.size());
  Serial.println(")");

  int index = 0;
  // Iterate though all elements
  for (JsonVariant value : arr) {
    // Print the index
    indent(nesting + 1);
    Serial.print("[");
    Serial.print(index);
    Serial.println("]");

    // Print the value
    dump(value, nesting + 2); // <- RECURSION

    index++;
  }
}
