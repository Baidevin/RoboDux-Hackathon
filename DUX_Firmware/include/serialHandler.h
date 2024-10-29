#include <Arduino.h>
#include "robot.h"

class Command
{
public:
    Command(char command, double arg1, double arg2);
    Command();
    char command;
    double arg1;
    double arg2;

};

class Handler
{
public:
    Handler(Robot* robot);
    void handleSerial();

private:
    Robot* robot;

    Command parseCommand(String data);

    void executeCommand(Command command);
    void sendResponse(String response);
};

