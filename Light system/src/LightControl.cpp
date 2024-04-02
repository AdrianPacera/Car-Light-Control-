#include "LightControl.hpp" 

LightControl::LightControl(const int interval){
  blink_interval_ms = interval;
}

void LightControl::initializeLights(){
  pinMode(LEFT_INDICATOR_LED, OUTPUT);
  pinMode(RIGHT_INDICATOR_LED, OUTPUT);
  pinMode(LEFT_LOWBEAM_LED, OUTPUT);
  pinMode(RIGHT_LOWBEAM_LED, OUTPUT);
  pinMode(LEFT_HIGHBEAM_LED, OUTPUT);
  pinMode(RIGHT_HIGHBEAM_LED, OUTPUT);
  pinMode(LEFT_REAR_LED, OUTPUT);
  pinMode(RIGHT_REAR_LED, OUTPUT);
  pinMode(LEFT_BREAK_LED, OUTPUT);
  pinMode(RIGHT_BREAK_LED, OUTPUT);
}

void LightControl::blinkLight(int pin, unsigned long current_millis, uint8_t *light_state){
  if (current_millis - light_prev_millis >= blink_interval_ms) {
    light_prev_millis = current_millis;

    *light_state = 1 - *light_state; 
    digitalWrite(pin, *light_state); 
  }   
}

void LightControl::ensureLightState(int pin, uint8_t desired_state){
  digitalWrite(pin, desired_state);
}

void LightControl::EVLLights(unsigned long current_millis, uint8_t *light_state) {
  if (current_millis - light_prev_millis >= blink_interval_ms) {
    light_prev_millis = current_millis;

    *light_state = 1 - *light_state;  
    digitalWrite(LEFT_INDICATOR_LED, *light_state); 
    digitalWrite(RIGHT_INDICATOR_LED, *light_state); 
  }
}