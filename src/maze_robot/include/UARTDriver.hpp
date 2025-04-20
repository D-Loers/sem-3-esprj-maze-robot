#pragma once
#include "ISerialCommunication.hpp"
#include "UARTENUMs.hpp"
#include "IMotorController.hpp"
#include <cstring>
#include "stdint.h"


class UARTDriver : public ISerialCommunication
{
    public:
    UARTDriver(void);
    UARTDriver(uint8_t tx_pin, uint8_t rx_pin, uint8_t output_pin);
    bool ReceiveSerialMessage(char*) override;
    void SendSerialMessage(const char*) override;
    bool IsSerialAvailable(void) override;

    UARTCommand ParseCommand(const char* message); // Parse a string into a UARTCommand
    void ExecuteCommand(UARTCommand command);      // Execute a UARTCommand
    IMotorController& motorController;

    private:
    uint8_t uart_tx_pin; 
    uint8_t uart_rx_pin;
    uint8_t uart_output_pin;

    static constexpr int BUFFER_SIZE = 100; // Max buffer size
    char buffer[BUFFER_SIZE];               // Buffer for received messages
}; 