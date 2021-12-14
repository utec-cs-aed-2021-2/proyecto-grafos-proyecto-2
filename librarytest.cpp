#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

using json = nlohmann::json;
using namespace std;


int main(){
    ifstream i("Parser/Data/airports.json");
    json airports;
    i >> airports;

    string name = airports[0]["destinations"][1];

    name.erase(remove(name.begin(), name.end(), '"'), name.end());

    int dest = stoi(name);
    cout << dest << endl;

    
    return EXIT_SUCCESS;
}