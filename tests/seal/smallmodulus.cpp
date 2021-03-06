// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include "gtest/gtest.h"
#include "seal/smallmodulus.h"

using namespace seal;
using namespace std;

namespace SEALTest
{
    TEST(SmallModulusTest, CreateSmallModulus)
    {
        SmallModulus mod;
        ASSERT_TRUE(mod.is_zero());
        ASSERT_EQ(0ULL, mod.value());
        ASSERT_EQ(0, mod.bit_count());
        ASSERT_EQ(1ULL, mod.uint64_count());
        ASSERT_EQ(0ULL, mod.const_ratio()[0]);
        ASSERT_EQ(0ULL, mod.const_ratio()[1]);
        ASSERT_EQ(0ULL, mod.const_ratio()[2]);

        mod = 3;
        ASSERT_FALSE(mod.is_zero());
        ASSERT_EQ(3ULL, mod.value());
        ASSERT_EQ(2, mod.bit_count());
        ASSERT_EQ(1ULL, mod.uint64_count());
        ASSERT_EQ(6148914691236517205ULL, mod.const_ratio()[0]);
        ASSERT_EQ(6148914691236517205ULL, mod.const_ratio()[1]);
        ASSERT_EQ(1ULL, mod.const_ratio()[2]);

        SmallModulus mod2(2);
        SmallModulus mod3(3);
        ASSERT_TRUE(mod != mod2);
        ASSERT_TRUE(mod == mod3);

        mod = 0;
        ASSERT_TRUE(mod.is_zero());
        ASSERT_EQ(0ULL, mod.value());
        ASSERT_EQ(0, mod.bit_count());
        ASSERT_EQ(1ULL, mod.uint64_count());
        ASSERT_EQ(0ULL, mod.const_ratio()[0]);
        ASSERT_EQ(0ULL, mod.const_ratio()[1]);
        ASSERT_EQ(0ULL, mod.const_ratio()[2]);

        mod = 0xF00000F00000F;
        ASSERT_FALSE(mod.is_zero());
        ASSERT_EQ(0xF00000F00000FULL, mod.value());
        ASSERT_EQ(52, mod.bit_count());
        ASSERT_EQ(1ULL, mod.uint64_count());
        ASSERT_EQ(1224979098644774929ULL, mod.const_ratio()[0]);
        ASSERT_EQ(4369ULL, mod.const_ratio()[1]);
        ASSERT_EQ(281470698520321ULL, mod.const_ratio()[2]);
    }

    TEST(SmallModulusTest, SaveLoadSmallModulus)
    {
        stringstream stream;

        SmallModulus mod;
        mod.save(stream);

        SmallModulus mod2;
        mod2.load(stream);
        ASSERT_EQ(mod2.value(), mod.value());
        ASSERT_EQ(mod2.bit_count(), mod.bit_count());
        ASSERT_EQ(mod2.uint64_count(), mod.uint64_count());
        ASSERT_EQ(mod2.const_ratio()[0], mod.const_ratio()[0]);
        ASSERT_EQ(mod2.const_ratio()[1], mod.const_ratio()[1]);
        ASSERT_EQ(mod2.const_ratio()[2], mod.const_ratio()[2]);

        mod = 3;
        mod.save(stream);
        mod2.load(stream);
        ASSERT_EQ(mod2.value(), mod.value());
        ASSERT_EQ(mod2.bit_count(), mod.bit_count());
        ASSERT_EQ(mod2.uint64_count(), mod.uint64_count());
        ASSERT_EQ(mod2.const_ratio()[0], mod.const_ratio()[0]);
        ASSERT_EQ(mod2.const_ratio()[1], mod.const_ratio()[1]);
        ASSERT_EQ(mod2.const_ratio()[2], mod.const_ratio()[2]);

        mod = 0xF00000F00000F;
        mod.save(stream);
        mod2.load(stream);
        ASSERT_EQ(mod2.value(), mod.value());
        ASSERT_EQ(mod2.bit_count(), mod.bit_count());
        ASSERT_EQ(mod2.uint64_count(), mod.uint64_count());
        ASSERT_EQ(mod2.const_ratio()[0], mod.const_ratio()[0]);
        ASSERT_EQ(mod2.const_ratio()[1], mod.const_ratio()[1]);
        ASSERT_EQ(mod2.const_ratio()[2], mod.const_ratio()[2]);
    }
}
