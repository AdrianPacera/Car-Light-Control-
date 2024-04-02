#pragma once

#include <Arduino.h>
#include <iostream>
#include "ILightControl.hpp"

//BLINKERS
#define LEFT_INDICATOR_LED 12
#define RIGHT_INDICATOR_LED 13
#define LEFT_BACK_INDICATOR_LED 12
#define RIGHT_BACK_INDICATOR_LED 13

//FRONT LIGHTS
#define LEFT_LOWBEAM_LED 14
#define RIGHT_LOWBEAM_LED 27
#define LEFT_HIGHBEAM_LED 26 
#define RIGHT_HIGHBEAM_LED 25

//REAR LIGHTS
#define LEFT_REAR_LED 33
#define RIGHT_REAR_LED 32
#define LEFT_BREAK_LED 15
#define RIGHT_BREAK_LED 2

class LightControl: public ILightControl{
    private:
        unsigned long light_prev_millis = 0;
        int blink_interval_ms = 500;
    public:
        LightControl(int blink_interval_ms);
        void initializeLights();
        void blinkLight(int pin, unsigned long current_millis, uint8_t *light_state);
        void ensureLightState(int pin, uint8_t desired_state);
        void EVLLights(unsigned long current_millis, uint8_t *light_state);
};