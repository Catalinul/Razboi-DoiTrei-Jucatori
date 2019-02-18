#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "constante.h"

FILE *fileW, *fileR;

void generare_pachet(int nrJucatori)
{   //pasul I, generarea pachetului de carti
    int i, j, c=1; // indici, c reprezinta numarul cartii

    //in acest mod se genereaza tot pachetul, fiecare carte fiind unica
    for (i=1; i<=4; i++) // 4 culori posibile
        for (j=2; j<=14; j++) // 13 valori posibile
    {
        carte[c].valoare = j;
        carte[c].culoare = i;
        c++;
    }

    //se face random shuffle pentru carti, se amesteca. t este folosit pentru swap
    for (i = 1; i < NUMAR_CARTI; i++)
        {
           j = i + (rand()/(RAND_MAX/(NUMAR_CARTI - i) + 1));
           t = carte[j];
          carte[j] = carte[i];
          carte[i] = t;
        }

    // se calculeaza dimensiunea mainii fiecarui jucator
    for (i=1; i<=nrJucatori; i++)
            jucator[i].dim = NUMAR_CARTI / nrJucatori;

}


void afisare_carte(int nrJucator, int poz)
{   // functia de afisare a unei carti din mana unui anumit jucator, de la o anumita pozita din mana

    switch(jucator[nrJucator].deck[poz].valoare)
            {
            case 11:
                 fprintf(fileW,"As (11)");
                break;
            case 12:
                fprintf(fileW,"Valet (12)");
                break;
            case 13:
                fprintf(fileW,"Dama (13)");
                break;
            case 14:
                fprintf(fileW,"Popa (14)");
                break;
            default:
                fprintf(fileW,"%d",jucator[nrJucator].deck[poz].valoare);
                break;
            }


    switch(jucator[nrJucator].deck[poz].culoare)
            {
            case 0:
                fprintf(fileW," (carte nula, bug)");
                break;
            case 1:
                fprintf(fileW," de inima neagra");
                break;
            case 2:
                fprintf(fileW," de inima rosie");
                break;
            case 3:
                fprintf(fileW," de trefla");
                break;
            case 4:
                fprintf(fileW," de romb");
                break;
            }

}

void afisare_carte2(int poz)
{   // functia de afisare a unei carti de la o anumita pozita din pachet, este folosita doar pentru functia ...
    // ... afisare_pachet(), inainte de impartirea cartilor jucatorilor

    switch(carte[poz].valoare)
            {
            case 11:
                 fprintf(fileW,"As (11)");
                break;
            case 12:
                fprintf(fileW,"Valet (12)");
                break;
            case 13:
                fprintf(fileW,"Dama (13)");
                break;
            case 14:
                fprintf(fileW,"Popa (14)");
                break;
            default:
                fprintf(fileW,"%d",carte[poz].valoare);
                break;
            }


    switch(carte[poz].culoare)
            {
            case 0:
                 fprintf(fileW," (carte nula, bug)");
                break;
            case 1:
                fprintf(fileW," de inima neagra");
                break;
            case 2:
                fprintf(fileW," de inima rosie");
                break;
            case 3:
                fprintf(fileW," de trefla");
                break;
            case 4:
                fprintf(fileW," de romb");
                break;
            }



}

void afisare_pachet(int nrJucatori)
{   //pasul II, functia de afisare a pachetului de carti inainte de impartirea acestuia jucatorilor. mai contine si text decorativ
    int i;
    fprintf(fileW,"\tRazboiul pentru %d jucatori a inceput! ",nrJucatori);
    fprintf(fileW,"\n \t*** Se afiseaza pachetul de carti... ***\n\n");

    for (i=1; i<=NUMAR_CARTI; i++)
    {
            fprintf(fileW,"Cartea %d: ",i);
            afisare_carte2(i);
            fprintf(fileW,"\n");
    }

    fprintf(fileW,"\n\t*** Se amesteca cartile... ****\n");
    fprintf(fileW,"\nshuffle...");
    fprintf(fileW,"\nshuffle...");
    fprintf(fileW,"\nshuffle...\n");
    fprintf(fileW,"\n\t*** Se imparte pachetul de carti jucatorilor... ***\n");
    fprintf(fileW,"\t*** Se afiseaza cartile fiecarui jucator... ***\n");

}

