#include <gtest/gtest.h>
#include <tree/disjoint_set.h>
// Demonstrate some basic assertions.
TEST(disjoint_set_Test, disjoint_set) {
    disjoint_set d;
    d.init(10);
    d.merge(0,1);
    d.merge(1,2);
    EXPECT_EQ(d.find(0),2);
  // Expect equality.
  EXPECT_EQ(d.size(1),2);
}