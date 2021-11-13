#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

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
};

#endif