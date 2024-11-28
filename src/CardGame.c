#include <stdio.h>
#include <CardGame.h>
#include <stdlib.h>

void inizializzaMazzo(Mazzo *mazzo) {
    int index = 0;
    for (int seme = Fiori; seme <= Quadri; seme++) {
        for (int valore = Asso; valore <= K; valore++) {
            mazzo->carte[index].seme = seme;
            mazzo->carte[index].valore = valore;
            index++;
        }
    }
    mazzo->num_carte = index;
}
void stampaCarta(const Carta *carta) {
    const char *semi[] = {"Fiori", "Cuori", "Picche", "Quadri"};
    const char *valori[] = { "Asso", "2", "3", "4", "5", "6", "7","J", "Q", "K"};

    if (carta->valore >= Asso && carta->valore <= K) {
        printf("%s di %s\n", valori[carta->valore], semi[carta->seme]);
    } else {
        printf("Carta non valida\n");
    }
}
void stampaMazzo(const Mazzo *mazzo) {
    for (int i = 0; i < mazzo->num_carte; i++) {
        stampaCarta(&mazzo->carte[i]);
    }
}
