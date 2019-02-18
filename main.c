/** Program realizat de Pirvu Constantin-Catalin, gr. 154, semigrupa prof. Ceachi Bogdan
 *  Programul consta in generarea unui joc de razboi pentru 2 sau 3 jucatori. Input si output din fisiere.
 */

#include <stdio.h>
#include <stdlib.h> // pentru RAND_MAX
#include "functii.h"

FILE *fileW, *fileR; // fisierele pentru scriere, respectiv citire

// nu sunt folosite variabile globale.

int main() // functia main() este cat mai minimala cu putinta
{
    int i,nrJucatori;

    fileW = fopen("razboi.txt","w");
    fileR = fopen("nrJucatori.txt","r");

    if (fileW == NULL) // se verifica daca sunt erori la fisierul de scriere
    {
        printf("Eroare la deschiderea fisierului de output!\n");
        perror("Error");
        exit(1);
    }

    fscanf(fileR,"%d",&nrJucatori); // citire din fisier a numarului de jucatori

    rescriereTastaturaNrJucatori(&nrJucatori); // se intreaba daca se doreste rescrierea numarului de jucatori, de la tastatura

    srand(time(NULL)); // altfel nu merge random bine

    generare_pachet(nrJucatori);

    afisare_pachet(nrJucatori);

    impartire_carti(nrJucatori);

    for (i=1; i<=nrJucatori; i++) // se afiseaza cartile din mana fiecarui jucator
           afisare_mana(i);

    if (nrJucatori == 2) // se incepe jocul pentru numarul de jucatori (2 sau 3)
        razboi2();
    else
        razboi3();

    fclose(fileW);

    return 0;
}
