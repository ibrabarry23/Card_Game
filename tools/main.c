#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "CardGame.h"  // Contiene tutte le tue struct e funzioni

extern int campoVita ;

int main(void) {
    printf("=== Inizio del Gioco ===\n\n");
//creazione mazzo
    Mazzo mazzo;
    inizializzaMazzo(&mazzo);
    srand(time(NULL));
//mescola mazzo
    shuffle(&mazzo, mazzo.num_carte);
//Selezione numero giocatori
    int num_giocatori;
    printf("Inserisci il numero di giocatori (2-20): ");
    scanf("%d", &num_giocatori);
    while (num_giocatori < 2 || num_giocatori > 20) {
        printf("Numero non valido. Riprova: ");
        scanf("%d", &num_giocatori);
    }

    Giocatore* head = NULL;
    giocatori(&head, num_giocatori);

    giocaPartita(&head, &mazzo); 
    // Deallocazione
    while (head) {
        Giocatore* tmp = head;
        head = head->next;
        free(tmp);
    }

    printf("\n=== Fine del Gioco ===\n");
    return 0;
}