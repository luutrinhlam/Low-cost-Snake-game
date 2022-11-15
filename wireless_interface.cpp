#include "wireless_interface.h"

const uint64_t pipe[2] = {PIPE_ADDR_0, PIPE_ADDR_1};

RF24 radio(9,10);

byte recv_message[2][2];
byte trans_message[2];

bool WI_init(bool is_recv, byte trans_pipe_num) {
  radio.begin();
  radio.setAutoAck(1);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(CHANNEL);
  
  if(is_recv) {
    radio.openReadingPipe(0,pipe[0]);
    radio.openReadingPipe(1,pipe[1]);
    radio.startListening();
    return true;  
  }
  else {
    radio.setRetries(1,1);  
    radio.setPALevel(RF24_PA_MAX);
    if(trans_pipe_num==0 || trans_pipe_num==1) {
      radio.openWritingPipe(pipe[trans_pipe_num]);
      return true;
    }
  }
  return false;
}


void WI_write() {
  radio.write(&trans_message, sizeof(trans_message));
}

bool WI_read(byte& pipeNum) {
  if(radio.available(&pipeNum)) {
    if(pipeNum==0 || pipeNum==1) {
      radio.read(&(recv_message[pipeNum]), sizeof(recv_message[pipeNum]));  
    }
    return true;
  }
  return false;
}
