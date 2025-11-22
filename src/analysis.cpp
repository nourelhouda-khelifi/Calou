#include "analysis.h"
#include "bpm.h"
#include <Arduino.h>

const char* analyserStress() {
    float moyenne = getMeanBPM();

    Serial.print("Moyenne BPM sur 30s : ");
    Serial.println(moyenne);

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
