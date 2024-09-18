#include <Ar_Stepper.h>

#define step  3
#define dir   4
#define en    2

Ar_Stepper stepper(step, dir, en);

void setup() 
{
    stepper.begin();
    stepper.setPulseWidth(200);
    stepper.dirCW();
    stepper.enable();

    for(int i =0 ; i<2000; i++)
    {
        stepper.takeStep();
    }

    stepper.dirCCW();
    for(int i =0 ; i<2000; i++)
    {
        stepper.takeStep();
    }
    stepper.disable();
}

void loop() 
{
 
}