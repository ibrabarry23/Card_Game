#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CardGame.h"

int main(void) {
    // Inizializzazione
    Mazzo mazzo;
    inizializzaMazzo(&mazzo);

    printf("Mazzo inizializzato:\n");
    stampaMazzo(&mazzo);

    // Mescolamento del mazzo
    srand(time(NULL)); // Imposta il seme per la generazione casuale
    shuffle(&mazzo, mazzo.num_carte);

    printf("\nMazzo mescolato:\n");
    stampaMazzo(&mazzo);

    // Creazione dei giocatori
    int num_giocatori = 4; // Cambia il numero di giocatori come desiderato
    Giocatore giocatori[num_giocatori];
    for (int i = 0; i < num_giocatori; i++) {
        giocatori[i].numeroGiocatore = i + 1;
        giocatori[i].vite = 2; // Ogni giocatore parte con 2 vite
    }

    // Distribuzione delle carte
    printf("\nDistribuzione delle carte ai giocatori:\n");
    distribuisci(giocatori, num_giocatori, &mazzo);

    for (int i = 0; i < num_giocatori; i++) {
        printf("Giocatore %d:\n", giocatori[i].numeroGiocatore);
        printf("Carta coperta: ");
        stampaCarta(&giocatori[i].mano[0]);
        printf("Carta scoperta: ");
        stampaCarta(&giocatori[i].mano[1]);
        printf("Vite: %d\n", giocatori[i].vite);
    }

    printf("\nCarte rimanenti nel mazzo: %d\n", mazzo.num_carte);
    return 0;
}
