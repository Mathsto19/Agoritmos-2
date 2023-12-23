#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    int key;
    struct Cell* next;
} Cell;

typedef struct Lista {
    Cell* head;
} Lista;

typedef struct GrafoLA {
    int V;
    int A;
    Lista** adj;
} GrafoLA;

int tempo = 0;

Lista* criar_lista() {
    Lista* l = (Lista*)malloc(sizeof(Lista));
    l->head = NULL;
    return l;
}

Cell* criar_celula(int key) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->key = key;
    c->next = NULL;
    return c;
}

int lista_vazia(Lista* l) {
    return (l == NULL) || (l->head == NULL);
}

void inserir_na_lista(int key, Lista* l) {
    Cell* auxA, *auxP;
    Cell* c = criar_celula(key);

    if (lista_vazia(l) || (l->head->key >= key)) {
        c->next = l->head;
        l->head = c;
    } else {
        auxA = l->head;
        auxP = auxA;

        while ((auxP != NULL) && (auxP->key < key)) {
            auxA = auxP;
            auxP = auxP->next;
        }

        auxA->next = c;
        c->next = auxP;
    }
}

void Busca_Profundidade(GrafoLA* G) {
    int* d = (int*)malloc(G->V * sizeof(int));
    int* f = (int*)malloc(G->V * sizeof(int));
    int* pai = (int*)malloc(G->V * sizeof(int));
    int* cor = (int*)malloc(G->V * sizeof(int));
    int* pilha = (int*)malloc(G->V * sizeof(int));
    int topo = -1;

    for (int i = 0; i < G->V; i++) {
        d[i] = 0;
        f[i] = 0;
        pai[i] = -1;
        cor[i] = 0;
    }

    for (int s = 0; s < G->V; s++) {
        if (cor[s] == 0) {
            cor[s] = 1;
            tempo++;
            d[s] = tempo;

            pilha[++topo] = s;
            
            while (topo >= 0) {
                int u = pilha[topo];
                int achou = 0;

                if (G->adj[u]->head != NULL) {
                    int v = G->adj[u]->head->key;

                    if (cor[v] == 0) {
                        cor[v] = 1;
                        tempo++;
                        d[v] = tempo;
                        pai[v] = u;

                        pilha[++topo] = v;
                        achou = 1;
                    }

                    G->adj[u]->head = G->adj[u]->head->next;

                    if (!achou) {
                        cor[u] = 2;
                        topo--;
                        tempo++;
                        f[u] = tempo;
                    }
                } else {
                    cor[u] = 2;
                    topo--;
                    tempo++;
                    f[u] = tempo;
                }
            }
        }
    }

    printf("v d f p\n");
    for (int v = 0; v < G->V; v++) {
        if (pai[v] == -1) {
            printf("%d %d %d -\n", v, d[v], f[v]);
        } else {
            printf("%d %d %d %d\n", v, d[v], f[v], pai[v]);
        }
    }

    free(d);
    free(f);
    free(pai);
    free(cor);
    free(pilha);
}

int main() {
    int V;
    scanf("%d", &V);

    GrafoLA* grafo = (GrafoLA*)malloc(sizeof(GrafoLA));
    grafo->V = V;
    grafo->A = 0;
    grafo->adj = (Lista**)malloc(V * sizeof(Lista*));

    for (int i = 0; i < V; i++) {
        grafo->adj[i] = criar_lista();

        int adjacente;
        while (1) {
            scanf("%d", &adjacente);
            if (adjacente == -1) {
                break;
            }
            inserir_na_lista(adjacente, grafo->adj[i]);
            grafo->A++;
        }
    }

    Busca_Profundidade(grafo);

    for (int i = 0; i < V; i++) {
        Cell* current = grafo->adj[i]->head;
        while (current != NULL) {
            Cell* next = current->next;
            free(current);
            current = next;
        }
        free(grafo->adj[i]);
    }
    free(grafo->adj);
    free(grafo);

    return 0;
}
