#include <stdio.h>
#include <CardGame.h>
#include <stdlib.h>

Mazzo * CreateMazzo() {
    Mazzo * nuovoMazzo =(Mazzo*) malloc (sizeof(Mazzo));
    nuovoMazzo->carta1;
    nuovoMazzo->carta2;
    return nuovoMazzo;
}

void PrintCard(Carta * mazzo) {

    Mazzo *a = CreateMazzo();
    printf("Seme: %p, Valore: %p\n", &mazzo->seme, &mazzo->valori);

}
