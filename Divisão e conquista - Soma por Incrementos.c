#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void soma_incremento(int *a, int b) {
    if (b == 1) {
        (*a)++;
    } else {
        if (b % 2 != 0) {
            (*a)++;
            b--;
        }
        soma_incremento(a, b/2);
        soma_incremento(a, b/2);
    }
}

int main() {
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        soma_incremento(&a, b);
        printf("%d\n", a);
    }
    return 0;
}
