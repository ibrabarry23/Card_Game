#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "CardGame.h"  // Contiene tutte le tue struct e funzioni

int campoVita = 0;

int main(void) {
    printf("=== Inizio del Gioco ===\n\n");

    // Inizializzazione mazzo
    Mazzo mazzo;
    inizializzaMazzo(&mazzo);
    srand(time(NULL));
    shuffle(&mazzo, mazzo.num_carte);

    // Input giocatori
    int num_giocatori;
    printf("Inserisci il numero di giocatori (2-20): ");
    scanf("%d", &num_giocatori);
    while (num_giocatori < 2 || num_giocatori > 20) {
        printf("Numero non valido. Riprova: ");
        scanf("%d", &num_giocatori);
    }

    // Creazione giocatori
    Giocatore* head = NULL;
    giocatori(&head, num_giocatori);
    distribuisci(head, num_giocatori, &mazzo);

    // Primo giocatore casuale
    Giocatore* primo = startPlayer(head, num_giocatori);
    printf("Primo giocatore selezionato: Giocatore %d\n", primo->numeroGiocatore);

    // Inizializzazione SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL Init Error: %s\n", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        fprintf(stderr, "IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Carte del Giocatore", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!win) {
        fprintf(stderr, "Errore creazione finestra: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        fprintf(stderr, "Errore creazione renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Carica le due texture delle carte del primo giocatore
    SDL_Texture* carta1 = Carte(ren, &primo->mano[0]); // Carta coperta
    SDL_Texture* carta2 = Carte(ren, &primo->mano[1]); // Carta scoperta

    if (!carta1 || !carta2) {
        fprintf(stderr, "Errore nel caricamento di una o più carte.\n");
    } else {
        int running = 1;
        SDL_Event e;

        while (running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = 0;
                }
            }

            SDL_SetRenderDrawColor(ren, 0, 120, 0, 255); // Verde tavolo
            SDL_RenderClear(ren);

            SDL_Rect rect1 = { 200, 150, 150, 220 };
            SDL_Rect rect2 = { 450, 150, 150, 220 };

            SDL_RenderCopy(ren, carta1, NULL, &rect1);
            SDL_RenderCopy(ren, carta2, NULL, &rect2);

            SDL_RenderPresent(ren);
        }
    }

    // Pulizia
    if (carta1) SDL_DestroyTexture(carta1);
    if (carta2) SDL_DestroyTexture(carta2);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    // Dealloca memoria giocatori
    while (head) {
        Giocatore* tmp = head;
        head = head->next;
        free(tmp);
    }

    printf("\n=== Fine del Gioco ===\n");
    return 0;
}
