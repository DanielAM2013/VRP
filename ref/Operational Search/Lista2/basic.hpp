#include <iostream>
#include <list>
#include <queue>
#include <ctime>
#include <algorithm>

typedef unsigned int num;
typedef unsigned int vertex;

class digraph
{
 public:
 bool arc_adj( vertex o, vertex d);
 bool insert_arc( vertex o, vertex d);
 bool remove_arc( vertex o, vertex d);
 num indeg( vertex v);
 num outdeg( vertex v);
 bool hasloop(void);
 bool paralell_arc(void);
 void print(void);
};

class arcs;
class list_adj;
class matriz_adj;

