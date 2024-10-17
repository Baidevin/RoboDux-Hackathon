#include <Arduino.h>
#pragma once

#define DELAY 200

enum DIR 
{
  FWD = 1,
  REV = 0
};

class Stepper {
public:
    Stepper();
    Stepper(int dirPin, int stepPin, int sleepPin);
    void step(int steps);
    void step();
    void setDir(int dir);
    void sleep(bool sleep);
    void sleep();
private:
    int dir;
    bool sleeping;
    int dirPin;
    int stepPin;
    int sleepPin;
    };