#include <Arduino.h>
#include "../include/sensor.h"
#include "../include/bpm.h"
#include "../include/analysis.h"
#include "../include/display_accueil.h"
#include "../include/display_alerte.h"
#include "../include/display_exercice.h"
#include "../include/sophro_exercices.h"
const int buttonPin = 12;        
const int sportPin = 13;  

const unsigned long debounceDelay = 50;
const unsigned long LONG_PRESS_DURATION = 3000;
unsigned long lastDebounceTimeActive = 0;
unsigned long pressStartTimeActive; 
int buttonActiveState = HIGH;
int lastButtonActiveState = HIGH;

unsigned long lastDebounceTimeSport = 0;
unsigned long pressStartTimeSport; 
int buttonSportState = HIGH;
int lastButtonSportState = HIGH;

bool activationOn = false;  
bool sportOn = false;

/**
 * @brief Reads a button, debounces it, and registers a press only if held for 3 seconds.
 * * @return true if a button state change (press OR release) occurred.
 */
bool updateActivateBouton() {
    bool stateChanged = false;
    int readingActive = digitalRead(buttonPin);
    int readingSport = digitalRead(sportPin);
    static bool buttonActiveRegistered = false; // Tracks if the long press was already handled
    static bool buttonSportRegistered = false; 
    // 1. Debounce Logic: Reset timer if the raw reading changes
    if (readingActive != lastButtonActiveState) {
        lastDebounceTimeActive = millis();
    }

    if (readingSport != lastButtonSportState) {
        lastDebounceTimeActive = millis();
    }

    // 2. Stable State Check: Check for debounced stability
    if ((millis() - lastDebounceTimeActive) > debounceDelay) {
        
        // --- A. If the stable state HAS changed ---
        if (readingActive != buttonActiveState) {
            
            // Update the stable state
            buttonActiveState = readingActive;
            stateChanged = true;
            
            if (buttonActiveState == LOW) {
                // Button just became stable LOW (pressed)
                // START tracking the press duration
                pressStartTimeActive = millis(); 
                Serial.println("Button stable LOW. Starting timer.");
            } else {
                // Button just became stable HIGH (released)
                Serial.println("Button released.");
                
                // Reset the registration flag when released
                buttonActiveRegistered = false; 
            }
        }

        if (readingSport != buttonSportState) {
            
            // Update the stable state
            buttonSportState = readingSport;
            stateChanged = true;
            
            if (buttonSportState == LOW) {
                // Button just became stable LOW (pressed)
                // START tracking the press duration
                pressStartTimeSport = millis(); 
                Serial.println("Button SPORT stable LOW. Starting timer.");
            } else {
                // Button just became stable HIGH (released)
                Serial.println("Button SPORT released.");
                
                // Reset the registration flag when released
                buttonSportRegistered = false; 
            }
        }

        // --- B. Long Press Check (Only run if button is currently pressed) ---
        if (buttonActiveState == LOW) {
            
            // Check if the required duration has passed AND the action hasn't run yet
            if ((millis() - pressStartTimeActive >= LONG_PRESS_DURATION) && !buttonActiveRegistered) {
                
                // --- ACTION: Long Press Registered! ---
                Serial.println("--- Long Press REGISTERED (3+ seconds)! ---");
                
                // 1. Toggle the application variable
                activationOn = !activationOn;
                
                // 2. Mark the action as done so it doesn't trigger again until released/re-pressed
                buttonActiveRegistered = true; 
                
                // Note: stateChanged remains false because the physical button state
                // (LOW) hasn't changed, only the *application* state has changed.
            }
        }

        if (buttonSportState == LOW) {
            
            // Check if the required duration has passed AND the action hasn't run yet
            if ((millis() - pressStartTimeSport >= LONG_PRESS_DURATION) && !buttonSportRegistered) {
                
                // --- ACTION: Long Press Registered! ---
                Serial.println("--- SPORT Long Press REGISTERED (3+ seconds)! ---");
                
                // 1. Toggle the application variable
                sportOn = !sportOn;
                
                // 2. Mark the action as done so it doesn't trigger again until released/re-pressed
                buttonSportRegistered = true; 
                
                // Note: stateChanged remains false because the physical button state
                // (LOW) hasn't changed, only the *application* state has changed.
            }
        }
    }

    // 3. Save the current raw reading for the next loop iteration
    lastButtonActiveState = readingActive;
    lastButtonSportState = readingSport;
    delay(50);
    return stateChanged;
}


