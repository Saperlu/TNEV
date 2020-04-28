// Toutes les valeurs sont à teste / vérifier / modifier lors de la phase de prototypage

#ifndef RESSOURCES
#define RESSOURCES

#include <Servo.h>

#define STOP 0
#define CATAPULTE 1
#define SLALOM 2


#define MARGE 40
#define COEF 0,5
#define VITESSEMAX 1024
#define TEMPS_AVANC 500

#define PUISSANCE_CHARG 1024
#define TEMPS_CHARG 2000
#define PUISSANCE_ENVOI 1024
#define TEMPS_ENVOI 2000

#define ANGLE_ENCL 10
#define ANGLE_DECL 20
#endif

Servo myServo;
int angle = 0;

const int bouState1 = 0,
          bouState2 = 1,
          phoGauche = 2,
          phoDroite = 3,

          pinRouGau1 = 4,
          pinRouGau2 = 5,
          pinPuiRouGau = 0,

          pinRouDroi1 = 6,
          pinRouDroi2 = 7,
          pinPuiRouDroi = 1,

// Catapulte à revoir
          pinServo = 3,

          pinLed = 8;

// Lis les valeurs de bouton 1 et 2
// Bouton 1 : Alternance STOP / SLALOM
// Bouton 2 : CATAPULTE
// Passage de STOP à SLALOM : La led clignote 2 sec avant de démarrer
int getMode(int mode, int *previousState1, int *previousState2) {
  int state1 = digitalRead(bouState1);
  int state2 = digitalRead(bouState2);

  if (state1 != *previousState1 && state1 == HIGH) {
    if (mode == STOP) {
      mode = SLALOM;
      for (size_t i = 0; i < 4; i++) {
        digitalWrite(pinLed, HIGH);
        delay(250);
        digitalWrite(pinLed, LOW);
        delay(250);
      }
    } else {
      mode = STOP;
    }
  }
  if (state2 != previousState2 && state2 == HIGH) {
    mode = CATAPULTE;
  }

  *previousState1 = state1;
  *previousState2 = state2;
  return mode;
}

int setLedState(int previousStateLed, int mode) {
  int stateLed;
  if (mode == CATAPULTE) { // Eteinte
    stateLed = LOW;
  } else if (mode == SLALOM) { // Clignote
    if (previousStateLed == HIGH) {
      stateLed = LOW;
    } else {
      stateLed = HIGH;
    }
  } else { // Allumée
    stateLed = HIGH;
  }
  digitalWrite(pinLed, stateLed);
  return stateLed;
}

void stop() {
  delay(1000);
}

void initServo() {
  myServo.attach(pinServo);
}

// Coince/Relache la ficelle avec le servo
void alternerCatapulte() {
  if (angle == ANGLE_DECL) {
    angle = ANGLE_ENCL;
    myServo.write(angle);
  } else {
    angle = ANGLE_DECL;
    myServo.write(angle);
  }
}



void roueGauche(int vitesse) {
  digitalWrite(pinRouGau1, HIGH);
  digitalWrite(pinRouGau2, LOW);
  analogWrite(pinPuiRouGau, vitesse);
}

void roueDroite(int vitesse) {
  digitalWrite(pinRouDroi1, HIGH);
  digitalWrite(pinRouDroi2, LOW);
  analogWrite(pinPuiRouDroi, vitesse);
}

// Lis valeurs des photorésistances et en déduis la direction à prendre
// Renvoie 0 pour tout droit, un nombre positif pour droite, négatif pour gauche
// Plus le nombre est grand, plus il faut tourner
int getDirection() {
  int lumGauche = analogRead(phoGauche);
  int lumDroite = analogRead(phoDroite);
  int retour = 0;

  if (lumGauche - lumDroite > MARGE) { // ligne est à droite
    retour = lumGauche - lumDroite; // différence positive
  } else if (lumDroite - lumGauche > MARGE) { // ligne est à gauche
    retour = lumGauche - lumDroite; // différence négative
  } else { // ligne est au milieu
    retour = 0;
  }
  return retour;
}

// Rêgle la puissance des moteurs Roues pour avancer selon la direction transmise
void avancer(int direction) {
  direction *= COEF;
  if (direction < 0) { // ligne à gauche
    roueGauche(VITESSEMAX - direction);
    roueDroite(VITESSEMAX);
  } else if (direction > 0) { // ligne à droite
    roueGauche(VITESSEMAX);
    roueDroite(VITESSEMAX - direction);
  } else {
    roueGauche(VITESSEMAX);
    roueDroite(VITESSEMAX);
  }
  delay(TEMPS_AVANC);
}
