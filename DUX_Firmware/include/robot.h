#include <Arduino.h>
#include "stepper.h"
#pragma once

int dir[] = {2, 8, 11, 5};
int step[] = {3, 9, 12, 6};
int sleep[] = {4, 10, 13, 7};
Stepper steppers[4];

class Robot
{
public:
    Robot();
    
private:
    void drawLine(int x, int y);
    void penup();
    void pendown();


};