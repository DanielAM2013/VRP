#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/* Para ter acesso à função rand e à constante RAND_MAX, preciso do arquivo-interface stdlib.h. */

#include <stdlib.h>

/* Vamos supor que nossos digrafos têm no máximo maxV vértices. */


#define Vertex int


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: A estrutura digraph representa um digrafo. O campo adj é um ponteiro para a matriz de adjacência do digrafo. O campo V contém o número de vértices e o campo A contém o número de arcos do digrafo. */

typedef struct Tdigraph {
   int V; 
   int A; 
   int **adj; 
} digraph;

/* Um objeto do tipo Digraph contém o endereço de um digraph. */

//typedef struct digraph *Digraph;

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: A função MATRIXint aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. Cada elemento da matriz recebe valor val. */

int **MATRIXint( int r, int c, int val) { 
   Vertex i, j;
   int **m = (int **) malloc(r * sizeof (int *));
   for (i = 0; i < r; i++)
      m[i] = (int *) malloc(c * sizeof (int));
   for (i = 0; i < r; i++)
      for (j = 0; j < c; j++)
         m[i][j] = val;
   return m;
}


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: A função DIGRAPHinit devolve um novo digrafo com vértices 0 1 .. V-1 e nenhum arco. */

digraph* DIGRAPHinit( int V) { 
   digraph *G = (digraph *) malloc(sizeof(digraph));
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, 0);
   return G;
}

digraph* DIGRAPHinit2( int V) { 
   digraph *G = (digraph *) malloc(sizeof(digraph));
   G->V = V; 
   G->A = 0;
   G->adj = MATRIXint( V, V, G->V);
   return G;
}


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: A função DIGRAPHinsertA insere um arco v-w no digrafo G. A função supõe que v e w são distintos, positivos  e menores que G->V. Se o digrafo já tem arco v-w, a função não faz nada. */

void DIGRAPHinsertA( digraph *G, Vertex v, Vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1;
      G->A++;
   }
}


/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: A função DIGRAPHremoveA remove do digrafo G  o arco que tem ponta inicial v  e ponta final w. A função supõe que v e w são distintos, positivos e menores que G->V. Se não existe arco v-w, a função não faz nada. */

void DIGRAPHremoveA( digraph *G, Vertex v, Vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--;
   }
}

/* REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIA: Para cada vértice v do digrafo G, esta função imprime, em uma linha, todos os vértices adjacentes a v. */

void DIGRAPHshow( digraph *G) { 
   Vertex v, w; 
   for (v = 0; v < G->V; v++) {
      //printf( "%2d:", v);
      for (w = 0; w < G->V; w++){
         //if (G->adj[v][w] == 1) 
            printf( " %2d\t", G->adj[v][w]);
      }	
      printf( "\n");
   }
}

 /* A função randV devolve um vértice aleatório do digrafo G. Ela é apenas um invólucro para a função rand da biblioteca stdlib, que produz um número inteiro (pseudo)aleatório no intervalo fechado 0 .. RAND_MAX. */



Vertex randV(digraph *G) {
   
   double r;
      
   r = rand( ) / (RAND_MAX + 1.0);
   return r * G->V;
}



 /* Gera digrafo aleatório com vértices 0..V-1 e exatamente A arcos.*/

digraph* DIGRAPHrand1( int V, int A) { 
   int v, w;
   digraph *G = DIGRAPHinit( V);
   while (G->A < A) {
      //printf("%d\n",G->A);
      v = randV( G);
      w = randV( G);
            if (v != w) 
         DIGRAPHinsertA( G, v, w);
   }
   return G;
}

#define maxV 10
static int conta, pre[maxV], parent[maxV];

/* A função dfsR supõe que o digrafo G é representado por uma matriz de adjacência.*/

void dfsR( digraph *G, Vertex v) 
{ 
   Vertex w;
   pre[v] = conta++; 
   for (w = 0; w < G->V; w++) {
      if (G->adj[v][w] != 0){         
         printf("\n %d->%d",v,w);
          
      }
   
      if (G->adj[v][w] != 0 && pre[w] == -1){
   	 parent[w]=v;  
         dfsR( G, w); 
      }
   }
   printf("\n");
}


 /* A função DIGRAPHdfs visita todos os vértices e todos os arcos do digrafo G. A função atribui um número de ordem pre[x] a cada vértice x:  o k-ésimo vértice visitado recebe número de ordem k.*/

void DIGRAPHdfs( digraph *G) 
{ 
   Vertex v;
   conta = 0;
   for (v = 0; v < G->V; v++) 
      pre[v] = -1;
   for (v = 0; v < G->V; v++)
      if (pre[v] == -1) {
         parent[v]=v; 
         dfsR( G, v);
          
      }
  for (v = 0; v < G->V; v++)
         printf("parent[%d]=%d\n",v,parent[v]);

}

#define maxV2 1000
static int conta, lbl[maxV2];
int queue[maxV2];
int cont_fila=0;

 /* A função DIGRAPHbfs visita todos os vértices do digrafo G que podem ser alcançados a partir do vértice s.  A ordem em que os vértices são visitados é registrada no vetor lbl.*/

