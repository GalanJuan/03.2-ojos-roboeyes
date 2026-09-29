// ============================================
// ARCHIVO: main.ino
// RESPONSABILIDAD: Orquestar el arranque, la máquina de estados (FSM) y el ciclo principal.
// ============================================

#include "config.h"
#include "i2c_manager.h"
#include "display.h"
#include "logboot.h"

// Variables de estado global para la FSM de arranque
bool bootComplete = false;      
unsigned long bootTime = 0; 
void setup() {
    // Inicialización de la consola serial a la velocidad estándar del taller
    Serial.begin(115200);
    delay(500); // Pequeña pausa para estabilizar el puerto serie

    Serial.println(F("[BOOT] sistema de ojos OLED"));

    // Ejecución de las tareas iniciales del Reto 1
    initI2C();
    scanI2C();
    testI2CDevice();
    initDisplay();

    // Ejecución de las tareas iniciales del Reto 2
    showLogo();   
    testDisplay();

    // Guardamos el momento exacto en que inicia la ventana de conteo para el estado BOOT
    bootTime = millis();
}

void loop() {
    // Máquina de Estados Finitos (FSM): Estado BOOT (Mientras el arranque no esté completo)
    if (!bootComplete) {
        if (millis() - bootTime >= 3000) {
            bootComplete = true; // Cambiamos el estado lógico de la FSM a verdadero (fin del arranque)

            Serial.println(F("[FSM] BOOT -> RUN"));
        } else {

            showLogo();
        }
        
    }


}