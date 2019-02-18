#include <stdio.h>
#include <stdlib.h>

// sunt folosite minim 2 structuri de date (imbricate). 1 camp de biti si 1 enumerare

struct pachet // structura pentru pachetul de carti
{
    // camp de biti
    unsigned short valoare : 4; // K - 14, Q - 13, J - 12, as - 11, restul normale; asul este mai mare ca toate

    // enumerare
    enum carte{inima_neagra = 1, inima_rosie = 2, trefla = 3, romb = 4}culoare; // 1 - inima neagra; 2 - inima rosie; 3 - trefla; 4 - romb

} carte[54],t; // t e variabila aux pentru swap

struct manaJucator // structura care atribuie fiecarui jucator o mana de carti
{
    struct pachet deck[54];
    int dim; // dim repr. numarul de carti din mana fiecarui jucator
} jucator[9];
