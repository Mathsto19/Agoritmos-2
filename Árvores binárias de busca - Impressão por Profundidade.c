#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node Node;

struct Node {
    int item;
    struct Node* left;
    struct Node* right;
};

Node* criar(int item) {
    Node* tree = (Node*)malloc(sizeof(Node));

    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

Node* inserir(int item, Node* tree) {
    if (tree == NULL)
        return criar(item);
    if (item < tree->item)
        tree->left = inserir(item, tree->left);
    else if (item > tree->item)
        tree->right = inserir(item, tree->right);

    return tree;
}

void imprimirProfundidadeP(Node* tree, int profundidade, int p) {
    if (tree == NULL)
        return;

    if (profundidade == p)
        printf("%d ", tree->item);

    imprimirProfundidadeP(tree->left, profundidade + 1, p);
    imprimirProfundidadeP(tree->right, profundidade + 1, p);
}

void liberar_arvore(Node* tree) {
    if (tree != NULL) {
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}

int main() {
    int p, N;
    scanf("%d", &p);
    scanf("%d", &N);

    Node* raiz = NULL;

    for (int i = 0; i < N; i++) {
        int valor;
        scanf("%d", &valor);
        raiz = inserir(valor, raiz);
    }

    imprimirProfundidadeP(raiz, 0, p);

    liberar_arvore(raiz);

    return 0;
}
