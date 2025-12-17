#include "sensor.h"

// Seuil minimal pour considérer qu'un doigt est posé sur le capteur
const int seuil_doigt = 30; 

/**
 * Lit le capteur et applique un filtre médian pour éliminer les parasites.
 * Le filtre médian est excellent pour supprimer les pics de bruit isolés.
 */
int lireCapteur() {
    int v[5]; // Tableau pour stocker 5 mesures successives

    // 1. ACQUISITION : On prend 5 échantillons très rapides
    for (int i = 0; i < 5; i++) {
        v[i] = analogRead(SENSOR_PIN); // Lecture de la valeur brute du capteur
        delay(2); // Petite pause pour laisser le convertisseur se stabiliser
    }

    // 2. TRI : On classe les 5 valeurs de la plus petite à la plus grande (Tri à bulles)
    // C'est nécessaire pour trouver la valeur centrale (la médiane)
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (v[j] < v[i]) {
                // On échange les places si la valeur suivante est plus petite
                int tmp = v[i]; 
                v[i] = v[j]; 
                v[j] = tmp;
            }
        }
    }

    // 3. RÉSULTAT : On retourne la valeur au milieu du tableau trié (index 2)
    // Cela permet d'ignorer les deux valeurs les plus basses et les deux plus hautes
    return v[2]; 
}

/**
 * Vérifie si la pression ou le signal est suffisant pour confirmer 
 * la présence d'un doigt sur le capteur.
 * @param valeur La valeur filtrée issue de lireCapteur()
 */
bool doigtPresent(int valeur) {
    // Si la valeur dépasse le seuil, retourne TRUE (vrai), sinon FALSE (faux)
    return valeur >= seuil_doigt;
}