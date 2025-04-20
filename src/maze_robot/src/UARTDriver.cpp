// #include "UARTDriver.hpp"
// #include "stm32f303xe.h"

// // Default constructor
// UARTDriver::UARTDriver() 
//     : uart_tx_pin(0), uart_rx_pin(0), uart_output_pin(0) {}

// // Parameterized constructor
// UARTDriver::UARTDriver(uint8_t tx_pin, uint8_t rx_pin, uint8_t output_pin)
//     : uart_tx_pin(tx_pin), uart_rx_pin(rx_pin), uart_output_pin(output_pin) {}

// // Parse a string into a UARTCommand
// UARTCommand UARTDriver::ParseCommand(const char* message) {
//     if (strcmp(message, "TURN_LEFT") == 0) {
//         return UARTCommand::TurnLeft;
//     } else if (strcmp(message, "TURN_RIGHT") == 0) {
//         return UARTCommand::TurnRight;
//     } else if (strcmp(message, "MOVE_FORWARD") == 0) {
//         return UARTCommand::MoveForward;
//     } else if (strcmp(message, "MOVE_BACKWARD") == 0) {
//         return UARTCommand::MoveBackward;
//     } else if (strcmp(message, "STOP") == 0) {
//         return UARTCommand::Stop;
//     } else {
//         return UARTCommand::Invalid; // Default for unrecognized commands
//     }
// }

// // Execute a parsed UARTCommand
// void UARTDriver::ExecuteCommand(UARTCommand command) {
//     switch (command) {
//         case UARTCommand::TurnLeft:
//             SendSerialMessage("Executing: Turn Left\r\n");
//              motorController.TurnLeft();  
//             break;

//         case UARTCommand::TurnRight:
//             SendSerialMessage("Executing: Turn Right\r\n");
//             motorController.TurnRight();
//             break;

//         case UARTCommand::MoveForward:
//             SendSerialMessage("Executing: Move Forward\r\n");
//             //Path clear and wall is maintained: Move forward
//             //Example pinOut
//             int forwardPin = 5;
//             motorController.MoveForward(forwardPin);
//             break;

//         case UARTCommand::MoveBackward:
//             SendSerialMessage("Executing: Move Backward\r\n");
//             motorController.MoveBackward();
//             break;

//         case UARTCommand::Stop:
//             SendSerialMessage("Executing: Stop\r\n");
//             motorController.Stop();
//             break;

//         case UARTCommand::Invalid:
//         default:
//             SendSerialMessage("Invalid Command\r\n");
//             break;
//     }
// }

// // Send a serial message
// void UARTDriver::SendSerialMessage(const char* message) {
//     while (*message) {
//         while (!(USART2->ISR & USART_ISR_TXE)); // Wait for transmit data register to be empty
//         USART2->TDR = *message++;
//     }
// }

// // Receive a serial message
// bool UARTDriver::ReceiveSerialMessage(char* message) {
//     int i = 0;
//     while (true) {
//         if (USART2->ISR & USART_ISR_RXNE) {
//             char c = USART2->RDR;
//             if (c == '\n' || c == '\r') { // End of message
//                 message[i] = '\0';
//                 return true;
//             } else if (i < BUFFER_SIZE - 1) {
//                 message[i++] = c;
//             }
//         }
//     }
// }

// // Check if serial data is available
// bool UARTDriver::IsSerialAvailable() {
//     return USART2->ISR & USART_ISR_RXNE; // Check if data is ready to read
// }
