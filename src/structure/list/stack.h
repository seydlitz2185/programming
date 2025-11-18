#include <iostream>

#ifndef Elemtype
#define Elemtype int
#endif

using std::cin;
using std::cout;
using std::endl;

const int N = 100010;

// 顺序栈，用数组模拟
//tt永远指向栈顶上一个空位置
typedef struct SequentialStack
{
    Elemtype stk[N], tt = 0;

    void pop()
    {
        tt--;
    }

    Elemtype top()
    {
        return stk[tt];
    }

    bool isEmpty()
    {
        return tt == 0;
    }

    void push(Elemtype x)
    {
        stk[++tt] = x;
    }

} SeqStack;
