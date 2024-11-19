#ifndef Ar_Stepper_h
#define Ar_Stepper_h
#include <Arduino.h>

/*
 * To do list 
 * Set the distance to current values.
 */

class Ar_Stepper
{

public:
    Ar_Stepper(int step, int dir, int en);
    ~Ar_Stepper();

    void begin();

    void dirCW();
    void dirCCW();
    void dirInvert();

    void enable();
    void disable();

    void setSpeedInMMPerSecond(float speed_mm_per_sec);
    void setPulseWidth(int tim);
    void setHomeMoveOut(int steps);

    void takeStep();
    void moveTo(float mm);  
    void moveBy(float mm);
    void asyncMoveTo(float mm);
    void asyncMoveBy(float mm);
    bool asyncRun();

    void setHoming(int limitSwitchPin, float homingSpeed);
    void home();
    void setStepsPerMM(float stepsPerMM);

    void setMaxDistance(float lengthMM);
    void setCurrentPosition(float pos_mm);

    void resetSteps();

    unsigned long getSteps();
    float getPosition();

private:
    int _stepPin;
    int _dirPin;
    int _enPin;
    int _limitSwitchPin;

    int _pulseWidthMicros;
    float _stepsPerMM;
    int _limit_move_out_steps;

    float _maxLengthMM = -1; 
    
    float _speedMMperSEC = 0;
    int _homingSpeed;

    bool inc = true;
    bool _set_dir = true;
    bool _homingEnabled = false;

    long _currentPosStep = 0;
    float _currentPosMM = 0.0;

    bool _asyncMoving = false;
    long _targetPositionStep = 0;
    unsigned long _lastStepTime = 0;
};

#endif