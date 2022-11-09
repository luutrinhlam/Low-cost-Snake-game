#include "World.h"

World world;
unsigned long pre_update_time = 0;

void setup() {
  // put your setup code here, to run once:
  joystick_init();
}


void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - pre_update_time >= 200) {
      pre_update_time = millis();
      world.update();
      world.draw();
  }
  monitor_display();
}
