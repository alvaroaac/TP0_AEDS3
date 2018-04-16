#include <stdio.h>
#include <stdlib.h>

/**  Begin Declaring Structs **/

struct Grafo
{
    unsigned int V; // numero de vertices
    struct Lista* lista;
};

struct Lista
{
    struct Node *head; // ponteiro pra cabeca da lista (topo)
};

struct Node
{
	unsigned int vertice;
    struct Node* next;
};

/**************************************************/


 /**            Funcoes                **/

struct Node* novoNode(unsigned int vertice);
struct Grafo* criaGrafo(unsigned int V);
void destroiGrafo (struct Grafo* grafo);
void acrescentaAresta(struct Grafo* grafo, unsigned int A, unsigned int B);
void DFS(unsigned int i, unsigned int * visited, struct Grafo* grafo);
int alcanceHit(unsigned int * visited, unsigned int num_V);
void inicializaPraZero(unsigned int * vetor, unsigned int tamanho);
void ehONovoHitDoVerao(); // pra geral curtir (se tiver menos de 35 anos)
