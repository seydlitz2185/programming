#include <iostream>
/*
@author: Steven Yu 2024/12/04
 */
#ifndef Elemtype
#define Elemtype int
#endif
const int N = 10010;//MSCV下N太大会导致StaticDlinkList内存不足，工程中应使用vector
using std::cin;
using std::cout;
using std::endl;

// 静态非循环单链表 带头结点head和非法数组下标-1做尾指针
typedef struct StaticLinklist
{
    // head :idx of first node（head node‘s next)
    // e[i] :Data of ith node
    // ne[i]:Next pointer of ith node
    // idx:allocate new node data in e[idx],ne[idx];
    // idx cannot use as length ;
    int head, e[N], ne[N], idx;

    void init()
    {
        head = -1; // empty list
        idx = 0;
    }
    // add new node as first node in list
    void add_to_head(int x)
    {
        e[idx] = x;
        ne[idx] = head;
        head = idx;
        idx++;
    }
    // add new node before kth node
    // let new node became new kth node
    void add(int k, int x)
    {
        e[idx] = x;
        ne[idx] = ne[k];
        ne[k] = idx;
        idx++;
    }

    void remove(int k)
    {
        if (ne[k] == -1)
            return;
        ne[k] = ne[ne[k]];
    }

    // print list
    void print()
    {
        int i = head;
        while (i != -1)
        {
            cout << e[i] << " ";
            i = ne[i];
        }
        cout << endl;
    }
    int size()
    {
        int i = head, size = 0;
        while (i != -1)
        {
            i = ne[i];
            size++;
        }
        return size;
    }

} StaticLinklist;

// 静态非循环双链表，带头、尾结点，头指针0，尾指针1；
typedef struct StaticDLinklist
{
    // head :idx of first node（head node‘s next)
    // e[i] :Data of ith node
    // l[i]:left pointer of ith node
    // r[i]:right  pointer of ith node
    // idx:allocate new node data in e[idx],ne[idx];
    int e[N], l[N], r[N], idx;

    void init()
    {
        memset(e,0,N);
        memset(l,0,N);
        memset(r,0,N);
        r[0] = 1, l[1] = 0;
        idx = 2;
    }

    int size()
    {
        if (r[0] == 1)
            return 0;
        int p = r[0], cnt = 1;
        while (p != 1)
        {
            cnt++;
            p = r[p];
        }
        return cnt;
    }

    void print()
    {
        int p = r[0];
        while (p != 1)
        {
            cout << e[p] << ' ';
            p = r[p];
        }
        cout << endl;
    }

    // 在第k个结点右侧插入x
    // 调用之前检查k是否为尾结点，避免非法操作
    void add_right(int k, int x)
    {
        e[idx] = x;
        r[idx] = r[k];
        l[idx] = k;
        // 下面两行不可交换顺序，否则出错
        l[r[k]] = idx; // 先修改r[k]结点(即k结点的左指针）
        r[k] = idx;    // 再修改k结点的右指针
        idx++;
    }

    void add_left(int k, int x)
    {
        add_right(l[k], x);
    }

    void remove(int k)
    {
        r[l[k]] = r[k];
        l[r[k]] = l[k];
    }
} StaticDLinklist;

// 动态单链表
class DynamicList
{
private:
    typedef struct Node
    {
        Elemtype data;
        struct Node *next;
    } LNode, *LinkList;

    LinkList L;

public:
    // 动态链表初始化
    bool Init()
    {
        this->L = (LNode *)malloc(sizeof(LNode));
        L->next = NULL;
        return true;
    }
    // 返回表长
    int Length()
    {
        int cnt = 0;
        LNode *p = this->L;
        while (p->next != NULL)
        {
            p = p->next;
            cnt++;
        }
        return cnt;
    }
    // 查找第i个结点,失败则返回头结点
    LNode *GetElem(int i)
    {
        LNode *p = this->L;
        while (i-- > 0 && p != NULL)
            p = p->next;
        return p;
    }
    // 按值查找,返回第一个相同值的结点
    LNode *LocateElem(Elemtype e)
    {
        LNode *p = this->L;
        while (p->next != NULL && p->data != e)
            p = p->next;
        return p;
    }
    // 在第i个结点后插入值为x的新结点
    bool ListInsert(int i, Elemtype x)
    {
        LNode *p = this->GetElem(i);
        if (p == NULL)
            return false;
        LNode *q = (LNode *)malloc(sizeof(LNode));
        q->data = x;
        q->next = p->next;
        p->next = q;
        return true;
    }
    // 前插入实现：先做后插入，再交换两结点数据
    bool ListInsertFore(int i, Elemtype x)
    {
        LNode *p = this->GetElem(i);
        if (p == NULL)
            return false;
        LNode *q = (LNode *)malloc(sizeof(LNode));
        q->data = p->data;
        p->data = x;
        q->next = p->next;
        p->next = q;
        return true;
    }
    // 删除第i个结点，e用于返回被删除结点的值
    bool ListDelete(int i, Elemtype &e)
    {
        LNode *q = this->GetElem(i);
        if (q == NULL)
            return false;
        LNode *p = this->GetElem(i - 1);
        p->next = q->next;
        e = q->data;
        free(q);
        return true;
    }
    void ToList(Elemtype a[])
    {
        LNode *p = L->next;
        for (int i = 0; i < this->Length(); i++)
        {
            a[i] = p->data;
            p = p->next;
        }
    }
    void PrintList()
    {
        LNode *p = L->next;
        while (p->next != NULL)
        {
            p = p->next;
            cout << p->data << " ";
        }
        cout << endl;
    }
};
