#include "main.hpp"

LightControl lightControlChild = LightControl(blink_interval_ms);
ILightControl *lightControl;

CANCommunicationManager communicationManagerChild = CANCommunicationManager(CAN_COM_PIN, MESSAGE_MAX_SIZE);
ICommunicationManager *communicationManager;

void blinkerLightsThread(void* pvParameters){
  while(true){
    switch(blinker_light_state){
      case BLINKER_LIGHTS_MODE::LEFT_DIRECTION_INDICATOR:
        lightControl->blinkLight(LEFT_INDICATOR_LED, millis(), &left_indicator_state);
        lightControl->ensureLightState(RIGHT_INDICATOR_LED, LOW);
        break;
      case BLINKER_LIGHTS_MODE::RIGHT_DIRECTION_INDICATOR:
        lightControl->blinkLight(RIGHT_INDICATOR_LED, millis(), &right_indicator_state);
        lightControl->ensureLightState(LEFT_INDICATOR_LED, LOW);
        break;
      case BLINKER_LIGHTS_MODE::EMERGENCY_LIGHTS:
        lightControl->EVLLights(millis(), &EVL_light_state);
        break;
      case BLINKER_LIGHTS_MODE::BLINKERS_OFF:
        lightControl->ensureLightState(LEFT_INDICATOR_LED, LOW);
        lightControl->ensureLightState(RIGHT_INDICATOR_LED, LOW);
      default:
        blinker_light_state = BLINKER_LIGHTS_MODE::BLINKERS_OFF;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(WATCHDOG_TASK_DELAY));
  }
}

void rearLightsThread(void* pvParameters){
  while(true){
    switch(rear_light_state){
      case REAR_LIGHTS_MODE::REAR_LIGHTS_ON:
        lightControl->ensureLightState(LEFT_REAR_LED, HIGH);
        lightControl->ensureLightState(RIGHT_REAR_LED, HIGH);
        break;
      case REAR_LIGHTS_MODE::BREAK_LIGHTS_ON:
        lightControl->ensureLightState(LEFT_BREAK_LED, HIGH);
        lightControl->ensureLightState(RIGHT_BREAK_LED, HIGH);
        break;
      case REAR_LIGHTS_MODE::BREAK_LIGHTS_OFF:
        lightControl->ensureLightState(LEFT_BREAK_LED, LOW);
        lightControl->ensureLightState(RIGHT_BREAK_LED, LOW);
        break;
      case REAR_LIGHTS_MODE::REAR_LIGHTS_OFF:
        lightControl->ensureLightState(LEFT_REAR_LED, LOW);
        lightControl->ensureLightState(RIGHT_REAR_LED, LOW);
        break;
      case REAR_LIGHTS_MODE::LIGHTS_OFF:
        lightControl->ensureLightState(LEFT_REAR_LED, LOW);
        lightControl->ensureLightState(RIGHT_REAR_LED, LOW);   
        lightControl->ensureLightState(LEFT_BREAK_LED, LOW);
        lightControl->ensureLightState(RIGHT_BREAK_LED, LOW);
        break;        
      default:
        rear_light_state = REAR_LIGHTS_MODE::LIGHTS_OFF;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(WATCHDOG_TASK_DELAY));
  }
}

void frontLightsThread(void* pvParameters){
  while(true){
    switch(front_light_state){
      case FRONT_LIGHTS_MODE::LOWBEAM_LIGHTS_ON:
        lightControl->ensureLightState(LEFT_LOWBEAM_LED, HIGH);
        lightControl->ensureLightState(RIGHT_LOWBEAM_LED, HIGH);
        lightControl->ensureLightState(LEFT_HIGHBEAM_LED, LOW);
        lightControl->ensureLightState(RIGHT_HIGHBEAM_LED, LOW);
        break;
      case FRONT_LIGHTS_MODE::HIGHBEAM_LIGHTS_ON:
        lightControl->ensureLightState(LEFT_HIGHBEAM_LED, HIGH);
        lightControl->ensureLightState(RIGHT_HIGHBEAM_LED, HIGH);
        lightControl->ensureLightState(LEFT_LOWBEAM_LED, LOW);
        lightControl->ensureLightState(RIGHT_LOWBEAM_LED, LOW);
        break;
      case FRONT_LIGHTS_MODE::FRONT_LIGHTS_OFF:
        lightControl->ensureLightState(LEFT_LOWBEAM_LED, LOW);
        lightControl->ensureLightState(RIGHT_LOWBEAM_LED, LOW);          
        lightControl->ensureLightState(LEFT_HIGHBEAM_LED, LOW);
        lightControl->ensureLightState(RIGHT_HIGHBEAM_LED, LOW);
      default:
        front_light_state = FRONT_LIGHTS_MODE::FRONT_LIGHTS_OFF;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(WATCHDOG_TASK_DELAY));
  }
}

void lightControlThread(void* pvParameters){
  while(true){
    switch(lightMode){
      case 'F':
        front_light_state = lightState;
        break;
      case 'R':
        rear_light_state = lightState;
        break;
      case 'B':
        blinker_light_state = lightState;
        break;
      default:
        front_light_state = FRONT_LIGHTS_MODE::FRONT_LIGHTS_OFF;
        rear_light_state = REAR_LIGHTS_MODE::LIGHTS_OFF; 
        blinker_light_state = BLINKER_LIGHTS_MODE::BLINKERS_OFF;
        break;
    }

    vTaskDelay(pdMS_TO_TICKS(WATCHDOG_TASK_DELAY));
  }  

}

void readMessage(void *pvParameters) { 
  while(true){
    communicationManager->CANHandleIncomingMessage(&lightMode, &lightState);

    delay(TASK_SLOWDOWN);

    vTaskDelay(pdMS_TO_TICKS(WATCHDOG_TASK_DELAY));
  }
}   

void setup() {
  lightControl = &lightControlChild;
  communicationManager = &communicationManagerChild;

  lightControl->initializeLights();
  communicationManager->CANInitialize();

  xTaskCreate(readMessage, "taskForReading", STACK_DEPTH, NULL, UX_PRIORITY, NULL);
  xTaskCreate(lightControlThread, "lightControlThread", STACK_DEPTH, NULL , UX_PRIORITY, NULL);
  xTaskCreate(blinkerLightsThread, "blinkersThread", STACK_DEPTH, NULL , UX_PRIORITY, NULL);
  xTaskCreate(frontLightsThread, "frontLightsThread", STACK_DEPTH, NULL , UX_PRIORITY, NULL);
  xTaskCreate(rearLightsThread, "rearLightsThread", STACK_DEPTH, NULL , UX_PRIORITY, NULL);
}

void loop(){
  
}