#include <Arduino.h>

//Fading Arduino RGB LED from one color to the other
//Common Anode - Attiny25/45/85

//Define the pins we will use with our rgb led
int redPin = 0;
int greenPin = 1;
int bluePin = 4;

//define that we are using common anode leds
#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int rgb[3];
//Arduino has no prebuilt function for hsi to rgb so we make one:
void hsi_to_rgb(float H, float S, float I) {
  int r, g, b;
  if (H > 360) {
    H = H - 360;
  }
  // Serial.println("H: "+String(H));
  H = fmod(H, 360); // cycle H around to 0-360 degrees
  H = 3.14159 * H / (float)180; // Convert to radians.
  S = S > 0 ? (S < 1 ? S : 1) : 0; // clamp S and I to interval [0,1]
  I = I > 0 ? (I < 1 ? I : 1) : 0;
  if (H < 2.09439) {
    r = 255 * I / 3 * (1 + S * cos(H) / cos(1.047196667 - H));
    g = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.047196667 - H)));
    b = 255 * I / 3 * (1 - S);
  } else if (H < 4.188787) {
    H = H - 2.09439;
    g = 255 * I / 3 * (1 + S * cos(H) / cos(1.047196667 - H));
    b = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.047196667 - H)));
    r = 255 * I / 3 * (1 - S);
  } else {
    H = H - 4.188787;
    b = 255 * I / 3 * (1 + S * cos(H) / cos(1.047196667 - H));
    r = 255 * I / 3 * (1 + S * (1 - cos(H) / cos(1.047196667 - H)));
    g = 255 * I / 3 * (1 - S);
  }
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;

}
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


///here we have our main loop and the for loop to shift color
void loop()
{
//the for loop counts to 360 and because its in our control loop it will run forever
// We will use int i to increment the actual desired color 
for (int i=0; i<=360;i++){
  hsi_to_rgb(i,1,1);
  setColor(rgb[0],rgb[1],rgb[2]);
  //Changing the delay() value in milliseconds will change how fast the
  //the light moves over the hue values 

  delay(100);		//Speed

  }


}

