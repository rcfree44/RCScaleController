#include "FastLED.h"

// Definition du n° de fils de commande des LEDs (sortie de l'Arduino)
#define LED_DATA_PIN 3

// Definition des LEDs
enum
{
  LED_AVG_E, // Avant chauche extérieure
  LED_AVG_I, // Avant chauche intérieure
  LED_AVD_I, // Avant droite  intérieure
  LED_AVD_E, // Avant droite  extérieure
  LED_ARD,   // Arriere droite
  LED_ARG,   // Arriere gauche
  LED_TOTAL  // Total du nombre de LEDs (6)
};
CRGB leds[LED_TOTAL];

// Definition des modes de fonctionnement des LEDs (ici pour une voiture RC)
typedef enum 
{
  CLIGNOTANTS_SANS,
  CLIGNOTANTS_DROIT,
  CLIGNOTANTS_GAUCHE,
  CLIGNOTANTS_WARNING
}Clignotants_e;
Clignotants_e Clignotants;

typedef enum
{
  FEUX_SANS,
  FEUX_CROISEMENT,
  FEUX_ROUTE,
} Feux_e;
Feux_e Feux;

// Fonction de gestion des Leds de la voiture RC (coeur du programme)
void Maj_Eclairage()
{
  // Etat initial : toutes Leds eteintes
  for(int i=0; i<LED_TOTAL; ++i)
  {
    leds[i] = CRGB::Black;
  }
  
  // Feux
  if (FEUX_CROISEMENT == Feux)
  {
    leds[LED_AVG_E] = 0x404040; //CRGB::Grey;
    leds[LED_AVG_I] = 0x404040; //CRGB::Grey;
    leds[LED_AVD_I] = 0x404040; //CRGB::Grey;
    leds[LED_AVD_E] = 0x404040; //CRGB::Grey;
    leds[LED_ARD]   = CRGB::Maroon;
    leds[LED_ARG]   = CRGB::Maroon;
  }
  if (FEUX_ROUTE == Feux)
  {
    leds[LED_AVG_E] = CRGB::White;
    leds[LED_AVG_I] = CRGB::White;
    leds[LED_AVD_I] = CRGB::White;
    leds[LED_AVD_E] = CRGB::White;
    leds[LED_ARD]   = CRGB::Maroon;
    leds[LED_ARG]   = CRGB::Maroon;
  }
  
  // Clignotants

  
  // Mise à jour finale des Leds
  FastLED.show();
}


// Point d'initalisation du programme (appelé à la mise sous tension de l'Arduino)
void setup() 
{ 
  // Attente de sécurité avant mise à route des LEDs
  // Ce temps sert à confirmer que les alimentions sont stables,
  // et correspond bien à une connexion franche de la batterie
  delay(3000); // 3s
  
  // Init des LEDs de type "WS2812B" 
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, LED_TOTAL);
  
  // Init des variables du programe
  Feux = FEUX_SANS;
  Clignotants = CLIGNOTANTS_SANS; 
}

// Boucle de traitement périodique (appelé en-boucle jusqu'à l'arrêt de l'Arduino)
void loop() 
{ 
  // 
  Feux = FEUX_SANS;
  Clignotants = CLIGNOTANTS_SANS;
  Maj_Eclairage();
  delay(5000);
  
  // 
  Feux = FEUX_CROISEMENT;
  Clignotants = CLIGNOTANTS_SANS;
  Maj_Eclairage();
  delay(5000);

  // 
  Feux = FEUX_ROUTE;
  Clignotants = CLIGNOTANTS_SANS;
  Maj_Eclairage();
  delay(5000);
  
#if 0
  // 
  Feux = FEUX_CROISEMENT;
  Clignotants = CLIGNOTANTS_DROIT;
  Maj_Eclairage();
  delay(5000);

  // 
  Feux = FEUX_CROISEMENT;
  Clignotants = CLIGNOTANTS_GAUCHE;
  Maj_Eclairage();
  delay(5000);
  
  // 
  Feux = FEUX_CROISEMENT;
  Clignotants = CLIGNOTANTS_WARNING;
  Maj_Eclairage();
  delay(5000);
#endif
}
