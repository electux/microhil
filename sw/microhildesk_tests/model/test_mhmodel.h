#pragma once

#include <gtest/gtest.h>
#include "microhil_model.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Fixture for MHModelTest tests
class MHModelTest : public ::testing::Test
{
protected:
    MHModel model;

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
