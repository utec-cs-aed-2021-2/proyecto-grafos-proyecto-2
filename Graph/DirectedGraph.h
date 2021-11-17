#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"
#include <stack>
#include <vector>

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    private: 
        std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    public:
    DirectedGraph() = default;
    ~DirectedGraph() {
        clear();
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
        if (!findVertex(id1) || !findVertex(id2)) return false;
        Vertex<TV,TE>* vert = vertexes[id1];
        Edge<TV,TE>* link = new Edge<TV,TE>;
        link->weight = w;
        link->vertex[0] = vertexes[id1];
        link->vertex[1] = vertexes[id2];
        vert->edges.push_front(link);
        return true;
    }    
 
    bool deleteVertex(string id)// MUY COSTOSO
    {
        if (!findVertex(id)) return false;
        Vertex<TV, TE>* vert = vertexes[id];
        vertexes.erase(id);
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            if (((it->second)->id) != id) {
                for (auto edge = (it->second)->edges.begin(); edge != (it->second)->edges.end(); edge++) {
                    if ((*edge)->vertex[1]->id == id) {
                        (it->second)->edges.erase(edge);
                    }
                }
            }
        }
        return true;
    }    

    bool deleteEdge(string id1, string id2)
    {
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((it->second)->vertex[1]->id == id2) {
                (it->second)->edges.erase(it);
            }
        }
    }   

    TE &operator()(string start, string end)
    {
        if (!findVertex(start) || !findVertex(end)) throw("No existe");

        for (auto it = vertexes[start]->edges.begin(); it != vertexes[end]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == end) {
                return (*it)->peso;
            }
        }
        // para grafo no dirigido
        for (auto it = vertexes[end]->edges.begin(); it != vertexes[end]->edges.end(); it++) {
            if ((*it)->vertex[0]->id == start) {
                return (*it)->peso;
            }
        }
    }  

    float density()
    {
        int edges = 0;
        int vertices = vertexes.size();
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            edges += (it->second)->edges.size();
        }
        return 1.0*(edges)/(vertices*(vertices-1)); 
    }

    bool isDense(float threshold = 0.5)
    {
        auto densidad = this->density();
        if(densidad>=threshold) return true;
        return false;
    }

    bool isConnected()
    {
        return isStronglyConnected();
    }

    bool isStronglyConnected() {
        unordered_map<string, bool> visitado;

        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            for (auto edge = (it->second)->edges.begin(); edge != (it->second)->edges.end(); edge++) {
                visitado[(*edge)->vertex[1]->id] = true;
            }
        }
        if (visitado.size() != vertexes.size()) return false;
        return true;
    }

    bool findEdge(string id1, string id2)
    {
        if(!findVertex(id1) || !findVertex(id2)) return false;
        
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id2) return true;
        }

        return false;
    }

    Edge<TV,TE>* getEdge(string id1, string id2)
    {
        if(!findVertex(id1) || !findVertex(id2)) throw("No existe vertice");
        
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id2) return (*it);
        }

        throw("No existe");
    }

    bool findVertex(string key)
    {
        if (vertexes.find(key) == vertexes.end())
            return false;
        return true;
    } 

    Vertex<TV, TE> getVertex(string key) {
        if (vertexes.find(key) == vertexes.end()) {
            throw("No existe");
        }
        return vertexes[key];
    }

    void clear() {
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            (it->second)->edges.clear();
        }
        vertexes.clear();
    }

    void displayVertex(string id)
    {
        if(!findVertex(id))
        {
            cout<<"Cant display, Vertex not present"<<endl;
            return;
        }
        cout<<"Vertex "<<id<<endl;
        cout<<"data: "<<vertexes[id]->data<<endl;
        cout<<"Edges: "<<endl;
        for(auto& it : vertexes[id]->edges )
            cout<<"("<<id<<","<<it->vertex[1]->id<<")"<<" ";
        cout<<endl<< endl;;
    }

    vector<Edge<TV, TE>*> DFS(string start) {
        vector<Edge<TV, TE>*> dfs_edges;

        unordered_map<string, bool> visitado;
        stack<Vertex<TV, TE>*> s;

        s.push(vertexes[start]);
        visitado[start] = true;

        Vertex<TV, TE>* actual = s.top();
        bool backtrack = true;
        while (visitado.size() != vertexes.size()) {
            backtrack = true;
            for (auto it = actual->edges.begin(); it != actual->edges.end(); it++) {
                if (visitado.find((*it)->vertex[1]->id) == visitado.end()) {
                    dfs_edges.push_back((*it));
                    s.push((*it)->vertex[1]);
                    visitado[(*it)->vertex[1]->id] = true;
                    backtrack = false;
                    break;
                }
            }
            actual = s.top();
            if (backtrack) s.pop();
        }
        return dfs_edges;
    }
    
    vector<Edge<TV, TE>*> BFS(string start) {
        vector<Edge<TV, TE>*> bfs_edges;

        queue<Vertex<TV, TE>*> q;
        unordered_map<string, bool> visitado;

        q.push(vertexes[start]);
        visitado[start] = true;

        Vertex<TV, TE>* actual = q.front();
        while (visitado.size() != vertexes.size()) {
            q.pop();
            for (auto it = actual->edges.begin(); it != actual->edges.end(); it++) {
                if (visitado.find((*it)->vertex[1]->id) == visitado.end()) {
                    bfs_edges.push_back((*it));
                    q.push((*it)->vertex[1]);
                    visitado[(*it)->vertex[1]->id] = true;
                }
            }
            actual = q.front();
        }
        return bfs_edges;
    }

    vector<Edge<TV, TE>*> prim(string start) {
        vector<Edge<TV, TE>*> prim_edges;
        auto comparador = [](Edge<TV, TE>* a, Edge<TV, TE>* b) {return a->weight > b->weight;};
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(comparador)> to_visit(comparador);
        unordered_map<string, bool> visitado;

        visitado[start] = true;
        Vertex<TV, TE>* actual;

        for (auto it = vertexes[start]->edges.begin(); it != vertexes[start]->edges.end(); it++) {
            to_visit.push((*it));
        }

        while (visitado.size() != vertexes.size()) {
            prim_edges.push_back(to_visit.top());
            visitado[to_visit.top()->vertex[1]->id] = true;
            actual = (to_visit.top())->vertex[1];
            for (auto it = actual->edges.begin(); it != actual->edges.end(); it++) {
                if (visitado.find((*it)->vertex[1]->id) == visitado.end()) {
                    to_visit.push((*it));
                }
            }
            to_visit.pop();
        }
        return prim_edges;
    }

    vector<Edge<TV, TE>*> kruskal() {
        auto comparador = [](Edge<TV, TE>* a, Edge<TV, TE>* b) {return a->weight > b->weight;};
        priority_queue<Edge<TV, TE>*, vector<Edge<TV, TE>*>, decltype(comparador)> to_visit(comparador);

        vector<Edge<TV, TE>*> kruskal_edges;

        unordered_map<string, bool> visitado;

        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            for (auto edge = (it->second)->edges.begin(); edge != (it->second->edges.end()); edge++) {
                to_visit.push((*edge));
            }
        }

        Edge<TV, TE>* actual;
        visitado[to_visit.top()->vertex[0]->id] = true;
        while (visitado.size() != vertexes.size()) {
            actual = to_visit.top();
            if (visitado.find(actual->vertex[0]->id) == visitado.end() && visitado.find(actual->vertex[1]->id) == visitado.end()) {
                visitado[actual->vertex[1]->id] = true;
                kruskal_edges.push_back(actual);
            }
            to_visit.pop();
        }
        
        return kruskal_edges;
    }
};

#endif