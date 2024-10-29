#include <Arduino.h>
#include "stepper.h"
#include "robot.h"

Robot::Robot()
:   dir {2, 8, 11, 5},
    step {3, 9, 12, 6},
    sleep {4, 10, 13, 7}
{
    for (int i = 0; i < 4; i++)
    {
        steppers[i] = Stepper(dir[i], step[i], sleep[i]);
    }
}

void Robot::drawLine(double x, double y)
{
    Serial.println("Drawing Line");
    Serial.println(x);
    Serial.println(y);
    double steps = sqrt(x * x + y * y);
    double dx = (x / steps) * STEPS2MM;
    double dy = (y / steps) * STEPS2MM;

    Serial.print("Steps: ");
    Serial.println(steps);
    int motorSpeeds[4];

    motorSpeeds[0] = (int) (dx - dy);
    motorSpeeds[1] = (int) (dx + dy);
    motorSpeeds[2] = (int) (dx - dy);
    motorSpeeds[3] = (int) (dx + dy);


    for (int i = 0; i < 4; i++)
    {
        steppers[i].sleep(false);
    }
    
    for (int i = 0; i < steps; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            steppers[j].step(motorSpeeds[j]);
        }
    }

    // for (int i = 0; i < 4; i++)
    // {
    //     steppers[i].sleep();
    // }
}

void Robot::penup()
{

}

void Robot::pendown()
{
    
}

void Robot::forward(int steps)
{
    for (auto stepper : steppers)
    {
        stepper.setDir(FWD);
    }

    for (int i = 0; i < steps; i++)
    {
        for (auto stepper : steppers)
        {
            stepper.step();
        }
    }
}

void Robot::stop()
{
    for (auto stepper : steppers)
    {
        stepper.sleep();
    }
}

void Robot::backward(int steps)
{
    for (auto stepper : steppers)
    {
        stepper.setDir(REV);
    }

    for (int i = 0; i < steps; i++)
    {
        for (auto stepper : steppers)
        {
            stepper.step();
        }
    }
}

void Robot::demo()
{
    drawLine(0, 100);
    delay(1000);
    drawLine(0, -100);
    delay(1000);
    drawLine(100, 0);
    delay(1000);
    drawLine(-100, 0);
    delay(1000);
    drawLine(100, 100);
    delay(1000);
    drawLine(-100, -100);
    delay(1000);
    drawLine(100, -100);
    delay(1000);
    drawLine(-100, 100);
    delay(1000);

}