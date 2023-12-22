#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) a > b ? a : b

int maior_preco (int *precos, int tam_haste){
    int i, j, q;
    int memoria[tam_haste + 1];
    memoria[0] = 0;
    
    for(i=1; i <=tam_haste; i++){
    q = INT_MIN;
    for(j=0; j < i; j++){
    q = max(q, precos[j] + memoria[i - j - 1]);    
}
    memoria[i] = q;
}

    return memoria[tam_haste];
}

int main(){

    int i, tam_haste, n;
    int *precos;
    
    scanf("%d", &tam_haste);
    scanf("%d", &n);

    precos = (int*) malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++) {
        scanf("%d", &precos[i]);
    }

    printf("%d\n", maior_preco(precos, tam_haste));
    
    free(precos);

    return 0;
}
