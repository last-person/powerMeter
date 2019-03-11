
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h> 

#include "index.h" //Our HTML webpage contents

//SSID and Password for ESP8266
const char* ssid = "Power Meter";
const char* password = "" ;
const String s = MAIN_page; //Read HTML page

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
  if ( server.hasArg ("userInput")){
    handlePostForm();
    Serial.println("new path worked");
    }
  else {
    server.send(200, "text/html", s); //Send web page
    }
}

void handlePostForm(){
  String userInput = server.arg("userInput");
  Serial.println("Text received. Contents: ");
  Serial.println(userInput); 
  server.send(200, "text/html", s);
}
void handleNotFound() {
  handleRoot();
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("Setting UP...");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
 
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
  
  server.on("/", handleRoot);      //Which routine to handle at root location
  //server.on("/postForm", handlePostForm); //Handle a form that's posted

  //start DNS
  if (!MDNS.begin("powermeter")) {             // Start the mDNS responder for esp8266.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.println("mDNS responder started");


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
