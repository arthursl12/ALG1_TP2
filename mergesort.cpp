#include "mergesort.h"
#include "ilha.h"
#include <cmath>
#include <iostream>

void mergesort(std::vector<ilha>& Ilhas, int esq, int dir){
    if (abs(esq-dir) <= 1)
        return;
    int meio = (esq+dir)/2;
    mergesort(Ilhas, esq, meio);
    mergesort(Ilhas, meio+1, dir);
    merge(Ilhas, esq, meio, dir);
}

void merge(std::vector<ilha>& Ilhas, int esq, int meio, int dir){
    std::vector<ilha> C_Ilhas;
    C_Ilhas = Ilhas;
    int i;
    i = esq;
    int meio_dir = meio+1;
    while ((esq <= meio) && (meio_dir <= dir)){
        //std::cout << C_Ilhas[esq].cdv << " vs " << C_Ilhas[meio_dir].cdv << std::endl;
        if (C_Ilhas[esq].cdv < C_Ilhas[meio_dir].cdv){
            Ilhas[i] = C_Ilhas[esq];
            i++;
            esq++;
        } 
        else{
            Ilhas[i] = C_Ilhas[meio_dir];
            meio_dir++;
            i++;
        }
    }
    
    while(meio_dir <= dir){
        Ilhas[i] = C_Ilhas[meio_dir];
        meio_dir++;
        i++;
    }   
    while(esq <= meio){
        Ilhas[i] = C_Ilhas[esq];
        i++;
        esq++;
    }
}

