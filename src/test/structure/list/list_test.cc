#include <gtest/gtest.h>
#include <list/list.h>
#include <random>
#include <vector>
#include <functional>

using std::cin;
using std::cout;
using std::vector;
TEST(list_test, StaticList_insertion_head)
{
    int size = 10;
    vector<int> a(size);
    a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> b(size);
    StaticLinklist L;
    L.init();

    // 头插入，每次将a[i]插入到表头
    for (int i = 0; i < size; i++)
    {
        L.add_to_head(a[i]);
    }

    // 从表头顺序读取链表
    int cnt = 0, idx = L.head;
    while (cnt < L.size())
    {
        b[cnt++] = L.e[idx];
        idx = L.ne[idx];
    }
    // 先检验表长是否相等
    // 注意如果删除过任意结点，idx不在表示表长；
    // EXPECT_EQ(size,L.size());
    EXPECT_EQ(size, L.size());
    // 检验b元素顺序是否为a的倒序
    for (int i = 0; i < size; i++)
    {
        // printf("%d\n",b[i]);
        EXPECT_EQ(a[size - i - 1], b[i]);
    }
}

TEST(list_test, StaticList_insertion_tail)
{
    int size = 10;

    vector<int> a(size);
    a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> b(size);
    StaticLinklist L;
    L.init();

    // 尾插入，每次将a[i]插入为L的第i个元素
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            L.add_to_head(a[i]);
        else
            L.add(i - 1, a[i]);
    }

    // 先检验表长是否相等
    EXPECT_EQ(size, L.size());
    // 检验b元素顺序是否与a相同
    int cnt = 0, idx = L.head;
    while (cnt < L.size())
    {
        b[cnt++] = L.e[idx];
        idx = L.ne[idx];
    }
    L.print();
    for (int i = 0; i < size; i++)
    {
        // printf("%d\n",b[i]);
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(list_test, StaticList_deletion)
{

    int size = 10;

    vector<int> a(size);
    a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> b(size);
    StaticLinklist L;
    L.init();

    // 尾插入，每次将a[i]插入为L的第i个元素
    for (int i = 0; i < size; i++)
    {
        if (i == 0)
            L.add_to_head(a[i]);
        else
            L.add(i - 1, a[i]);
    }
    // 移出后半段链表（向下取整）
    for (int i = 0; i < size / 2; i++)
    {
        a.pop_back();
        // 这个删除的实现不太好
        L.remove(size - 2 - i);
    }
    // 先检验表长是否相等
    EXPECT_EQ(a.size(), L.size());
    // 检验b元素顺序是否与a相同
    int cnt = 0, idx = L.head;
    while (cnt < L.size())
    {
        b[cnt++] = L.e[idx];
        idx = L.ne[idx];
    }
    /*
  L.print();
  for(auto x : a){
      cout<< x <<" ";
  }
  cout << endl;
  */
    for (int i = 0; i < size - size / 2; i++)
    {
        // printf("%d %d\n",a[i],b[i]);
        EXPECT_EQ(a[i], b[i]);
    }
}

TEST(list_test, DynamicList)
{
    int size = 10;
    DynamicList L;
    EXPECT_TRUE(L.Init());
    // 尾插入
    for (int i = 0; i < size; i++)
    {
        L.ListInsert(i, i + 1);
        EXPECT_EQ(L.GetElem(i + 1)->data, i + 1);
    }
    // 头插入，插入成功后链表应是中心对称的（回文串）
    for (int i = 0; i < size; i++)
    {
        L.ListInsertFore(1, i + 1);
    }
    // 检查是否是回文串
    vector<int> a(L.Length());
    int* b = &a[0];
    L.ToList(b);
    int l = 0, r = L.Length() - 1;
    while (l < r)
    {
        EXPECT_EQ(a[l], a[r]);
        l++, r--;
    }
}

TEST(list_test, StaticDLinklist){
    int size = 10;
    StaticDLinklist L;
    L.init();
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
            L.add_right(0, i + 1);
        else
            L.add_left(1, i + 1);
        // L.print();
    }
    vector<int> a(size);
    vector<int> b(size);
    int cnt = 0;
    for (int i = L.r[0], j = L.l[1]; (i != 1) && (j != 0); i = L.r[i], j = L.l[j])
    {
        a[cnt] = L.e[i];
        b[size - 1 - cnt] = L.e[j];
        cnt++;
        // printf("%d %d\n",L.e[i],L.e[j]);
    }
    /*
    for(int i = 0; i< size; i++){
        printf("%d %d\n",a[i],b[i]);
    }
    EXPECT_EQ(0,1);
    */
    int*c = &b[0];
    EXPECT_TRUE(std::equal(a.begin(),a.end(), c));
}
