#ifndef CARDGAME_H
#define CARDGAME_H

typedef enum {
    Fiori = 0,
    Cuori = 1,
    Picche = 2,
    Quadri = 3,
} Seme;

typedef enum {
    ASSO = 1,
    DUE=2, TRE=3, QUATTRO=4, CINQUE=5, SEI=6, SETTE=7 , J=8, Q=9, K=10
} Valori;

typedef struct Carta {
    Seme seme;
    Valori valore;
    bool valida; 
} Carta;

typedef struct Mazzo {
    Carta carte[40];
    int num_carte;
} Mazzo;

typedef struct Giocatore {
    int numeroGiocatore;
    int vite;
    Carta mano[2];
    struct Giocatore *next;
} Giocatore;

void stampaMazzo(const Mazzo *mazzo);
void stampaCarta(const Carta *carta, bool is_coperta);
void inizializzaMazzo(Mazzo *mazzo);
void shuffle(Mazzo *mazzo, size_t mazzo_size);
void swap(Carta *a, Carta *b);
void giocatori(Giocatore **head, int num);
void distribuisci(Giocatore *head, Mazzo *mazzo);
void effetti(Giocatore *giocatore, Giocatore *head, int indiceCarta);
Giocatore* startPlayer(Giocatore *player, int n_player);
void svoglimentoFase (Giocatore* giocatore, Giocatore *head, int num_giocatori);
int contaGiocatoriVivi(Giocatore* head);
void eliminaGiocatoriMorti(Giocatore** head) ;
void giocaPartita(Giocatore** head, Mazzo* mazzo);
void ridistribuisciCarte(Giocatore* head, int num_giocatori);
Carta pescaCarta();
#endif//CARDGAME_H