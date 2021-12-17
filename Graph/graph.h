#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////
template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertex[2];
    TE weight;
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
    double lat; //x
    double lon; //y
    std::list<Edge<TV, TE>*> edges;
    string id;
};

template<typename TV, typename TE>
class Graph{
protected:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    
public:
    Graph() = default;

    ~Graph()
    {

    }

    bool insertVertex(string id, TV vertex)
    {
        Vertex<TV,TE>* vert = new Vertex<TV,TE>;
        vert->data = vertex;
        vert->id = id;
        vertexes[id] = vert;
        return true;
    }  

    bool createEdge(string id1, string id2, TE w)
    {
        if (!check_key(id1) || !check_key(id2)) return false;
        Vertex<TV,TE>* vert = vertexes[id1];
        Edge<TV,TE>* link = new Edge<TV,TE>;
        link->weight = w;
        link->vertex = vertexes[id2];
        vert->edges.push_front(link);
        return true;
    }    

    bool deleteVertex(string id)
    {
        if (!check_key(id)) return false;
        Vertex<TV, TE>* vert = vertexes[id];
        vertexes.erase(id);
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            if ((it->second) != vert) {
                for (auto edge = (it->second)->edges->begin(); edge != (*it)->edges->end(); edge++) {
                    if ((*edge) == vert) {
                        (*it)->edges.erase(edge);
                    }
                }
            }
        }
    }    

    bool deleteEdge(string id1, string id2) // O(k): k es la cantidad de edges de un vertice
    {
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((it->second)->vertex->id == id2) {
                (it->second)->edges.erase(it);
            }
        }
        // para grafo no dirigido
        for (auto it = vertexes[id2]->edges.begin(); it != vertexes[id2]->edges.end(); it++) {
            if ((it->second)->vertex->id == id1) {
                (it->second)->edges.erase(it);
            }
        }
    }   

    TE &operator()(string start, string end)
    {
        if (!check_key(start) || !check_key(end)) throw("No existe");

        for (auto it = vertexes[start]->edges.begin(); it != vertexes[end]->edges.end(); it++) {
            if ((*it)->vertex->id == end) {
                return (*it)->peso;
            }
        }
        // para grafo no dirigido
        for (auto it = vertexes[end]->edges.begin(); it != vertexes[end]->edges.end(); it++) {
            if ((*it)->vertex->id == start) {
                return (*it)->peso;
            }
        }
    }  

    float density() //O(n)
    {
        int edges = 0;
        int vertices = vertexes.size();
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            edges += (it->second)->edges.size();
        }
        return 2.0*(edges)/(vertices*(vertices-1)); 
    }

    bool isDense(float threshold = 0.5)
    {
        float densidad = this->density();
        if(densidad >= threshold) return true;
        return false;
    }
    
    bool isConnected()
    {
        for (auto entrada = vertexes.begin(); entrada != vertexes.end(); entrada++) {
            for (auto salida = vertexes.begin(); salida != vertexes.end(); salida++) {
                if (!hasPath((entrada->second)->id, (salida->second)->id)) return false;
            }
        }
        return true;
    }

    bool hasPath(string start, string end) {
        if (start == end) return true;
        for (auto it = vertexes[start]->edges.begin(); it != vertexes[start]->edges.end(); it++) {
            return hasPath((*it)->vertex->id, end);
        }
        return false;
    }
    //bool isStronglyConnected() throw();
    
    bool empty()
    {
        return vertexes.empty();
    }
    void clear()
    {
        while(!vertexes.empty())
        {
            auto beg = vertexes.begin();
            deleteVertex(beg->first);
        }
    } 
    
    bool check_key(string key)
    {
        if (vertexes.find(key) == vertexes.end())
            return false;
        return true;
    }    
      
    void displayVertex(string id) // O(E)
    {
        if(!check_key(id))
        {
            cout<<"Cant display, Vertex not present"<<endl;
            return;
        }
        cout<<"id:   "<<id<<endl;
        cout<<"data: "<<vertexes[id]->data<<endl;
        cout<<"Edges: "<<endl;
        for(auto& it : vertexes[id]->edges )
            cout<<"( "<<id<<","<<it->vertex->id<<")"<<" ";
        cout<<endl;
    }
    
    bool findByIdV(string id)// O(1)
    {
        if(!check_key(id))
        {
            return false;
        }
        return true;
    }

    //void display() = 0;
};

#endif