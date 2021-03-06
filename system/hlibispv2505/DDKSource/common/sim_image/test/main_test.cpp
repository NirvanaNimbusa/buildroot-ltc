/**
******************************************************************************
 @file main_test.cpp

 @brief Point of entry of the unit tests

 @copyright Imagination Technologies Ltd. All Rights Reserved.

 @license Strictly Confidential.
   No part of this software, either material or conceptual may be copied or
   distributed, transmitted, transcribed, stored in a retrieval system or
   translated into any human or computer language in any form by any means,
   electronic, mechanical, manual or other-wise, or disclosed to third
   parties without the express written permission of
   Imagination Technologies Limited,
   Unit 8, HomePark Industrial Estate,
   King's Langley, Hertfordshire,
   WD4 8LZ, U.K.

******************************************************************************/
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    int ret = EXIT_SUCCESS;

    ::testing::InitGoogleTest(&argc, argv);
    ret = RUN_ALL_TESTS();

    return ret;
}