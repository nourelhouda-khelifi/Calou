#include <Arduino.h>
#include "../include/sensor.h"
#include "../include/bpm.h"
#include "../include/analysis.h"
#include "../include/display_accueil.h"
#include "../include/display_alerte.h"
#include "../include/display_exercice.h"
#include "../include/sophro_exercices.h"


const int buttonPin = 12;        // The pin the button is connected to
const int sportPin = 13;          // An output pin to show the result

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
const unsigned long LONG_PRESS_DURATION = 3000;
unsigned long pressStartTime; 

bool activationOn = false;  

/**
 * @brief Reads a button, debounces it, and registers a press only if held for 3 seconds.
 * * @return true if a button state change (press OR release) occurred.
 */
bool updateActivateBouton() {
    bool stateChanged = false;
    int reading = digitalRead(buttonPin);
    static bool buttonIsRegistered = false; // Tracks if the long press was already handled

    // 1. Debounce Logic: Reset timer if the raw reading changes
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    // 2. Stable State Check: Check for debounced stability
    if ((millis() - lastDebounceTime) > debounceDelay) {
        
        // --- A. If the stable state HAS changed ---
        if (reading != buttonState) {
            
            // Update the stable state
            buttonState = reading;
            stateChanged = true;
            
            if (buttonState == LOW) {
                // Button just became stable LOW (pressed)
                // START tracking the press duration
                pressStartTime = millis(); 
                Serial.println("Button stable LOW. Starting timer.");
            } else {
                // Button just became stable HIGH (released)
                Serial.println("Button released.");
                
                // Reset the registration flag when released
                buttonIsRegistered = false; 
            }
        }

        // --- B. Long Press Check (Only run if button is currently pressed) ---
        if (buttonState == LOW) {
            
            // Check if the required duration has passed AND the action hasn't run yet
            if ((millis() - pressStartTime >= LONG_PRESS_DURATION) && !buttonIsRegistered) {
                
                // --- ACTION: Long Press Registered! ---
                Serial.println("--- Long Press REGISTERED (3+ seconds)! ---");
                
                // 1. Toggle the application variable
                activationOn = !activationOn;
                
                // 2. Mark the action as done so it doesn't trigger again until released/re-pressed
                buttonIsRegistered = true; 
                
                // Note: stateChanged remains false because the physical button state
                // (LOW) hasn't changed, only the *application* state has changed.
            }
        }
    }

    // 3. Save the current raw reading for the next loop iteration
    lastButtonState = reading;
    delay(50);
    return stateChanged;
}
