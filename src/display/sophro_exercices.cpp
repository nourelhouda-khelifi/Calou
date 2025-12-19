#include "sophro_exercices.h"

/**
 * Affiche un message d'urgence si le stress est détecté.
 */
void displayAlerte() {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Vous etes stress!");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("Respirons ensemble!");
    
    // Animation visuelle simple (points verticaux)
    for(int i=0;i<3;i++){
        SeeedOled.setTextXY(3+i,2);
        SeeedOled.putString("O");
    }
}


// RESET DE L'AFFICHAGE
void commencer_affichage() {
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
}


// --- GESTION DU COMPTE À REBOURS ---
void afficher_countdown() {
    commencer_affichage();
    
    // On affiche le titre de l'exercice
    SeeedOled.setTextXY(1, 2);
    SeeedOled.putString("EXERCICE");
    SeeedOled.setTextXY(2, 3);
    SeeedOled.putString("SORPHO");
    
    if(!verifierActivation()) return; // Sécurité : si on éteint le bracelet, on sort
    if(sportOn) {return; }          // Si le mode sport est actif, on ne fait pas le countdown
    
    // Boucle de décompte : 3, 2, 1
    for(int i = 3; i >= 1; i--) {
        if(!verifierActivation()) return;
        if(sportOn) { return; }    
        
        commencer_affichage();
        SeeedOled.setTextXY(1, 2);
        SeeedOled.putString("EXERCICE");
        SeeedOled.setTextXY(2, 3);
        SeeedOled.putString("SORPHO");
        
        SeeedOled.setTextXY(4, 6);
        SeeedOled.putNumber(i); // Affiche le chiffre actuel
        
        delay(1000); // Attend 1 seconde entre chaque chiffre
    }
    
    commencer_affichage();
    SeeedOled.setTextXY(2, 3);
    SeeedOled.putString("C'est parti !");
    delay(1500);
}

// --- LOGIQUE DE L'EXERCICE ---
/**
 * Enchaîne 5 cycles de respiration avec une difficulté croissante.
 */
bool exercice_sophro_normal() {
    int tenir_secondes = 1000; // Durée d'apnée initiale (1s)
    
    for(int i = 0; i < 5; i++){
        // Si un cycle est interrompu par l'utilisateur, on arrête tout
        if(!cycle(tenir_secondes)){
            return false;
        }
        // On augmente la difficulté : on demande de tenir l'air plus longtemps à chaque fois
        if(i!=3){
            tenir_secondes += 1000;
        }
    }
    return true;
}

/**
 * Définit un cycle complet : Inspiration -> Rétention -> Expiration
 */
bool cycle(int tenir_secondes){
    if (inspirer_cycle() && tenir_cycle(tenir_secondes) && expirer_cycle()) {
        return true; 
    }
    return false; 
}

// --- PHASES DE RESPIRATION ANIMÉES ---

bool inspirer_cycle() {
    // Liste des images du ballon qui gonfle
    static const unsigned char* const frames[] = {
        ballon_etat1, ballon_etat2, ballon_etat3, 
        ballon_etat4, ballon_etat5, ballon_etat6
    };

    commencer_affichage();
    for (uint8_t i = 0; i < 6; i++) {
        if(!verifierActivation() || sportOn) return false;
        
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)frames[i], TAILLE_BITMAP); // Dessine le ballon
        SeeedOled.setTextXY(7, 5);
        SeeedOled.putString("Inspire");
        delay(500); // Vitesse de gonflement
    }
    return true;
}

bool tenir_cycle(int nb_ms) {
    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*)ballon_etat7, TAILLE_BITMAP); // Ballon plein
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Tiens");
    
    if(!verifierActivation() || sportOn) return false;
    delay(nb_ms); // Temps d'apnée (bloquer la respiration)
    return true;
}

bool expirer_cycle() {
    // Liste des images du ballon qui se dégonfle (ordre inverse)
    static const unsigned char* const frames[] = {
        ballon_etat6, ballon_etat5, ballon_etat4, 
        ballon_etat3, ballon_etat2, ballon_etat1
    };

    commencer_affichage();
    for (uint8_t i = 0; i < 6; i++) {
        if(!verifierActivation() || sportOn) return false;
        
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)frames[i], TAILLE_BITMAP);
        SeeedOled.setTextXY(7, 5);
        SeeedOled.putString("Souffle");
        delay(1000); // L'expiration est plus longue que l'inspiration (relaxant)
    }

    commencer_affichage();
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Bravo!");
    delay(2000);
    return true;
}

/**
 * Vérifie à chaque étape si le bouton ON/OFF a été basculé.
 * Permet de quitter l'exercice instantanément.
 */
bool verifierActivation(){
    updateActivateBouton();
    if(!activationOn){
        SeeedOled.clearDisplay();
        displaydeactivate();
    }
    return activationOn;
}