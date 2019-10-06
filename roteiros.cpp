#include "roteiros.h"
#include "mergesort.h"

/* Retorna o índice da ilha com maior 'cdv' que é possível ir com o 'Orçamento';
começa a procurar do índice 'idx' do vetor; retorna -1 caso
não seja possível ir para nenhuma ilha */    
int idx_ilha(int idx, std::vector<ilha>& Ilhas_ordenadas, int N, int Orcamento){
    while (idx != N){
        if (Ilhas_ordenadas[idx].custo <= Orcamento){
            /* Há uma ilha que podemos ir */
            return idx;
        }
        idx++;
    }
    /* Não há mais ilhas para ir */
    return -1;
}

/* Obtém a melhor pontuação e duração de viagem, dado um conjunto de N ilhas com
custos e valores associados, além de um custo máximo de gastos; Adota uma estratégia
gulosa, procurando a cada dia, ficar na ilha que dá mais retorno em termos de 
valor com base no custo investido; Repetições são permitidas; */
void guloso(int& pontu, int& dias, int Max, int N, std::vector<ilha>& Ilhas){
    /* O atributo 'cdv' de 'ilha' é o custo por dia por unidade de valor */
    /* Ordena o vetor com base no custo por dia por unidade de valor */
    std::vector<ilha> C_Ilhas = Ilhas;
    mergesort(C_Ilhas, 0, N-1);

    /* Encontra o roteiro */
    int disponivel = Max;
    bool possivel = false;
    int idx = idx_ilha(0,C_Ilhas, N, disponivel);
    if (idx != -1)
        possivel = true;
    while (possivel == true){
        int estadia = disponivel/C_Ilhas[idx].custo;
        dias += estadia;
        disponivel -= estadia * C_Ilhas[idx].custo;
        pontu += estadia * C_Ilhas[idx].valor;

        possivel = false;
        idx = idx_ilha(idx,C_Ilhas, N, disponivel);
        if (idx != -1)
            possivel = true;
    }
}
