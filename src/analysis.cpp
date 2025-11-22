#include "analysis.h"
#include "bpm.h"

void analyserStress() {
    float moyenne = getMeanBPM();
    Serial.print("Moyenne BPM sur 30s : "); Serial.println(moyenne);

    if (moyenne > 100) Serial.println(">>> STRESS DETECTE <<<");
    else Serial.println("Etat : CALME");

    Serial.println("-------------------------");
    resetBPM();
}
