#include <Arduino.h>
#include "serialHandler.h"

Handler::Handler(Robot* robot)
{
    this->robot = robot;

    Serial.begin(9600);
    Serial.println("Serial Handler Initialized");
}

void Handler::handleSerial()
{
    if (Serial.available())
    {
        delay(10);
        String data = Serial.readStringUntil('\n');
        // Serial.println(data);
        Command cmd = parseCommand(data);
        executeCommand(cmd);
    }
}

Command Handler::parseCommand(String data)
{
    if (data.charAt(0) != '!')
    {
        return Command();
    }
    char command = data.charAt(1);
    double arg1 = 0;
    double arg2 = 0;
    switch (command)
    {
    case 'M':
        // Seperate by commas
        int commaIndex = data.indexOf(',');
        arg1 = data.substring(2, commaIndex).toDouble();
        arg2 = data.substring(commaIndex + 1).toDouble();
        break;    
    default:
        break;
    }
    Serial.println("$C");
    Command cmd = Command(command, arg1, arg2);
    return cmd;
}

void Handler::executeCommand(Command command)
{
    Serial.println("$R");
    switch (command.command)
    {
    case 'M':
        robot->drawLine(command.arg1, command.arg2);
        break;
    case 'S':
        robot->stop();
        break;
    case 'U':
        robot->penup();
        break;
    case 'D':
        robot->pendown();
        break;
    default:
        break;
    }
    Serial.println("$A");
}

Command::Command(char command, double arg1, double arg2)
{
    this->command = command;
    this->arg1 = arg1;
    this->arg2 = arg2;
}

Command::Command()
{
    this->command = ' ';
    this->arg1 = 0;
    this->arg2 = 0;
}