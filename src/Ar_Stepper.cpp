
#include "Ar_Stepper.h"

Ar_Stepper::Ar_Stepper(int step, int dir, int en)
{
    _stepPin = step;
    _dirPin = dir;
    _enPin = en;
}

Ar_Stepper::~Ar_Stepper()
{
}

void Ar_Stepper::begin()
{
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    // pinMode(_enPin, OUTPUT);

    disable();
}

void Ar_Stepper::dirCCW()
{
    digitalWrite(_dirPin, _set_dir);
    inc = !_set_dir;
}

void Ar_Stepper::dirCW()
{
    digitalWrite(_dirPin, !_set_dir);
    inc = _set_dir;
}

void Ar_Stepper::dirInvert()
{
    _set_dir != _set_dir;
}

void Ar_Stepper::enable()
{
    // digitalWrite(_enPin, LOW);
}

void Ar_Stepper::disable()
{
    // digitalWrite(_enPin, HIGH);
}

void Ar_Stepper::takeStep()
{
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(_pulseWidthMicros);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(_pulseWidthMicros);

    if (inc == true)
    {
        _currentPosStep++;
        // _currentPosMM += 1.0 / _stepsPerMM;
    }
    else
    {
        _currentPosStep--;
        // _currentPosMM -= 1.0 / _stepsPerMM;
    }
}

void Ar_Stepper::setPulseWidth(int tim)
{
    _pulseWidthMicros = (float)tim / 2.0;
}

void Ar_Stepper::setSpeedInMMPerSecond(float speed_mm_per_sec) 
{
    _speedMMperSEC = speed_mm_per_sec;
    
    int steps_per_second = speed_mm_per_sec * _stepsPerMM;

    // Calculate the pulse width in microseconds (1 second = 1,000,000 microseconds)
    _pulseWidthMicros = 1000000 / steps_per_second;

    _pulseWidthMicros = (float)_pulseWidthMicros/2.0;
}

void Ar_Stepper::setStepsPerMM(float stepsPerMM)
{
    _stepsPerMM = stepsPerMM;
}

unsigned long Ar_Stepper::getSteps()
{
    return _currentPosStep;
}

void Ar_Stepper::setMaxDistance(float lengthMM)
{
    _maxLengthMM = lengthMM;
}

void Ar_Stepper::setCurrentPosition(float pos_mm)
{
    if (pos_mm < _maxLengthMM)
    {
        _currentPosStep = pos_mm * _stepsPerMM;
    }
}

void Ar_Stepper::resetSteps()
{
    _currentPosStep = 0;
    _currentPosMM = 0.0;
}

void Ar_Stepper::moveTo(float mm)
{
    _currentPosMM = _currentPosStep / _stepsPerMM;
    float distance = mm - _currentPosMM;
    moveBy(distance);
}

void Ar_Stepper::moveBy(float mm)
{
    long stepsToMove = mm * _stepsPerMM;

    if (_maxLengthMM > 0)
    {
        float newPosMM = _currentPosMM + mm;
        if (newPosMM > _maxLengthMM)
        {
            stepsToMove = (_maxLengthMM - _currentPosMM) * _stepsPerMM;
        }
    }

    if (stepsToMove > 0) {
        dirCW();
    } else {
        dirCCW();
    }

    for (long i = 0; i < abs(stepsToMove); i++) {
        takeStep();
    }
}

float Ar_Stepper::getPosition()
{
    return _currentPosStep/_stepsPerMM;
}

void Ar_Stepper::setHoming(int limitSwitchPin, float homingSpeed)
{
    _limitSwitchPin = limitSwitchPin;
    _homingSpeed = homingSpeed;
    _homingEnabled = true;

    pinMode(_limitSwitchPin, INPUT_PULLUP);
}

void Ar_Stepper::home()
{
    if (!_homingEnabled) {
        return;  
    }

    enable();
    dirCCW();  

    while (digitalRead(_limitSwitchPin) == HIGH) 
    {
        takeStep();
        // delay(1000 / _homingSpeed);  
    }

    // Back off a bit after hitting the limit switch
    dirCW();
    while (digitalRead(_limitSwitchPin) == LOW)
    { 
        takeStep();
        // delay(1000 / (_homingSpeed * 2));
    }

    for (int i = 0; i < 20; i++) 
    { 
        takeStep();
        // delay(1000 / (_homingSpeed * 2)); 
    }

    resetSteps(); 
    disable();
}