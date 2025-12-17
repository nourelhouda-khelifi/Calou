#include "analysis.h"


const char* analyserStress() {

    // --- 1. GESTION DE L'ACTIVATION ---
    // Détecte si un des bouttons est appuyé
    updateActivateBouton();
   
    // Si le système n'est pas activé, on nettoie l'interface
    if(!activationOn) {
        displaydeactivate(); 
        return "INACTIF";         // On arrête la fonction ici
    }

    if(sportOn){
        return "SPORT"; // Si le mode sport est activé, on arrête la fonction ici
    }

    // --- 2. TRAITEMENT DES DONNÉES ---
    // Récupère la moyenne calculée des battements par minute (BPM)
    float moyenne = getMeanBPM();

    // Envoi de la donnée brute vers le moniteur série pour le débogage 
    Serial.print("Moyenne BPM sur 30s : ");
    Serial.println(moyenne);
    // Mise à jour de la variable globale du bpm pour l'affichage écran
    bpm_affiche = int(moyenne);


    // --- 3. LOGIQUE DE DÉCISION ---
    const char* etat;
    // Seuil de diagnostic : 100 BPM est ici la limite entre calme et stress
    if (moyenne > 100) {
        etat = "STRESS";
        Serial.println(">>> STRESS DETECTE <<<");
    } else {
        etat = "CALME";
        Serial.println("Etat : CALME");
    }
    Serial.println("-------------------------");

    // --- 4. RÉINITIALISATION ET SORTIE ---
    // Vide le tableau/historique des BPM pour préparer la prochaine mesure de 30s
    resetBPM(); 
    // Retourne le résultat (utilisé par la fonction appelante pour l'affichage)
    return etat; 
}