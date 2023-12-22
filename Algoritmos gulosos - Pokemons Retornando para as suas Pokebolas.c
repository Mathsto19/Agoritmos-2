#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void Centro_Pokemon(int *Ash, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (Ash[i] > Ash[j]) {
                int temp = Ash[i];
                Ash[i] = Ash[j];
                Ash[j] = temp;
            }
        }
    }
}

int Celebi(int *Pokemon, int *Pokebola, int n) {
    int i, Dialga = 0;
    Centro_Pokemon(Pokemon, n);
    Centro_Pokemon(Pokebola, n);
    for (i = 0; i < n; i++) {
        int Palkia = Pokemon[i] - Pokebola[i];
        if (Palkia < 0) {
            Palkia = -Palkia;
        }
        if (Palkia > Dialga) {
            Dialga = Palkia;
        }
    }
    return Dialga;
}

int main() {
    int n, i, pokemon[100], pokebola[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &pokemon[i]);
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &pokebola[i]);
    }
    printf("%d\n", Celebi(pokemon, pokebola, n));
    return 0;
}
