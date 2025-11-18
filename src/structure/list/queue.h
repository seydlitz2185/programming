#include <iostream>
#include <math.h>
/*
@author: Steven Yu 2024/12/10
 */
#ifndef Elemtype
#define Elemtype int
#endif
const int N = 10010;//MSCV下N太大会导致queue内存不足，工程中应使用vector
const int maxSize = 100;
using std::cin;
using std::cout;
using std::endl;

// 非循环顺序队列，用数组模拟
//hh指向队头（初始为0），队头弹出
//tt指向队尾前一个元素（初始为-1），队尾插入
typedef struct SquentialQueue
{
    Elemtype q[N], hh=0, tt = -1;

    void enqueue(int x)
    {
        q[++tt] = x;
    }

    bool isEmpty()
    {
        return hh > tt;
    }

    void dequeue()
    {
        hh++;
    }

    Elemtype back ()
    {
        return q[tt+1];
    }

    Elemtype front ()
    {
        return q[hh];
    }
} SeqQueue;

//循环顺序队列，长度为100
//判断方法为空一个队列元素,队尾指针指向队尾下一块空余位置，每次入队先放元素再增加指针
//约定队头指针在队尾指针的下一个位置（即队尾的下两个位置）上时队满（尽管此时还空一位置）
typedef struct CircularQueue{

    Elemtype q[maxSize], hh=0,tt=0;
//循环队列为空的条件 hh == tt
    bool isEmpty(){
        return hh == tt;
    }
//循环队列满的条件 (队尾的下一个位置是队头)
    bool isFull(){
        return (( tt + 1 ) % maxSize )== hh;
    }
//循环队列计算大小：（队尾-队头+长度）%长度
    int size(){
        return ( tt - hh + maxSize) % maxSize;
    }
    void enqueue(Elemtype e){
        q[(tt++)%maxSize] = e;
    }

    void dequeue(){
        hh =(hh+1) % maxSize;
    }

    Elemtype front(){
        return q[hh];
    }

    Elemtype back(){
        return q[(tt-1)%maxSize];
    }
}CirQueue;

//简单小根堆，只支持插入元素和删除堆顶元素
typedef struct simple_priority_queue{
    int h[N],size=0;//h[0]空置，元素从h[1]开始存放

    void init(){
        memset(h,0,N);
    }
    //层序打印二叉堆
    void printPQ(){
        printf("%d\n",h[1]);
        for(int i = 0; (2<<(i)) < size;i++){
            for(int j = (2<< i); j<(2<<(i+1));j++){
                printf("%d ",h[j]);
            }
            printf("\n");
        }
    }
    void swap(int & a, int &b){
        int i  = a;
        a = b;      
        b = i;
    }

    void down(int u){
        //先找到u，u的左右子结点中的最小值，存放在t中
        int t = u;
        if(u*2 <=size && h[u*2] < h[t]) t =u *2;
        if(u*2+1 <=size && h[u*2 + 1] < h[t]) t =u *2+1;
        //只要根节点不最小值，递归调用down
        if(u != t){
            swap(h[u],h[t]);
            down(t);
        }
    }

    void up(int u){
        while(u/2 && h[u/2] > h[u]){
            swap(h[u/2],h[u]);
            u /=2; 
        }
    }

    void push(int x){
        h[++size] = x;
        up(size);
    }
    int top(){
        return h[1];
    }
    void pop(){
        h[1] = h[size--];//h[0]空置，若只有一个元素，则h[1]更新为0
        down(1);
    }
}simple_PQueue;

//在小根堆基础上支持1）删除第k个元素2）修改第k个元素
typedef struct priorty_queue{
    //ph[k]存放第k个插入的元素在h中的下标；（下标映射到堆）
    //hp[j]存放堆中的第j个元素是第几次插入的（堆映射到下标）
    //m记录第m次插入操作；
    int h[N],ph[N],hp[N],m=0,size=0;

    void init(){
        memset(h,0,N);
        memset(ph,0,N);
        memset(hp,0,N);
    }
    void printPQ(){
        printf("%d\n",h[1]);
        for(int i = 0; (2<<(i)) < size;i++){
            for(int j = (2<< i); j<(2<<(i+1));j++){
                printf("%d ",h[j]);
            }
            printf("\n");
        }
    }

        void swap(int & a, int &b){
        int i  = a;
        a = b;      
        b = i;
    }

    void heap_swap(int a,int b){
        //顺序不能乱，先修改ph，再修改hp，最后修改h;
        swap(ph[hp[a]],ph[hp[b]]);
        swap(hp[a],hp[b]);
        swap(h[a],h[b]);
    }

    void down(int u){
        //先找到u，u的左右子结点中的最小值，存放在t中
        int t = u;
        if(u*2 <=size && h[u*2] < h[t]) t =u *2;
        if(u*2+1 <=size && h[u*2 + 1] < h[t]) t =u *2+1;
        //只要根节点不最小值，递归调用down
        if(u != t){
            heap_swap(u,t);
            down(t);
        }
    }
    void up(int u){
        while(u/2 && h[u/2] > h[u]){
            heap_swap(u/2,u);
            u /=2; 
        }
    }
    void push(int x){
        size ++;
        m++;
        ph[m] = size,hp[size] = m;
        h[size]  =x;
        up(size);
    }
    int top(){
        return h[1];
    }
    void pop(){
        heap_swap(1,size--);
        down(1);
    }

    void pop_k(int k){
        k = ph[k];
        heap_swap(k,size--);
        down(k),up(k);
    }
    void update(int k, int x){
        k = ph[k];
        h[k] = x;
        down(k),up(k);
    }
}PQueue;