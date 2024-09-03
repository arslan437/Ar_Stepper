#include <Ar_Stepper.h>

#define step  3
#define dir   4
#define en    2

Ar_Stepper stepper(step, dir, en);

void setup() 
{
    motor.begin();
    motor.set_pulse_time(200);
    motor.dir_cw();
    motor.enable();

    for(int i =0 ; i<2000; i++)
    {
        motor.takeStep();
    }
    motor.backward();
    for(int i =0 ; i<2000; i++)
    {
        motor.takeStep();
    }
    motor.disable();
}

void loop() 
{
 
}