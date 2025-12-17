#include "display_accueil.h"

// Variables pour suivre l'état actuel de l'affichage et du mode sport
int currentDisplayState = 0;
int currentSportState = 0;

/**
 * Affiche l'écran d'accueil avec une animation fluide.
 * Cette fonction est appelée en boucle pour créer un effet de mouvement.
 */
void displayAccueil() {
    // static permet de garder la valeur en mémoire entre deux appels de la fonction
    static unsigned long lastAnimTime = 0; 
    static int animStep = 0;               // Étape de l'animation (0, 1, 2 ou 3)
    
    unsigned long currentTime = millis();
    
    // GESTION DU TIMING : On change d'image toutes les 800ms
    if(currentTime - lastAnimTime >= 800) {
        lastAnimTime = currentTime;
        animStep = (animStep + 1) % 4; // Alterne entre 0, 1, 2, 3 puis revient à 0
    }
    
    // --- LIGNE 0 : Titre animé ---
    // Change les symboles autour du nom "CALOU" pour attirer l'œil
    SeeedOled.setTextXY(0, 0);
    if(animStep == 0)      { SeeedOled.putString("* CALOU *"); } 
    else if(animStep == 1) { SeeedOled.putString("~ CALOU ~"); } 
    else if(animStep == 2) { SeeedOled.putString("o CALOU o"); } 
    else                   { SeeedOled.putString("+ CALOU +"); }
    
    // --- LIGNE 1 & 2 : Mise en page ---
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("================"); // Séparateur horizontal
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("                "); // Ligne vide pour aérer
    
    // --- LIGNE 3 & 4 : Messages rassurants ---
    SeeedOled.setTextXY(3, 1);
    SeeedOled.putString("Bonjour! :)");
    SeeedOled.setTextXY(4, 3);
    SeeedOled.putString("Je suis la");
    
    // --- LIGNE 5 : Mascotte animée ---
    // Simule un petit cœur qui bat (alternance entre <3 et ><)
    SeeedOled.setTextXY(5, 5);
    if(animStep < 2) {
        SeeedOled.putString("<3 <3"); // Cœur ouvert
    } else {
        SeeedOled.putString(">< ><"); // Cœur fermé
    }
    
    // --- LIGNE 6 : Instruction utilisateur ---
    SeeedOled.setTextXY(6, 2);
    SeeedOled.putString("Pose ton doigt");
    
    // --- LIGNE 7 : Pied de page ---
    // Petite barre de progression ou points de suspension animés
    SeeedOled.setTextXY(7, 1);
    if(animStep % 2 == 0) {
        SeeedOled.putString(". . . . .");
    } else {
        SeeedOled.putString("  . . .  ");
    }
}

/**
 * Éteint l'écran (utilisé quand le système est désactivé)
 */
void displaydeactivate(){
    SeeedOled.clearDisplay();
}

/**
 * Affiche une animation spéciale (Naruto) pour le mode sport.
 * Utilise des bitmaps (images pré-enregistrées en mémoire).
 */
void displaySport(){
    // On ne lance l'animation que si le mode sport est actif (état 1)
    if (currentSportState == 1) { 
        SeeedOled.setTextXY(0, 0);
        // Affiche successivement 3 images pour créer un mouvement (GIF)
        SeeedOled.drawBitmap((unsigned char*)naruto_1, TAILLE_BITMAP);
        delay(10); // Temps très court entre les images
        SeeedOled.drawBitmap((unsigned char*)naruto_2, TAILLE_BITMAP);
        delay(10);
        SeeedOled.drawBitmap((unsigned char*)naruto_3, TAILLE_BITMAP);
        delay(10);
    }
}

/**
 * Fonction réservée pour un futur usage (quand on quitte le mode sport)
 */
void displayNotSport(){
    // Actuellement vide
}