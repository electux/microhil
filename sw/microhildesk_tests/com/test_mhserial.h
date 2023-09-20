#pragma once

#include <gtest/gtest.h>
#include "microhil_serial_com.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Fixture for MHSerialCom tests
class MHSerialComTest : public ::testing::Test
{
protected:
    MHSerialCom m_serial;

    void SetUp() override
    {
        // Setup code that will be called before each test
        // You can initialize the MHSerialCom instance or any other setup here
    }

    void TearDown() override
    {
        // Teardown code that will be called after each test
    }
};
