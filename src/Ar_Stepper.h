#ifndef Ar_Stepper_h
#define Ar_Stepper_h
#include <Arduino.h>

class Ar_Stepper
{

public:
    Ar_Stepper(int step, int dir, int en);
    ~Ar_Stepper();

    void begin();
    void dir_cw();
    void dir_ccw();
    void enable();
    void disable();
    void takeStep();
    void set_pulse_time(int tim);
    void invert();
    void resetSteps();

    unsigned long getSteps();

private:
    int _step;
    int _dir;
    int _en;
    int _tim;

    bool inc = true;
    bool _set_dir = true;

    long _stp = 0;
};

#endif