void impartire_carti(int nrJucatori)
{   //pasul III, functia prin care se impart cartile in mod egal jucatorilor, dupa ce cartile au fost in prealabil amestecate.
    int i,j,dimMana = jucator[1].dim;

    for (i=1; i<=nrJucatori; i++)
        for (j=1; j<=dimMana; j++)
            {
                jucator[i].deck[j].valoare = carte[j + (i-1)*dimMana].valoare;
                jucator[i].deck[j].culoare = carte[j + (i-1)*dimMana].culoare;
            } // i reprezinta nr. crt. al jucatorului, iar j pozitia cartii din mana acestuia
              // expresia j + (i-1)*dimMana reprezinta indicele cartii in pachet
}

void afisare_mana(int nrJucator)
{   // aceasta functie este utlizata la afisarea tuturor cartilor din mana unui jucator anume
    int j;

        fprintf(fileW,"\nJucatorul %d...\n\n",nrJucator);

            for (j=1; j<=jucator[nrJucator].dim; j++)
        {

                 fprintf(fileW,"Cartea %d a jucatorului %d: ",j,nrJucator);
                 afisare_carte(nrJucator,j);
                 fprintf(fileW,"\n");
        }

}

void mutareElemLaDreapta(int nrJucator, int dimMana)
{   // aceasta functie este folosita in cadrul razboi2().
    //se face loc si se aranjeaza cartile in pachet atunci cand un jucator castiga o mana

    int val = jucator[nrJucator].deck[dimMana].valoare; // salvez datele cartii care se va pierde cand shiftez spre dreapta cu o pozitie
    int cul = jucator[nrJucator].deck[dimMana].culoare;

    int dimNou = dimMana + 1, dimManaCop = dimMana;
    jucator[nrJucator].dim = dimNou;

    while (dimMana) //shhiftez spre dreapta cu o pozitie
    {
        jucator[nrJucator].deck[dimMana].valoare = jucator[nrJucator].deck[dimMana - 1].valoare;
        jucator[nrJucator].deck[dimMana].culoare = jucator[nrJucator].deck[dimMana - 1].culoare;
        dimMana--;
    }

    jucator[nrJucator].deck[1].valoare = val; // punem cartea pierduta pe prima pozitie
    jucator[nrJucator].deck[1].culoare = cul;

    while (dimManaCop) // shiftez la dreapta pentru a face loc noi carti
    {
        jucator[nrJucator].deck[dimNou].valoare = jucator[nrJucator].deck[dimManaCop].valoare;
        jucator[nrJucator].deck[dimNou].culoare = jucator[nrJucator].deck[dimManaCop].culoare;
        dimManaCop--;
        dimNou --;
    }

    jucator[nrJucator].deck[1].valoare = 0; // acum pe prima pozitie este o carte nula
    jucator[nrJucator].deck[1].culoare = 0;

}

