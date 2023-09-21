#pragma once

#include <gtest/gtest.h>
#include "microhil_log.h" 

////////////////////////////////////////////////////////////////////////////
/// @brief Fixture for MHLogTest tests
class MHLogTest : public ::testing::Test
{
protected:
    MHLog log;

    void SetUp() override
    {
        // Setup code that will be called before each test
        // You can initialize the MHConfig instance or any other setup here
    }

    void TearDown() override
    {
        // Teardown code that will be called after each test
    }
};
