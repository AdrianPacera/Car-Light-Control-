#pragma once

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <mcp_can.h>

#include "ILightControl.hpp"
#include "LightControl.hpp"
#include "ICANCommunicationManager.hpp"
#include "CANCommunicationManager.hpp"
#include "LightControlEnums.hpp"

//CAN CONSTANTS
#define BOARD_ID 0x003
#define CAN_COM_PIN 5
#define MESSAGE_MAX_SIZE 8
#define STATE_MAX_SIZE 3

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

//FREERTOS CONSTANTS
#define STACK_DEPTH 4208
#define UX_PRIORITY 1
#define WATCHDOG_TASK_DELAY 10

//TASK CONSTANTS
#define TASK_SLOWDOWN 1
                 
//LIGHT VARIABLES
const int blink_interval_ms = 500;   
uint8_t left_indicator_state = LOW;  
uint8_t right_indicator_state = LOW;  
uint8_t EVL_light_state = LOW;

//ENUM VARIABLES
char lightMode = '0';
int lightState = 0;
int blinker_light_state = 0;
int front_light_state = 0;
int rear_light_state = 0;
