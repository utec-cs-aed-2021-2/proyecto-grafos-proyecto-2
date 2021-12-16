#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <stack>
#include <queue>

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    private:
        std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    public:
    UnDirectedGraph() = default;
    ~UnDirectedGraph() {
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
        Vertex<TV,TE>* vert1 = vertexes[id1];
        Vertex<TV, TE>* vert2 = vertexes[id2];
        Edge<TV,TE>* link1 = new Edge<TV,TE>;
        Edge<TV, TE>* link2 = new Edge<TV, TE>;
        link1->weight = w;
        link1->vertex[0] = vertexes[id1];
        link1->vertex[1] = vertexes[id2];
        vert1->edges.push_front(link1);
        link2->weight = w;
        link2->vertex[0] = vertexes[id2];
        link2->vertex[1] = vertexes[id1];
        vert2->edges.push_front(link2);
        return true;
    }    

    bool deleteVertex(string id) {
        if (!findVertex(id)) return false;
        Vertex<TV, TE>* vert = vertexes[id];
        vert->edges.clear();
        vertexes.erase(id);
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            if ((it->second) != vert) {
                for (auto edge = (it->second)->edges.begin(); edge != (it->second)->edges.end(); edge++) {
                    if ((*edge)->vertex[1] == vert) {
                        (it->second)->edges.erase(edge);
                    }
                }
            }
        }
        return true;
    }  

    bool deleteEdge(string id1, string id2) {
        if (!findVertex(id1) || !findVertex(id2)) return false;
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id2) {
                vertexes[id1]->edges.erase(it);
            }
        }

        for (auto it = vertexes[id2]->edges.begin(); it != vertexes[id2]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id1) {
                vertexes[id2]->edges.erase(it);
            }
        }
        return true;
    }   
    TE &operator()(string start, string end) {
        if (!findVertex(start) || !findVertex(end)) throw("No existe");

        for (auto it = vertexes[start]->edges.begin(); it != vertexes[start]->edges.end(); it++) {
            if ((*it)->vertex->id == end) {
                return (*it)->peso;
            }
        }
    }  

    float density() {
        int edges = 0;
        int vertices = vertexes.size();
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            edges += (it->second)->edges.size();
        }
        return 2.0*(edges)/(vertices*(vertices-1)); 
    }

    bool isDense(float threshold = 0.5) {
        float densidad = this->density();
        if(densidad >= threshold) return true;
        return false;
    }

    bool isConnected() {
        unordered_map<string, bool> visitado;
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            for (auto edge = (it->second)->edges.begin(); edge != (it->second)->edges.end(); edge++) {
                visitado[(*edge)->vertex[1]->id] = true;
            }
        }
        if (visitado.size() != vertexes.size()) return false;
        return true;
    }

    int size(){
        return vertexes.size();
    }

    bool isStronglyConnected() {
        cout << "Esta funcion es usada para grafos dirigidos. Retornando funcion isConnected()" << endl;
        return isConnected();
    }

    bool empty() {
        return vertexes.empty();
    }

    void clear() {
        for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
            (it->second)->edges.clear();
        }
        vertexes.clear();
    }
      
    void displayVertex(string id) {
        if(!findVertex(id))
        {
            cout<<"Cant display, Vertex not present"<<endl;
            return;
        }
        cout<<"id:   "<<id<<endl;
        cout<<"data: "<<vertexes[id]->data<<endl;
        cout<<"Edges: "<<endl;
        for(auto& it : vertexes[id]->edges )
            cout<<"( "<<it->vertex[0]->id<<","<<it->vertex[1]->id<<")"<<" ";
        cout<<endl;
    }

    void display();

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

    bool findEdge(string id1, string id2) {
        if (!findVertex(id1) || !findVertex(id2)) return false;
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id2) return true;
        }
        return false;
    }

    Edge<TV, TE> getEdge(string id1, string id2) {
        if (!findVertex(id1) || !findVertex(id2)) throw("No existen vertices");
        for (auto it = vertexes[id1]->edges.begin(); it != vertexes[id1]->edges.end(); it++) {
            if ((*it)->vertex[1]->id == id2) return (*it);
        }
        throw("No existe");
    }


    vector<Edge<TV, TE>*> DFS(string start) {
        vector<Edge<TV, TE>*> dfs_edges;

        unordered_map<string, bool> visitado;
        stack<Vertex<TV, TE>*> s;

        s.push(vertexes[start]);
        visitado[start] = true;

        Vertex<TV, TE>* actual = s.top();
        bool backtrack = true;
        while (!s.empty()) {
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
        while (!q.empty()) {
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
        while (!to_visit.empty()) {
            while (visitado.find(to_visit.top()->vertex[0]->id) != visitado.end() && visitado.find(to_visit.top()->vertex[1]->id) != visitado.end()) {
                to_visit.pop();
                if (to_visit.empty()) {
                    return prim_edges;
                }
            }
            prim_edges.push_back(to_visit.top());
            visitado[to_visit.top()->vertex[1]->id] = true;
            actual = (to_visit.top())->vertex[1];
            for (auto it = actual->edges.begin(); it != actual->edges.end(); it++) {
                to_visit.push((*it));
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
        while (!to_visit.empty()) {
            while (visitado.find(to_visit.top()->vertex[0]->id) != visitado.end() && visitado.find(to_visit.top()->vertex[1]->id) != visitado.end()) {
                to_visit.pop();
                if (to_visit.empty()) {
                    return kruskal_edges;
                }
            }
            actual = to_visit.top();
            visitado[actual->vertex[1]->id] = true;
            kruskal_edges.push_back(actual);
            to_visit.pop();
        }
        
        return kruskal_edges;
    }

    void dijkstra(TV start) {
        unordered_map<TV, TV> padres;
        unordered_map<TV, bool> visitados;
        unordered_map<TV, TE> costos;

        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            costos[(vert->first)] = INT_MAX;
        }
        cout << "Nodo incial: " << start << endl;

        costos[start] = 0;
        padres[start] = start;
        
        Vertex<TV, TE>* current; 
        TV key;
        while (visitados.size() != vertexes.size()) {
            TE min = INT_MAX;
            for (auto it = costos.begin(); it != costos.end(); it++) {
                if (it->second <= min && (visitados.find(it->first) == visitados.end())) {
                    TV v = (it->first);
                    current = vertexes[v];
                    min = (it->second);
                }
            }
            if (min == INT_MAX) break;
            key = current->data;
            for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
                TE current_costo = costos[key];
                TE nuevo_costo = current_costo + (*edge)->weight;
                if (nuevo_costo < costos[(*edge)->vertex[1]->data]) {
                    costos[(*edge)->vertex[1]->data] = nuevo_costo;
                    padres[(*edge)->vertex[1]->data] = (*edge)->vertex[0]->data;
                }
            }

            visitados[current->data] = true;
        }

        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            if (vert->first != start) {
                TV current2 = (vert->first);
                if (padres.find(current2) == padres.end()) {
                    cout << "No se puede llegar al nodo " << current2 << endl;
                } else {
                    cout << "Costo para llegar al nodo " << current2 << ": " << costos[current2] << endl;
                    cout << current2 << " ";
                    while (current2 != start) {
                        cout << padres[current2] << " ";
                        current2 = padres[current2];
                    }
                    cout << endl;
                }
            }
        }
        cout << endl;
    }
};
#endif