void razboi2()
{   //pasul IV, functia pentru jocul intre 2 jucatori
    int dim1 = jucator[1].dim, dim2 = jucator[2].dim; // dimenisiunile mainilor celor 2 jucatori

    while (dim1>0 && dim2>0) // jocul continua pana cand un jucator a adunat toate cartile
    {
        if (jucator[1].deck[dim1].valoare > jucator[2].deck[dim2].valoare || (jucator[1].deck[dim1].valoare == 11 && jucator[2].deck[dim2].valoare != 11)  )
        { // se verifica care carte este mai mare si daca aceasta nu este cumva As
            fprintf(fileW,"\n[J1 > J2] "); afisare_carte(1,dim1); fprintf(fileW," este mai mare ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 1 castiga mana!");

            mutareElemLaDreapta(1, dim1);

            jucator[1].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
            jucator[1].deck[1].culoare = jucator[2].deck[dim2].culoare;

            dim1++; // se creste dimensiunea mainii jucatorului 1

            jucator[2].deck[dim2].valoare = 0; // face nula cartea care a fost pierduta
            jucator[2].deck[dim2].culoare = 0;

            dim2--; // se scade dimensiunea mainii jucatorului 2

             fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti.\n\n",dim1,dim2);

        }
        else if (jucator[1].deck[dim1].valoare < jucator[2].deck[dim2].valoare || (jucator[2].deck[dim2].valoare == 11 && jucator[1].deck[dim1].valoare != 11) )
        { // se verifica care carte este mai mare si daca aceasta nu este cumva As
            fprintf(fileW,"\n[J1 < J2] "); afisare_carte(1,dim1); fprintf(fileW," este mai mic ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 2 castiga mana!");

            mutareElemLaDreapta(2, dim2);

            jucator[2].deck[1].valoare = jucator[1].deck[dim1].valoare; // adaugam elementul pe prima pozitie in pachet
            jucator[2].deck[1].culoare = jucator[1].deck[dim1].culoare;

            dim2++; // se creste dimensiunea mainii jucatorului 2

            jucator[1].deck[dim1].valoare = 0; // se face nula cartea care a fost pierduta
            jucator[1].deck[dim1].culoare = 0;

            dim1--; // se scade dimensiunea mainii jucatorului 1

             fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti.\n\n",dim1,dim2);
        }
        else if (jucator[1].deck[dim1].valoare == jucator[2].deck[dim2].valoare)
        { // se verifica daca este egalitate intre carti
            fprintf(fileW,"\n[J1 = J2] "); afisare_carte(1,dim1); fprintf(fileW," este egal cu "); afisare_carte(2,dim2); fprintf(fileW,".");

            fprintf(fileW,"\n\n\t!!!RAZBOI!!!\n");

            int dimWar = jucator[1].deck[dim1].valoare; // dimWar repr. dimensiunea razboiului (i.e. cartile care se vor da jos) este egala cu valoarea uneia dintre carti
            int indWar1, indWar2, dif1, dif2; // indWar reprezinta cartea care decide cine castiga razboiul
                                              // dif reprezinta un contor ce pastreaza numarul de carti care mai sunt disponibile in mana

            if (dimWar >= dim1)  // daca dimWar depaseste numarul de carti din mana atunci ultima carte din mana va fi cea care va decide razboiul
                indWar1 = 1;
            else
                indWar1 = dim1 - dimWar; // daca dim este suficient de mare atunci se calculeaza pozitia ultimei carti
            dif1 = MIN(dim1,dimWar);

            if (dimWar >= dim2)
                indWar2 = 1;
            else
                indWar2 = dim2 - dimWar;
            dif2 = MIN(dim2,dimWar);

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti.\n\n",dim1,dim2);

            while (jucator[1].deck[indWar1].valoare == jucator[2].deck[indWar2].valoare) //se face astfel incat ultimele carti de la razboi sa nu fie egale
            {
                    if (indWar1 > 1) // se verifica daca mai sunt carti in pachet si apoi se trece la urmatoare carte
                        {
                            indWar1 --;
                            dif1++;
                        }

                    if (indWar2 > 1)
                        {
                            indWar2 --;
                            dif2++;
                        }
            }


            if (jucator[1].deck[indWar1].valoare > jucator[2].deck[indWar2].valoare || jucator[1].deck[indWar1].valoare == 11)
                {  // se verifica care carte este mai mare si daca aceasta nu este cumva As
                    fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mare ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 1 castiga razboiul!\n");

                while (dif2) // se adauga cartile pierzatorului in pachetul castigatorului
                   {
                    mutareElemLaDreapta(1, dim1);

                    jucator[1].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[1].deck[1].culoare = jucator[2].deck[dim2].culoare;

                    dim1++;

                    jucator[2].deck[dim2].valoare = 0;
                    jucator[2].deck[dim2].culoare = 0;

                    dim2--;
                    dif2--;


                    }

                }
            else
            {   // inseamna ca jucatorul 2 are cartea mai mare
                fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mic ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 2 castiga razboiul!\n");
                while (dif1) // se adauga cartile pierzatorului in pachetul castigatorului
               {
                    mutareElemLaDreapta(2, dim2);

                    jucator[2].deck[1].valoare = jucator[1].deck[dim1].valoare;
                    jucator[2].deck[1].culoare = jucator[1].deck[dim1].culoare;

                    dim2++;

                    jucator[1].deck[dim1].valoare = 0;
                    jucator[1].deck[dim1].culoare = 0;

                    dim1--;
                    dif1--;
               }

            }

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti.\n",dim1,dim2);

            fprintf(fileW,"\n\tSFARSIT DE RAZBOI\t\n");

        }
    }

    if (dim1 <= 0)
         {fprintf(fileW,"\nJucatorul 2 a castigat!\n");
          fprintf(fileW,"\nJucatorul 1 a pierdut!\n");}


    if (dim2 <=0)
        {fprintf(fileW,"\nJucatorul 1 a castigat!\n");
         fprintf(fileW,"\nJucatorul 2 a pierdut!\n");}
}

