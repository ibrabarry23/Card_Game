#include <stdio.h>
#include <CardGame.h>
#include <stdlib.h>
#include <time.h>

void inizializzaMazzo(Mazzo *mazzo) {
    int index = 0;
    for (int seme = Fiori; seme <= Quadri; seme++) {
        for (int valore = UNO; valore <K; valore++) {
            mazzo->carte[index].seme = seme;
            mazzo->carte[index].valore = valore;
            index++;
        }
    }
    mazzo->num_carte = index;
}
void stampaCarta(const Carta *carta) {
    const char *semi[] = {"Fiori", "Cuori", "Picche", "Quadri"};
    const char *valori[] = { "1", "2", "3", "4", "5", "6", "7","J", "Q", "K"};

    if (carta->valore >= UNO && carta->valore <= K) {
        printf("%s di %s\n", valori[carta->valore], semi[carta->seme]);
    } else {
        printf("Carta non valida\n");
    }
}
void stampaMazzo(const Mazzo *mazzo) {
    for (int i = 0; i < mazzo->num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo->carte[i].valore, mazzo->carte[i].seme);
        stampaCarta(&mazzo->carte[i]);
    }
}

void swap (Carta * a , Carta *b) {
    Carta tmp = *a;
        *a = *b;
        *b = tmp;
}
void shuffle(Mazzo * mazzo, size_t mazzo_size) {
    for(size_t i = mazzo_size-1; i > 0 ;i--) {
       int  j = rand()% (i+1);
        swap(&mazzo->carte[i],&mazzo->carte[j]);
    }

}
