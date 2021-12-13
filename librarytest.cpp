#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;


int main(){
    std::ifstream i("Parser/Data/testData.json");
    json airports;
    i >> airports;

    cout << airports["pi"] << endl;


    
    return EXIT_SUCCESS;
}