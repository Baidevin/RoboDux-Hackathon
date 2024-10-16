#include <Arduino.h>
#include "stepper.h"
#include "robot.h"

Robot::Robot()
{
    for (int i = 0; i < 4; i++)
    {
        steppers[i] = Stepper(dir[i], step[i], sleep[i]);
    }
}

void Robot::drawLine(int x, int y)
{

}

void Robot::penup()
{

}

void Robot::pendown()
{
    
}
