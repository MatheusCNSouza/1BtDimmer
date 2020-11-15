#include <mbed.h>

DigitalOut orange_led(p5);
DigitalOut blue_led(p6);
InterruptIn btn(p7);
Ticker ticker;
typedef enum{state_up, state_down, state_rise, state_fall, state_max, state_min} State;
State init = state_up;
//float led_aux = 1.0f;

void estado_up() {
  orange_led = 1;
  blue_led = 0;
}

void estado_down() {
  orange_led = 0;
  blue_led = 1;
}

int main() {

  // put your setup code here, to run once:

  while(1) {
    // put your main code here, to run repeatedly:
  }
}