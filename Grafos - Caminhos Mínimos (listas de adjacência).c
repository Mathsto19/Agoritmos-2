#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Cell Cell;
typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;

struct Cell {
    int chave;
    int peso;
    Cell* next;
};

struct Lista {
    Cell* heap;
};

struct GrafoLA {
    int V;
    int A;
    Lista** adj;
};

void Galao(GrafoLA* G) {
    int* dist = (int*)malloc(G->V * sizeof(int));
    int* ante = (int*)malloc(G->V * sizeof(int));
    int* visi = (int*)malloc(G->V * sizeof(int));

    for (int i = 0; i < G->V; i++) {
        dist[i] = INT_MAX;
        ante[i] = -1;
        visi[i] = 0;
    }

    dist[0] = 0;

    for (int cont = 0; cont < G->V - 1; cont++) {
        int u = -1;
        int menorDist = INT_MAX;

        for (int v = 0; v < G->V; v++) {
            if (!visi[v] && dist[v] < menorDist) {
                u = v;
                menorDist = dist[v];
            }
        }

        if (u == -1) {
            break;
        }

        visi[u] = 1;

        Cell* vizinho = G->adj[u]->heap;
        while (vizinho != NULL) {
            int v = vizinho->chave;
            int peso = vizinho->peso;

            if (!visi[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                ante[v] = u;
            }

            vizinho = vizinho->next;
        }
    }

    for (int i = 0; i < G->V; i++) {
        if (i == 0) {
            printf("%d: -\n", i);
        } else {
            printf("%d: %d\n", i, ante[i]);
        }
    }

    free(dist);
    free(ante);
    free(visi);
}

int main() {
    int V, A;
    scanf("%d", &V);
    scanf("%d", &A);

    GrafoLA* G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = V;
    G->A = A;
    G->adj = (Lista**)malloc(V * sizeof(Lista*));

    for (int i = 0; i < V; i++) {
        G->adj[i] = (Lista*)malloc(sizeof(Lista));
        G->adj[i]->heap = NULL;
    }

    for (int i = 0; i < A; i++) {
        int u, v, peso;
        scanf("%d %d %d", &u, &v, &peso);

        Cell* newCell = (Cell*)malloc(sizeof(Cell));
        newCell->chave = v;
        newCell->peso = peso;
        newCell->next = G->adj[u]->heap;
        G->adj[u]->heap = newCell;
    }

    Galao(G);

    for (int i = 0; i < V; i++) {
        while (G->adj[i]->heap != NULL) {
            Cell* temp = G->adj[i]->heap;
            G->adj[i]->heap = temp->next;
            free(temp);
        }
        free(G->adj[i]);
    }
    free(G->adj);
    free(G);

    return 0;
}
