#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
using edge_queue_t = priority_queue<Edge, vector<Edge>, function<bool(Edge, Edge)> >;

template<typename TV, typename TE>
inline auto edge_compare = [](Edge e1, Edge e2) {return e1.weight > e2.weight;};

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{
    public:
    DirectedGraph() = default;
    bool createEdge(string id1, string id2, TE w)
    {
        Vertex<TV,TE>* vert1 = this->vertexes[id1];
        Vertex<TV,TE>* vert2 = this->vertexes[id2];
        Edge<TV,TE>* link = new Edge<TV,TE>;
        link->weight = w;
        link->vertexes[0] = vert1;
        link->vertexes[1] = vert2;
        //cout<<"prueba"<<endl;
        vert1->edges.push_front(link);
        //vert2->edges.push_front(link);
        return true;
    }   
    bool deleteEdge(string id1, string id2)
    {
        Vertex<TV,TE>* vert1 = this->vertexes[id1];
        Vertex<TV,TE>* vert2 = this->vertexes[id2];

        int check1 = 0;
        auto it = this->vertexes[id1]->edges.begin();
        auto ending = this->vertexes[id1]->edges.end();
        while(it!=ending)
        {
            if((*it)->vertexes[0]->id == vert1->id && (*it)->vertexes[1]->id == vert2->id )
            {
                vert1->edges.erase(it);
                return true;
            }
            ++it;
        }
        return false;
        
    }   
    bool deleteVertex(string id)// MUY COSTOSO
    {
        if(check_key(this->vertexes,id))
        {
            //auto it = vertexes[id]->edges.begin();
            auto ending = this->vertexes[id]->edges.end();
            while(!this->vertexes[id]->edges.empty())
            {
                auto it = this->vertexes[id]->edges.begin();
                string id2 = "";
                id2 = (*it)->vertexes[1]->id;
                if(!deleteEdge(id,id2))
                {
                    deleteEdge(id2,id);
                }
            }
            auto it = this->vertexes.begin();
            while(it!=this->vertexes.end())
            {
                //cout<<(*it).second->id<<endl;
                auto ited = it->second->edges.begin();
                while(ited!=it->second->edges.end())
                {
                    //cout<<"("<<(*ited)->vertexes[0]->id<<"-"<<(*ited)->vertexes[1]->id<<")"<<endl;
                    if((*ited)->vertexes[1]->id==id)
                    {
                        deleteEdge((*ited)->vertexes[0]->id,id);
                        ited = it->second->edges.begin();
                    }
                    else
                    {
                        ++ited;
                    }
                }
                ++it;
            }
            this->vertexes.erase(id);
            return true;
        }
        cout<<"Cant delete, Vertex not present"<<endl;
        return false;
 
    }    
    double density()
    {
        unordered_map<string, bool> edgges;
            int v = 0;
            auto beg = this->vertexes.begin();
            while(beg!=this->vertexes.end())
            {
                v++;
                for(auto& it : (*beg).second->edges )
                {
                    string edege;
                    edege  = it->vertexes[0]->id + "-" + it->vertexes[1]->id;
                    edgges[edege] = true;                
                }
                beg++;
            }
            int e = 0;
            for(auto& it : edgges)
                {
                    ++e;
                    //cout<<it.first<<" "<<endl;
                }
        // cout<<"**    e: "<<e<<" v: "<<v<<"   **"<<endl;
            auto density = 1.0*e/(1.0*v*(1.0*v-1.0));
            return density;
    }
    bool isDense(float threshold = 0.5)
    {
        auto densidad = this->density();
        //cout<<densidad<<"aaa";
        if(densidad>=threshold) return true;
        return false;
    }
  bool findByIdE(string id1, string id2)
    {
        if(!check_key(this->vertexes,id1)) return false;
        if(!check_key(this->vertexes,id2)) return false;
        auto it = this->vertexes[id1]->edges.begin();
        while(it!=this->vertexes[id1]->edges.end())
        {
            if((*it)->vertexes[0]->id == id1 && (*it)->vertexes[1]->id == id2)
            {
                //cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return true;
            }

            ++it;
        }
        return false;
    }

    Edge<TV,TE>* getEdge(string id1, string id2)
    {
        if(!check_key(this->vertexes,id1)) throw("No existe");
        if(!check_key(this->vertexes,id2)) throw("No existe");
        auto it = this->vertexes[id1]->edges.begin();
        while(it!=this->vertexes[id1]->edges.end())
        {
            if((*it)->vertexes[0]->id == id1 && (*it)->vertexes[1]->id == id2)
            {
                //cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return (*it);
            }
            ++it;
        }
        throw("No existe");
    }

    // todavia es una idea------------------------------------------------ Para BFS, prim y kruskal
    template<typename BinaryFunction>
    void bfs(BinaryFunction bf) {
        // variables
        queue <Vertex> q;
        unordered_set<Vertex> visited;
        // estructuras auxiliares (lambda)
        auto is_visited = [&visited](Vertex vx) -> bool {
            return visited.find(vx) != end(visited);
        };
        // Paso #1: tomar cualquier vertice y agregarlo al Q y V
        auto fv = 0;
        q.push(fv);
        visited.insert(fv);
        // Paso #2: recorrer el Q si no esta vacio
        while(!q.empty()) {
            // 2.1: Obtener el valor del front
            auto v = q.front();
            auto it = find_if(begin(vertices), end(vertices),
                              [&v](pair<identify_t, Vertex> item){
                                  return item.second == v;
                              });
            bf(v, it->first);
            // 2.2: Retirar del queue
            q.pop();
            // 2.3: Agregar sus adjacentes
            for (auto [a, w]: adjacents[v])
                if (!is_visited(a)) {
                    q.push(a);
                    visited.insert(a);
                }
        }
    }

    int prim(string id){
        vector<Edge> result;
        unordered_set<Vertex> visited;
        edge_queue_t available_edges(edge_compare);
        auto is_visited = [&visited](Vertex vx) -> bool { // estructura lambda [variables fuera de la funcion a usar] (parametros de funcuin) tipo de return {cuerpo}
            return visited.find(vx) != end(visited);
        }; // funcion pequeña que se ve mas como una variable
        // 1. ubicamos cualquier vertice
        auto vx = vertexes[id];
        visited.insert(vx);
        // 2. agregamos el vertices seleccionado a visitados
        for(auto [a, b]: adjacents[vx]){
            available_edges.push({vx, a, b});

        }
        // 2.1 agregar las aristas adjacientes a disponibles "available_edges"
        // recorrer el PQ edge_queue_t
        // 3. reconocer si el PQ esta vacio
        while(!available_edges.empty()){
            // 3.1 reconocemos el tope del PQ
            auto [vx, ad, weight] = available_edges.top();
            // 3.2 pop
            available_edges.pop();

            if(!is_visited(ad)){
                // 3.3.1 si el vertice es adjaciente () si es visitado
                visited.insert(ad);
                // 3.3.2 retorno la arista
                result.push_back({vx, ad, weight});
                // 3.3.3 agrego los adjacientes
                for(auto [ad2, weight]: adjacents[ad]){
                    if(!is_visited(ad2)){
                        available_edges.push({ad, ad2, weight});
                    }
                }
            }
        }
        return result;
    }

    int kruskal(){
        edge_queue_t available_edges(edge_compare);
        vector<Edge> result;
        join_find jf(vertices.size()); // todavia solo es la idea
        while(!available_edges.empty()){
            auto [vx1, vx2, bl] = available_edges.top();
            available_edges.pop();
            if(jf.find(vx1) != jf.find(vx2)){
                jf.join(vx1, vx2);
                result.push_back({vx1, vx2, bl});
            }

        }
        return result;
    }
};

#endif