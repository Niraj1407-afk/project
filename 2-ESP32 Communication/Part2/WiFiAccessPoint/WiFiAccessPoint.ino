/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED_BUILTIN on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <Arduino.h>
#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 2  // Set the GPIO pin where you connected your test LED_BUILTIN or comment this line out if your dev board has a built-in LED_BUILTIN
#endif

// Set these to your desired credentials.
const char *ssid = "CDACESD";
const char *password = "1234567890";

NetworkServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  // a valid password must have more than 7 characters
  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation faiLED_BUILTIN.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  static bool blinked = false;

  if (WiFi.softAPgetStationNum() > 0) {
    if (!blinked) {
    digitalWrite(LED_BUILTIN ,HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN,LOW);
    delay(200);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN,LOW);
    blinked = true; 
    }
  } else {
    blinked = false; 
  }
  
  NetworkClient client = server.accept(); // listen for incoming clients   
  if (client) {                     // if you get a client,
    
            int sentval = random(10,99);
            Serial.print("Sending int Number to Station:- ");
            Serial.println(sentval);
    
            client.println(sentval);
            
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
