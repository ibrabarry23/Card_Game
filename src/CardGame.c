#include <stdio.h>
#include <stdbool.h>
#include <CardGame.h>
#include <stdlib.h>


/**
 * @brief Funzione che inizializza il mazzo con tutti i semi e valori possibili
 * @param mazzo : mazzo di carte da inizializzare
 */

void inizializzaMazzo(Mazzo *mazzo) {

    // indice per tenere
    int i = 0;

    for (int seme = Fiori; seme <= Quadri; seme++) {
        for (int valore = ASSO; valore <= K; valore++) {
            // assegno a ogni seme il suo valore
            mazzo->carte[i].seme = seme;
            mazzo->carte[i].valore = valore;
            i++;
        }
    }

    // aggiorna il numero totale di carte nel mazzo
    mazzo->num_carte = i;
}

/**
 * @brief Funzione per stampare le carte
 * @param carta : carta da stampare
 * @param coperta : indica se la carta deve essere stampata
 */


void stampaCarta(const Carta *carta, bool coperta) {

    const char *semi[] = {"Fiori", "Cuori", "Picche", "Quadri"};
    const char *valori[] = {"Asso", "2", "3", "4", "5", "6", "7","J", "Q", "K"};

    if(!carta || !carta->valida) {
        printf("Carta non valida\n");
        return;
    }

    // se la carta è coperta stampo solo un messaggio
    if (coperta) {
        printf("Carta Coperta\n");
    } else {
        // se la carta rientra nell'intervallo allora la stampo
        if (carta->valore >= ASSO && carta->valore <= K) {
            printf("%s di %s (valore=%d)\n", valori[carta->valore - 1], semi[carta->seme], carta->valore);
        } else {
            // altrimenti non è valida
            printf("Carta non valida\n");
        }
    }
}

/**
 * @bried Funzione di debug per visualizzare le carte nel mazzo
 * @param mazzo : mazzo da stampare
 */

void stampaMazzo(const Mazzo *mazzo) {

    if (!mazzo || mazzo->num_carte == 0) {
        printf("Mazzo non valido\n");
        return;
    }

    for (int i = 0; i < mazzo->num_carte; i++) {
        printf("Carta %d: Valore=%d, Seme=%d\n", i, mazzo->carte[i].valore, mazzo->carte[i].seme);
        stampaCarta(&mazzo->carte[i], false);
    }
}



/**
 * @bried Funzione per mescolare il mazzo
 * @param mazzo : mazzo da mescolare
 * @param mazzo_size : numero di carte nel mazzo
 */


void shuffle(Mazzo * mazzo, size_t mazzo_size) {

    if (!mazzo || mazzo_size == 0) return;

    for(size_t i = mazzo_size-1; i > 0 ;i--) {
        // utilizzo un indice casuale tra 0 e i
        int j = rand()% (i+1);
        // scambio la carta corrente con quello con l'indice casuale
        swap(&mazzo->carte[i],&mazzo->carte[j]);
    }
}


/**
 * @bried Funzione per decidere il giorcatore iniziale casualmente
 * @param player : testa della lista giocatori
 * @param n_player : numero di giocatori totali
 * @return giocatore iniziale
 */


Giocatore * startPlayer(Giocatore* player, int n) {
    // Verifica la  validità dei parametri
    if(!player || n <1){
        printf("Errore: Il giocatore o il numero di giocatori non sono validi.\n");
        return NULL;
    }
    // Seleziona un numero casuale di passi nella lista
    int  passi = rand()% n;

    for (int i = 0; i < passi; i++)
        player = player->next;

    return player;
}



/**
 * @bried Funzione ausiliaria per scambiare 2 carte
 * @param a : prima carta
 * @param b : seconda carta
 */

