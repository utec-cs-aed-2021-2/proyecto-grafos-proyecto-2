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

        if (vertexes[start]->edges.size() == 0) {
            cout << "Nodo sin nodos adyacentes" << endl;
            return dfs_edges;
        }

        s.push(vertexes[start]);
        visitado[start] = true;

        Vertex<TV, TE>* actual;
        bool backtrack = true;
        while (!s.empty()) {
            actual = s.top();
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
            if (backtrack) s.pop();
        }
        return dfs_edges;
    }
    
    vector<Edge<TV, TE>*> BFS(string start) {
        vector<Edge<TV, TE>*> bfs_edges;

        queue<Vertex<TV, TE>*> q;
        unordered_map<string, bool> visitado;

        if (vertexes[start]->edges.size() == 0) {
            cout << "Nodo sin nodos adyacentes" << endl;
            return bfs_edges;
        }

        q.push(vertexes[start]);
        visitado[start] = true;

        Vertex<TV, TE>* actual;
        while (!q.empty()) {
            actual = q.front();
            for (auto it = actual->edges.begin(); it != actual->edges.end(); it++) {
                if (visitado.find((*it)->vertex[1]->id) == visitado.end()) {
                    bfs_edges.push_back((*it));
                    q.push((*it)->vertex[1]);
                    visitado[(*it)->vertex[1]->id] = true;
                }
            }
            q.pop();
        }
        return bfs_edges;
    }

    // void dijkstra(TV start) {
    //     unordered_map<TV, TV> padres;
    //     unordered_map<TV, bool> visitados;
    //     unordered_map<TV, TE> costos;

    //     for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
    //         costos[(vert->first)] = INT_MAX;
    //     }
    //     cout << "Nodo incial: " << start << endl;

    //     costos[start] = 0;
    //     padres[start] = start;
        
    //     Vertex<TV, TE>* current; 
    //     TV key;
    //     while (visitados.size() != vertexes.size()) {
    //         TE min = INT_MAX;
    //         for (auto it = costos.begin(); it != costos.end(); it++) {
    //             if (it->second < min && (visitados.find(it->first) == visitados.end())) {
    //                 TV v = (it->first);
    //                 current = vertexes[v];
    //                 min = (it->second);
    //             }
    //         }
    //         key = current->data;
    //         for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
    //             TE current_costo = costos[key];
    //             TE nuevo_costo = current_costo + (*edge)->weight;
    //             if (nuevo_costo < costos[(*edge)->vertex[1]->data]) {
    //                 costos[(*edge)->vertex[1]->data] = nuevo_costo;
    //                 padres[(*edge)->vertex[1]->data] = (*edge)->vertex[0]->data;
    //             }
    //         }

    //         visitados[current->data] = true;
    //     }

    //     for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
    //         if (vert->first != start) {
    //             TV current2 = (vert->first);
    //             cout << "Costo para llegar al nodo " << current2 << ": " << costos[current2] << endl;
    //             cout << current2 << " ";
    //             while (current2 != start) {
    //                 cout << padres[current2] << " ";
    //                 current2 = padres[current2];
    //             }
    //             cout << endl;
    //         }
    //     }
    // }

};

#endif