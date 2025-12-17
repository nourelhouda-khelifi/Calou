#include "bpm.h"

// --- CONFIGURATION ET PARAMÈTRES ---

const int seuil_pic = 20;     // Différence minimale par rapport à la moyenne pour détecter un battement
const int bpm_min = 50;       // Limite basse pour filtrer les erreurs de lecture
const int bpm_max = 150;      // Limite haute pour filtrer les erreurs de lecture

unsigned long lastBeat = 0;   // Stocke le temps (ms) du dernier battement détecté
float baseline = 0;           // Moyenne flottante du signal pour s'adapter aux variations

int bpm_values[200];          // Tableau pour stocker les mesures de BPM (le buffer)
int bpm_index = 0;            // Position actuelle dans le tableau (compteur de mesures)

/**
 * Détecte un battement de cœur à partir d'une valeur brute du capteur.
 * @param valeur La donnée brute reçue par le capteur (ex: phototransistor)
 */
int detecterBPM(int valeur) {
    updateActivateBouton();
    // Arrêt si le bouton est sur OFF
    if(!activationOn){
        displaydeactivate();
        return 0; 
    }

    // --- FILTRAGE DU SIGNAL (Moyenne exponentielle) ---
    // On calcule une "baseline" (ligne de base) pour suivre le niveau moyen du signal
    // Cela permet au capteur de s'adapter si la luminosité ambiante change.
    baseline = baseline * 0.9 + valeur * 0.1; 

    // --- DÉTECTION DU PIC ---
    // Si la valeur actuelle dépasse la moyenne + le seuil, c'est peut-être un battement
    if (valeur > baseline + seuil_pic) {

        unsigned long now = millis(); // Temps actuel en millisecondes

        // Anti-rebond (Debounce) : On ignore tout signal si le dernier battement
        // date de moins de 300ms (un cœur ne bat pas à 200+ BPM en repos)
        if (now - lastBeat > 300) { 

            // Calcul du BPM : 60 000 ms divisé par le temps entre deux battements
            int bpm = 60000 / (now - lastBeat);

            lastBeat = now; // On enregistre l'heure de ce nouveau battement

            // Vérification de la cohérence du résultat
            if (bpm >= bpm_min && bpm <= bpm_max) {
                // On stocke le BPM dans le tableau pour faire la moyenne plus tard
                bpm_values[bpm_index++] = bpm;

                Serial.print("BPM : ");
                Serial.println(bpm);

                return bpm;   
            }
        }
    }

    return 0; // Pas de battement détecté sur cette lecture
}

/**
 * Retourne le nombre de battements enregistrés depuis le dernier reset
 */
int getBPMCount() {
    return bpm_index;
}

/**
 * Calcule la moyenne arithmétique de tous les BPM stockés dans le tableau
 */
float getMeanBPM() {
    if (bpm_index == 0) return 0; // Éviter la division par zéro

    float somme = 0;
    // On additionne chaque valeur stockée
    for (int i = 0; i < bpm_index; i++) {
        somme += bpm_values[i];
    }

    return somme / bpm_index; // Retourne la moyenne réelle (ex: 72.5)
}

/**
 * Réinitialise le compteur pour démarrer une nouvelle session de mesure
 */
void resetBPM() {
    bpm_index = 0; // On ne vide pas le tableau physiquement, on remet juste l'index au début
}