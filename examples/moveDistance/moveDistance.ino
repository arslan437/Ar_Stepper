#include <Ar_Stepper.h>

#define STEP_PIN 2
#define DIR_PIN 3
#define EN_PIN 4

#define STEPS_PER_MM 100

Ar_Stepper myStepper(STEP_PIN, DIR_PIN, EN_PIN, STEPS_PER_MM);

void setup() {
    Serial.begin(9600);
    myStepper.begin();
    myStepper.set_pulse_time(500); 
    myStepper.enable();
}

void loop() {
    // Move 10mm forward
    myStepper.move(10);
    delay(1000);

    // Move 5mm backward
    myStepper.move(-5);
    delay(1000);

    // Move to absolute position 0mm
    myStepper.moveTo(0);
    delay(1000);

    // Print current position in mm
    Serial.print("Current Position: ");
    Serial.println(myStepper.getPosition());
}