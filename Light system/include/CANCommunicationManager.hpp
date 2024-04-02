#pragma once

#include <Arduino.h>
#include <mcp_can.h>
#include "ICANCommunicationManager.hpp"

class CANCommunicationManager: public ICommunicationManager{
    private:
        MCP_CAN CAN0 = 0;    
        long unsigned int rxId = 0;
        unsigned char len = 0;
        unsigned char rxBuf[8] = {0};
        char message[8];

    public:
        CANCommunicationManager(int pinNumber, int lentgth);
        int CANInitialize();
        void CANHandleIncomingMessage(char* lightMode, int* lightState);
        int CANSendMessage(char* message[]);
        int CANParseMessage(char* lightMode, int* lightState);
};