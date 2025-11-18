#include <gtest/gtest.h>
#include <list/queue.h>
#include <random>
#include <vector>
#include <functional>

using std::cin;
using std::cout;
using std::vector;

TEST(queue_test, Simple_Queue)
{
    int size = 10;
    SeqQueue q;
    EXPECT_TRUE(q.isEmpty());
    for (int i = 0; i < size; i++)
    {
        q.enqueue(i + 1);
    }
    for (int i = 0; i < size; i++)
    {
        EXPECT_EQ(q.front(), i+1);
        q.dequeue();
    }
    EXPECT_TRUE(q.isEmpty());
}

TEST(queue_test, CircularQueue)
{
    int size = 99;
    size = size%maxSize;//maxSize定义在queue.h中，防止循环队列溢出
    CirQueue q;
    EXPECT_TRUE(q.isEmpty());
    for (int i = 0; i < size; i++)
    {
        q.enqueue(i + 1);
    }
    EXPECT_TRUE((q.isFull()) == (size==maxSize-1));
    for (int i = 0; i < size; i++)
    {
        EXPECT_EQ(q.front(), i+1);
        q.dequeue();
    }
    EXPECT_TRUE(q.isEmpty());
}

TEST(queue_test, simple_PQueue){
    simple_PQueue pq;
    int n = 15;
    
    for(int i = 0; i < n;i++){
        pq.push(i+1);
    }
    pq.printPQ();
    for(int i =0 ; i<n ; i++){
        EXPECT_EQ(pq.top(),i+1);
        pq.pop();
    }
}

TEST(queue_test, PQueue){
    priorty_queue pq;
    //pq.init();
    /*
    int n = 15;
    
    for(int i = 0; i < n;i++){
        pq.push(i+1);
    }
    pq.pop_k(7);
    for(int i = 7; i<n;i++){
        pq.update(i,i);
    }
    pq.printPQ();
    EXPECT_EQ(1,1);
    */
}