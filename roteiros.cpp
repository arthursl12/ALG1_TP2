#include <string>
#include "roteiros.h"
#include "mergesort.h"

/* Particiona a string 'str' pelo delimitador 'delimiter' e guarda o token particionado 
na string 'token' (o token é removido da string original); Se não encontrar o token, 
apenas coloca a string original no 'token'; Retorna 'True' se foi possível fazer 
a operação, 'False' se não encontrar o delimitador e não conseguir fazer o particionamento; */
bool str_tok(std::string& str, std::string delimiter, std::string& token){
    std::size_t idx = str.find(delimiter);
    token = str.substr(0, idx);

    if (idx == std::string::npos){
        /* Não achou o delimitador: não faz nada e coloca a string original no token*/
        token = str;
        return false;
    }
    str.erase(0, idx+1); /* Remove o token e o delimitador da string original */
    return true;
}

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

/* Tempo: (Lin*Col). Espaço: (Lin*Col) */
/* Cria uma matriz de 'node', de dimensões 'lin' x 'col' */
void cria_matriz(std::vector<std::vector<node>>& matriz, int lin, int col){
    for (int i = 0; i < lin; i++){
        std::vector<node> linha;
        matriz.push_back(linha);
        for (int j = 0; j < col; j++){
            node nulo;
            nulo.pontuacao = -1;
            nulo.dias = -1;
            matriz[i].push_back(nulo);
        }
    }
}

// https://en.wikipedia.org/wiki/Knapsack_problem
/* Melhor solução para as 'k' primeiras ilhas e o peso 'peso' */
void opt(std::vector<std::vector<node>>& matriz, std::vector<ilha>& Ilhas, int k, int peso){
    int i = k-1; // O índice da ilha só vai até 4
    /* 0 ilhas ou custo máximo 0 */
    if ((k == 0) || (peso <= 0)){
        matriz[k][peso].pontuacao = 0;
        matriz[k][peso].dias = 0;
        return;
    }
    
    /* Não calculamos ainda com 'k-1' ilhas e o peso 'peso' */
    if (matriz[k-1][peso].pontuacao == -1)
        opt(matriz, Ilhas, k-1, peso);

    /* O custo da nova ilha 'k' é maior que o custo total (peso da mochila) */
    if (Ilhas[i].custo > peso){
        matriz[k][peso] = matriz[k-1][peso];
    }else{
        /* Não calculamos ainda com 'k-1' ilhas e o peso ('peso'-'peso de k') */
        if (matriz[k-1][peso-Ilhas[i].custo].pontuacao == -1){
            opt(matriz, Ilhas, k-1, peso-Ilhas[i].custo);
        }

        /* Olha o maior entre não colocar a ilha 'k' ou colocá-la */
        if (matriz[k-1][peso].pontuacao > (matriz[k-1][peso-Ilhas[i].custo].pontuacao + Ilhas[i].valor)){
            matriz[k][peso] = matriz[k-1][peso];
        }else{
            matriz[k][peso].pontuacao = matriz[k-1][peso-Ilhas[i].custo].pontuacao + Ilhas[i].valor;
            matriz[k][peso].dias = matriz[k-1][peso-Ilhas[i].custo].dias + 1;
        }
    }
}

/* Obtém a melhor pontuação e duração de viagem, dado um conjunto de N ilhas com
custos e valores associados, além de um custo máximo de gastos; Adota programação
dinâmica, resolvendo um 'problema da mochila'; */
void dinamica(int& pontu, int& dias, int Max, int N, std::vector<ilha>& Ilhas){
    int n_colunas = Max+1; // A 'capacidade' da mochila é o custo máximo total
    int n_linhas = N+1; // Os 'objetos' são as ilhas com suas pontuações associadas

    std::vector<std::vector<node>> matriz;
    cria_matriz(matriz, n_linhas, n_colunas);

    opt(matriz, Ilhas, N, Max);
    pontu = matriz[N][Max].pontuacao;
    dias = matriz[N][Max].dias;
}
