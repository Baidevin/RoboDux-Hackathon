#include <Arduino.h>
#include "stepper.h"
#pragma once

#define STEPS2MM 40.0
class Robot
{
public:
    Robot();

    void drawLine(double x, double y);
    void demo();

    // Debug methods
    void forward(int steps);
    void backward(int steps);
    void penup();
    void pendown();
    void stop();
    int dir[4];
    int step[4];
    int sleep[4];
private:
    Stepper steppers[4];
};