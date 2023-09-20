#pragma once

#include <gtest/gtest.h>
#include "microhil_config.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Fixture for MHConfig tests
class MHConfigTest : public ::testing::Test
{
protected:
    MHConfig m_config;

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