void DIGRAPHbfs( digraph *G, Vertex s)
{ 
   Vertex v, w;
   conta = 0;
   for (v = 0; v < G->V; v++)
      lbl[v] = -1;
   lbl[s] = conta++; 
   //Enfileira o primeiro vertice;
   queue[++cont_fila]=s;
   while (cont_fila > 0) {
      //desenfileira vertice
      v = queue[cont_fila--];  
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1 && lbl[w] == -1) {
            lbl[w] = conta++; 
	    printf("%d->%d\n",v,w);	
            //enfileira vertice
            queue[++cont_fila]=w;
         }
   }
   
}


/* Supondo que o digrafo têm no máximo maxV vértices. */

static int conta, pre[maxV], pos[maxV];
 /* A função devolve 1 se o digrafo G tem um ciclo e devolve 0 em caso contrário. */

int DIGRAPHcycle( digraph *G) 
{ 
   Vertex v;
   conta = 0;
   for (v = 0; v < G->V; v++)
      pre[v] = pos[v] = -1;
   for (v = 0; v < G->V; v++)
      if (pre[v] == -1) 
         if (cycleR( G, v) == 1) return 1;
   return 0;
}

int cycleR( digraph *G, Vertex v) 
{ 
   //link a;
   Vertex w;
   pre[v] = conta++;
   
   for (w = 0; w < G->V; w++) {
      
      if ((G->adj[v][w] == 1))
      if (pre[w] == -1) {
         if (cycleR( G, w) == 1) return 1;
      } else if (pos[w] == -1) return 1; /* v-w é arco de retorno */
   }
   pos[v] = conta++;
   return 0;
}


#define Graph Digraph
#define GRAPHinit DIGRAPHinit
/* Insere no grafo G uma aresta com pontas v e w e custo cost. Supõe-se que G ainda não tem arco v-w. */


void Dijkstra( digraph *G,int s, int *parent,
                    int *dist) 
{ 

const int INFINITO = G->V;
   int v, w, v0, w0; 
   //link a;
   for (w = 0; w < G->V; w++) 
      parent[w] = -1, dist[w] = INFINITO;
   parent[s] = s; 
   dist[s] = 0.0; 

   while (1) {
      double mindist = INFINITO;
      for (v = 0; v < G->V; v++) 
         if (parent[v] != -1) 
            for (w=0; w < G->V; w++)               
		if (parent[w] == -1 && mindist > dist[v] + G->adj[v][w]) {
                  mindist = dist[v] + G->adj[v][w];	
                  v0 = v, w0 = w;
               }
      if (mindist == INFINITO) break; 
      parent[w0] = v0;
      dist[w0] = mindist;

   }

   for (v = 0; v < G->V; v++)
        printf("%d:%d:%d\n",v,parent[v],dist[v]);
}

digraph *GRAPHinsertE(digraph *G, int v, int w, int cost) {
   const int INFINITO = G->V; 
   if (G->adj[v][w] == INFINITO) {
      G->adj[v][w] = cost; 
      G->adj[w][v] = cost; 
      G->A += 2;
   }
   return G;
}


int main (){
        int i = 0; int *parent; int *dist;      
        srand((unsigned int )time(NULL));
	digraph *g;
	//g=DIGRAPHrand1(4, 3);
        g=DIGRAPHinit2(4);
        parent = (int *)malloc(4*sizeof(int));
	dist = (int *)malloc(4*sizeof(int));
        g=GRAPHinsertE(g, 0, 1, 1);
        g=GRAPHinsertE(g, 0, 2, 2);
        //g=GRAPHinsertE(g, 0, 3, 3);
        g=GRAPHinsertE(g, 1, 3, 5);
        g=GRAPHinsertE(g, 2, 3, 5);
	//DIGRAPHinsertA(g,0,1);
        //DIGRAPHinsertA(g,1,2);
   	//DIGRAPHinsertA(g,2,3);
	
	//DIGRAPHinsertA(g,0,3);
	//sDIGRAPHinsertA(g,0,2);
	//DIGRAPHinsertA(g,2,3);
        //DIGRAPHinsertA(g,1,0);
        //DIGRAPHdfs(g);
        DIGRAPHshow(g);

        Dijkstra(g, 0, parent, dist);
        //DIGRAPHbfs(g, 0);
         //DIGRAPHdist(g,0);
        //printf("Grafo possui ciclo?: %d\n",DIGRAPHcycle(g));
        
	
	//DIGRAPHremoveA(g,0,1);
	//DIGRAPHshow(g);
	return 0;	

}

