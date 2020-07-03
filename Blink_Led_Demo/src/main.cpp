#include <Arduino.h>

#define LED	13

void setup () {
	Serial.begin(115200);
	Serial.println (".....");
	pinMode(LED,OUTPUT);
}

void loop () {
	digitalWrite(LED, LOW);
	Serial.println("Led Off");
	delay (500);
	digitalWrite(LED, HIGH);
	Serial.println("Led On");
	delay (500);
}
