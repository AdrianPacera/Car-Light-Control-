#pragma once

class ICommunicationManager{
    public:
        virtual int CANInitialize() = 0;
        virtual void CANHandleIncomingMessage(char* lightMode, int* lightState) = 0;
        virtual int CANSendMessage(char* message[]) = 0;
};