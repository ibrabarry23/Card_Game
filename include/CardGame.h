

#ifndef CARDGAME_H
#define CARDGAME_H

#endif //CARDGAME_H

typedef
struct Giocatore {
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
	J = 10,
	Q,
	K
} Valori;

typedef struct Carta {
	Seme seme ;
	Valori valori;
} Carta;


typedef
struct Mazzo {
	GIocatore giocatore;
	Carta carta1, carta2;
} Mazzo;

