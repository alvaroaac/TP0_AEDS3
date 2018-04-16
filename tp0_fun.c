// Trabalho Pratico '0' de Algoritmos e Estrutura de Dados III
// Nome: Alvaro Augusto Alves de Carvalho
// Matricula: 2015430231
#include "tp0.h"

#define IDADE_MAX 35


 //funcao para criar um node de uma lista
struct Node* novoNode(unsigned int vertice) {
    struct Node* newNode =
    (struct Node*) malloc(sizeof(struct Node));
    newNode->vertice = vertice;
    newNode->next = NULL;
    return newNode;
}

 // funcao para criar um Grafo de V vertices
struct Grafo* criaGrafo(unsigned int V) {

    struct Grafo* graph = (struct Grafo*) malloc(sizeof(struct Grafo));
    graph->V = V;

    // alocar memoria para um array de V listas encadeadas
    graph->lista = (struct Lista*) malloc((V+1) * sizeof(struct Lista));

    // inicializa cada lista como vazia
    unsigned int i;
    for (i=0;i<V;i++) {
        //graph->lista[i].head = (struct Node*) malloc(sizeof(struct Node));
	graph->lista[i].head = NULL;
    }

    return graph; // retorna grafo vazio de V vértices
}

 // funcao para destruir um Grafo
void destroiGrafo (struct Grafo* grafo) {
	if (grafo) {
		if(grafo->lista) {
			int i;
			struct Node* navegador;
			for (i=0;i<grafo->V;i++) {
				struct Node* navegador = grafo->lista[i].head;
				
				while(navegador) {
					struct Node* temp = navegador;
					navegador = navegador->next;
					free(temp);			
				}
				free(navegador);			
			}	

			free(grafo->lista);		
		}
		free(grafo);		
	}
}

 // Adiciona uma aresta a um grafo
void acrescentaAresta(struct Grafo* grafo, unsigned int A, unsigned int B) {
    //acrescenta uma aresta do ponto A ate o ponto B

	// adiciona um Node no inicio da lista de A
    struct Node* newNode = novoNode(B);
    newNode->next = grafo->lista[A].head;
    grafo->lista[A].head = newNode;

    // para grafo nao direcionado: faz o mesmo de B para A
    newNode = novoNode(A);
    newNode->next = grafo->lista[B].head;
    grafo->lista[B].head = newNode;

}


void DFS(unsigned int i, unsigned int * visited, struct Grafo* grafo) {
// Depth First Search
	struct Node* navegador = grafo->lista[i].head;

    visited[i] = 1;

    while(navegador!=NULL) {
        i = navegador->vertice;
        if (!visited[i])
            DFS(i, visited, grafo);

        navegador = navegador->next;
    }
}

int alcanceHit(unsigned int * visited, unsigned int num_V) {
// Conta quantas pessoas gostaram do HIT DO VERAO

	unsigned int i;
	unsigned int curtiramOHit = 0;
	for (i = 0; i<num_V; i++) {
		if (visited[i] == 1) {
			curtiramOHit++;
		}
	}
	return curtiramOHit;
}

void inicializaPraZero(unsigned int * vetor, unsigned int tamanho) {
	unsigned int i;
	for (i=0;i<tamanho;i++) {
		vetor[i] = 0;
	}
}

void ehONovoHitDoVerao() { // pra geral curtir (se tiver menos que 35 anos)

	unsigned int N;  // numero de pessoas (vertices)
	unsigned int M;  // numero de relacoes
	unsigned int ID; // Identificador da pessoa
	int idade;       // idade da pessoa
	unsigned int ID_1; unsigned int ID_2; // IDs para construir relacao dos familiares
	unsigned int quemOuvePrimeiro; // ID do infeliz que vai espalhar o HIT do verao

	scanf("%u", &N);
	scanf("%u", &M);
	unsigned int pessoasQueGostam[N+1];

	inicializaPraZero(pessoasQueGostam, N+1);

	int i;

	unsigned int NUM_V = 0; // numero de vertices no grafo

	for (i=0; i<N; i++) {
		scanf("%u%d", &ID, &idade);
		if (idade < IDADE_MAX) {
			pessoasQueGostam[ID] = 1;
			NUM_V++;
		}
		else {
			pessoasQueGostam[ID] = 0;
		}
	}

	unsigned int visited[N+1];  // array de vertices visitados a ser usado na DFS
	inicializaPraZero(visited, N+1);
	struct Grafo* grafo = criaGrafo(N);

	for (i=0;i<M;i++) {
		scanf("%u%u", &ID_1, &ID_2);
		if (pessoasQueGostam[ID_1] && pessoasQueGostam[ID_2]) {
			acrescentaAresta(grafo, ID_1,ID_2);
		}
	}

	scanf("%u", &quemOuvePrimeiro); // O Infeliz

	DFS(quemOuvePrimeiro, visited, grafo);

	printf("%d\n", alcanceHit(visited, N+1));

	destroiGrafo(grafo);

}
