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

    for (int i = 0; i < steps; i++) 
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
    }
}

void Stepper::step()
{
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
}

void Stepper::setDir(int dir)
{
    if (dir < -1 || dir > 1)
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