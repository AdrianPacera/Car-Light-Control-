#pragma once
#include <iostream>

class ILightControl{
    public:
        virtual void initializeLights() = 0;
        virtual void blinkLight(int pin, unsigned long current_millis, uint8_t *light_state) = 0;
        virtual void ensureLightState(int pin, uint8_t desired_state) = 0;
        virtual void EVLLights(unsigned long current_millis, uint8_t *light_state) = 0;
};