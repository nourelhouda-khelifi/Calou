#include "analysis.h"
#include "bpm.h"
#include <Arduino.h>
#include "./display/display_accueil.h"
#include "./display/calou_active.h"
#include <SeeedOLED.h>

const char* analyserStress() {
    updateActivateBouton();
    if(!activationOn){
        SeeedOled.clearDisplay();
        displaydeactivate();
        return;
    }
    float moyenne = getMeanBPM();

    Serial.print("Moyenne BPM sur 30s : ");
    Serial.println(moyenne);
    bpm_affiche = int(moyenne);

    const char* etat;

    if (moyenne > 100) {
        etat = "STRESS";
        Serial.println(">>> STRESS DETECTE <<<");
    } else {
        etat = "CALME";
        Serial.println("Etat : CALME");
    }

    Serial.println("-------------------------");

    resetBPM();   // on reset la liste des BPM

    return etat;  // IMPORTANT ! maintenant on retourne le texte
}