void mutareElemLaDreapta2(int nrJucator, int dimMana)
{   // aceasta functie este folosita in cadrul razboi3().
    //se face loc 2 pozitii si se aranjeaza cartile in pachet atunci cand un jucator castiga o mana

    int val = jucator[nrJucator].deck[dimMana].valoare; // salvez datele cartii care se va pierde cand shiftez spre dreapta cu o pozitie
    int cul = jucator[nrJucator].deck[dimMana].culoare;

    int dimNou = dimMana + 2, dimManaCop = dimMana;
    jucator[nrJucator].dim = dimNou;

    while (dimMana) //shhiftez spre dreapta cu o pozitie
    {
        jucator[nrJucator].deck[dimMana].valoare = jucator[nrJucator].deck[dimMana - 1].valoare;
        jucator[nrJucator].deck[dimMana].culoare = jucator[nrJucator].deck[dimMana - 1].culoare;
        dimMana--;
    }

    jucator[nrJucator].deck[1].valoare = val; // punem cartea pierduta pe prima pozitie
    jucator[nrJucator].deck[1].culoare = cul;

    while (dimManaCop) // shiftez la dreapta pentru a face loc noi carti
    {
        jucator[nrJucator].deck[dimNou].valoare = jucator[nrJucator].deck[dimManaCop].valoare;
        jucator[nrJucator].deck[dimNou].culoare = jucator[nrJucator].deck[dimManaCop].culoare;
        dimManaCop--;
        dimNou --;
    }

    jucator[nrJucator].deck[1].valoare = 0; // acum pe prima pozitie este o carte nula
    jucator[nrJucator].deck[1].culoare = 0;

    jucator[nrJucator].deck[2].valoare = 0; // acum pe a doua pozitie este o carte nula
    jucator[nrJucator].deck[2].culoare = 0;

}

