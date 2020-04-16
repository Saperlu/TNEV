#include "ressources.h"

int mode = STOP;
int direction = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  mode = getMode();

  if (mode == CATAPULTE) {
    chargerCatapulte();
    envoyerCatapulte();

  } else if (mode == SLALOM) {
    direction = getDirection();
    avancer(direction);
  } else {
    stop();
  }
}
