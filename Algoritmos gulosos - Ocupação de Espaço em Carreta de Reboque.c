#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void calcularPreenchimento(int l, int m, int n, int *quantidade_m, int *quantidade_n, int *espaco_restante) {
    *quantidade_m = 0;
    *quantidade_n = 0;

    if (m < n) {
        int temp = m;
        m = n;
        n = temp;
    }

    while (l >= m || l >= n) {
        if (l >= m) {
            (*quantidade_m)++;
            l -= m;
        } else if (l >= n) {
            (*quantidade_n)++;
            l -= n;
        }
    }

    *espaco_restante = l;
}

int main() {
    int l, m, n;
    scanf("%d %d %d", &l, &m, &n);

    int quantidade_m, quantidade_n, espaco_restante;

    calcularPreenchimento(l, m, n, &quantidade_m, &quantidade_n, &espaco_restante);

    printf("%d\n%d\n%d\n", quantidade_m, quantidade_n, espaco_restante);

    return 0;
}
