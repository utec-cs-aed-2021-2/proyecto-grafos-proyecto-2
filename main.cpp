#include <iostream>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
//#include "Tester/tester.h"
//#include "Parser/parser.h"

using namespace std;

template <typename TV, typename TE>
void displayVector(vector<Edge<TV, TE>*> v) {
  for (auto it = v.begin(); it != v.end(); it++) {
    cout<<"("<<(*it)->vertex[0]->id<<","<<(*it)->vertex[1]->id<<")"<<" ";
  }
  cout << endl;
}

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    
    //Graph<float,int> graph;
    //graph = UnDirectedGraph<float,int>();
    string a = "a";
    string b = "b";
    string c = "c";
    string d = "d";
    string e = "e";/*
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
    graph.insertVertex(a,7.0);
    graph.insertVertex(a,8.0);
    graph.displayVertex(a);
    if(graph.empty()) cout<<"vacio"<<endl;
    else cout<<"no vacio"<<endl;
    graph.displayVertex(a);
    graph.clear();
    if(graph.empty()) cout<<"vacio"<<endl;
    else cout<<"no vacio"<<endl;
    graph.displayVertex(a);
    */
    /*graph.insertVertex(a,7.0);
    graph.insertVertex(b,8.0);
    graph.insertVertex(c,9.0);
    graph.insertVertex(d,10.0);
    graph.insertVertex(e,11.0);
    graph.createEdge(a,b,1);
    graph.createEdge(b,c,2);
    graph.createEdge(c,d,3);
    graph.createEdge(d,e,4);
    cout<<"Density: "<<graph.density()<<endl;
    if(graph.isDense())
    {
      cout<<"Dense"<<endl;
      cout<<"Density: "<<graph.density()<<endl;
    } 
    else cout<<"Not Dense"<<endl;*/
    /*graph.findByIdE(a,b);
    cout<<"weight: a-b: "<<graph(a,b)<<endl;
    graph(a,b) = graph(a,b) + 5 ;
    cout<<"weight: a-b: "<<graph(a,b)<<endl;
*/
    UnDirectedGraph<int, int> graph = UnDirectedGraph<int, int>();
    graph.insertVertex(a, 0);
    graph.insertVertex(b, 0);
    graph.insertVertex(c, 0);
    graph.insertVertex(d, 0);
    graph.insertVertex(e, 0);
    graph.createEdge(a, b, 1);
    graph.createEdge(a, c, 6);
    graph.createEdge(b, c, 4);
    graph.createEdge(b, d, 3);
    graph.createEdge(c, d, 1);
    graph.createEdge(b, e, 1);
    graph.createEdge(d, e, 1);

    if (graph.isConnected()) {
      cout << "El grafo es conexo" << endl;
    } else {
      cout << "El grafo no es conexo" << endl;
    }

    cout << "Aristas del algoritmo Prim: " << endl;
    displayVector(graph.prim(e));

    cout << "Aristas del algoritmo Kruskal: " << endl;
    displayVector(graph.kruskal());

    cout << "Aristas del BFS desde vertice c: " << endl;
    displayVector(graph.BFS(c));

    cout << "Aristas del DFS desde vertice a: " << endl;
    displayVector(graph.DFS(a));

    if (graph.isDense()) {
      cout << "El grafo es denso con un factor de densidad de: " << graph.density() << endl;;
    } else {
      cout << "El grafo no es denso con un factor de densidad de: " << graph.density() << endl;
    }


    /*
    DirectedGraph<float, int> dgraph = DirectedGraph<float,int>();
    dgraph.insertVertex(a,7.0);
    dgraph.insertVertex(b,8.0);
    dgraph.insertVertex(c,8.0);
    dgraph.createEdge(b, a, 69);
    dgraph.createEdge(a, c, 1);
    dgraph.createEdge(c, a, 3);
    dgraph.createEdge(b, c, 2);
    dgraph.createEdge(a, b, 7);
    cout << dgraph.isStronglyConnected() << endl;
    dgraph.displayVertex(a);
    dgraph.displayVertex(b);
    dgraph.displayVertex(c);
    displayVector(dgraph.kruskal());
    cout << "densidad: " << dgraph.density() << endl;
    if(dgraph.findEdge(a,b)) cout<<"Encontrado"<<endl;
    else cout<<"Nay";
    if(dgraph.findEdge(b,a)) cout<<"Encontrado"<<endl;
    else cout<<"Nay"<<endl;
    cout<<dgraph.density()<<endl;
    if(dgraph.isDense()) cout<<"Denso pa"<<endl;
    else cout<<"No Denso"<<endl;
    cout<<dgraph.getEdge(a,b)->weight<<endl;
    dgraph.deleteVertex(b);
    dgraph.displayVertex(a);
    cout << "densidad: " << dgraph.density() << endl;
    */
    //Tester::executeExamples();
    //Tester::executeParser();
    
    return EXIT_SUCCESS;
}