#include <iostream>
#include "Graph/UndirectedGraph.h"
//#include "Tester/tester.h"
//#include "Parser/parser.h"

using namespace std;

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    Graph<float,int> graph;
    graph = UnDirectedGraph<float,int>();
    string a = "a";
    string b = "b";
    string c = "c";
    string d = "d";
    string e = "e";
    graph.insertVertex(a,7.0);
    graph.insertVertex(b,8.0);
    graph.insertVertex(c,9.0);
    graph.insertVertex(d,10.0);
    graph.insertVertex(e,11.0);
    graph.createEdge(a,b,1);
    graph.createEdge(a,c,2);
    graph.createEdge(a,d,3);
    graph.createEdge(a,e,4);
    graph.displayVertex(a);
    graph.deleteEdge(a,b);
    graph.displayVertex(a);
    graph.deleteVertex(a);
    graph.displayVertex(e);
    graph.displayVertex(a);
    graph.deleteVertex(a);

    //Tester::executeExamples();
    //Tester::executeParser();
    
    return EXIT_SUCCESS;
}