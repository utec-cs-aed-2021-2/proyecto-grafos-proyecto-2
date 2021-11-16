#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////
template<typename TV, typename TE, typename T>
bool check_key(unordered_map<TV, TE> m, T key)
{
    // Key is not present
    if (m.find(key) == m.end())
        return false;

    return true;
}
template<typename TV, typename TE>
struct Edge {
    Vertex<TV, TE>* vertexes[2];
    TE weight;
};

template<typename TV, typename TE>
struct Vertex {
    TV data;
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
        if (!check_key(vertexes, id1) || !check_key(vertexes, id2)) return false;
        Vertex<TV,TE>* vert1 = vertexes[id1];
        Vertex<TV,TE>* vert2 = vertexes[id2];
        Edge<TV,TE>* link = new Edge<TV,TE>;
        link->weight = w;
        link->vertexes[0] = vert1;
        link->vertexes[1] = vert2;
        cout<<"Nada que ver"<<endl;
        vert1->edges.push_front(link);
        vert2->edges.push_front(link);
        return true;
    }        
    bool deleteVertex(string id)
    {
        if(check_key(vertexes,id))
        {
            //auto it = vertexes[id]->edges.begin();
            auto ending = vertexes[id]->edges.end();
            while(!vertexes[id]->edges.empty())
            {
                auto it = vertexes[id]->edges.begin();
                string id2 = "";
                if((*it)->vertexes[0]->id == id)
                {
                    id2 = (*it)->vertexes[1]->id;
                }
                else
                {
                    id2 = (*it)->vertexes[0]->id;
                }
                deleteEdge(id,id2);

            }
            /*
            for(auto& it : vertexes[id]->edges )
            {
                string id2;
                if(it->vertexes[0]->id == id)
                {
                    id2 = it->vertexes[1]->id;
                }
                else
                {
                    id2 = it->vertexes[0]->id;
                }
                deleteEdge(id,id2);
            }*/
            /*
            while(it!=ending)
            {   
                string id2;
                if((*it)->vertexes[0]->id == id)
                {
                    id2 = (*it)->vertexes[1]->id;
                }
                else
                {
                    id2 = (*it)->vertexes[0]->id;
                }
                deleteEdge(id,id2);
                it++;
            }*/
            vertexes.erase(id);
            return true;
        }
        cout<<"Cant delete, Vertex not present"<<endl;
        return false;
    }    
    bool deleteEdge(string id1, string id2)
    {
        Vertex<TV,TE>* vert1 = vertexes[id1];
        Vertex<TV,TE>* vert2 = vertexes[id2];

        int check1 = 0;
        auto it = vertexes[id1]->edges.begin();
        auto ending = vertexes[id1]->edges.end();
        /*for(auto& it : vertexes[id1]->edges )
        {
            if((it->vertexes[0]->data == vertexes[id1]->data && it->vertexes[1]->data == vertexes[id2]->data)) //|| (it->vertexes[0]->data == vert2->data && it->vertexes[1]->data == vert1->data))
            {
                vertexes[id1]->edges.erase(it);
                check1=1;
            }
            if(check1 == 1)
                return true;
            
        }
        */
        while(it!=ending && check1==0)
        {
            if(((*it)->vertexes[0]->data == vert1->data && (*it)->vertexes[1]->data == vert2->data) || ((*it)->vertexes[0]->data == vert2->data && (*it)->vertexes[1]->data == vert1->data))
            {
                vert1->edges.erase(it);
                check1=1;
            }
            ++it;
        }
        
        if(check1 = 1)
        {
            int check2 = 0;
            auto it = vertexes[id2]->edges.begin();
            auto ending = vertexes[id2]->edges.end();
              /*for(auto& it : vert2->edges )
                {
                    if((it->vertexes[0]->data == vert1->data && it->vertexes[1]->data == vert2->data)) //|| (it->vertexes[0]->data == vert2->data && it->vertexes[1]->data == vert1->data))
                    {
                        vert2->edges.erase(it);
                        check2=1;
                    }
                    if(check2 == 1)
                        return true;
                    
                }*/
              while(it!=ending && check2==0)
                {
                    if(((*it)->vertexes[0]->data == vert1->data && (*it)->vertexes[1]->data == vert2->data) || ((*it)->vertexes[0]->data == vert2->data && (*it)->vertexes[1]->data == vert1->data))
                    {
                        vert2->edges.erase(it);
                        check2=1;
                    }
                    ++it;
                }
                return true;
        }
      

        return false;
    }   
    TE &operator()(string start, string end)
    {
        if(!check_key(vertexes,start)) throw("No existe");
        if(!check_key(vertexes,end)) throw("No existe");
        auto it = vertexes[start]->edges.begin();
        while(it!=vertexes[start]->edges.end())
        {
            if((*it)->vertexes[0]->id == start && (*it)->vertexes[1]->id == end)
            {
                auto &peso = (*it)->weight;
                return peso;
            }
            else if ((*it)->vertexes[1]->id == start && (*it)->vertexes[0]->id == end)
            {
                auto &peso = (*it)->weight;
                return peso;             
            }
            ++it;
        }
        throw("No existe");      
    }  
    float density() //O(n^2) --- POSIBLE CAMBIO
    {
        unordered_map<string, bool> edgges;
        int v = 0;
        auto beg = vertexes.begin();
        while(beg!=vertexes.end())
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
        auto density = 2.0*e/(1.0*v*(1.0*v-1.0));
        return density;

    }
    bool isDense(float threshold = 0.5)
    {
        auto densidad = this->density();
        //cout<<densidad<<"aaa";
        if(densidad>=threshold) return true;
        return false;
    }
    bool isConnected()
    {
            //TO DO
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
      
    void displayVertex(string id) // O(E)
    {
        if(!check_key(vertexes,id))
        {
            cout<<"Cant display, Vertex not present"<<endl;
            return;
        }
        cout<<"id:   "<<id<<endl;
        cout<<"data: "<<vertexes[id]->data<<endl;
        cout<<"Edges: "<<endl;
        for(auto& it : vertexes[id]->edges )
            cout<<"( "<<it->vertexes[0]->id<<","<<it->vertexes[1]->id<<")"<<" ";
        cout<<endl;
    }
    
    bool findByIdV(string id)// O(1)
    {
        if(!check_key(vertexes,id))
        {
            return false;
        }
        return true;
    }

    bool findByIdE(string id1, string id2)
    {
        if(!check_key(vertexes,id1)) return false;
        if(!check_key(vertexes,id2)) return false;
        auto it = vertexes[id1]->edges.begin();
        while(it!=vertexes[id1]->edges.end())
        {
            if((*it)->vertexes[0]->id == id1 && (*it)->vertexes[1]->id == id2)
            {
                cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return true;
            }
            else if ((*it)->vertexes[1]->id == id1 && (*it)->vertexes[0]->id == id2)
            {
                cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return true;                
            }
            ++it;
        }
        return false;
    }

    Edge<TV,TE>* getEdge(string id1, string id2)
    {
        if(!check_key(vertexes,id1)) throw("No existe");
        if(!check_key(vertexes,id2)) throw("No existe");
        auto it = vertexes[id1]->edges.begin();
        while(it!=vertexes[id1]->edges.end())
        {
            if((*it)->vertexes[0]->id == id1 && (*it)->vertexes[1]->id == id2)
            {
                cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return (*it);
            }
            else if ((*it)->vertexes[1]->id == id1 && (*it)->vertexes[0]->id == id2)
            {
                cout<<"("<<(*it)->vertexes[0]->id<<"-"<<(*it)->vertexes[1]->id<<")"<<endl;
                return (*it);                
            }
            ++it;
        }
        throw("No existe");
    }
    //void display() = 0;
};

#endif