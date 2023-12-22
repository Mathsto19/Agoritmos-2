#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b, int c) {
    if (a >= b && a >= c) return a;
    if (b >= a && b >= c) return b;
    return c;
}

int maxSomaCruzada(int vetor[], int baixo, int meio, int alto) {
    int somaEsquerda = INT_MIN;
    int soma = 0;
    for (int i = meio; i >= baixo; i--) {
        soma += vetor[i];
        if (soma > somaEsquerda) somaEsquerda = soma;
    }

    int somaDireita = INT_MIN;
    soma = 0;
    for (int i = meio + 1; i <= alto; i++) {
        soma += vetor[i];
        if (soma > somaDireita) somaDireita = soma;
    }

    return max(somaEsquerda, somaDireita, somaEsquerda + somaDireita);
}

int maxSubsequenciaSoma(int vetor[], int baixo, int alto) {
    if (baixo == alto) {
        return vetor[baixo];
    }

    int meio = (baixo + alto) / 2;

    int somaEsquerda = maxSubsequenciaSoma(vetor, baixo, meio);
    int somaDireita = maxSubsequenciaSoma(vetor, meio + 1, alto);
    int somaCruzada = maxSomaCruzada(vetor, baixo, meio, alto);

    return max(somaEsquerda, somaDireita, somaCruzada);
}

int main() {
    int n;
    scanf("%d", &n);

    int vetor[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &vetor[i]);
    }

    int maxSoma = maxSubsequenciaSoma(vetor, 0, n - 1);

    printf("%d\n", maxSoma);

    return 0;
}
