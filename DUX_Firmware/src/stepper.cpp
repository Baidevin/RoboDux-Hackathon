#include <Arduino.h>
#include "stepper.h"

Stepper::Stepper(int dirPin, int stepPin, int sleepPin) 
{
    this->dirPin = dirPin;
    this->stepPin = stepPin;
    this->sleepPin = sleepPin;
    pinMode(dirPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(sleepPin, OUTPUT);
    digitalWrite(sleepPin, HIGH);
}

Stepper::Stepper() 
{
}

void Stepper::step(int steps) 
{
    if (steps < 0)
    {
        setDir(REV);
    }
    else
    {
        setDir(FWD);
    }

    for (int i = 0; i < abs(steps); i++) 
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(DELAY);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(DELAY);
    }
}

void Stepper::step()
{
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(DELAY);
    digitalWrite(stepPin, LOW);
}

void Stepper::setDir(int dir)
{
    if (dir < 0 || dir > 1)
    {
        return;
    }

    this->dir = dir;
    digitalWrite(dirPin, dir);
}

void Stepper::sleep(bool sleep)
{
    digitalWrite(sleepPin, sleep ? LOW : HIGH);
    this->sleeping = sleep;
}

void Stepper::sleep()
{
    sleep(true);
}