#include <iostream>
#include "Graph/UndirectedGraph.h"
#include "Graph/DirectedGraph.h"
//#include "Tester/tester.h"
//#include "Parser/parser.h"

using namespace std;

template <typename TV, typename TE>
void displayVector(vector<Edge<TV, TE>*> v) {
  for (auto it = v.begin(); it != v.end(); it++) {
    cout<<"("<<(*it)->vertex[0]->id<<","<<(*it)->vertex[1]->id<<"): "<< (*it)->weight<< " ";
  }
  cout << endl;
}

void UDGTest() {
    cout << "---------------------" << endl;
    cout << "UnDirected Graph Test" << endl;
    cout << "---------------------" << endl;
    cout << "(grafo sacado de diapositiva 47 de ppt: Presentacion 05 (Grafos))" << endl;
    string a = "a";
    string b = "b";
    string c = "c";
    string d = "d";
    string e = "e";
    UnDirectedGraph<int, int> graph = UnDirectedGraph<int, int>();
    if (graph.empty()) {
      cout << "El grafo esta vacio" << endl;
    } else {
      cout << "El grafo no esta vacio" << endl;
    }
    graph.insertVertex(a, 0);
    graph.insertVertex(b, 0);
    graph.insertVertex(c, 0);
    graph.insertVertex(d, 0);
    graph.insertVertex(e, 0);
    graph.createEdge(a, b, 1);
    graph.createEdge(a, c, 6);
    graph.createEdge(b, c, 4);
    graph.createEdge(b, d, 1);
    graph.createEdge(c, d, 3);
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

    cout << "Eliminando aristas (b, e) y (d, e)" << endl;
    graph.deleteEdge(b, e);
    graph.deleteEdge(d, e);
    cout << "Luego de elminar las aristas, el grafo ";
    if (graph.isConnected()) {
      cout << "sigue siendo conexo" << endl;
    } else {
      cout << "ya no es conexo" << endl;
    }

    cout << "Eliminando vertice e" << endl;
    graph.deleteVertex(e);

    if (graph.isConnected()) {
      cout << "El grafo vuelve a ser conexo" << endl;
    } else {
      cout << "El grafo no es conexo" << endl;
    }

    cout << "Haciendo clear... " << endl;
    graph.clear();
    if (graph.empty()) {
      cout << "El grafo esta vacio" << endl;
    } else {
      cout << "El grafo no esta vacio" << endl;
    }
}

void DGTest() {
  cout << "-------------------" << endl;
  cout << "Directed Graph Test" << endl;
  cout << "-------------------" << endl;
  cout << "(grafo sacado de diapositiva 52 de ppt: Presentacion 05 (Grafos))" << endl;
  string v1 = "v1";
  string v2 = "v2";
  string v3 = "v3";
  string v4 = "v4";
  string v5 = "v5";
  string v6 = "v6";
  string v7 = "v7";
  string v8 = "v8";
  DirectedGraph<string, int> dgraph = DirectedGraph<string, int>();
  dgraph.insertVertex(v1, v1);
  dgraph.insertVertex(v2, v2);
  dgraph.insertVertex(v3, v3);
  dgraph.insertVertex(v4, v4);
  dgraph.insertVertex(v5, v5);
  dgraph.insertVertex(v6, v6);
  dgraph.insertVertex(v7, v7);
  dgraph.insertVertex(v8, v8);
  dgraph.createEdge(v6, v8, 4);
  dgraph.createEdge(v6, v7, 3);
  dgraph.createEdge(v6, v3, 2);
  dgraph.createEdge(v7, v5, 8);
  dgraph.createEdge(v3, v7, 10);
  dgraph.createEdge(v3, v4, 7);
  dgraph.createEdge(v3, v2, 1);
  dgraph.createEdge(v1, v3, 12);
  dgraph.createEdge(v1, v2, 4);
  dgraph.createEdge(v2, v4, 6);
  dgraph.createEdge(v4, v5, 16);

  if (dgraph.isStronglyConnected()) {
    cout << "El grafo es fuertemente conexo" << endl;
  } else {
    cout << "El grafo no es fuertemente conexo" << endl;
  }

  cout << "Aristas de BFS a partir de nodo v5: " << endl;
  displayVector(dgraph.BFS(v5));
  cout << "Aristas de DFS a partir de nodo v5: " << endl;
  displayVector(dgraph.DFS(v5));

  cout << "La densidad del grafo es " << dgraph.density() << " por lo que es ";
  if (dgraph.isDense()) {
    cout << "denso" << endl; 
  } else {
    cout << "no denso" << endl;
  }

  cout << "Insertando aristas (v5, v4, 3), (v2, v1, 19), (v4, v3, 12) y (v3, v6, 7)..." << endl;
  dgraph.createEdge(v5, v4, 3);
  dgraph.createEdge(v2, v1, 19);
  dgraph.createEdge(v4, v3, 12);
  dgraph.createEdge(v3, v6, 7);

  if (dgraph.isStronglyConnected()) {
    cout << "El grafo ahora es fuertemente conexo" << endl;
  } else {
    cout << "El grafo sigue no siendo fuertemente conexo" << endl;
  }
}

int main(int argc, char *argv[]) {
    std::cout << "================================================" << std::endl;
    std::cout << "MENU GRAPH TESTER" << std::endl;
    std::cout << "================================================" << std::endl;
    

    UDGTest();
    DGTest();

    return EXIT_SUCCESS;
}