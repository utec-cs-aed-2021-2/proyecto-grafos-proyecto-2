#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"
#include <stack>
#include <cmath>
#include <map>
#include <limits>
#include <algorithm>
#include <queue>

#define pi 3.14159265358979323846

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{
    private:
        std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    public:
    UnDirectedGraph() = default;
    ~UnDirectedGraph() {
        clear();
    }
    bool insertVertex(string id, TV vertex, double lat, double lon)
    {
        Vertex<TV,TE>* vert = new Vertex<TV,TE>;
        vert->data = vertex;
        vert->id = id;
        vert->lat = lat;
        vert->lon = lon;
        vertexes[id] = vert;
        return true;
    }

    double getDistance(string id1, string id2){
        if (!findVertex(id1) || !findVertex(id2)) return 0;
        Vertex<TV, TE>* vertex1 = getVertex(id1);
        Vertex<TV, TE>* vertex2 = getVertex(id2);

        double lat1 = vertex1->lat, lon1 = vertex1->lon, lat2 = vertex2->lat, lon2 = vertex2->lon;

        double dist;
        dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(lon1 - lon2));
        dist = acos(dist);
        dist = 6371 * dist;
        return dist;
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

    Vertex<TV, TE>* getVertex(string key) {
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
    double toRad(double degree) {
        return degree/180 * pi;
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
            key = current->id;
            for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
                TE current_costo = costos[key];
                TE nuevo_costo = current_costo + (*edge)->weight;
                if (nuevo_costo < costos[(*edge)->vertex[1]->id]) {
                    costos[(*edge)->vertex[1]->id] = nuevo_costo;
                    padres[(*edge)->vertex[1]->id] = (*edge)->vertex[0]->id;
                }
            }

            visitados[current->id] = true;
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

    unordered_map<string, unordered_map<string, TE>> floyd_warshall() {
        unordered_map<string, unordered_map<string, TE>> matriz;
        
        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            Vertex<TV, TE>* current = (vert->second);
            auto node = (vert->first);

            auto &actual = matriz[node];

            for (auto vert2 = vertexes.begin(); vert2 != vertexes.end(); vert2++) {
                string node2 = (vert2->first);
                Vertex<TV, TE>* next = vert2->second;
                bool found = false;
                TE w;

                for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
                    if (vert2->first == (*edge)->vertex[1]->id){
                        found = true;
                        w = (*edge)->weight;
                    }   
                }
                if (vert->first == vert2->first) {
                    actual[vert2->first] = (TE) 0;
                } else if (found) {
                    actual[vert2->first] = w;
                } else {
                    actual[vert2->first] = INT_MAX/2;
                }
            }
        }
        
        /*
        for (auto it = matriz.begin(); it != matriz.end(); it++) {
            cout << it->first << ": ";
            for (auto it2 = (it->second).begin(); it2 != (it->second).end(); it2++) {
                cout << it2->second << " ";
            }
            cout << endl;
        }
        */

        for (auto v1 = vertexes.begin(); v1 != vertexes.end(); v1++) {
            for (auto v2 = vertexes.begin(); v2 != vertexes.end(); v2++) {
                for (auto v3 = vertexes.begin(); v3 != vertexes.end(); v3++) {
                    if (matriz[v2->first][v3->first] > matriz[v2->first][v1->first] + matriz[v1->first][v3->first]) {
                        matriz[v2->first][v3->first] = matriz[v2->first][v1->first] + matriz[v1->first][v3->first];
                    }
                }
            }
        }
        

        return matriz;
    }

    void bellman_ford(TV start) {
        unordered_map<string, TE> pesos;
        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            pesos[vert->first] = INT_MAX/2;
        }

        pesos[start] = 0;

        bool change = true;
        for (auto val = pesos.begin(); val != pesos.end(); val++) {
            cout << val->first << ": " << val->second << endl;
        }

        while (change) {
            change = false;
            for (auto nodo = vertexes.begin(); nodo != vertexes.end(); nodo++) {
                for (auto edge = (nodo->second)->edges.begin(); edge != (nodo->second)->edges.end(); edge++) {
                    if (pesos[nodo->first] + (*edge)->weight < pesos[(*edge)->vertex[1]->id]) {
                        pesos[(*edge)->vertex[1]->id] = pesos[nodo->first] + (*edge)->weight;
                        change = true;
                    }
                }
            }
        }

        for (auto val = pesos.begin(); val != pesos.end(); val++) {
            cout << val->first << ": " << val->second << endl;
        }
    }

    void bestfirst(string start, string end) {
        cout << "Buscando camino con BestFirst Search desde: " << vertexes[start]->data << " hacia " << vertexes[end]->data << endl;
        unordered_map<string, TE> valores;
        unordered_map<string, Vertex<TV, TE>*> padres;
        unordered_map<string, bool> visitados;

        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            visitados[(vert->first)] = false;
            valores[(vert->first)] = INT_MAX/2;
            valores[(vert->first)] = INT_MAX/2;
        }

        auto compare = [valores](Vertex<TV, TE>* v1, Vertex<TV, TE>* v2){
            return valores.at(v1->id) > valores.at(v2->id);
        };

        priority_queue<Vertex<TV, TE>*, vector<Vertex<TV, TE>*>, decltype(compare)> posibles(compare);

        Vertex<TV, TE>* current = vertexes[start];

        posibles.push(current);
        valores[current->id] = getDistance(current->id, vertexes[end]->id);

        while (current != vertexes[end]) {
            while (!posibles.empty() && visitados[posibles.top()->id]) {
                posibles.pop();
            }

            current = posibles.top();
            visitados[current->id] = true;

            for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
                Vertex<TV, TE>* adyacente = (*edge)->vertex[1];
                if (!visitados[adyacente->id]) {
                    posibles.push(adyacente);
                }
                valores[adyacente->id] = getDistance(adyacente->id, vertexes[end]->id);
                padres[adyacente->id] = current;
            }
        }


        cout << "El camino es: " << endl;
        printPath(vertexes[start], current, padres);

    }

    void printPath(Vertex<TV, TE>* inicial, Vertex<TV, TE>* v, unordered_map<string, Vertex<TV, TE>*> padres) {
        if (v == inicial) {
            cout << v->data << ", ";
            return;
        }

        printPath(inicial, padres[v->id], padres);
        cout << v->data << ", ";
    }

    void astar(string start, string end) {
        cout << "Buscando camino con A* desde: " << vertexes[start]->data << " hacia " << vertexes[end]->data << endl;
        unordered_map<string, TE> valores;
        unordered_map<string, TE> pesos;
        unordered_map<string, Vertex<TV, TE>*> padres;
        unordered_map<string, bool> visitados;

        for (auto vert = vertexes.begin(); vert != vertexes.end(); vert++) {
            visitados[(vert->first)] = false;
            pesos[(vert->first)] = INT_MAX/2;
            valores[(vert->first)] = INT_MAX/2;
        }

        auto compare = [valores](Vertex<TV, TE>* v1, Vertex<TV, TE>* v2){
            return valores.at(v1->id) > valores.at(v2->id);
        };

        priority_queue<Vertex<TV, TE>*, vector<Vertex<TV, TE>*>, decltype(compare)> posibles(compare);

        Vertex<TV, TE>* current = vertexes[start];

        posibles.push(current);
        pesos[current->id] = (TE) 0;
        valores[current->id] = getDistance(current->id, vertexes[end]->id);

        while (!posibles.empty() && current != vertexes[end]) {
            while (!posibles.empty() && visitados[posibles.top()->id]) {
                posibles.pop();
            }

            current = posibles.top();
            visitados[current->id] = true;

            for (auto edge = current->edges.begin(); edge != current->edges.end(); edge++) {
                Vertex<TV, TE>* adyacente = (*edge)->vertex[1];
                if (!visitados[adyacente->id]) {
                    posibles.push(adyacente);
                }
                TE nuevo_peso = pesos[current->id] + (*edge)->weight;
                if (nuevo_peso < pesos[adyacente->id]) {
                    pesos[adyacente->id] = pesos[current->id] + (*edge)->weight;
                }
                valores[adyacente->id] = pesos[adyacente->id] + getDistance(adyacente->id, vertexes[end]->id);
                padres[adyacente->id] = current;
            }
        }

        cout << "El camino es: " << endl;
        printPath(vertexes[start], current, padres);

        /*
        cout << "El camino tiene un peso de: " << valores[current->id] << " y es: " << endl;
        while (current != vertexes[start]) {
            cout << current->data << ", ";
            current = padres[current->id];
        }
        cout << current->data << endl;
        */

    }

    
};
#endif