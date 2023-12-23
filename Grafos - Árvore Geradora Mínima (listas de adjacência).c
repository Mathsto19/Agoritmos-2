#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta* proxima;
} Aresta;

typedef struct Vertice {
    Aresta* lista_adjacencia;
} Vertice;

typedef struct GrafoLA {
    int V;
    Vertice* vertices;
} GrafoLA;

GrafoLA* criarGrafo(int V) {
    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->vertices = (Vertice*)malloc(V * sizeof(Vertice));

    for (int i = 0; i < V; i++) {
        grafo->vertices[i].lista_adjacencia = NULL;
    }

    return grafo;
}

void liberarGrafo(GrafoLA* grafo) {
    for (int v = 0; v < grafo->V; v++) {
        Aresta* atual = grafo->vertices[v].lista_adjacencia;
        while (atual != NULL) {
            Aresta* proxima = atual->proxima;
            free(atual);
            atual = proxima;
        }
    }
    free(grafo->vertices);
    free(grafo);
}

void adicionarAresta(GrafoLA* grafo, int origem, int destino, int peso) {
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    nova_aresta->destino = destino;
    nova_aresta->peso = peso;
    nova_aresta->proxima = grafo->vertices[origem].lista_adjacencia;
    grafo->vertices[origem].lista_adjacencia = nova_aresta;

    nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    nova_aresta->destino = origem;
    nova_aresta->peso = peso;
    nova_aresta->proxima = grafo->vertices[destino].lista_adjacencia;
    grafo->vertices[destino].lista_adjacencia = nova_aresta;
}

int encontrarMinimo(int chaves[], int incluido[], int V) {
    int minimo = INT_MAX;
    int indice_minimo = -1;

    for (int v = 0; v < V; v++) {
        if (!incluido[v] && chaves[v] < minimo) {
            minimo = chaves[v];
            indice_minimo = v;
        }
    }

    return indice_minimo;
}

void imprimirAGM(int pai[], int V) {
    printf("0: -\n");
    for (int v = 1; v < V; v++) {
        printf("%d: %d\n", v, pai[v]);
    }
}

void Gerd_Muller(GrafoLA* grafo) {
    int V = grafo->V;
    int pai[V];
    int chaves[V];
    int incluido[V];

    for (int v = 0; v < V; v++) {
        chaves[v] = INT_MAX;
        incluido[v] = 0;
    }

    chaves[0] = 0;
    pai[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = encontrarMinimo(chaves, incluido, V);
        incluido[u] = 1;

        Aresta* aresta = grafo->vertices[u].lista_adjacencia;
        while (aresta != NULL) {
            int v = aresta->destino;
            if (!incluido[v] && aresta->peso < chaves[v]) {
                pai[v] = u;
                chaves[v] = aresta->peso;
            }
            aresta = aresta->proxima;
        }
    }

    imprimirAGM(pai, V);
}

int main() {
    int V, A;
    scanf("%d", &V);
    scanf("%d", &A);
    GrafoLA* grafo = criarGrafo(V);

    for (int i = 0; i < A; i++) {
        int origem, destino, peso;
        scanf("%d %d %d", &origem, &destino, &peso);
        adicionarAresta(grafo, origem, destino, peso);
    }

    Gerd_Muller(grafo);
    liberarGrafo(grafo);

    return 0;
}
