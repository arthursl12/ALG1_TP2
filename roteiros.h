#ifndef ROTEIROS_H
#define ROTEIROS_H

#include <vector>
#include "ilha.h"

int idx_ilha(int idx, std::vector<ilha>& Ilhas_ordenadas, int N, int Orcamento);
void guloso(int& pontu, int& dias, int Max, int N, std::vector<ilha>& Ilhas);

#endif /* ROTEIROS_H */