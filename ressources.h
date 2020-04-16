#ifndef RESSOURCES
#define RESSOURCES
#define STOP 0
#define CATAPULTE 1
#define SLALOM 2

#endif



int getMode() {
  return 0;
}

void stop() {
  delay(1000);
}

// Tire sur la ficelle avec le moteur Cata
void chargerCatapulte() {

}

// Relache la ficelle avec le moteur Cata
void envoyerCatapulte() {

}

// Lis valeurs des photorésistances et en déduis la direction à prendre
int getDirection() {
  return 0;
}

// Rêgle la puissance des moteurs Roues pour avance selon la direction transmise
void avancer(int direction) {

}
