#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>

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
    if (m.count(key) == 0)
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
private:    
    std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    
public:
    Graph() = default;
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
        Vertex<TV,TE>* vert1 = vertexes[id1];
        Vertex<TV,TE>* vert2 = vertexes[id2];
        Edge<TV,TE>* link = new Edge<TV,TE>;
        link->weight = w;
        link->vertexes[0] = vert1;
        link->vertexes[1] = vert2;
        
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
    /*TE &operator()(string start, string end)= 0;  
    float density() = 0;
    bool isDense(float threshold = 0.5) = 0;
    bool isConnected()= 0;
    bool isStronglyConnected() throw();
    bool empty();
    void clear()= 0;  
      */
    void displayVertex(string id)
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
    /*
    bool findById(string id) = 0;
    void display() = 0;*/
};

#endif