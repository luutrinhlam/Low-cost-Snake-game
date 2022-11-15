#ifndef WIRELESS_INTERFACE_h
#define WIRELESS_INTERFACE_h

#include <SPI.h>
#include "RF24.h"

#define PIPE_ADDR_0 0x7878787878LL
#define PIPE_ADDR_1 0xB3B4B5B6F1LL
#define CHANNEL     10

extern byte recv_message[2][2];
extern byte trans_message[2];

bool WI_init(bool is_recv, byte trans_pipe_num);
bool WI_read(byte& pipeNum);
void WI_write();

#endif
