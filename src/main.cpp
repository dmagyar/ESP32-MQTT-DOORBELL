#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "local.h"

void setup() {
  	Serial.begin(115200);
  	Serial.println("[BOOTED]");
	Serial.println();	
	WifiMqttSetup();
	while (wifiready == 0) {
		Serial.println("Waiting for wifi...");
		delay(1000);
	}
	OTAsetup();
	WebSetup();
	AudioSetup();
}

void loop() {
	ArduinoOTA.handle();
	AudioLoop();
	yield();
}
