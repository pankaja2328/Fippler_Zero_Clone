#include <Arduino.h>
#include <WiFi.h>
#include "MenuUI.h"
#include "ApScan.h"


void setup() {
    Serial.begin(115200);
    delay(1000); 

    WiFi.mode(WIFI_STA);     
    WiFi.disconnect(true);  
    delay(100);
    menuSetup();
}

void loop() {
    menuLoop();
}

