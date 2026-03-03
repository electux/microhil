# ILibSerialPort Interface

## Overview
The `ILibSerialPort` interface abstracts the `LibSerial::SerialPort` class, enabling dependency injection and mocking for unit testing. It provides methods to configure and interact with a serial port.

### Methods
- `void Open(const std::string &device)`: Opens the serial port device.
- `void Close()`: Closes the serial port device.
- `bool IsOpen() const`: Checks if the serial port is currently open.
- `void Read(std::vector<uint8_t> &data, size_t len)`: Reads data from the serial port.
- `void Write(const std::vector<uint8_t> &data)`: Writes data to the serial port.
- `void SetBaudRate(BaudRate baudRate)`: Sets the baud rate for the serial port.
- `void SetCharacterSize(CharacterSize characterSize)`: Sets the character size for the serial port.
- `void SetParity(Parity parity)`: Sets the parity mode for the serial port.
- `void SetStopBits(StopBits stopBits)`: Sets the number of stop bits for the serial port.
- `void SetFlowControl(FlowControl flowControl)`: Sets the flow control mode for the serial port.

## Mocking Example
Below is an example of how to mock the `ILibSerialPort` interface for unit testing using Google Test:

```cpp
#include <gmock/gmock.h>
#include <com/ilib.h>

class MockILibSerialPort : public Electux::App::Com::ILibSerialPort {
public:
    MOCK_METHOD(void, Open, (const std::string &device), (override));
    MOCK_METHOD(void, Close, (), (override));
    MOCK_METHOD(bool, IsOpen, (), (const, override));
    MOCK_METHOD(void, Read, (std::vector<uint8_t> &data, size_t len), (override));
    MOCK_METHOD(void, Write, (const std::vector<uint8_t> &data), (override));
    MOCK_METHOD(void, SetBaudRate, (BaudRate baudRate), (override));
    MOCK_METHOD(void, SetCharacterSize, (CharacterSize characterSize), (override));
    MOCK_METHOD(void, SetParity, (Parity parity), (override));
    MOCK_METHOD(void, SetStopBits, (StopBits stopBits), (override));
    MOCK_METHOD(void, SetFlowControl, (FlowControl flowControl), (override));
};

// Example Test
TEST(MockILibSerialPortTest, OpenCloseTest) {
    MockILibSerialPort mockPort;
    EXPECT_CALL(mockPort, Open("/dev/ttyS0"));
    EXPECT_CALL(mockPort, Close());

    mockPort.Open("/dev/ttyS0");
    mockPort.Close();
}
```