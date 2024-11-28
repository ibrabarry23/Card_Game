

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
	Asso = 1,
	DUE,
	TRE,
	QUATTRO,
	CINQUE,
	SEI,
	SETTE,
	OTTO,
	NOVE,
	J = 10,
	Q,
	K
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





#endif //CARDGAME_H
