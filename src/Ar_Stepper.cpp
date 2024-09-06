
#include "Ar_Stepper.h"

Ar_Stepper::Ar_Stepper(int step, int dir, int en, float stepsPerMM)
{
    _stepPin = step;
    _dirPin = dir;
    _enPin = en;

    _stepsPerMM = stepsPerMM;
}

Ar_Stepper::~Ar_Stepper()
{
}

void Ar_Stepper::begin()
{
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enPin, OUTPUT);

    disable();
}

void Ar_Stepper::dir_ccw()
{
    digitalWrite(_dirPin, _set_dir);
    inc = true;
}

void Ar_Stepper::dir_cw()
{
    digitalWrite(_dirPin, !_set_dir);
    inc = false;
}

void Ar_Stepper::enable()
{
    digitalWrite(_enPin, LOW);
}

void Ar_Stepper::disable()
{
    digitalWrite(_enPin, HIGH);
}

void Ar_Stepper::takeStep()
{
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(_pulseTime);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(_pulseTime);

    if (inc == true)
    {
        _currentPosStep++;
        _currentPosMM += 1.0 / _stepsPerMM;
    }
    else
    {
        _currentPosStep--;
        _currentPosMM -= 1.0 / _stepsPerMM;
    }
}

void Ar_Stepper::set_pulse_time(int tim)
{
    _pulseTime = tim;
}

void Ar_Stepper::invert()
{
    _set_dir != _set_dir;
}

unsigned long Ar_Stepper::getSteps()
{
    return _currentPosStep;
}

void Ar_Stepper::resetSteps()
{
    _currentPosStep = 0;
    _currentPosMM = 0.0;
}

void Ar_Stepper::moveTo(float mm)
{
    float distance = mm - _currentPosMM;
    move(distance);
}

void Ar_Stepper::move(float mm)
{
    long stepsToMove = mm * _stepsPerMM;

    if (stepsToMove > 0) {
        dir_cw();
    } else {
        dir_ccw();
    }

    for (long i = 0; i < abs(stepsToMove); i++) {
        takeStep();
    }
}

float Ar_Stepper::getPosition()
{
    return _currentPosMM;
}