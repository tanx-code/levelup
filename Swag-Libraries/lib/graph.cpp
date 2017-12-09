#include<iostream>
#include<memory>
#include<deque>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<cassert>

template<typename T>
class Edge;


template<typename Vt, typename Et = int>
class Vertex
{
public:
    typedef Edge<Et>* EdgeType;
    Vertex(const Vt& d) : vData_(d) {}
    virtual ~Vertex() {}

public:
    Vt vData_;
    std::vector<EdgeType> outputs;
    std::vector<EdgeType> inputs;
};



template<typename T>
class Edge
{
public:
    Edge(Vertex<T> *t, const T& d) : target_(t), eData_(d) {}
    virtual ~Edge() {}

public:
    T eData_;
    Vertex<T> *target_;
};


template<typename Vt, typename Et = int>
class Graph
{
public:
    typedef Vertex<Vt,Et>* VertexPtr;
    typedef Edge<Et>* EdgePtr;
    Graph() {}
    virtual ~Graph() {}


public:
    void newEdge(VertexPtr source, VertexPtr target, Et data)
    {
        EdgePtr e = new Edge<Et>(target, data);
        source->outputs.push_back(e);
        edgeList_.push_back(std::shared_ptr<Edge<Et>>(e));
    }
    VertexPtr newVertex(const Vt& d)
    {
        VertexPtr v = new Vertex<Vt,Et>(d);
        vertexList_.push_back(std::shared_ptr<Vertex<Vt,Et>>(v));
        return v;
    }
    int getIndex(VertexPtr t)
    {
        int i = 0;
        for( ;i<vertexList_.size();i++){
            if(vertexList_[i].get() == t)
                return i;
        }
        return -1;
    }

    void destroy()
    {
        vertexList_.clear();
        edgeList_.clear();
    }
    void printGraph()
    {
        int m = 0,n = 0;
        for(auto i : vertexList_)
        {
            std::cout<<"Vertex<"<<m++<<">: vdata="<<i->vData_<<"\n";
            auto outs = i->outputs;
            for(auto j : outs)
            {
                std::cout<<"    "<<"Edge<"<< n++ << ">: edata=" << j->eData_
                        << " , To Vertex<" << getIndex(j->target_) << ">\n ";
            }
            std::cout<<"\n";
        }
    }





    void BFS(VertexPtr &start)
    {
        std::queue<VertexPtr> q;
        std::map<VertexPtr, bool> visit;

        for(auto i: vertexList_)
        {
            visit[i.get()] = false;
        }

        visit[start] = true;
        q.push(start);


        while(!q.empty())
        {
            VertexPtr node =  q.front();
            q.pop();



            for(auto edge : node->outputs)
            {
                if(!visit[edge->target_])
                {
                    visit[edge->target_] = true;
                    q.push(edge->target_);
                }
            }
        } 
    }

    void DFSHelper(VertexPtr &s, std::map<VertexPtr,bool> &visit)
    {
        if(!s) return;


        for(auto edge : s->outputs)
        {
            if(!visit[edge->target_])
            {
                visit[edge->target_] = true;
                DFSHelper(edge->target_, visit);
            }
        }
    }
    void DFS(VertexPtr &start)
    {
        std::map<VertexPtr,bool> visit;

        for(auto i : vertexList_)
        {
            visit[i.get()] = false;
        }

        DFSHelper(start, visit);
    }


    void DijkstraHelper(VertexPtr &s, std::map<VertexPtr,bool> &visit,
                        std::map<VertexPtr, int> &dist, std::map<VertexPtr, VertexPtr> &path)
    {
        if(!s) return;

        

        while(1)
        {
            int min = INT_MAX;
            VertexPtr u = nullptr;


            for(auto v : vertexList_)
            {
                if(dist[v.get()] < min && !visit[v.get()])
                {
                    min = dist[v.get()];
                    u = v.get();
                }
            }


            if(!u) break;

            visit[u] = true;

            for(auto edge : u->outputs)
            {
                if(!visit[edge->target_])
                {            
                    int d = dist[u] + edge->eData_;
                    // 如果当前的距离小于原来的距离，则更新结点的路径，距离信息
                    if(d < dist[edge->target_])
                    {
                        dist[edge->target_] = d;
                        path[edge->target_] = u;
                    }
                }
            }

        }

        
    }
    void Dijkstra(VertexPtr &start)
    {

        std::map<VertexPtr,bool>        visit;
        std::map<VertexPtr, int>        dist;
        std::map<VertexPtr, VertexPtr>  path;


        for(auto i : vertexList_)
        {
            visit[i.get()] = false;
            dist[i.get()] = INT_MAX;
            path[i.get()] = nullptr;
        }


        visit[start] = false;
        dist[start] = 0;
        path[start] = nullptr;

        DijkstraHelper(start, visit, dist, path);


        for(auto i : vertexList_)
        {
            if(i.get() == start)
            {
                std::cout<<i->vData_<<" "<<dist[i.get()]<<" nullptr"<<"\n";
                continue;
            }    
            std::cout<<i->vData_<<" "<<dist[i.get()]<<" "<<path[i.get()]->vData_<<"\n";
        }

    }

private:
    std::deque<std::shared_ptr<Vertex<Vt, Et> > > vertexList_;
    std::deque<std::shared_ptr<Edge<Et> > > edgeList_;

};



int main()
{
    {
        Graph<int> g;
        g.newEdge(g.newVertex(1), g.newVertex(2), 0);

        //g.printGraph();

        g.destroy();
    }


    {
        Graph<int> g;
        auto start = g.newVertex(8);
        auto n1 = g.newVertex(1);
        auto n2 = g.newVertex(2);
        auto n3 = g.newVertex(5);
        auto n4 = g.newVertex(3);
        auto n5 = g.newVertex(6);

        g.newEdge(start, n1, 1);
        g.newEdge(start, n2, 2);
        g.newEdge(start, n4, 3);
        g.newEdge(n2, n5, 2);
        g.newEdge(n1, n3, 2);
        g.newEdge(n4, n5, 2);
        g.newEdge(n3, n4, 2);


        g.BFS(start);

        g.DFS(start);

        g.Dijkstra(start);
    }

    return 0;
}