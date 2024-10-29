#include <Arduino.h>
#include "robot.h"
#include "serialHandler.h"

Robot robot = Robot();

Handler handler = Handler(&robot);

void setup() {
    Serial.begin(9600);
    Serial.println("Starting");
}

void loop() {
    handler.handleSerial();
    // Serial.println("Looping");
    delay(100);
}