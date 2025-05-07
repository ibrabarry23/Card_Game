#include <stdio.h>
#include <stdbool.h>
#include <CardGame.h>
#include <stdlib.h>
#include <time.h>


void inizializzaMazzo(Mazzo *mazzo) {
    int index = 0;
    for (int seme = Fiori; seme <= Quadri; seme++) {
        for (int valore = ASSO; valore <= K; valore++) {
            mazzo->carte[index].seme = seme;
            mazzo->carte[index].valore = valore;
            index++;
        }
    }
    mazzo->num_carte = index;
}



void stampaCarta(const Carta *carta, bool is_coperta) {
    const char *semi[] = {"Fiori", "Cuori", "Picche", "Quadri"};
    const char *valori[] = {
        "Asso", "2", "3", "4", "5", "6", "7","J", "Q", "K"
    };
    if(!carta->valida) {
        printf("Carta non valida\n");
        return;
    }

    if (is_coperta) {
        printf("Carta Coperta\n");
    } else {
        if (carta->valore >= ASSO && carta->valore <= K) {
            printf("%s di %s (valore=%d)\n",
                   valori[carta->valore - 1],    
                   semi[carta->seme],
                   carta->valore);               
        }  else {
            printf("Carta non valida\n");
        }
    }
}





void stampaMazzo(const Mazzo *mazzo) {
    for (int i = 0; i < mazzo->num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo->carte[i].valore, mazzo->carte[i].seme);
        stampaCarta(&mazzo->carte[i], false);
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





void distribuisci(Giocatore* head, Mazzo* mazzo) {
    if (!head || !mazzo || mazzo->num_carte < 2) return;

    Giocatore* corrente = head;
    int carte_distribuite = 0;

    while (corrente != NULL && carte_distribuite < mazzo->num_carte) {
        if (corrente->vite > 0) {
            // Carta coperta
            corrente->mano[0] = mazzo->carte[carte_distribuite++];
            corrente->mano[0].valida = true;

            // Carta scoperta
            if (carte_distribuite < mazzo->num_carte) {
                corrente->mano[1] = mazzo->carte[carte_distribuite++];
                corrente->mano[1].valida = true;
            } else {
                corrente->mano[1].valida = false;
            }
        }
        corrente = corrente->next;
    }

    mazzo->num_carte -= carte_distribuite;
}


int campoVita=0;
void effetti(Giocatore *giocatore, Giocatore *head, int indiceCarta) {
    if (!giocatore || indiceCarta < 0 || indiceCarta > 1 || !giocatore->mano[indiceCarta].valida) {
        printf("Errore: Carta non valida o indice non valido per il Giocatore %d.\n", giocatore->numeroGiocatore);
        return;
    }

    Carta carta = giocatore->mano[indiceCarta];

    switch (carta.valore) {
        case DUE: case TRE: case QUATTRO: case CINQUE: case SEI:
            printf("Giocatore %d: Nessun effetto.\n", giocatore->numeroGiocatore, carta.valore);
            break;

        case SETTE: {
            Giocatore *next = giocatore->next ? giocatore->next : head;
            printf("Giocatore %d forza il Giocatore %d a scoprire la sua carta coperta.\n", giocatore->numeroGiocatore, next->numeroGiocatore);
            if (next->mano[0].valida) {
                stampaCarta(&next->mano[0], false);
                effetti(next, head, 0); // Applica l'effetto della carta coperta del giocatore forzato
                next->mano[0].valore = -1;
                next->mano[0].seme = -1;
            } else {
                printf("Il Giocatore %d non ha una carta coperta da scoprire.\n", next->numeroGiocatore);
            }
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

        case ASSO:
            printf("Giocatore %d perde 1 punto vita.\n", giocatore->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--;
                campoVita++;
            }
            break;

        case K: 
            printf("Giocatore %d raccoglie %d punti vita dal campo (%d).\n", giocatore->numeroGiocatore, campoVita, campoVita);
            giocatore->vite += campoVita;
            campoVita = 0;
            break;

        default:
            printf("Giocatore %d ha giocato una carta senza effetto speciale.\n", giocatore->numeroGiocatore);
            break;
    }
}







int contaGiocatoriVivi(Giocatore* head) {
    int count = 0;
    while (head) {
        if (head->vite > 0) count++;
        head = head->next;
    }
    return count;
}




void eliminaGiocatoriMorti(Giocatore** head) {
    Giocatore* curr = *head;
    Giocatore* prev = NULL;

    while (curr) {
        if (curr->vite <= 0) {
            Giocatore* toDelete = curr;
            if (prev)
                prev->next = curr->next;
            else
                *head = curr->next;

            curr = curr->next;
            printf("Giocatore %d eliminato.\n", toDelete->numeroGiocatore);
            free(toDelete);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void giocaPartita(Giocatore** head, Mazzo* mazzo, int num_giocatori) {
    while (contaGiocatoriVivi(*head) > 1) {
        distribuisci(*head, mazzo);

        Giocatore* inizio = startPlayer(*head, contaGiocatoriVivi(*head));
        svoglimentoFase(inizio, *head, contaGiocatoriVivi(*head));
        
        eliminaGiocatoriMorti(head);

        printf("\n--- Stato dei giocatori ---\n");
        Giocatore* g = *head;
        while (g) {
            printf("Giocatore %d - Vite: %d\n", g->numeroGiocatore, g->vite);
            g = g->next;
        }
    }

    printf("\n--- FINE PARTITA ---\n");
    if (*head)
        printf("Il vincitore è il Giocatore %d con %d vite!\n", (*head)->numeroGiocatore, (*head)->vite);
    else
        printf("Nessun vincitore.\n");
}
Carta pescaCarta(void) {
    Carta c;
    c.valida = true;
    c.valore = rand() % 10 + 1;  // da ASSO (1) a K (10)
    c.seme = rand() % 4;         // da Fiori (0) a Quadri (3)
    return c;
}
void sostituisciCarta(Giocatore* g, int indice) {
    if (g->mano[indice].valida) {
      
        g->mano[indice].valida = false;
        g->mano[indice].valore = -1;
        g->mano[indice].seme = -1;

        g->mano[indice] = pescaCarta();
    }
}



void svoglimentoFase(Giocatore* start, Giocatore* head, int num_giocatori) {
    Giocatore* corrente = start;
    int decisioni = 0;

    while (decisioni < num_giocatori) {
        printf("\n--- Turno Giocatore %d ---\n", corrente->numeroGiocatore);

        // Carta scoperta
        if (corrente->mano[1].valida) {
            printf("Scoperta: ");
            stampaCarta(&corrente->mano[1], false);
            effetti(corrente, head, 1);
            sostituisciCarta(corrente, 1); // Sostituzione carta scoperta
        } else {
            printf("Giocatore %d non ha una carta scoperta.\n", corrente->numeroGiocatore);
        }

        // Carta coperta
        if (corrente->vite > 0 && corrente->mano[0].valida) {
            int scelta = 0;
            printf("Vuoi scoprire la carta coperta? [1 = Sì, 0 = No]: ");
            scanf("%d", &scelta);

            if (scelta == 1) {
                printf("Coperta: ");
                stampaCarta(&corrente->mano[0], false);
                effetti(corrente, head, 0);
                sostituisciCarta(corrente, 0); // Sostituzione carta coperta
            } else {
                printf("Hai scelto di non scoprire la carta coperta.\n");
            }
        }

        decisioni++;
        corrente = corrente->next ? corrente->next : head;
    }

    printf("\n Fine fase \n");
}
