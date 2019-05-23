/******************************************
   The unmodified version of this code is originally
   by kakopappa and can be found at http://bit.ly/2kKQiRg.

   This version of the code has been modified by Charles Gantt
   and requires five additional files which can be found at http://bit.ly/2lRDwAJ

   Find out more about this project on Charles' website
   http://www.themakersworkbench.com

   Follow Charles and TheMakersWorkbench on the following sites:
   YouTube: bit.ly/TMWB-on-YouTube
   TMWB on Facebook: bit.ly/TMWB-on-Facebook
   CJGanttMakes on Facebook: bit.ly/CJGanttMakes
   TMWB on Twitter: bit.ly/TMWB-on-Twitter
   Charles Gantt on Twitter: bit.ly/CJGanttOnTwitter
   Instructables: bit.ly/CJGanttOnInstructables
   TMWB Website: bit.ly/TheMakersWorkbench
   Charles Gantt on Element14: bit.ly/CJGantt-On-E14
   Charles Gantt on GitHub: bit.ly/CJGantt-on-Github
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "Switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>

// prototypes
boolean connectWifi();

//on/off callbacks
void woahZoneOneOn();
void woahZoneOneOff();
void woahZoneTwoOn();
void woahZoneTwoOff();
void woahZoneThreeOn();
void woahZoneThreeOff();
void woahZoneFourOn();
void woahZoneFourOff();
void woahAllZonesOn();
void woahAllZonesOff();

// Change this before you flash
const char* ssid = "dd-wrt";
const char* password = "";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *woahZoneOne = NULL;
Switch *woahZoneTwo = NULL;
Switch *woahZoneThree = NULL;
Switch *woahZoneFour = NULL;
Switch *woahAllZones = NULL;

int relayOne = 14;
int relayTwo = 12;
int relayThree = 13;
int relayFour = 15;



void setup()
{
  Serial.begin(115200);

  // Initialise wifi connection
  wifiConnected = connectWifi();
  Serial.print("WiFi Connected");

  if (wifiConnected) {
    upnpBroadcastResponder.beginUdpMulticast();


    // Define your switches here. Max 14
    // Format: Alexa invocation name, local port no, on callback, off callback
    woahZoneOne = new Switch("Plant One", 80, woahZoneOneOn, woahZoneOneOff);
    woahZoneTwo = new Switch("Plant Two", 81, woahZoneTwoOn, woahZoneTwoOff);
    woahZoneThree = new Switch("Plant Three", 82, woahZoneThreeOn, woahZoneThreeOff);
    woahZoneFour = new Switch("Plants Four", 83, woahZoneFourOn, woahZoneFourOff);
    woahAllZones = new Switch("All Plants", 84, woahAllZonesOn, woahAllZonesOff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*woahZoneOne);
    upnpBroadcastResponder.addDevice(*woahZoneTwo);
    upnpBroadcastResponder.addDevice(*woahZoneThree);
    upnpBroadcastResponder.addDevice(*woahZoneFour);
    upnpBroadcastResponder.addDevice(*woahAllZones);

    //Set relay pins to outputs
    pinMode(relayOne, OUTPUT);
    pinMode(relayTwo, OUTPUT);
    pinMode(relayThree, OUTPUT);
    pinMode(relayFour, OUTPUT);
 

 
    //Set each relay pin to HIGH this display status messagefor each relay
    digitalWrite(relayOne, HIGH);   // sets relayOne on
    digitalWrite(relayTwo, HIGH);   // sets relayOne on
    digitalWrite(relayThree, HIGH);   // sets relayOne on
    digitalWrite(relayFour, HIGH);   // sets relayOne on
    //Create system initialized message

  }
}

void loop()
{
  if (wifiConnected) {
    upnpBroadcastResponder.serverLoop();
    woahZoneOne->serverLoop();
    woahZoneTwo->serverLoop();
    woahZoneThree->serverLoop();
    woahZoneFour->serverLoop();
    woahAllZones->serverLoop();
  }
}

void woahZoneOneOn() {
  Serial.print("Plant 1");
  digitalWrite(relayOne, LOW); // sets relayOne on
}

void woahZoneOneOff() {
  Serial.print("Plant 1 Watered");
  digitalWrite(relayOne, HIGH);   // sets relayOne off
}

void woahZoneTwoOn() {
  Serial.print("Plant 2");
  digitalWrite(relayTwo, LOW);   // sets relayTwo on
}

void woahZoneTwoOff() {
  Serial.print("Plant 2 Watered");
  digitalWrite(relayTwo, HIGH);   // sets relayTwo Off
}

void woahZoneThreeOn() {
  Serial.print("Plant 3");
  digitalWrite(relayThree, LOW);   // sets relayThree on
}

void woahZoneThreeOff() {
  Serial.print("Plant 3 Watered");
  digitalWrite(relayThree, HIGH);   // sets relayThree off
}

void woahZoneFourOn() {
  Serial.print("Plant 4");
  digitalWrite(relayFour, LOW);   // sets relayFour on
}

void woahZoneFourOff() {
  Serial.print("Plant 4 Watered");
  digitalWrite(relayFour, HIGH);   // sets relayFour off
}

void woahAllZonesOn() {
  Serial.print("Switch 1 turn on ...");
  digitalWrite(relayOne, LOW);   
  Serial.print("Switch 2 turn on ...");
  digitalWrite(relayTwo, LOW);   
  Serial.print("Socket 1 turn on ...");
  digitalWrite(relayThree, LOW);   
  Serial.print("Socket 2 turn on ...");
  digitalWrite(relayFour, LOW);   
}

void woahAllZonesOff() {
  Serial.print("Switch 1 turn off ...");
  digitalWrite(relayOne, HIGH); 
  Serial.print("Switch 2 turn off ...");
  digitalWrite(relayTwo, HIGH);  
  Serial.print("Socket 1 turn off ...");
  digitalWrite(relayThree, HIGH);   
  Serial.print("Socket 2 turn off ...");
  digitalWrite(relayFour, HIGH);   
}

// connect to wifi – returns true if successful or false if not
  boolean connectWifi() {
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }

  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}
