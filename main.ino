#include "ressources.h"

int mode = STOP;
int state1 = LOW, state2 = LOW;
int direction = 0;
int LedState = LOW;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinLed, OUTPUT);
  pinMode(pinRouGau1, OUTPUT);
  pinMode(pinRouGau2, OUTPUT);
  pinMode(pinRouDroi1, OUTPUT);
  pinMode(pinRouDroi2, OUTPUT);

  pinMode(bouState1, INPUT);
  pinMode(bouState2, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  mode = getMode(mode, &state1, &state2);
  LedState = setLedState(LedState, mode);

  if (mode == CATAPULTE) {
    chargerCatapulte();
    envoyerCatapulte();
    mode = STOP;

  } else if (mode == SLALOM) {
    direction = getDirection();
    avancer(direction);
  } else {
    stop();
  }
}
