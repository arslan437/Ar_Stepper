
#include "Ar_Stepper.h"

Ar_Stepper::Ar_Stepper(int step, int dir, int en)
{
    _step = step;
    _dir = dir;
    _en = en;
}

Ar_Stepper::~Ar_Stepper()
{
}

void Ar_Stepper::begin()
{
    pinMode(_step, OUTPUT);
    pinMode(_dir, OUTPUT);
    pinMode(_en, OUTPUT);
}

void Ar_Stepper::dir_ccw()
{
    digitalWrite(_dir, _set_dir);
    inc = true;
}

void Ar_Stepper::dir_cw()
{
    digitalWrite(_dir, !_set_dir);
    inc = false;
}

void Ar_Stepper::enable()
{
    digitalWrite(_en, LOW);
}

void Ar_Stepper::disable()
{
    digitalWrite(_en, HIGH);
}

void Ar_Stepper::takeStep()
{
    digitalWrite(_step, HIGH);
    delayMicroseconds(_tim);
    digitalWrite(_step, LOW);
    delayMicroseconds(_tim);

    if (inc == true)
    {
        _stp++;
    }
    else
    {
        _stp--;
    }
}

void Ar_Stepper::set_pulse_time(int tim)
{
    _tim = tim;
}

void Ar_Stepper::invert()
{
    _set_dir != _set_dir;
}

unsigned long Ar_Stepper::getSteps()
{
    return _stp;
}

void Ar_Stepper::resetSteps()
{
    _stp = 0;
}