/*Para todas as representaçoes de grafos (matriz de adjacencia, lista-de-adjacencia, vetor de arcos) dadas como exemplos em programas, fazer:

1. Escreva uma função DIGRAPHindeg que calcule o grau de entrada um vértice v de um digrafo G.  Escreva uma função DIGRAPHoutdeg que calcule o grau de saída de v. 
2. Inserção de aresta.  Escreva uma função GRAPHinsertE que insira (os dois arcos de) uma aresta v-w em um grafo G.
3. Remoção de aresta.  Escreva uma função GRAPHremoveE que remova de um grafo G (os dois arcos de) uma aresta v-w.
4. Escreva uma função DIGRAPHcopy que receba um digrafo, crie uma cópia do digrafo, e devolva (o endereço d)a cópia. 
5. Escreva uma função DIGRAPHdestroy que destrua a representação de um digrafo G, ou seja, libere o espaço que a representação ocupa na memória. Escreva uma versão para digrafos representados por vetor de arcos, outra para digrafos representados por matriz de adjacência, e outra para digrafos representados por listas de adjacência.
6. Consistência.  Escreva uma função que confira a consistência da representação de um digrafo G.(Em particular, verifique se a representação não tem laços nem arcos paralelos.)
7. Considere o problema de decidir se dois vértices são adjacentes num digrafo G. Quanto tempo consome a solução do problema?  Dê sua resposta em função do número de vértices e arcos do digrafo.  (O consumo de tempo pode depender da representação do digrafo.) 
8. Escreva funções que convertam uma representação de um digrafo em outra.
9. Alterar a função DIGRAPHrand1 para que sejam inseridas arestas (não direcionadas) no lugar de arcos (direcionados atuais)
(de 10 a 13 somente para matriz de adjacencia)
10. Modifique a função dfsR para que o vetor pre[] seja criado dinamicamente, conforme quantidade de vertices do digrafo.
11. Considere o digrafo definido pelos arcos  0-1 1-2 1-3 3-4 3-5 1-6 0-7 7-8 7-9 8-6 .  Faça uma busca dfs.  Em que ordem os vértices são visitados?
12. Documente no código, explicando o que faz cada linha das funções DIGRAPHdfs e dfsR 
13. Uma árvore de busca (arborescencia) é um digrafo em que não existem vértices com grau de entrada maior que 1, existe exatamente um vértice com grau de entrada 0, cada um dos vértices é término de um caminho com origem no único vértice que tem grau de entrada nulo. 
           13.1 Escreva uma função que decida se um dado digrafo é ou não uma arborescência. Em caso afirmativo, a função deve devolver a raiz da arborescência. Em caso negativo, a função deve devolver -1. 
           13.2 Escreva uma função que construa uma arborescência aleatória com V vértices. Faça isso de modo que cada vértice tenha no máximo f filhos. 
14. Faça uma busca em largura, a partir do vértice 0, no grafo definido pelo seguinte conjunto de arestas. 8-9 3-7 1-4 7-8 0-5 5-2 3-8 2-9 0-6 4-9 2-6 6-4. O grafo está representado por sua matriz de adjacência. Faça um desenho da arborescência de busca. 
15. Na função DIGRAPHbfs implementar o enfileiramento e desenfileiramento utilizando fila dinâmica. Como sugestão, utilizar o seguinte com seu respectivo trecho de código para implementação de filas. 

#define maxV 1000
static int conta, lbl[maxV];

/*void DIGRAPHbfs( digraph *G, Vertex s) 
{ 
   Vertex v, w;
   //ponteiro para tipo fila
   fila *f;	
   conta = 0;
   for (v = 0; v < G->V; v++)
      lbl[v] = -1;
   //inicia fila apontando para NULL
   f=QUEUEinit(f);
   lbl[s] = conta++; 
   //Enfileira
   f=QUEUEput (f, s);
   while (f!=NULL) {
      //Desenfileira
      f=QUEUEget(f,&v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1 && lbl[w] == -1) {
            lbl[w] = conta++; 
            //Enfileira
            f=QUEUEput (f, s);
         }
   }
   QUEUEfree( ); 
}

16. Escreva uma versão da função DIGRAPHbfs para digrafos representados por listas de adjacência.  
17. Implemente a função a seguir que determina distância entre um vértice inicial v e os demais vértices de um grafo.

void DIGRAPHdist( digraph *G, Vertex s) 
{ 
   const int INFINITO = G->V;
   Vertex v, w;
   fila *f;
   for (v = 0; v < G->V; v++)
      dist[v] = INFINITO;
   f=QUEUEinit(f);
   dist[s] = 0;
   f=QUEUEput (f, s);

   while (f!=NULL) {
      f=QUEUEget(f,&v);
      for (w = 0; w < G->V; w++)
         if (G->adj[v][w] == 1 && dist[w] == INFINITO) { 
            dist[w] = dist[v] + 1;             
            f=QUEUEput (f, w);
            printf("%d->%d->dist(%d)\n",v,w,dist[w]);
         }
   }
   f=QUEUEfree(f);
}
18. Modifique a função DIGRAPHdist de maneira que sejam determinadas as distâncias de cada vértice para todos os demais vértices de um grafo
 
19. Altere a função CYCLER para que ela detemine se existem ciclos em um grafo dado por uma lista de adjacencias

20. Um ciclo é  trivial  se tem comprimento 2. Escreva uma função que verifique se uma sequência seq[0..k] de vértices de um digrafo é um ciclo não trivial.
*/
	   	
     






