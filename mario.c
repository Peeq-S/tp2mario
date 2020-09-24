#include <stdio.h>
#include "mario.h"

int main() {
    int tableau[5] = {1,1,1,1,-5};
    int tableau2[5] = {2,2,2,2,-4};
    int tableauAcc[5] = {0,0,0,0,0};
    //int resultat= tempsRetour(tableau2, 5);
    sauverMario(tableau, 5, 2);
    positionLibres(tableau2, tableauAcc, 5);
}

int plongeon(int tableau[], int tailleTableau, int position){
    if(0 <= tableau[position]+position && tableau[position]+position < tailleTableau) {
        return position+tableau[position];
    } else {
        return -1;
    }
}

void sauverMario(int tableau[], int tailleTableau, int position){
    for(int j = 0; j < tailleTableau; j++){
        position = plongeon(tableau, tailleTableau, position);
        if (position == -1) {
            printf("Mario est libre\n");
            return;
        }
    }
    printf("Mario est piege dans un cycle");
}

int longueurCycle(int tableau[], int tailleTableau, int position){
    for(int positionInitiale = position, longueur = 1; longueur <= tailleTableau; longueur++){
        position = plongeon(tableau, tailleTableau, position);
        if(positionInitiale == position){
            return longueur;
        }
    }
    return -1;
}

int tempsRetour(int tableau[], int tailleTableau){
    int tableauTempsRetour[5];
    for (int position = 0; position < tailleTableau; position++)
    {
        tableauTempsRetour[position] = longueurCycle(tableau, tailleTableau, position);
        if(position > 0){
            tableauTempsRetour[position] = ppcm(tableauTempsRetour[position], tableauTempsRetour[position-1]);
        }
    }
    return tableauTempsRetour[tailleTableau-1];
    
}

int ppcm(int X,int Y)
{
  int A=X;
  int B=Y;
  while (A!=B)
  {
    while (A>B) B=B+Y;
    while (A<B) A=A+X;
  }
  return A;
}

void acceleration(int tableau[], int tableauAcc[], int tailleTableau, int nbAcceleration) {
    for (int position = 0; position < tailleTableau; position++){
        int sortie = position;
        for (int j = 0; j < nbAcceleration; j++)
        {
            sortie = plongeon(tableau, tailleTableau, sortie);
            if(sortie < 0 || tailleTableau <= sortie){
                sortie = tailleTableau;
                break;
            } 
        }
        tableauAcc[position] = (sortie == 5 ? 5 : -tableau[sortie]);
    }
}

void positionLibres(int tableau[], int tableauAcc[], int tailleTableau){    
    int nbAcc = ((int)ceil(log(tailleTableau))) + 1;
    acceleration(tableau, tableauAcc, tailleTableau, nbAcc);
    for(int i = 0; i < tailleTableau; i++){
        if(tableauAcc[i] == tailleTableau){
            printf("Position %d est libre\n", i);
        }
    }
}
