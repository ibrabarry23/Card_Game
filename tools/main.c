#include <stdio.h>
#include <CardGame.h>

int main(void) {
    Mazzo mazzo;
    inizializzaMazzo(&mazzo);

    shuffle( &mazzo, mazzo.num_carte);
    stampaMazzo(&mazzo);

    return 0;
}