void razboi3()
{   //pasul IV, razboi3() este analog razboi2(), fiind mai complex datorita numarului de 3 jucatori

    int  ok = 1, dim1 = jucator[1].dim, dim2 = jucator[2].dim, dim3 = jucator[3].dim; // dimenisiunile mainilor celor 2 jucatori

    while ( (dim1>0 && dim2>0) && (dim1>0 && dim3>0) && (dim2>0 && dim3>0) )
    {
        int v[3];
        v[1] = jucator[1].deck[dim1].valoare, v[2] = jucator[2].deck[dim2].valoare, v[3] = jucator[3].deck[dim3].valoare ;


        if ( dim1>0 && ( ((v[1] > v[2]) && (v[1] > v[3])) || (v[1] == 11 && (v[2]!=11 && v[3] != 11))) )
        {
            fprintf(fileW,"\n[J1 > J2 si J3] "); afisare_carte(1,dim1); fprintf(fileW," este mai mare ca "); afisare_carte(2,dim2); fprintf(fileW," si ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 1 castiga mana!");

            mutareElemLaDreapta2(1, dim1);

            jucator[1].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
            jucator[1].deck[1].culoare = jucator[2].deck[dim2].culoare;

            dim1++;

            jucator[1].deck[2].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe a doua pozitie in pachet
            jucator[1].deck[2].culoare = jucator[3].deck[dim3].culoare;

            dim1++;

            jucator[2].deck[dim2].valoare = 0;
            jucator[2].deck[dim2].culoare = 0;

            dim2--;

            jucator[3].deck[dim3].valoare = 0;
            jucator[3].deck[dim3].culoare = 0;

            dim3--;

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);
        }
        else if (dim2>0 && ( ((v[2] > v[1]) && (v[2] > v[3])) || (v[2] == 11 && (v[1]!=11 && v[3] != 11))))
        {
            fprintf(fileW,"\n[J2 > J1 si J3] "); afisare_carte(2,dim2); fprintf(fileW," este mai mare ca "); afisare_carte(1,dim1); fprintf(fileW," si ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 2 castiga mana!");

            mutareElemLaDreapta2(2, dim2);

            jucator[2].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
            jucator[2].deck[1].culoare = jucator[2].deck[dim2].culoare;

            dim2++;

            jucator[2].deck[2].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe a doua pozitie in pachet
            jucator[2].deck[2].culoare = jucator[3].deck[dim3].culoare;

            dim2++;

            jucator[1].deck[dim2].valoare = 0;
            jucator[1].deck[dim2].culoare = 0;

            dim1--;

            jucator[3].deck[dim3].valoare = 0;
            jucator[3].deck[dim3].culoare = 0;

            dim3--;

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);
        }
        else if (dim3>0 && ( ((v[3] > v[1]) && (v[3] > v[2])) || (v[3] == 11 && (v[1]!=11 && v[2] != 11))))
        {
            fprintf(fileW,"\n[J3 > J1 si J2] "); afisare_carte(3,dim3); fprintf(fileW," este mai mare ca "); afisare_carte(1,dim1); fprintf(fileW," si ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 3 castiga mana!");

            mutareElemLaDreapta2(3, dim3);

            jucator[3].deck[1].valoare = jucator[1].deck[dim1].valoare; // adaugam elementul pe prima pozitie in pachet
            jucator[3].deck[1].culoare = jucator[1].deck[dim1].culoare;

            dim3++;

            jucator[3].deck[2].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe a doua pozitie in pachet
            jucator[3].deck[2].culoare = jucator[2].deck[dim2].culoare;

            dim3++;

            jucator[1].deck[dim1].valoare = 0;
            jucator[1].deck[dim1].culoare = 0;

            dim1--;

            jucator[2].deck[dim2].valoare = 0;
            jucator[2].deck[dim2].culoare = 0;

            dim2--;

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);
        }
        else if ( (dim1>0&&dim2>0&&dim3>0) && ( (v[1] == v[2]) && (v[2] == v[3]) ) )
        {
            fprintf(fileW,"\n[J1 = J2 = J3] "); afisare_carte(1,dim1); fprintf(fileW," este egal cu "); afisare_carte(2,dim2); fprintf(fileW," si cu "); afisare_carte(3,dim3); fprintf(fileW,".");

            fprintf(fileW,"\n\n\t!!!RAZBOI!!!\n");

            int dimWar = v[1];
            int indWar1, indWar2, indWar3, dif1, dif2, dif3;

            if (dimWar >= dim1)
                indWar1 = 1;
            else
                indWar1 = dim1 - dimWar;
            dif1 = MIN(dim1,dimWar);

            if (dimWar >= dim2)
                indWar2 = 1;
            else
                indWar2 = dim2 - dimWar;
            dif2 = MIN(dim2,dimWar);

            if (dimWar >= dim3)
                indWar3 = 1;
            else
                indWar3 = dim3 - dimWar;
            dif3 = MIN(dim3,dimWar);

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            while (jucator[1].deck[indWar1].valoare == jucator[2].deck[indWar2].valoare) //se face astfel incat ultimele carti de la razboi sa nu fie egale
            {
                    if (indWar1 > 1)
                        {
                            indWar1 --;
                            dif1++;
                        }

                    if (indWar2 > 1)
                        {
                            indWar2 --;
                            dif2++;
                        }

                   if (indWar3 > 1)
                        {
                            indWar3 --;
                            dif3++;
                        }
            }

             if (((jucator[1].deck[indWar1].valoare >= jucator[2].deck[indWar2].valoare) && (jucator[1].deck[indWar1].valoare >= jucator[3].deck[indWar3].valoare))  || (jucator[1].deck[indWar1].valoare == 11))
                {
                    fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mare ca "); afisare_carte(2,dim2); fprintf(fileW," si ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 1 castiga razboiul!\n");

                while (dif2 && dif3)
                   {
                    mutareElemLaDreapta2(1, dim1);

                    jucator[1].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[1].deck[1].culoare = jucator[2].deck[dim2].culoare;

                    dim1++;

                    jucator[1].deck[2].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[1].deck[2].culoare = jucator[3].deck[dim3].culoare;

                    dim1++;

                    jucator[2].deck[dim2].valoare = 0;
                    jucator[2].deck[dim2].culoare = 0;

                    dim2--;
                    dif2--;

                    jucator[3].deck[dim3].valoare = 0;
                    jucator[3].deck[dim3].culoare = 0;

                    dim3--;
                    dif3--;


                    }
                }
                else if ((jucator[2].deck[indWar2].valoare >= jucator[1].deck[indWar1].valoare) && (jucator[2].deck[indWar2].valoare >= jucator[3].deck[indWar3].valoare)  || jucator[2].deck[indWar2].valoare == 11)
                {
                    fprintf(fileW,"\n"); afisare_carte(2,indWar2); fprintf(fileW," este mai mare ca "); afisare_carte(1,dim1); fprintf(fileW," si ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 2 castiga razboiul!\n");

                while (dif1 && dif3)
                   {
                    mutareElemLaDreapta2(2, dim2);

                    jucator[2].deck[1].valoare = jucator[1].deck[dim1].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[2].deck[1].culoare = jucator[1].deck[dim1].culoare;

                    dim2++;

                    jucator[2].deck[2].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[2].deck[2].culoare = jucator[3].deck[dim3].culoare;

                    dim2++;

                    jucator[1].deck[dim1].valoare = 0;
                    jucator[1].deck[dim1].culoare = 0;

                    dim1--;
                    dif1--;

                    jucator[3].deck[dim3].valoare = 0;
                    jucator[3].deck[dim3].culoare = 0;

                    dim3--;
                    dif3--;


                    }
                }
                else
                {
                    fprintf(fileW,"\n"); afisare_carte(3,indWar3); fprintf(fileW," este mai mare ca "); afisare_carte(1,dim1); fprintf(fileW," si ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 3 castiga razboiul!\n");

                while (dif1 && dif2)
                   {
                    mutareElemLaDreapta2(3, dim3);

                    jucator[3].deck[1].valoare = jucator[1].deck[dim1].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[3].deck[1].culoare = jucator[1].deck[dim1].culoare;

                    dim3++;

                    jucator[3].deck[2].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[3].deck[2].culoare = jucator[2].deck[dim2].culoare;

                    dim3++;

                    jucator[1].deck[dim1].valoare = 0;
                    jucator[1].deck[dim1].culoare = 0;

                    dim1--;
                    dif1--;

                    jucator[2].deck[dim2].valoare = 0;
                    jucator[2].deck[dim2].culoare = 0;

                    dim2--;
                    dif2--;


                    }
                }

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            fprintf(fileW,"\n\tSFARSIT DE RAZBOI\n");
        }
        else if ( (dim1>0&&dim2>0) && (v[1] == v[2]))
        {
            fprintf(fileW,"\n[J1 = J2] "); afisare_carte(1,dim1); fprintf(fileW," este egal cu "); afisare_carte(2,dim2); fprintf(fileW,".");

            fprintf(fileW,"\n\n\t!!!RAZBOI!!!\n");

            int dimWar = jucator[1].deck[dim1].valoare;
            int indWar1, indWar2, dif1, dif2;

            if (dimWar >= dim1)
                indWar1 = 1;
            else
                indWar1 = dim1 - dimWar;
            dif1 = MIN(dim1,dimWar);

            if (dimWar >= dim2)
                indWar2 = 1;
            else
                indWar2 = dim2 - dimWar;
            dif2 = MIN(dim2,dimWar);

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            while (jucator[1].deck[indWar1].valoare == jucator[2].deck[indWar2].valoare) //se face astfel incat ultimele carti de la razboi sa nu fie egale
            {
                    if (indWar1 > 1)
                        {
                            indWar1 --;
                            dif1++;
                        }

                    if (indWar2 > 1)
                        {
                            indWar2 --;
                            dif2++;
                        }
            }


            if (jucator[1].deck[indWar1].valoare > jucator[2].deck[indWar2].valoare || jucator[1].deck[indWar1].valoare == 11)
                {
                    fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mare ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 1 castiga razboiul!\n");

                while (dif2)
                   {
                    mutareElemLaDreapta(1, dim1);

                    jucator[1].deck[1].valoare = jucator[2].deck[dim2].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[1].deck[1].culoare = jucator[2].deck[dim2].culoare;

                    dim1++;

                    jucator[2].deck[dim2].valoare = 0;
                    jucator[2].deck[dim2].culoare = 0;

                    dim2--;
                    dif2--;


                    }

                }
            else
            {
                fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mic ca "); afisare_carte(2,dim2); fprintf(fileW,". Jucatorul 2 castiga razboiul!\n");
                while (dif1)
               {
                    mutareElemLaDreapta(2, dim2);

                    jucator[2].deck[1].valoare = jucator[1].deck[dim1].valoare;
                    jucator[2].deck[1].culoare = jucator[1].deck[dim1].culoare;

                    dim2++;

                    jucator[1].deck[dim1].valoare = 0;
                    jucator[1].deck[dim1].culoare = 0;

                    dim1--;
                    dif1--;
               }

            }

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            fprintf(fileW,"\n\tSFARSIT DE RAZBOI\n");
        }
        else if ( (dim2>0&&dim3>0) && (v[2] == v[3]))
        {
            fprintf(fileW,"\n[J2 = J3] "); afisare_carte(2,dim2); fprintf(fileW," este egal cu "); afisare_carte(3,dim3); fprintf(fileW,".");

            fprintf(fileW,"\n\n\t!!!RAZBOI!!!\n");

            int dimWar = jucator[2].deck[dim2].valoare;
            int indWar2, indWar3, dif2, dif3;

            if (dimWar >= dim2)
                indWar2 = 1;
            else
                indWar2 = dim2 - dimWar;
            dif2 = MIN(dim2,dimWar);

            if (dimWar >= dim3)
                indWar3 = 1;
            else
                indWar3 = dim3 - dimWar;
            dif3 = MIN(dim3,dimWar);

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            while (jucator[2].deck[indWar2].valoare == jucator[3].deck[indWar3].valoare) //se face astfel incat ultimele carti de la razboi sa nu fie egale
            {
                    if (indWar2 > 1)
                        {
                            indWar2 --;
                            dif2++;
                        }

                    if (indWar3 > 1)
                        {
                            indWar3 --;
                            dif3++;
                        }
            }


            if (jucator[2].deck[indWar2].valoare > jucator[3].deck[indWar3].valoare || jucator[2].deck[indWar2].valoare == 11)
                {
                    fprintf(fileW,"\n"); afisare_carte(2,indWar2); fprintf(fileW," este mai mare ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 2 castiga razboiul!\n");

                while (dif3)
                   {
                    mutareElemLaDreapta(2, dim2);

                    jucator[2].deck[1].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[2].deck[1].culoare = jucator[3].deck[dim3].culoare;

                    dim2++;

                    jucator[3].deck[dim3].valoare = 0;
                    jucator[3].deck[dim3].culoare = 0;

                    dim3--;
                    dif3--;


                    }

                }
            else
            {
                fprintf(fileW,"\n"); afisare_carte(2,indWar2); fprintf(fileW," este mai mic ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 3 castiga razboiul!\n");
                while (dif2)
               {
                    mutareElemLaDreapta(3, dim3);

                    jucator[3].deck[1].valoare = jucator[2].deck[dim2].valoare;
                    jucator[3].deck[1].culoare = jucator[2].deck[dim2].culoare;

                    dim3++;

                    jucator[2].deck[dim2].valoare = 0;
                    jucator[2].deck[dim2].culoare = 0;

                    dim2--;
                    dif2--;
               }

            }

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            fprintf(fileW,"\n\tSFARSIT DE RAZBOI\n");
        }
        else if ( (dim1>0&&dim3>0) && (v[1] == v[3]))
        {
            fprintf(fileW,"\n[J1 = J3] "); afisare_carte(1,dim1); fprintf(fileW," este egal cu "); afisare_carte(3,dim3); fprintf(fileW,".");

            fprintf(fileW,"\n\n\t!!!RAZBOI!!!\n");

            int dimWar = jucator[1].deck[dim1].valoare;
            int indWar1, indWar3, dif1, dif3;

            if (dimWar >= dim1)
                indWar1 = 1;
            else
                indWar1 = dim1 - dimWar;
            dif1 = MIN(dim1,dimWar);

            if (dimWar >= dim3)
                indWar3 = 1;
            else
                indWar3 = dim3 - dimWar;
            dif3 = MIN(dim3,dimWar);

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            while (jucator[1].deck[indWar1].valoare == jucator[3].deck[indWar3].valoare) //se face astfel incat ultimele carti de la razboi sa nu fie egale
            {
                    if (indWar1 > 1)
                        {
                            indWar1 --;
                            dif1++;
                        }

                    if (indWar3 > 1)
                        {
                            indWar3 --;
                            dif3++;
                        }
            }


            if (jucator[1].deck[indWar1].valoare > jucator[3].deck[indWar3].valoare || jucator[1].deck[indWar1].valoare == 11)
                {
                    fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mare ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 1 castiga razboiul!\n");

                while (dif3)
                   {
                    mutareElemLaDreapta(1, dim1);

                    jucator[1].deck[1].valoare = jucator[3].deck[dim3].valoare; // adaugam elementul pe prima pozitie in pachet
                    jucator[1].deck[1].culoare = jucator[3].deck[dim3].culoare;

                    dim1++;

                    jucator[3].deck[dim3].valoare = 0;
                    jucator[3].deck[dim3].culoare = 0;

                    dim3--;
                    dif3--;


                    }

                }
            else
            {
                fprintf(fileW,"\n"); afisare_carte(1,indWar1); fprintf(fileW," este mai mic ca "); afisare_carte(3,dim3); fprintf(fileW,". Jucatorul 3 castiga razboiul!\n");
                while (dif1)
               {
                    mutareElemLaDreapta(3, dim3);

                    jucator[3].deck[3].valoare = jucator[1].deck[dim1].valoare;
                    jucator[3].deck[3].culoare = jucator[1].deck[dim1].culoare;

                    dim3++;

                    jucator[1].deck[dim1].valoare = 0;
                    jucator[1].deck[dim1].culoare = 0;

                    dim1--;
                    dif1--;
               }

            }

            fprintf(fileW,"\nIn pachetul jucatorului 1 sunt %d carti. In pachetul jucatorului 2 sunt %d carti. In pachetul jucatorului 3 sunt %d carti.\n\n",dim1,dim2,dim3);

            fprintf(fileW,"\n\tSFARSIT DE RAZBOI\n");
        }

    }

    if (dim1 != 0)
         fprintf(fileW,"\nJucatorul 1 a castigat!\n");
         else
        fprintf(fileW,"\nJucatorul 1 a pierdut!\n");

    if (dim2 !=0)
        fprintf(fileW,"\nJucatorul 2 a castigat!\n");
        else
        fprintf(fileW,"\nJucatorul 2 a pierdut!\n");

     if (dim3 !=0)
        fprintf(fileW,"\nJucatorul 3 a castigat!\n");
        else
        fprintf(fileW,"\nJucatorul 3 a pierdut!\n");

}

void rescriereTastaturaNrJucatori(int* nrJucatori)
{  // in cazul in care se doreste un alt numar de jucatori decat cel aflat in fisier
    char s[3];

    printf("Numarul de jucatori este %d. Doriti sa schimbati acest numar? [DA/NU]\n",*nrJucatori);
    scanf("%s",s);

    if (strcmp(s,"DA") == 0 || strcmp(s,"da") == 0)
    {
        printf("Introduceti noul numar de jucatori. [2/3]\n");
        while(1)
        {
            scanf("%d",&(*nrJucatori));

            if (*nrJucatori != 2 && *nrJucatori !=3)
                printf("Nu ati introdus un numar valid.\n");

            if (*nrJucatori == 2 || *nrJucatori == 3)
                { printf("Noul numar de jucatori este %d.",*nrJucatori); break; }
        }
    }
    else
        printf("Numarul de jucatori nu a fost schimbat.");
}
