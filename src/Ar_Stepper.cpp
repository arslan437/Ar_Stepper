
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
    delayMicroseconds(_pulseGapMicros);
}

void Ar_Stepper::setPulseWidth(int tim)
{
    // _pulseGapMicros = (float)tim / 2.0;
    _pulseGapMicros = tim;
}

void Ar_Stepper::setHomeMoveOut(int steps)
{
    _limit_move_out_steps = steps;
}

void Ar_Stepper::setSpeedInMMPerSecond(float speed_mm_per_sec) 
{
    _speedMMperSEC = speed_mm_per_sec;
    
    int steps_per_second = speed_mm_per_sec * _stepsPerMM;

    // Calculate the pulse width in microseconds (1 second = 1,000,000 microseconds)
    _pulseGapMicros = 1000000 / steps_per_second;
    _pulseGapMicros -= (_pulseWidthMicros * 2 );
    // _pulseGapMicros = (float)_pulseGapMicros/2.0;
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
    long stepsToMove = 0;

    if (mm > _maxLengthMM)
    {
        stepsToMove = (_maxLengthMM - getPosition()) * _stepsPerMM;
    }
    else 
    {
        stepsToMove = mm * _stepsPerMM;
    }

    stepsToMove = stepsToMove - _currentPosStep; 

    if (stepsToMove > 0) 
    {
        dirCW();
    } 
    else 
    {
        dirCCW();
    }

    for (long i = 0; i < abs(stepsToMove); i++) 
    {
        if (digitalRead(_limitSwitchPin) == HIGH && _currentPosStep >= 0)
        {
            takeStep();
        }
    }
}


void Ar_Stepper::moveBy(float mm)
{
    moveTo(getPosition() + mm);
}

void Ar_Stepper::asyncTakeStep()
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

void Ar_Stepper::asyncMoveTo(float mm) 
{
    _targetPositionStep = mm * _stepsPerMM; 
    _asyncMoving = true; 
    _lastStepTime = micros(); 
}

void Ar_Stepper::asyncMoveBy(float mm) 
{
    asyncMoveTo(getPosition() + mm);
}

bool Ar_Stepper::asyncRun() 
{
    if (!_asyncMoving)
    {
        return false; 
    }

    if (micros() - _lastStepTime >= _pulseGapMicros) 
    {
        _lastStepTime = micros(); 

        if (_currentPosStep < _targetPositionStep) {
            dirCW();
            asyncTakeStep();
        } else if (_currentPosStep > _targetPositionStep) {
            dirCCW();
            asyncTakeStep();
        }

        // Check if the target is reached
        if (_currentPosStep == _targetPositionStep) {
            _asyncMoving = false; // Movement complete
        }
    }

    return _asyncMoving; // Return true if still moving
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

    for (int i = 0; i < _limit_move_out_steps; i++) 
    { 
        takeStep();
        // delay(1000 / (_homingSpeed * 2)); 
    }

    resetSteps(); 
    disable();
}