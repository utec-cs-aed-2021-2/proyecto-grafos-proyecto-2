#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
#include <vector>
#include <cmath>

#define pi 3.14159265358979323846

using json = nlohmann::json;
using namespace std;

template <typename TV, typename TE>
void displayVector(vector<Edge<TV, TE>*> v) {
  for (auto it = v.begin(); it != v.end(); it++) {
    cout<<"("<<(*it)->vertex[0]->data<<","<<(*it)->vertex[1]->data<<"): "<< (*it)->weight<< " ";
  }
  cout << endl;
}

double toRad(double degree) {
    return degree/180 * pi;
}

double getDistance(int pos1, int pos2, json airports){
    bool noExiste = false;
    std::string Lat1 = airports[pos1]["Latitude"].is_null()? "0": airports[pos1]["Latitude"];
    std::string Long1 = airports[pos1]["Longitude"].is_null()? "0": airports[pos1]["Longitude"];
    Lat1.erase(remove(Lat1.begin(), Lat1.end(), '"'), Lat1.end());
    Long1.erase(remove(Long1.begin(), Long1.end(), '"'), Long1.end());
    std::string Lat2 = airports[pos2]["Latitude"].is_null()? "0": airports[pos2]["Latitude"];
    std::string Long2 = airports[pos2]["Longitude"].is_null()? "0": airports[pos2]["Longitude"];
    Lat2.erase(remove(Lat2.begin(), Lat2.end(), '"'), Lat2.end());
    Long2.erase(remove(Long2.begin(), Long2.end(), '"'), Long2.end());

    if(Long1 == "0" || Lat1 == "0" || Lat2 == "0" || Long2 == "0") noExiste = true;

    double lat1 = stod(Lat1), long1 = stod(Long1), lat2 = stod(Lat2), long2 = stod(Long2);
    double dist;
    dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
    dist = acos(dist);
    dist = 6371 * dist;
    return noExiste? 0: dist;

}

bool isNumber(std::string s) {
    for (auto c = s.begin(); c != s.end(); c++) {
        if (!(isdigit(*c) || (*c) == '.'|| (*c) == '-')) return false;
    }
    return true;
}

void pruebaUndirected(){
    ifstream i("Parser/Data/pe.json");
    json airports;
    i >> airports;
    UnDirectedGraph<std::string, int> graph = UnDirectedGraph<std::string, int>();


    for(int x = 0; x < airports.size(); x++){
        std::string name = airports[x]["Name"];
        std::string idStr = airports[x]["Airport ID"];
        std::string lat = airports[x]["Latitude"];
        std::string lon = airports[x]["Longitude"];

        name.erase(remove(name.begin(), name.end(), '"'), name.end());
        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
        lat.erase(remove(lat.begin(), lat.end(), '"'), lat.end());
        lon.erase(remove(lon.begin(), lon.end(), '"'), lon.end());

        graph.insertVertex(idStr,name,stod(lat),stod(lon));
    }

    for(int x = 0; x < airports.size(); x++){
        std::string idStr = airports[x]["Airport ID"];

        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
        for(int j = 0; j < airports[x]["destinations"].size(); j++){
            std::string destino = airports[x]["destinations"][j];
            destino.erase(remove(destino.begin(), destino.end(), '"'), destino.end());
            if(graph.findVertex(destino)){
                if(!graph.findEdge(idStr, destino)){
                graph.createEdge(idStr, destino, graph.getDistance(idStr,destino));
                cout << "Join: " << idStr << " and " << destino << " with weight: " << getDistance(x,j,airports) << endl;
            }
            }
        }
    }

    std::string idStr = airports[0]["Airport ID"];
    idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());

    displayVector(graph.prim(idStr));
    displayVector(graph.kruskal());
    displayVector(graph.BFS(idStr));
    displayVector(graph.DFS(idStr));
}

void pruebaDirected(){
    ifstream i("Parser/Data/pe.json");
    //ifstream i("Parser/Data/airports.json");
    json airports;
    i >> airports;
    DirectedGraph<std::string, int> graph = DirectedGraph<std::string, int>();

    for(int x = 0; x < airports.size(); x++){
        std::string name = airports[x]["Name"];
        std::string idStr = airports[x]["Airport ID"];
        std::string lat = airports[x]["Latitude"];
        std::string lon = airports[x]["Longitude"];
        cout << lat << endl << lon << endl;

        name.erase(remove(name.begin(), name.end(), '"'), name.end());
        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
        lat.erase(remove(lat.begin(), lat.end(), '"'), lat.end());
        lon.erase(remove(lon.begin(), lon.end(), '"'), lon.end());
        if (!isNumber(lat)) lat = "0";
        if (!isNumber(lon)) lon = "0";

        graph.insertVertex(idStr,name,stod(lat),stod(lon));
    }

    for(int x = 0; x < airports.size(); x++){
        std::string idStr = airports[x]["Airport ID"];

        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
        for(int j = 0; j < airports[x]["destinations"].size(); j++){
            std::string destino = airports[x]["destinations"][j];
            destino.erase(remove(destino.begin(), destino.end(), '"'), destino.end());
            if(graph.findVertex(destino)){
                graph.createEdge(idStr, destino, graph.getDistance(idStr,destino));
                //cout << "Join: " << idStr << " to " << destino << " with weight: " << getDistance(x,j,airports) << endl;
            }
        }
    }

    std::string idStr = airports[0]["Airport ID"];
    idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
    cout << "Aplicando BFS desde Jorge Chavez: " << endl;
    displayVector(graph.BFS("2789"));
    cout << endl;
    cout << "Aplicando DFS desde Jorge Chavez: " << endl;
    displayVector(graph.DFS("2789"));
    cout << endl << "Aplicando dijkstra:" << endl;
    graph.dijkstra("2796");
    cout << endl << "Aplicando Bellman Ford desde Jorge Chavez:" << endl;
    graph.bellman_ford("2796");
    cout << endl << "Aplicando algoritmo Floyd Warshall: " << endl;
    graph.floyd_warshall();
    cout << endl;
    graph.astar("2789", "2796");
    cout << endl << endl;
    graph.bestfirst("2789", "2796");
}


int main(){
    pruebaDirected();

   
    return EXIT_SUCCESS;
}