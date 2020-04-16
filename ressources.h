// Toutes les valeurs sont à teste / vérifier / modifier lors de la phase de prototypage

#ifndef RESSOURCES
#define RESSOURCES
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
#endif

const int bouState1 = 0,
          bouState2 = 1,
          phoGauche = 2,
          phoDroite = 3,

          pinRouGau1 = 4,
          pinRouGau2 = 5,
          pinPuiRouGau = 0,

// Catapulte à revoir
          pinCata1  = pinRouGau1,
          pinCata2  = pinRouGau2,
          pinPuiCata  = pinPuiRouGau,

          pinRouDroi1 = 6,
          pinRouDroi2 = 7,
          pinPuiRouDroi = 1;


int getMode() {
  return 0;
}

void stop() {
  delay(1000);
}

// Tire sur la ficelle avec le moteur Cata
void chargerCatapulte() { // A REVOIR
  digitalWrite(pinCata1, HIGH);
  digitalWrite(pinCata2, LOW);
  analogWrite(pinPuiCata, PUISSANCE_CHARG);
  delay(TEMPS_CHARG);
}

// Relache la ficelle avec le moteur Cata
void envoyerCatapulte() { // A REVOIR
  digitalWrite(pinCata1, LOW);
  digitalWrite(pinCata2, LOW);
  analogWrite(pinPuiCata, PUISSANCE_ENVOI);
  delay(TEMPS_ENVOI);
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
