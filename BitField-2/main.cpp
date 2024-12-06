#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "BitField.h"


int main(int argc, char **argv) {

    BitField bff = BitField(23);
    size_t t = 8;
    bff.SizeT(t);
    std:: cout << bff << std::endl;

    // ::testing::InitGoogleTest(&argc, argv);

    // return RUN_ALL_TESTS();
}