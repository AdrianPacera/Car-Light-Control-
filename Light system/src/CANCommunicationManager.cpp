#include "CANCommunicationManager.hpp"

CANCommunicationManager::CANCommunicationManager(int pinNumber, int lenght){
    CAN0 = MCP_CAN(pinNumber);  
    rxId = 0;
    len = lenght;
    rxBuf[8] = {0};
    message[8] = {0};
}

int CANCommunicationManager::CANInitialize(){
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) != CAN_OK){
    return -1;
  }    
  
  CAN0.setMode(MCP_NORMAL);   

  return 0;
}

int CANCommunicationManager::CANParseMessage(char* lightMode, int* lightState){
  char charStateData[8];

  memccpy(message, rxBuf, MAX_CHAR_IN_MESSAGE, sizeof(message));

  if(message[0] == 'L'){
    *lightMode = message[1];
    charStateData[0] = message[2];
    charStateData[1] = message[3];
    charStateData[2] = message[4];
    sscanf(charStateData,"%d", &lightState);
  }  
  else{
    return -1;
  }

  return 0;
}

void CANCommunicationManager::CANHandleIncomingMessage(char* lightMode, int* lightState){
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    CANParseMessage(lightMode, lightState);
}

int CANCommunicationManager::CANSendMessage(char* message[]){
  return 0;
}