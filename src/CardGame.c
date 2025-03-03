#include <stdio.h>
#include <CardGame.h>
#include <stdlib.h>
#include <time.h>

void inizializzaMazzo(Mazzo *mazzo) {
    int index = 0;
    for (int seme = Fiori; seme <= Quadri; seme++) {
        for (int valore = UNO; valore <= K; valore++) {
            mazzo->carte[index].seme = seme;
            mazzo->carte[index].valore = valore;
            index++;
        }
    }
    mazzo->num_carte = index;
}
void stampaCarta(const Carta *carta) {
    const char *semi[] = {"Fiori", "Cuori", "Picche", "Quadri"};
    const char *valori[] = { "1", "2", "3", "4", "5", "6", "7","J", "Q", "K"};

    if (carta->valore >= UNO && carta->valore <= K) {
        printf("%s di %s\n", valori[carta->valore], semi[carta->seme]);
    } else {
        printf("Carta non valida\n");
    }
}
void stampaMazzo(const Mazzo *mazzo) {
    for (int i = 0; i < mazzo->num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo->carte[i].valore, mazzo->carte[i].seme);
        stampaCarta(&mazzo->carte[i]);
    }
}

void swap (Carta * a , Carta *b) {
    Carta tmp = *a;
        *a = *b;
        *b = tmp;
}

void shuffle(Mazzo * mazzo, size_t mazzo_size) {
    for(size_t i = mazzo_size-1; i > 0 ;i--) {
        int  j = rand()% (i+1);
        swap(&mazzo->carte[i],&mazzo->carte[j]);
    }
}

Giocatore * startPlayer(Giocatore* player, int n_player) {
    int  j = rand()% n_player;

    // ciclo per avanzare fino al giocatore scelto casualmente
    for (int i = 0; i < j; i++)
        player = player->next;

    return player;
}

void giocatori ( Giocatore **head, int num) {

    if (num < 2 || num > 20) exit(EXIT_FAILURE);

     Giocatore *giocatore_precedente = NULL;

    for (int i = 1; i <= num; i++) {
        Giocatore *giocatore = (Giocatore *)malloc(sizeof(Giocatore));

        if (giocatore == NULL) exit(EXIT_FAILURE);

        giocatore->numeroGiocatore = i;
        giocatore->vite = 2;
        giocatore->next = NULL;

        if(*head == NULL) {
            *head = giocatore;
        } else {
            giocatore_precedente->next = giocatore;
        }
        giocatore_precedente = giocatore;
    }
}

void distribuisci( Giocatore *players, int n, Mazzo *mazzo){
    if(mazzo->num_carte <= n*2) {
        printf(" Non ci sono abbastanza giocatori");
        return;
    }

    int count = 0;

    while (players != NULL && count < n * 2) {
        if (players->vite > 0) {
            players->mano[0] = mazzo->carte[count++]; // Carta coperta
            players->mano[1] = mazzo->carte[count++]; // Carta scoperta
        }
        players = players->next;
    }

    mazzo->num_carte -= count;
}

int campoVita=0;
void effetti(Giocatore *giocatore, Giocatore *head) {
    if (!giocatore) return;

    Carta carta = giocatore->mano[1];

    switch (carta.valore) {
        case DUE: case TRE: case QUATTRO: case CINQUE: case SEI:
            printf("Giocatore %d: Nessun effetto per la carta %d.\n", giocatore->numeroGiocatore, carta.valore);
            break;

        case SETTE: {
            Giocatore *next = giocatore->next ? giocatore->next : head;
            printf("Giocatore %d forza il Giocatore %d a scoprire la sua carta.\n", giocatore->numeroGiocatore, next->numeroGiocatore);
            effetti(next, head);
            break; 
        }

        case J: {
            Giocatore *previous = head;
            if (giocatore != head) {
                while (previous->next != giocatore && previous->next != NULL) {
                    previous = previous->next;
                }
            }
            printf("Giocatore %d dà 1 punto vita al Giocatore %d.\n", giocatore->numeroGiocatore, previous->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--;
                previous->vite++;
            }
            break;
        }

        case Q: {
            Giocatore *target = (giocatore->next && giocatore->next->next) ? giocatore->next->next : head;
            printf("Giocatore %d dà 1 punto vita al Giocatore %d.\n", giocatore->numeroGiocatore, target->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--;
                target->vite++;
            }
            break;
        }

        case UNO:
            printf("Giocatore %d perde 1 punto vita.\n", giocatore->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--;
                campoVita++;
            }
            break;

        case K:
            printf("Giocatore %d raccoglie %d punti vita dal campo.\n", giocatore->numeroGiocatore, campoVita);
            giocatore->vite += campoVita;
            campoVita = 0;
            break;

        default:
            printf("Giocatore %d ha giocato una carta senza effetto speciale.\n", giocatore->numeroGiocatore);
            break;
    }
}