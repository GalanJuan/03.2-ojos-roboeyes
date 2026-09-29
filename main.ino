// ============================================
// ARCHIVO: main.ino
// RESPONSABILIDAD: Orquestar el arranque, la máquina de estados (FSM) y el ciclo principal.
// ============================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logboot.h"
#include "eyes.h"         
#include "debug_serial.h" 


bool bootComplete = false;      
unsigned long bootTime = 0; 

void setup() {

    Serial.begin(115200);
    delay(500);

    Serial.println(F("[BOOT] sistema de ojos OLED"));


    initI2C();
    scanI2C();
    testI2CDevice();
    initDisplay();


    showLogo();   
    testDisplay();


    initEyes();

   
    bootTime = millis();
}

void loop() {
  
    if (!bootComplete) {
        if (millis() - bootTime >= 3000) {
            bootComplete = true; 

            Serial.println(F("[FSM] BOOT -> RUN"));
            

        } else {
            showLogo();
        }
        
        return;
    }

 
    debugSerialTick(); 
    updateEyes(); 
}