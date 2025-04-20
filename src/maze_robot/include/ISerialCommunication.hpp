#pragma once

class ISerialCommunication 
{
    public:
    virtual ~ISerialCommunication()= default;
    virtual bool ReceiveSerialMessage(char*) = 0;
    virtual void SendSerialMessage(const char*) = 0;
    virtual bool IsSerialAvailable(void) = 0;
}; 