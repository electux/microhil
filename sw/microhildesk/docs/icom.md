# ICom Interface

## Overview
The `ICom` interface defines the contract for managing communication port lifecycle (open/close), configuration, and data exchange (read/write).

### Methods
- `bool open()`: Opens the communication channel.
- `bool close()`: Closes the communication channel.
- `bool isOpen() const`: Checks if the communication channel is currently open.
- `void read(std::vector<uint8_t> &data, size_t len)`: Reads data from the communication channel.
- `void write(const std::vector<uint8_t> &data)`: Writes data to the communication channel.

## Mocking Example
Below is an example of how to mock the `ICom` interface for unit testing using Google Test:

```cpp
#include <gmock/gmock.h>
#include <com/icom.h>

class MockICom : public Electux::App::Com::ICom {
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(bool, close, (), (override));
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(void, read, (std::vector<uint8_t> &data, size_t len), (override));
    MOCK_METHOD(void, write, (const std::vector<uint8_t> &data), (override));
};

// Example Test
TEST(MockIComTest, OpenCloseTest) {
    MockICom mockCom;
    EXPECT_CALL(mockCom, open()).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockCom, close()).WillOnce(::testing::Return(true));

    ASSERT_TRUE(mockCom.open());
    ASSERT_TRUE(mockCom.close());
}
```