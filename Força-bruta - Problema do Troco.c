#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int CalculaTroco(int moedas[], int tam_vetor, int troco, int pos_moeda, int MIN) {
    if (pos_moeda >= tam_vetor) {
        if (troco > 0) {
            return INT_MAX;
        } else {
            return MIN;
        }
    }
    int S1 = CalculaTroco(moedas, tam_vetor, troco, pos_moeda + 1, MIN); 
    int S2 = CalculaTroco(moedas, tam_vetor, troco % moedas[pos_moeda], pos_moeda + 1, MIN + troco / moedas[pos_moeda]); 
    return (S1 < S2) ? S1 : S2; 
}

int main() {
    int troco_valor;
    int num_moedas;
    scanf("%d", &troco_valor);
    scanf("%d", &num_moedas);
    int moedas[num_moedas];
    for (int i = 0; i < num_moedas; i++) {
        scanf("%d", &moedas[i]);
    }
    int resultado = CalculaTroco(moedas, num_moedas, troco_valor, 0, 0);
    printf("%d", resultado);
    return 0;
}
