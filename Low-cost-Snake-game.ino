#include "World.h"
#include "wireless_interface.h"

World world;
unsigned long pre_update_time = 0;
unsigned long pre_samp_time = 0;
byte pipeNum;

void setup() {
  Serial.begin(9600);
  if(WI_init(true,0)==false) {
    while(true);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - pre_update_time >= 200) {
      pre_update_time = millis();
      world.update();
      draw_score(world.score1,world.score2);
      world.draw();
  }
  if(millis() - pre_samp_time >= 50) {
      pre_samp_time = millis();
      dir_update();
  }
  monitor_display();
}

void dir_update() {
  if(WI_read(pipeNum)) {
    if(pipeNum==0) {
      if(recv_message[0][1] != 0)
        world.changeDirection(PLAYER1, recv_message[0][1]);
    }
    else if(pipeNum==1){
      if(recv_message[1][1] != 0)
        world.changeDirection(PLAYER2, recv_message[1][1]);
    }
  }
}
