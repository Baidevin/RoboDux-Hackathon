#include <Arduino.h>
#include "stepper.h"
#pragma once

#define STEPS2MM 40.0
class Robot
{
public:
    Robot();

    void drawLine(int x, int y);
    void demo();

    // Debug methods
    void forward(int steps);
    void backward(int steps);
    int dir[4];
    int step[4];
    int sleep[4];
private:
    Stepper steppers[4];

    void penup();
    void pendown();

};