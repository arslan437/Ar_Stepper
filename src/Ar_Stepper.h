#ifndef Ar_Stepper_h
#define Ar_Stepper_h
#include <Arduino.h>

class Ar_Stepper
{

public:
    Ar_Stepper(int step, int dir, int en, float stepsPerMM);
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

    void moveTo(float mm);  
    void move(float mm);

    unsigned long getSteps();
    float getPosition();

private:
    int _stepPin;
    int _dirPin;
    int _enPin;
    int _pulseTime;

    bool inc = true;
    bool _set_dir = true;

    long _currentPosStep = 0;
    float _stepsPerMM; 
    float _currentPosMM = 0.0;
};

#endif