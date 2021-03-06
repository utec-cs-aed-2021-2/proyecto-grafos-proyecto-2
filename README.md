[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6129290&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------

## Integrantes
- Mauricio Croquet
- Fracisco Maggot
- Rubén Vargas

----

En este proyecto se han implementdo dos tipos de grafos utilizando una lista de adyacencia. Estos grafos son los grafos dirigidos y no dirigidos.

Para cada uno de los grafos se ha implementado las siguientes funcionalidades:
- Inserción de Vértices
- Inserción de Aristas
- Eliminación de Vertices
- Eliminación de Aristas
- DFS
- BFS
- Verficiar si el grafo es conexo (o fuertemente conexo segun sea el caso)
- Calcular densidad de grafo
- Dijkstra
- A*
- Bellman-Ford
- Floyd Warshall
- Best First Search

Para el grafo no dirigido, se han implementado algunas funciones que no pueden ser implementadas en grafos dirigido como por ejemplo:
- Kruskal
- Prim

Además, se ha generado un parser de json utilizando una libreria externa, para así ingresar la información sobre aeropuertos y convertirla en un grafo.

Para probar los algoritmos, se han utilizado algunos ejemplos de grafos del PPT: Presentación 05 (Grafos) brindada en clase así como un video que brinda un grafo como ejemplo del algoritmo de Bellman-Ford.

El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 

Las clases Grafo dirigido y Grafo No dirigido son derivadas de la clase padre grafo. La estructura del grafo está compuesta por un Unordered Map que contiene los vértices. Estos vértices son un objeto llamado Vertex donde se almacenan la data, la logitud, la latitud, una lista de edges y el id. Asimismo, los edges son un objeto que contiene el peso de la arista y un array de vértices donde se guardan los vértices iniciales y finales. 

### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

### Algorithms:
```cpp
//Given the graph
UndirectedGraph<char, int> graph;

//1- Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<char, int> kruskal(&graph);
UndirectedGraph<char, int> result = kruskal.apply();//return a tree

//2- Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree

//3- A *
AStar<char, int> astar(&graph, "A", "Z", vector<int> heuristics);
UndirectedGraph<char, int> result = astar.apply();

```


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 


### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```

## [Git Karma Guidelines](http://karma-runner.github.io/5.2/dev/git-commit-msg.html)

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* parser
* main
* tester


> **PD:** Puntos extras sobre Evaluación Continua si se implementa una GUI.


distance calculator: https://stackoverflow.com/questions/27126714/c-latitude-and-longitude-distance-calculator/63767823
