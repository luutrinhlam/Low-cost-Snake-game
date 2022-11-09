#include "joystick.h"


unsigned long pre_scan_time = 0;


void joystick_init() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
}

bool joystick_is_pressed() {
  return !digitalRead(SW);
}
int joystick_direction() {
  static int mapX=0,mapY=0;
  mapX = map(analogRead(VRx), 0, 1023, -512, 512);
  mapY = map(analogRead(VRy), 0, 1023, -512, 512);

  if(mapX>=490) {
    return 2;
  }
  else if(mapX<=-490) {
    return 4;
  }
  else if(mapY>=490) {
    return 1;
  }
  else if(mapY<=-490) {
    return 3;
  }
  return 0;
}
