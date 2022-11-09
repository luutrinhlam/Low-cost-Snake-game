#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>


#define VRx A0
#define VRy A1
#define SW  2

void joystick_init();
bool joystick_is_pressed();
int joystick_direction();

#endif