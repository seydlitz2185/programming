#include <gtest/gtest.h>
#include <list/stack.h>
#include <random>
#include <vector>
#include <functional>

using std::cin;
using std::cout;
using std::vector;

TEST(stack_test, Simple_Stack)
{
    int size = 10;
    SeqStack s;
    EXPECT_TRUE(s.isEmpty());
    for (int i = 0; i < size; i++)
    {
        s.push(i + 1);
    }
    for (int i = size; i > 0; i--)
    {
        EXPECT_EQ(s.top(), i);
        s.pop();
    }
    EXPECT_TRUE(s.isEmpty());
}