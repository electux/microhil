#include "test_mhserial.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Test convert baud rate to uint
/// @param MHSerialComTest is test fixture
/// @param ReadTest is test name
// TEST_F(MHSerialComTest, ReadTest)
// {
//     MHVecByte data{};
//     const MHString device = "/dev/ttyUSB0";
//     const MHSerialParams params = {
//         .baudRate = BaudRate::BAUD_115200,
//         .dataBits = CharacterSize::CHAR_SIZE_8,
//         .parity = Parity::PARITY_NONE,
//         .stopBits = StopBits::STOP_BITS_1
//     };

//     m_serial.setup(device, params);
//     EXPECT_NO_THROW(m_serial.read(data, 64, 100));
// }
