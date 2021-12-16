#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include "Graph/UndirectedGraph.h"
#include <vector>
#include <cmath>

#define pi 3.14159265358979323846

using json = nlohmann::json;
using namespace std;

template <typename TV, typename TE>
void displayVector(vector<Edge<TV, TE>*> v) {
  for (auto it = v.begin(); it != v.end(); it++) {
    cout<<"("<<(*it)->vertex[0]->id<<","<<(*it)->vertex[1]->id<<"): "<< (*it)->weight<< " ";
  }
  cout << endl;
}

double toRad(double degree) {
    return degree/180 * pi;
}

double getDistance(int pos1, int pos2, json airports){
    string Lat1 = airports[pos1]["Latitude"].is_null()? "0": airports[pos1]["Latitude"];
    string Long1 = airports[pos1]["Longitude"].is_null()? "0": airports[pos1]["Longitude"];
    Lat1.erase(remove(Lat1.begin(), Lat1.end(), '"'), Lat1.end());
    Long1.erase(remove(Long1.begin(), Long1.end(), '"'), Long1.end());
    string Lat2 = airports[pos2]["Latitude"].is_null()? "0": airports[pos2]["Latitude"];
    string Long2 = airports[pos2]["Longitude"].is_null()? "0": airports[pos2]["Longitude"];
    Lat2.erase(remove(Lat2.begin(), Lat2.end(), '"'), Lat2.end());
    Long2.erase(remove(Long2.begin(), Long2.end(), '"'), Long2.end());

    double lat1 = stod(Lat1), long1 = stod(Long1), lat2 = stod(Lat2), long2 = stod(Long2);
    double dist;
    dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(toRad(long1 - long2));
    dist = acos(dist);
    dist = 6371 * dist;
    return dist;

}


int main(){
    ifstream i("Parser/Data/pe.json");
    json airports;
    i >> airports;
    UnDirectedGraph<string, int> graph = UnDirectedGraph<string, int>();


    for(int x = 0; x < airports.size(); x++){

        string name = airports[x]["Name"];
        string idStr = airports[x]["Airport ID"];

        name.erase(remove(name.begin(), name.end(), '"'), name.end());
        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());

        graph.insertVertex(idStr,name);
    }

    for(int x = 0; x < airports.size(); x++){
        string idStr = airports[x]["Airport ID"];

        idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());
        for(int j = 0; j < airports[x]["destinations"].size(); j++){
            string destino = airports[x]["destinations"][j];
            destino.erase(remove(destino.begin(), destino.end(), '"'), destino.end());
            if(!graph.findEdge(idStr, destino)){
                graph.createEdge(idStr, destino, getDistance(x,j,airports));
                cout << "Join: " << idStr << " and " << destino << " with weight: " << getDistance(x,j,airports) << endl;
            }
        }
    }

    string idStr = airports[0]["Airport ID"];
    idStr.erase(remove(idStr.begin(), idStr.end(), '"'), idStr.end());

    displayVector(graph.prim(idStr));
    displayVector(graph.kruskal());
    displayVector(graph.BFS(idStr));
    displayVector(graph.DFS(idStr));

   
    return EXIT_SUCCESS;
}