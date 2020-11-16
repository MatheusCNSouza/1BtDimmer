#include <mbed.h>

DigitalOut orange_led(p5);
DigitalOut blue_led(p6);
InterruptIn btn(p7);
Ticker ticker;
typedef enum{state_up, state_down, state_rise, state_fall, state_max, state_min} State;
int state = state_up;
float counter = 0.0;
float i = 0.0;
float led_aux = 1.0f;

void ticker_orange(){
    static int e5_aux = 1;
    e5_aux = !e5_aux;    
    orange_led = e5_aux? led_aux:0;
}

void estado_up() {
  state = state_up;
  orange_led = 1;
  blue_led = 0;
}

void estado_down() {
  state = state_down;
  orange_led = 0;
  blue_led = 1;
}

void estado_rise(){
  state = state_rise;
  while (i < 1.0){
    i += 0.05;
    wait_ms(1000);
  }
  while (1){
    wait_ms(10);
  }
  btn.fall(&reach_max);
}

void estado_fall(){
  state = state_fall;
  while (i < 1.0){
    i -= 0.05;
    wait_ms(1000);
  }
  while (1){
    wait_ms(10);
  }
  btn.fall(&reach_min);
}

void set_mode(){
  if (state == state_up) estado_down();
  else if (state == state_down) estado_up();
}

void reach_max(){
  if (i==1.0) state = state_max;
  else estado_up();
}

void reach_min(){
  if (i==1.0) state = state_min;
  else estado_down();
}

void btn_transit(){
  if (state == state_up){
    btn.fall(&set_mode);
    while(counter < 1.0){
      counter += 0.01;
      wait_ms(10);
    }
    estado_rise();
  }
  else if (state == state_down){
    btn.fall(&set_mode);
    while(counter < 1.0){
      counter += 0.01;
      wait_ms(10);
    }
    estado_fall();
  }
  else if (state == state_max) estado_down();
  else if (state == state_min) estado_up();
}

void estado_max(){
  state = state_max;
  btn.fall(&btn_transit);
}

void estado_min(){
  state = state_min;
  btn.fall(&btn_transit);
}

int main() {
  estado_up();
  btn.rise(&btn_transit);
  while(1) {
    wait_ms(100);
  }
}