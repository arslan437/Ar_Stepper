#include <Arduino.h>
#include <Ar_Stepper.h>

#define STEP_PIN 3
#define DIR_PIN 2
#define EN_PIN 4
#define HOME_LIMIT_SWITCH 5

#define STEPS_PER_MM 80
#define DISTANCE_TO_TRAVEL 200
#define MAX_TRAVEL_DISTANCE 500

#define FAST_SPEED 10
#define SLOW_SPEED 3

Ar_Stepper stepper(STEP_PIN, DIR_PIN, EN_PIN);

void setup() 
{

  Serial.begin(9600);
  stepper.setStepsPerMM(STEPS_PER_MM);
  stepper.setMaxDistance(MAX_TRAVEL_DISTANCE);
  stepper.setSpeedInMMPerSecond(FAST_SPEED);
  stepper.setHoming(HOME_LIMIT_SWITCH, SLOW_SPEED);
  stepper.setHomeMoveOut(400);
  stepper.begin();

  stepper.setSpeedInMMPerSecond(SLOW_SPEED);
  stepper.home();
  stepper.asyncMoveTo(DISTANCE_TO_TRAVEL);
}

void loop()
{
  if(!stepper.asyncRun())
  {
    Serial.println("Movement completed...");
  }
}