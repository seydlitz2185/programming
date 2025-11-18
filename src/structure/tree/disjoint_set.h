#include <iostream>

using namespace std;
const int N = 100010;

// 并查集，每个集合的根结点为-n，表示集合内元素个数，
//合并时进行路径压缩
typedef struct disjoint_set
{
    int p[N];
    void init(int n){
        for(int i = 1; i<=n; i++) p[i] = -1;
    }
    int size(int k){
        return -p[find(k)];
    }

    int find(int x){
        if(p[x] > 0) x = find(p[x]);
        return x;
    }

    //把a和b所在的集合合并为一个集合；
    //路径压缩，把a的每一个结点都直接连接到b的根结点上
    void merge(int a,int b){
        int t = p[a];
        while(t > 0){
            p[a] = find(b);
            p[find(b)] --;
            //每次同时追踪a与a的父结点
            a = p[t];
            t = p[a];
        }
        //处理a所在集合只有一个点的情况
        p[a] = find(b);
        p[find(b)]--;
    }
} DisjointSet;
