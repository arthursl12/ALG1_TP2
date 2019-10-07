#ifndef ROTEIROS_H
#define ROTEIROS_H

#include <vector>
#include "ilha.h"

bool str_tok(std::string& str, std::string delimiter, std::string& token);

int idx_ilha(int idx, std::vector<ilha>& Ilhas_ordenadas, int N, int Orcamento);
void guloso(int& pontu, int& dias, int Max, int N, std::vector<ilha>& Ilhas);

typedef struct node{
    int pontuacao;
    int dias;
} node;

void cria_matriz(std::vector<std::vector<node>>& matriz, int lin, int col);
void opt(std::vector<std::vector<node>>& matriz, std::vector<ilha>& Ilhas, int k, int peso);
void dinamica(int& pontu, int& dias, int Max, int N, std::vector<ilha>& Ilhas);

#endif /* ROTEIROS_H */