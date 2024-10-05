#define DEBUG 0

#define LEDPIN1 25                // CHANGE THIS TO MATCH THE PIN YOUR LED STRIP IS CONNECTED TO (PODIUM)
#define LEDPIN2 26                // CHANGE THIS TO MATCH THE PIN YOUR LED STRIP IS CONNECTED TO (STAGE)

#define TRIGGERSWITCH 16          // CHANGE THIS TO MATCH THE PIN YOUR TRIGGER SWITCH IS CONNECTED TO 
#define RESETSWITCH   17          // CHANGE THIS TO MATCH THE PIN YOUR RESET SWITCH IS CONNECTED TO

#define STRIP_1_COUNT 17          // CHANGE THIS TO MATCH THE NUMBER OF LEDS ON YOUR STRIP  (PODIUM)
#define STRIP_2_COUNT 50          // CHANGE THIS TO MATCH THE NUMBER OF LEDS ON YOUR STRIP  (STAGE)

#define SPEED          50         // ADJUST THIS TO CHANGE SPEED OF ANIMATION 1 IS FASTER 500 IS SLOWER 
#define DEBOUNCE_DELAY 500        

#define WHITE   255, 255, 255
#define RED     255, 0,   0
#define GREEN   0,   255, 0
#define BLUE    0,   0,   255
#define OFF     0,   0,   0


#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(STRIP_1_COUNT, LEDPIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(STRIP_2_COUNT, LEDPIN2, NEO_GRB + NEO_KHZ800);

uint32_t lastUpdateMillis = 0;  


void ioSetup() {
  pinMode(TRIGGERSWITCH, INPUT_PULLUP);
  pinMode(RESETSWITCH, INPUT_PULLUP);

  strip1.begin(); strip1.clear(); strip1.show();
  strip2.begin(); strip2.clear(); strip2.show();
}

void triggerStrip(){
  for (int i = 0; i < STRIP_1_COUNT; i++){
    strip1.setPixelColor(i, WHITE);
    strip1.show();
    delay(SPEED);
  }
  for (int i = 0; i < STRIP_2_COUNT/2; i++){
    strip2.setPixelColor(i, WHITE);  strip2.setPixelColor(STRIP_2_COUNT-i, WHITE);
    strip2.show();
    if (DEBUG){ Serial.println( "i:" + String(i) + "\t STRIP_2_COUNT-i: " + String(STRIP_2_COUNT-i));}
    delay(SPEED);
  }
}

void resetStrip(){
  for (int i = 0; i < STRIP_1_COUNT; i++){
    strip1.setPixelColor(i, OFF);
  }
  for (int i = 0; i < STRIP_2_COUNT; i++){
    strip2.setPixelColor(i, OFF);
  } 
  strip1.show(); strip2.show();
}

void readSwitches(){
  if (digitalRead(TRIGGERSWITCH) == LOW){
    if (millis() - lastUpdateMillis < DEBOUNCE_DELAY ) {return;}
    lastUpdateMillis = millis();
    triggerStrip();
  }
  if (digitalRead(RESETSWITCH) == LOW){
    if (millis() - lastUpdateMillis < DEBOUNCE_DELAY ) {return;}
    lastUpdateMillis = millis();
    resetStrip();
  }
}

void setup() {
  Serial.begin(9600);
  ioSetup();
}

void loop() {
  readSwitches();
}
