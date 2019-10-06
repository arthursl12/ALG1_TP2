#include "mergesort.h"
#include "ilha.h"

void mergesort(std::vector<ilha> Ilhas, int esq, int dir){
    if (esq == dir)
        return;
    int meio = (esq+dir)/2;
    mergesort(Ilhas, esq, meio);
    mergesort(Ilhas, meio+1, dir);
    merge(Ilhas, esq, meio, dir);
}

void merge(std::vector<ilha> Ilhas, int esq, int meio, int dir){
    std::vector<ilha> C_Ilhas;
    int meio_inic = meio;
    while ((esq != meio_inic) && (meio != dir)){
        if (C_Ilhas[esq] < C_Ilhas[meio]){
            Ilhas[esq] = C_Ilhas[esq];
            esq++;
        } 
        else{
            Ilhas[esq] = C_Ilhas[meio];
            meio++;
        }
    }
}

