#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CardGame.h"
#include "../include/CardGame.h"

int main(void) {
    printf("=== Inizio del Gioco ===\n\n");

    // Inizializzazione del mazzo
    Mazzo mazzo;
    inizializzaMazzo(&mazzo);
    printf("Mazzo inizializzato.\n");

    // Stampa il mazzo inizializzato
    printf("\nCarte nel mazzo prima del mescolamento:\n");
    for (int i = 0; i < mazzo.num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo.carte[i].valore, mazzo.carte[i].seme);
    }

    // Mescolare il mazzo
    srand(time(NULL));
    shuffle(&mazzo, mazzo.num_carte);
    printf("\nMazzo mescolato.\n");

    // Stampa il mazzo dopo il mescolamento
    printf("\nCarte nel mazzo dopo il mescolamento:\n");
    for (int i = 0; i < mazzo.num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo.carte[i].valore, mazzo.carte[i].seme);
    }

    // Creazione dei giocatori
    int num_giocatori;

    printf("\nInserisci il numero di giocatori che desideri: ");
    scanf("%d", &num_giocatori);
    while(num_giocatori < 2 || num_giocatori > 20){
        printf("Errore! Inserisci il numero di giocatori compresto tra 2 e 20: ");
        scanf("%d", &num_giocatori);
    }
   

    

    Giocatore *head = NULL;
    giocatori(&head, num_giocatori);
    printf("\nGiocatori creati: %d\n", num_giocatori);
   // stampaGiocatori(head);

    // Distribuzione delle carte
    printf("\nDistribuzione delle carte ai giocatori...\n");
    distribuisci(head, num_giocatori, &mazzo);

    // Stampa le carte dei giocatori
    Giocatore *current = head;
    while (current != NULL) {
        printf("\nGiocatore %d ha ricevuto le seguenti carte:\n", current->numeroGiocatore);
        for (int i = 0; i < 2; i++) {
            printf("Carta %d: Valore=%d, Seme=%d\n", i + 1, current->mano[i].valore, current->mano[i].seme);
        }
        current = current->next;
    }

    // Mostra il numero di carte rimanenti nel mazzo
    printf("\nCarte rimanenti nel mazzo: %d\n", mazzo.num_carte);

    Giocatore* primo_giocatore = startPlayer(head, num_giocatori);
    printf("\nIl primo giocatore è: %d\n", primo_giocatore->numeroGiocatore);

    // Pulizia della memoria
    while (head != NULL) {
        Giocatore *temp = head;
        head = head->next;
        free(temp);
    }

    printf("\n=== Fine del Gioco ===\n");
    return 0;

}
