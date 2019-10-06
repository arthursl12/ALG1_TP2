#ifndef MERGESORT_H
#define MERGESORT_H

#include "ilha.h"
#include <vector>

void mergesort(std::vector<ilha> Ilhas, int esq, int dir);
void merge(std::vector<ilha> Ilhas, int esq, int meio, int dir);

#endif /* MERGESORT_H */