# ISerial Interface

## Overview
The `ISerial` interface defines the contract for configuring serial port parameters and provides utility methods to convert between LibSerial enums and generic numeric types for easier configuration handling.

### Methods
- `bool setup(const SerialParams &params)`: Configures the serial port with specific parameters.
- `void setBaudRate(BaudRate baudRate)`: Sets the baud rate for the serial port.
- `void setCharacterSize(CharacterSize characterSize)`: Sets the character size for the serial port.
- `void setParity(Parity parity)`: Sets the parity mode for the serial port.
- `void setStopBits(StopBits stopBits)`: Sets the number of stop bits for the serial port.
- `void setFlowControl(FlowControl flowControl)`: Sets the flow control mode for the serial port.

## Mocking Example
Below is an example of how to mock the `ISerial` interface for unit testing using Google Test:

```cpp
#include <gmock/gmock.h>
#include <com/iserial.h>

class MockISerial : public Electux::App::Com::ISerial {
public:
    MOCK_METHOD(bool, setup, (const SerialParams &params), (override));
    MOCK_METHOD(void, setBaudRate, (BaudRate baudRate), (override));
    MOCK_METHOD(void, setCharacterSize, (CharacterSize characterSize), (override));
    MOCK_METHOD(void, setParity, (Parity parity), (override));
    MOCK_METHOD(void, setStopBits, (StopBits stopBits), (override));
    MOCK_METHOD(void, setFlowControl, (FlowControl flowControl), (override));
};

// Example Test
TEST(MockISerialTest, SetupTest) {
    MockISerial mockSerial;
    SerialParams params{"/dev/ttyS0", BaudRate::BAUD_9600, CharacterSize::CHAR_SIZE_8, Parity::PARITY_NONE, StopBits::STOP_BITS_1, FlowControl::FLOW_CONTROL_NONE};

    EXPECT_CALL(mockSerial, setup(params)).WillOnce(::testing::Return(true));

    ASSERT_TRUE(mockSerial.setup(params));
}
```