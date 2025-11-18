#include <gtest/gtest.h>
#include <pattern_matching/KMP.h>
#include <string.h>
// Demonstrate some basic assertions.
TEST(kmp_test, simple_kmp) {
    //这个例子来自于大二数据结构课上的例子
    //南京农业大学信息管理与信息系统专业 2020年9月
    //上课讲师为刘浏
    char s[12] ={'a','b','a','b','a','a','b','a','a','b','a','c'};
    int n = 12;
    char p[7] = {'a','b','a','a','b','a','c'};
    int m = 7;
    KMP k;
    k.Init(s,p,n,m);
    k.get_next();
    int match = k.match();
    EXPECT_EQ(match,6);
}

TEST(kmp_test, nextVal) {
    char s[10] ={'a','a','a','b','a','a','a','a','a','b'};
    int n = 10;
    char p[5] = {'a','a','a','a','b'};
    int m = 5;
    KMP k;
    k.Init(s,p,n,m);
    k.get_nextVal();
    int match = k.match_nextVal();
    EXPECT_EQ(match,6);
}

TEST(kmp_test, sentence) {
    string sentence = "The quick brown fox jumps over a lazy dog";
    int n = (int)sentence.size();
    char s[10010];
    strcpy(s,sentence.c_str());
    string word = "jump";
    int m = (int)word.size();
    char p[10010] ;
    strcpy(p,word.c_str());
    KMP k;
    k.Init(s,p,n,m);
    k.get_nextVal();
    int match = k.match_nextVal();
    EXPECT_EQ(match,21);
}
