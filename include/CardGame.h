

#ifndef CARDGAME_H
#define CARDGAME_H


typedef struct Giocatore {
	int numeroGiocatore;
	int vite;
} GIocatore;

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
void stampaMazzo(const Mazzo *mazzo);
void stampaCarta(const Carta *carta);
void inizializzaMazzo(Mazzo *mazzo) ;
void shuffle(Mazzo * mazzo, size_t mazzo_size);
void swap (Carta * a, Carta *b);



#endif //CARDGAME_H
