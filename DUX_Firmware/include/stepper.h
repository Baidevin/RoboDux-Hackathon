#include <Arduino.h>
#pragma once
enum DIR 
{
  FWD = 1,
  REV = -1
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