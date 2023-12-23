#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Cell Cell;
typedef struct Lista Lista;
typedef struct GrafoLA GrafoLA;


struct Cell{
    int key;
    struct Cell *next;
};


struct Lista{
    Cell *head;
};

struct GrafoLA{
   int V;
   int A;
   Lista **adj;
};

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

    c->next = NULL;

    return c;
}

int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}


int procurar(int key, Lista *l) {
    Cell *aux = NULL;

    if (l != NULL) {
        aux = l->head;

        while (aux != NULL && key < aux->key)
            aux = aux->next;
    }

    if (aux != NULL && key == aux->key)
        return 1;
    else
        return 0;
}

void inserir_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key);
    }else{
        c = criar_celula(key);

        if (l->head->key >= key){
           c->next = l->head;


           l->head = c;
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key)){
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}


int remover_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;

    if (!lista_vazia(l)){
        auxA = l->head;

        if(auxA->key == key)
            l->head = l->head->next;
        else{
            auxP = auxA;

            while((auxA != NULL) && (key < auxA->key)){
                auxP = auxA;
                auxA = auxA->next;
            }

            if (auxA->key == key)
                auxP->next = auxA->next;
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}


void imprimir(Lista *l){
    Cell *aux;

    if (!lista_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}


int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}

static Lista** iniciar_LA(int n){
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}


GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    G->adj = iniciar_LA(G->V);

    return G;
}


int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}


void inserir_arestaLA(GrafoLA* G, int v1, int v2){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v1, G->adj[v1]);
        G->A++;
    }
}


void remover_arestaLA(GrafoLA* G, int v1, int v2){
    if (aresta_existeLA(G, v1, v2)){
        remover_na_lista(v1, G->adj[v1]);
        G->A--;

    }
}


void imprimir_arestasLA(GrafoLA* G){
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++){
            aux = G->adj[i]->head;

            while (aux != NULL){
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }

        }
}

void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}


void Busca_Largura(GrafoLA* G, int raiz) {
    int *distancia = (int*)malloc(G->V * sizeof(int));
    int *pai = (int*)malloc(G->V * sizeof(int));
    int *visitados = (int*)malloc(G->V * sizeof(int));

    for (int i = 0; i < G->V; i++) {
        distancia[i] = -1;
        pai[i] = -1;
        visitados[i] = 0;
    }

    distancia[raiz] = 0;
    pai[raiz] = -1;
    visitados[raiz] = 1;

    int *fila = (int*)malloc(G->V * sizeof(int));
    int inicio = 0, fim = 0;
    fila[fim++] = raiz;

    while (inicio < fim) {
        int u = fila[inicio++];
        Cell *atual = G->adj[u]->head;

        while (atual != NULL) {
            int v = atual->key;
            if (!visitados[v]) {
                visitados[v] = 1;
                distancia[v] = distancia[u] + 1;
                pai[v] = u;
                fila[fim++] = v;
            }
            atual = atual->next;
        }
    }

    printf("v d p\n");
    for (int i = 0; i < G->V; i++) {
        if (distancia[i] == -1) {
            printf("%d -", i);
        } else {
            printf("%d %d", i, distancia[i]);
        }

        if (pai[i] != -1) {
            printf(" %d\n", pai[i]);
        } else {
            printf(" -\n");
        }
    }

    free(distancia);
    free(pai);
    free(visitados);
    free(fila);
}

int main() {
    int V;
    scanf("%d", &V);

    GrafoLA *G = (GrafoLA*)malloc(sizeof(GrafoLA));
    G->V = V;
    G->A = 0;
    G->adj = (Lista**)malloc(V * sizeof(Lista*));

    for (int i = 0; i < V; i++) {
        G->adj[i] = criar_lista();
        int adjacente;
        while (1) {
            scanf("%d", &adjacente);
            if (adjacente == -1) break;
            inserir_na_lista(adjacente, G->adj[i]);
            G->A++;
        }
    }

    int vertice_raiz;
    scanf("%d", &vertice_raiz);

    Busca_Largura(G, vertice_raiz);

    for (int i = 0; i < V; i++) {
        liberar_lista(G->adj[i]);
    }

    free(G->adj);
    free(G);

    return 0;
}
