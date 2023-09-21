#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test the setup serial port
/// @param MHSerialComTest is test fixture
/// @param SetupTest is test name
TEST_F(MHSerialComTest, SetupTest)
{
    const MHString device = "/dev/ttyUSB0";
    const MHSerialParams params = {
        .baudRate = BaudRate::BAUD_115200,
        .dataBits = CharacterSize::CHAR_SIZE_8,
        .parity = Parity::PARITY_NONE,
        .stopBits = StopBits::STOP_BITS_1
    };

    EXPECT_NO_THROW(m_serial.setup(device, params));
}
