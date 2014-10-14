/*
1. Função DIGRAPHindeg que calcule o grau de entrada um vértice v de um digrafo G. Escreva uma função DIGRAPHoutdeg que calcule o grau de saída de v. 
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.

2. Inserção de aresta. Escreva uma função GRAPHinsertE que insira (os dois arcos de) uma aresta v-w em um grafo G.
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.

3. Remoção de aresta.  Escreva uma função GRAPHremoveE que remova de um grafo G (os dois arcos de) uma aresta v-w.
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// A linguagem C++ já disponibiliza, através dos construtores, um método de copiar estruturas
4. Função DIGRAPHcopy que receba um digrafo, crie uma cópia do digrafo, e devolva (o endereço d) a cópia. 
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.

// A liguagem C++ já disponibiliza esta funcionalidade
5. Função DIGRAPHdestroy que destrua a representação de um digrafo G, ou seja, libere o espaço que a representação ocupa na memória
Versão para 
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

6. Escreva uma função que confira a consistência da representação de um digrafo G.
 6.1 Verificar se há laços
 [+][+] Vetor de arcos,
 [+][+] Matriz de adjacência,
 [+][+] Listas de adjacência.

 6.2 Verificar se há arcos paralelos
 [+][+] Vetor de arcos,
 [?] Matriz de adjacência,
 [+][+] Listas de adjacência.

7. Considere o problema de decidir se dois vértices são adjacentes num digrafo G.
 Quanto tempo consome a solução do problema? Dê sua resposta em função do número de vértices "V" e
arcos do digrafo "A".
Para:
[+][+] Vetor de arcos,
 Custo: Linear < A
[+][+] Matriz de adjacência,
 Custo: Constante.
[+][+] Listas de adjacência.
 Custo: Quadrático < c*V^2

8. Escreva funções que convertam uma representação de um digrafo em outra.      
Vetor de Arcos      : 1
Matriz de Adjacência: 2
Lista de Adjacência : 3

   1 2 3   1 2 3
1: o + + | o + +
2: + o + | + o +
3: + + o | + + o

9. Alterar a função DIGRAPHrand1 para que sejam inseridas arestas (não direcionadas) no lugar de arcos 
[+][+] Vetor de arcos,
[+][+] Matriz de adjacência,
[+][+] Listas de adjacência.

//------------------------------------------------------------------------------------------------
// de 10 a 13 somente para matriz de adjacencia

[+][+] 10: Modifique a função dfsR para que o vetor pre[] seja criado dinamicamente, conforme quantidade de vertices do digrafo.

[+][+] 11: Considere o digrafo definido pelos arcos  0-1 1-2 1-3 3-4 3-5 1-6 0-7 7-8 7-9 8-6 .  Faça uma busca dfs.  Em que ordem os vértices são visitados?

[+][+] 12: Documente no código, explicando o que faz cada linha das funções DIGRAPHdfs e dfsR 

[+] 13: Uma árvore de busca (arborescencia) é um digrafo em que não existem vértices com grau de entrada maior que 1, existe exatamente um vértice com grau de entrada 0, cada um dos vértices é término de um caminho com origem no único vértice que tem grau de entrada nulo. 
  [+][+] Escreva uma função que decida se um dado digrafo é ou não uma arborescência. Em caso afirmativo, a função deve devolver a raiz da arborescência. Em caso negativo, a função deve devolver -1. 
  [+][+] Escreva uma função que construa uma arborescência aleatória com V vértices. Faça isso de modo que cada vértice tenha no máximo f filhos. 

[+][+] 14: Faça uma busca em largura, a partir do vértice 0, no grafo definido pelo seguinte conjunto de arestas. 8-9 3-7 1-4 7-8 0-5 5-2 3-8 2-9 0-6 4-9 2-6 6-4. O grafo está representado por sua matriz de adjacência. Faça um desenho da arborescência de busca.

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
[+][+] 15: Na função DIGRAPHbfs implementar o enfileiramento e desenfileiramento utilizando fila dinâmica. Como sugestão, utilizar o seguinte com seu respectivo trecho de código para implementação de filas. 
// A bibliotéca <queue> ( C++) já disponibiliza uma estrutura de fila
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

[+][+] 16: Escreva uma versão da função DIGRAPHbfs para digrafos representados por listas de adjacência.  

[+][+] 17: Implemente a função a seguir que determina distância entre um vértice inicial v e os demais vértices de um grafo.
*/
