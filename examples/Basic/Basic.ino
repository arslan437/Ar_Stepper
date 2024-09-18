#include <Ar_Stepper.h>

#define step  3
#define dir   4
#define en    2

Ar_Stepper stepper(step, dir, en);

void setup() 
{
    stepper.begin();
    stepper.set_pulse_time(200);
    stepper.dir_cw();
    stepper.enable();

    for(int i =0 ; i<2000; i++)
    {
        stepper.takeStep();
    }
    stepper.backward();
    for(int i =0 ; i<2000; i++)
    {
        stepper.takeStep();
    }
    stepper.disable();
}

void loop() 
{
 
}