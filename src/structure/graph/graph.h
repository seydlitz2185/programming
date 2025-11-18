#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::cout;
using std::string;
using std::pair;
using std::vector;
using std::map;
using std::make_pair;

//临接表存储的有向图
struct vertex 
{
    typedef pair<int, vertex*> ve;
    vector<ve> adj; //cost of edge, destination vertex
    string name;
    vertex(string s) : name(s) {}
};

class graph
{
public:
    typedef map<string, vertex *> vmap;//按键值对存储顶点名称及其对应的结构体的指针
    vmap work;
    void addvertex(const string&);
    void addedge(const string& from, const string& to, double cost);
    void printvertex();
    void printedge();
};

void graph::addvertex(const string &name)
{
     //使用迭代器按名称寻找是否已经有同名的顶点
    vmap::iterator itr = work.find(name);
    //如果不存在同名顶点，则可以插入一个新的顶点
    if (itr == work.end())
    {
        vertex *v;
        v = new vertex(name);
        work[name] = v;
        return;
    }
    cout << "\nVertex already exists!";
}

void graph::addedge(const string& from, const string& to, double cost)
{
    //从顶点表work中取出边的起点和终点，用pair
    vertex *f = (work.find(from)->second);
    vertex *t = (work.find(to)->second);
    //新建以pair存放一条边
    pair<int, vertex *> edge = make_pair(cost, t);
    f->adj.push_back(edge);
}


void graph::printvertex(){
    cout <<"vertices: ";
    for(vmap::iterator itr = work.begin();itr !=work.end(); ++itr){
        cout << itr->first << " ";
    } 
    cout <<"\n";
}

void graph::printedge(){
    cout <<"edges: (format: from vertex --cost-->to vertex)\n";
    for(vmap::iterator itr = work.begin();itr !=work.end(); ++itr){
        for(int i=0;i<itr->second->adj.size();i++){
             cout <<itr->first << "--"<< itr->second->adj[i].first <<"-->"<< itr->second->adj[i].second->name<< "\n";
        }
    } 
}