

#ifndef CARDGAME_H
#define CARDGAME_H



typedef enum  {
	Fiori,
	Cuori,
	Picche,
	Quadri
} Seme;
typedef enum {
	UNO,
	DUE,
	TRE,
	QUATTRO,
	CINQUE,
	SEI,
	SETTE,
	J = 8,
	Q = 9,
	K = 10,
} Valori;

typedef struct Carta {
	Seme seme ;
	Valori valore;
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
void stampaCarta(const Carta *carta);
void inizializzaMazzo(Mazzo *mazzo) ;
void shuffle(Mazzo * mazzo, size_t mazzo_size);
void swap (Carta * a, Carta *b);
void distribuisci(Giocatore *players,int n, Mazzo *mazzo);



#endif //CARDGAME_H
