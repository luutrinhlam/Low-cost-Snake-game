#include "monitor.h"
#include "stdlib.h"
#include "World.h"

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

const uint8_t snake1_bitmap[] U8G_PROGMEM = {
  0xF0,         // 11110000
  0xF0,         // 11110000
  0xF0,         // 11110000
  0xF0,         // 11110000
};

const uint8_t snake2_bitmap[] U8G_PROGMEM = {
  0xF0,         // 11110000
  0x90,         // 10010000
  0x90,         // 10010000
  0xF0,         // 11110000
};

const uint8_t food_bitmap[] U8G_PROGMEM = {
  0x90,         // 10010000
  0x60,         // 01100000
  0x60,         // 01100000
  0x90,         // 10010000
};

uint8_t snake1_locs[50][2];
uint8_t snake1_len=0;
uint8_t snake2_locs[50][2];
uint8_t snake2_len=0;
uint8_t food_locs[2]={0,0};
char score_1[4];
char score_2[4];

void draw();

void draw() {
  for(int i=0; i<snake1_len; i++) {
    u8g.drawBitmapP(snake1_locs[i][0], snake1_locs[i][1], 1, 4, snake1_bitmap);
  }
  for(int i=0; i<snake2_len; i++) {
    u8g.drawBitmapP(snake2_locs[i][0], snake2_locs[i][1], 1, 4, snake2_bitmap);
  }
  u8g.drawBitmapP(food_locs[0], food_locs[1], 1, 4, food_bitmap);


  u8g.drawBox((MATRIX_LENGTH)*4, 0, 4, MATRIX_WIDTH*4);
  
  u8g.setFont(u8g_font_5x8);
  u8g.drawStr((MATRIX_LENGTH+3)*4, 10, "P1:");
  u8g.drawStr((MATRIX_LENGTH+3)*4, 20, score_1);
  u8g.drawStr((MATRIX_LENGTH+3)*4, 40, "P2:");
  u8g.drawStr((MATRIX_LENGTH+3)*4, 50, score_2);
}

void monitor_display() {
  static unsigned long pre_page_time = 0;
  
  if(!u8g.nextPage() && (millis() - pre_page_time >= 100)) {
    pre_page_time = millis();
    u8g.firstPage();
  }
  draw();  
}

void draw_snake(int snake_arr[][2], int snake_len, int which_snake) {
  for(int i=0; i < snake_len; i++) {
      if(which_snake==0) {
        snake1_locs[i][0] = 4*snake_arr[i][0];
        snake1_locs[i][1] = 4*snake_arr[i][1];
      }
      else {
        snake2_locs[i][0] = 4*snake_arr[i][0];
        snake2_locs[i][1] = 4*snake_arr[i][1];
      }
  }
  if(which_snake==0) {
      snake1_len = snake_len;
    }
  else {
      snake2_len = snake_len;
  }
}
void draw_food(int x, int y) {
  food_locs[0] = 4*x;
  food_locs[1] = 4*y;
}

void draw_score(int s1, int s2) {
  itoa(s1,score_1,10);
  itoa(s2,score_2,10);
}
