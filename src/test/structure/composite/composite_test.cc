#include <gtest/gtest.h>
#include <composite/enum.h>
#include <composite/union.h>

// Demonstrate some basic assertions.
TEST(enum_Test, enum) {
    spectrum band;
    band = infrared;
    EXPECT_EQ(band,0);
    //band++; cannot increment expression of enum type 'spectrum'
    int color = blue ;
    EXPECT_EQ(color,5);
}

TEST(union_Test, union) {
    one4all pail;
    pail.int_val = 15;
    EXPECT_EQ(pail.int_val,15);
    pail.double_val = 1.0;
    EXPECT_EQ(pail.double_val,1.0);
    pail.char_val = 'c';
    EXPECT_EQ(pail.char_val,'c');
}