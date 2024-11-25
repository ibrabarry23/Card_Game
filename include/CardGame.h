

#ifndef CARDGAME_H
#define CARDGAME_H

#endif //CARDGAME_H
typedef enum  {
	Fiori,
	Cuori,
	Picche,
	Quadri
} Seme;

typedef struct Carta {
	Seme seme ;
	int valore;
} carta;

