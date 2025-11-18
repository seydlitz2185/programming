#include "graph.h"
#include "../list/My_Priority_Queue_Sample.h"
#include <limits>

using std::to_string;
using std::priority_queue;
using std::numeric_limits;
typedef pair<vertex*,double>distance; 
typedef map<vertex*,double>dist_to;
typedef map<vertex*,vertex*>edge_to;
typedef map<vertex*,bool> marked;
struct cmp {
    bool operator()(distance a, distance b){
        return a.second > b.second;
    }
};
typedef My_Priority_Queue<distance, vector<distance>,cmp> frienge;

graph init_directed_graph(){
    graph g;
    g.addvertex("0");
    g.addvertex("1");
    g.addvertex("2");
    g.addvertex("3");
    g.addvertex("4");
    g.addvertex("5");
    g.addvertex("6");
    g.addedge("0","1",2.0);
    g.addedge("0","2",1.0);
    g.addedge("1","2",5.0);
    g.addedge("1","4",3.0);
    g.addedge("1","3",11.0);
    g.addedge("2","5",15.0);
    g.addedge("3","4",2.0);
    g.addedge("4","2",1.0);
    g.addedge("4","6",5.0);
    g.addedge("4","5",4.0);
    g.addedge("6","3",1.0);
    g.addedge("6","5",1.0);
    g.printvertex();
    g.printedge();
    return g;
}

graph init_undirected_graph(){
    graph g;
    g.addvertex("0");
    g.addvertex("1");
    g.addvertex("2");
    g.addvertex("3");
    g.addvertex("4");
    g.addvertex("5");
    g.addvertex("6");
    g.addedge("0","1",2.0);
    g.addedge("1","0",2.0);
    g.addedge("0","2",1.0);
    g.addedge("2","0",1.0);
    g.addedge("1","2",5.0);
    g.addedge("2","1",5.0);
    g.addedge("1","4",3.0);
    g.addedge("4","1",3.0);
    g.addedge("1","3",11.0);
    g.addedge("3","1",11.0);
    g.addedge("2","5",15.0);
    g.addedge("5","2",15.0);
    g.addedge("3","4",2.0);
    g.addedge("4","3",2.0);
    g.addedge("4","2",1.0);
    g.addedge("2","4",1.0);
    g.addedge("4","6",5.0);
    g.addedge("6","4",5.0);
    g.addedge("4","5",4.0);
    g.addedge("5","4",4.0);
    g.addedge("6","3",1.0);
    g.addedge("3","6",1.0);
    g.addedge("6","5",1.0);
    g.addedge("5","6",1.0);
    g.printvertex();
    g.printedge();
    return g;
}

void init_frienge(graph g, const string  &origin,frienge &f,dist_to &d,edge_to &e){
    graph::vmap::iterator it;
    //cout<<"initing frienge:\n";
   //cout<<"{ "; 
    for (it = g.work.begin();it!=g.work.end();++it){
        distance dist;
        dist.first = it->second;
        if(dist.first->name==origin){
            dist.second=0;
            f.push(dist);
                //cout<<"distance("<<dist.first->name<<", "<<dist.second<<"),"<<"\n";
            e[dist.first]=dist.first;
        }else{
            dist.second=numeric_limits<double>::max();
            e[dist.first]=NULL;
        }
        d[dist.first]=dist.second;    
        
    }
    // cout<<"}\n"; 
}

dist_to dijkstra( graph g,const string  &origin){
    dist_to d;
    edge_to e;
    frienge f;
    graph::vmap::iterator it = g.work.find(origin);
    dist_to::iterator itrd;
    edge_to::iterator itre;
    if (it == g.work.end()){
        cout<<"vertex does not exist!\n";
        return d;
    }
    init_frienge(g,origin,f,d,e);
    while(!f.empty()){
        vertex *v = f.top().first;
        double length = f.top().second;
        for(int i=0;i<v->adj.size();i++){
            distance temp;
            temp.first =v->adj[i].second;
            if( (d[v]+v->adj[i].first) < d[temp.first]){
                temp.second =  d[v]+v->adj[i].first;
                d[temp.first]=temp.second;
                e[temp.first]=v;
                f.push(temp);
            }
        }
        f.pop();
    }
    for (itrd = d.begin(); itrd!= d.end(); itrd++){
        cout<<itrd->first->name<<" shortest distance is "<<itrd->second<<"\n";
    }
    for (itre = e.begin(); itre!= e.end(); itre++){
        cout<<itre->first->name<<" comes  from  "<<itre->second->name<<"\n";
    }
    return d;
}

graph prim( graph g,const string  &origin){
    graph mst;
    dist_to d;
    edge_to e;
    marked m;
    frienge f;
    graph::vmap::iterator it = g.work.find(origin);
    dist_to::iterator itrd;
    edge_to::iterator itre;
    if (it == g.work.end()){
        cout<<"vertex does not exist!\n";
        return mst;
    }
    init_frienge(g,origin,f,d,e);
    while(!f.empty()){
        vertex *v = f.top().first;
        double length = f.top().second;
        m[v]=true;
        for(int i=0;i<v->adj.size();i++){
            distance temp;
            temp.first =v->adj[i].second;
            if(m[temp.first]){
                continue;
            }
            if( (v->adj[i].first) < d[temp.first]){
                temp.second =  v->adj[i].first;
                d[temp.first]=temp.second;
                e[temp.first]=v;
                f.push(temp);
            }
        }
        f.pop();
    }
    for (itrd = d.begin(); itrd!= d.end(); itrd++){
        cout<<itrd->first->name<<" shortest distance is "<<itrd->second<<"\n";
    }
    for (itre = e.begin(); itre!= e.end(); itre++){
        cout<<itre->first->name<<" comes  from  "<<itre->second->name<<"\n";
    }
    return mst;
}