void swap (Carta * a , Carta *b) {
    Carta tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * @brief Funzione per creare una lista che collega i giocatori
 * @param head : testa della lista
 * @param num : numero di giocatori
 */


void giocatori ( Giocatore **head, int num) {
    //controllo se il numero inserito è valido
    if (num <1 || num > 20)
        exit(EXIT_FAILURE);

    Giocatore *giocatore_precedente = NULL;
    //inizializza "num" giocatori
    for (int i = 1; i <= num; i++) {
        //alloca memoria per un nuovo giocatore
        Giocatore *giocatore = (Giocatore*) malloc (sizeof(Giocatore) );
        //controllo allocazione di memoria
        if (!giocatore)
            exit(EXIT_FAILURE);

        giocatore->numeroGiocatore = i; //assegna un numero a ogni giocatore
        giocatore->vite = 2; //ogni giocatore inizia il gioco con 2 vite
        giocatore->next= NULL; //il giocatore "i" è, momentaneamnte, l'ultimo giocatore
        //se head è vuoto, allora il giocatore "i" viene inserito in testa alla lista
        if(!*head) {
            *head = giocatore;
        } else { //altrimenti viene aggiunto in coda
            giocatore_precedente->next = giocatore;
        }
        giocatore_precedente= giocatore;
    }
}

/**
 * @brief Funzione per distribuire le carte ai giocatori
 * @param head : testa della lista
 * @param mazzo : mazzo dal quale si distribuiscono le carte
 */


void distribuisci(Giocatore* head, Mazzo* mazzo) {
    //controllo se i giocatori e il masso sono validi
    if (!head || !mazzo || mazzo->num_carte < 2) return;

    Giocatore* corrente = head;
    int carte_distribuite = 0;
    //il ciclo termina quando le carte sono state consegnate a tutti i giocatori
    while (corrente != NULL) {
        if (corrente->vite > 0) {
            // Carta coperta --> indice 0
            if (carte_distribuite < mazzo->num_carte) {
                corrente->mano[0] = mazzo->carte[carte_distribuite++];//incrementa il numero di carte distribuite
                corrente->mano[0].valida = true; //carta valida (= correttamente distribuita)
            } else {// controllo: se non ci sono carte a sufficienza per distribuire la carta
                corrente->mano[0].valida = false; // allora la carta coperta non è valida
            }

            // Carta scoperta --> indice 1
            if (carte_distribuite < mazzo->num_carte) {
                corrente->mano[1] = mazzo->carte[carte_distribuite++]; //incrementa il numero di carte distribuite
                corrente->mano[1].valida = true;//carta valida (= correttamente distribuita)
            } else { // controllo: se non ci sono cart e a sufficienza per distribuire la carta
                corrente->mano[1].valida = false; // allora la carta scoperta non è valida
            }
        }
        corrente = corrente->next;
    }

    mazzo->num_carte -= carte_distribuite; //aggiorno il numero di carte rimaste nel mazzo
}


int campoVita=0; //inizialmente il campo vita è vuoto

/**
 * @bief Funzione per usare gli effetti delle carte dei giocatori
 * @param giocatore : Giocatore che ha giocato la carta
 * @param head : testa della lista giocatori
 * @param indiceCarta : indica se la carta è scoperta (1) o coperta (0)
 */

void effetti(Giocatore *giocatore, Giocatore *head, int indiceCarta) {
    if (!giocatore || indiceCarta < 0 || indiceCarta > 1 || !giocatore->mano[indiceCarta].valida) {
        printf("Errore: Carta non valida o indice non valido per il Giocatore %d.\n", giocatore->numeroGiocatore);
        return;
    }

    Carta carta = giocatore->mano[indiceCarta];

    switch (carta.valore) {
      //caso in cui il valore della carta pescata sia uguale a 2, 3, 4, 5 o 6 --> non succede nulla
        case DUE: case TRE: case QUATTRO: case CINQUE: case SEI:
            printf("Giocatore %d: Nessun effetto.\n", giocatore->numeroGiocatore);
            break;
        /*caso in cui il valore della carta pescata sia uguale a 7 --> il giocatore in possesso della carta forza il giocatore
        successivo a scoprire la sua carta coperta e ad applicarne l’effetto.*/
        case SETTE: {
            Giocatore *next = giocatore->next ? giocatore->next : head;
            printf("Il Giocatore %d forza il Giocatore %d a scoprire la sua carta coperta ed applicarne l'effetto.\n", giocatore->numeroGiocatore, next->numeroGiocatore);
            if (next->mano[0].valida) { //se il giocatore successivo possiede una carta coperta valida
                stampaCarta(&next->mano[0], false);
                effetti(next, head, 0); // Scopre e applica l'effetto della carta coperta del giocatore successivo
                next->mano[0].valore = -1;
                next->mano[0].seme = -1;
            } else { //Se la carta coperta del giocatore successivo è gia stata scoperta per altri effetti (o non è valida)
                printf("Il Giocatore %d non ha una carta coperta da scoprire.\n", next->numeroGiocatore);
            }
            break;
        }
        /*caso in cui il valore della carta pescata sia uguale a J --> il giocatore in possesso della carta deve
        dare 1 punto vita al giocatore precedente. */
        case J: {
            Giocatore *previous = head;
            if (giocatore != head) {
                while (previous->next != giocatore && previous->next != NULL) {
                    previous = previous->next;
                }
            }
            printf("Giocatore %d dà 1 punto vita al Giocatore %d.\n", giocatore->numeroGiocatore, previous->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--; //il giocatore in possesso della carta perde una vita
                previous->vite++; // il giocatore precedente guadagna una vita
            }
            break;
        }

        /*caso in cui il valore della carta pescata sia uguale a Q --> il giocatore in possesso della carta deve dare 1 punto vita al secondo giocatore
        successivo (cioè, saltando un giocatore).*/
        case Q: {
          //il giocatore target è il secondo successivo a chi possiede la carta con valore Q
            Giocatore *target = (giocatore->next && giocatore->next->next) ? giocatore->next->next : head;
            printf("Giocatore %d dà 1 punto vita al Giocatore %d.\n", giocatore->numeroGiocatore, target->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--; //il giocatore in possesso della carta perde una vita
                target->vite++; // il giocatore target guadagna una vita
            }
            break;
        }

        /*caso in cui il valore della carta pescata sia uguale a 1 (asso) --> il giocatore in possesso della carta perde 1 punto
        vita, che verrà lasciata sul campo di gioco (le vite sul campo di gioco non vengono resettate a ogni fase,
        quindi rimangono anche per le successive se non sono state riscosse).*/
        case ASSO:
            printf("Giocatore %d perde 1 punto vita.\n", giocatore->numeroGiocatore);
            if (giocatore->vite > 0) {
                giocatore->vite--; //il giocatore in possesso della carta perde una vita
                campoVita++; //aggiorno il numero di vite contenute nel campo di gioco
            }
            break;

       /*caso in cui il valore della carta pescata sia uguale a 1 --> il giocatore in possesso della carta, riceve tutti i
     punti vita lasciati sul campo di gioco fino a quel momento.*/
        case K:
            printf("Giocatore %d raccoglie %d punti vita dal campo (%d).\n", giocatore->numeroGiocatore, campoVita, campoVita);
            giocatore->vite += campoVita; //il giocatore in possesso della carta guadagna tutte le vite presenti nel campo di gioco
            campoVita = 0; //il campo di gioco viene così azzerato
            break;

        default:
            printf("Giocatore %d ha giocato una carta senza effetto speciale.\n", giocatore->numeroGiocatore);
            break;
    }
}

/**
 * @brief Funzione asiliaria per contare i giocatori vivi
 * @param head : testa della lista
 * @return numero di giocatori vivi
 */

int contaGiocatoriVivi(Giocatore* head) {
    if(!head) return 0;
    int count = 0;
    while (head) {
        if (head->vite > 0) count++;
        head = head->next;
    }
    return count;
}



/**
 * @brief Funzione per eliminare i giocatori senza vite
 * @param head : testa della lista
 */


void eliminaGiocatoriMorti(Giocatore** head) {
    if(!head || !(*head)) return;
    Giocatore* curr = *head;
    Giocatore* prev = NULL;
    int eliminati = 0;
    while (curr) {
        //rimuove i giocatori con 0 vite o meno
        if (curr->vite <= 0) {
            Giocatore* toDelete = curr;
            if (prev)
                prev->next = curr->next;
            else
                *head = curr->next;

            curr = curr->next;
            printf("Giocatore %d eliminato.\n", toDelete->numeroGiocatore);
            free(toDelete);
            eliminati++;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    eliminati >0 ? printf("%d giocatori eliminati.\n", eliminati) : printf("Nessun giocatore eliminato.\n");
}

/**
 * @brief Funzione che gestisce lo svolgimento della partita
 * @param head : testa della lista
 * @param mazzo : mazzo di carte
 * @param num_giocatori : numero di giocatori totali
 */

void giocaPartita(Giocatore** head, Mazzo* mazzo) {
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

/**
 * @brief Funzione che permette di pescare una carta casuale dal mazzo
 * @return carta generata casualmente
 */


Carta pescaCarta(void) {
    Carta c;
    c.valida = true;
    c.valore = (rand() % 10) + 1;  // da ASSO (1) a K (10)
    c.seme = rand() % 4;         // da Fiori (0) a Quadri (3)
    return c;
}

/**
 * @brief Funzione che ridistribuisce le carte
 * @param head : testa della lista di giocatori
 * @param num_giocatori : numero di giocatori ancora in vita
 */

void ridistribuisciCarte(Giocatore* head, int num_giocatori) {
    Giocatore* corrente = head;
    int cont = 0;

    while (cont < num_giocatori) {
        if (corrente->vite > 0) {
            corrente->mano[0] = pescaCarta();
            corrente->mano[1] = pescaCarta();
        } else {
            // Giocatori eliminati non ricevono carte
            corrente->mano[0].valida = false;
            corrente->mano[1].valida = false;
        }

        corrente = corrente->next ? corrente->next : head;
        cont++;
    }
}


/**
 * @brief Funzione che gestiche la fase di gioco di ogni giocatore
 * @param start : primo giocatore
 * @param head  : testa della lista
 * @param num_giocatori : numero di giocatori totali
 */


void svoglimentoFase(Giocatore* start, Giocatore* head, int num_giocatori) {
    ridistribuisciCarte(head, num_giocatori);

    Giocatore* corrente = start;
    int turni = 0;

    while (turni < num_giocatori) {
        printf("\n--- Turno Giocatore %d ---\n", corrente->numeroGiocatore);

        if (corrente->vite > 0) {
            if (corrente->mano[1].valida) {
                printf("Scoperta: ");
                stampaCarta(&corrente->mano[1], false);
                effetti(corrente, head, 1);
            } else {
                printf("Giocatore %d non ha una carta scoperta.\n", corrente->numeroGiocatore);
            }

            if (corrente->mano[0].valida) {
                int scelta = 0;
                printf("Vuoi scoprire la carta coperta? [1 = Sì, 0 = No]: ");
                if (scanf("%d", &scelta) == 1 && (scelta == 1 || scelta == 0)) {
                    if (scelta == 1) {
                        printf("Coperta: ");
                        stampaCarta(&corrente->mano[0], false);
                        effetti(corrente, head, 0);

                    } else {
                        printf("Hai scelto di non scoprire la carta coperta.\n");
                    }
                } else {
                    printf("Input non valido. Turno saltato.\n");
                    while (getchar() != '\n');
                }
            }
        } else {
            printf("Giocatore %d è eliminato. Salta il turno.\n", corrente->numeroGiocatore);
        }

        turni++;
        corrente = corrente->next ? corrente->next : head;
    }

    printf("\n Fine della fase\n");
}