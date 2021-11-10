#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
/*
template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    std::list<Edge<TV, TE>*> edges;
};

template<typename TV, typename TE>
class Graph{
private:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
*/
template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    public:
    UnDirectedGraph()
    {
        Graph<TV,TE>();
    }
   /* bool deleteVertex(string id) = 0;     
    bool deleteEdge(string id) = 0;   
    TE &operator()(string start, string end)= 0;  
    float density() = 0;
    bool isDense(float threshold = 0.5) = 0;
    bool isConnected()= 0;
    bool isStronglyConnected() throw();
    bool empty();
    void clear()= 0;  
      
    void displayVertex(string id)= 0;
    bool findById(string id) = 0;
    void display() = 0;*/
};

#endif