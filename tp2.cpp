#include <fstream>
#include <iostream>
#include <vector>
#include "mergesort.h"
#include "ilha.h"
#include "roteiros.h"

/* GULOSO:
- Calcula o custo por unidade de valor por dia
- Ordena em ordem crescente
- Começa da mais barata por dia com maior valor
- Fica ali até não poder mais (custo)
- Vai para a segunda mais barata por valor
- Segue nisso até acabar o dinheiro
*/

/* P. DINÂMICA:
Problema da Mochila:
    Capacidade: custo máximo
    Objetos: ilhas com seu valor
- Monta matriz: [5+1,MAX+1]
- Preenche linha a linha, coluna a coluna, a partir do [0,0]
- A resposta é a última célula
*/

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

typedef struct node{
    int pontuacao;
    int dias;
} node;

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

int main(int argc, char* argv[]){
    /* Coleta o argumento: nome do arquivo a ser lido e abre o arquivo*/
    if (argc != 2){std::cout << "Argumento faltando"; exit(1);}
    std::string nome_arq = argv[1];
    std::ifstream arq;
    arq.open(nome_arq, std::ios::in);
    if (!arq.is_open()){std::cout << "Erro na abertura do arquivo"; exit(1);}

    
    /* Leitura dos dados */
    std::vector<ilha> Ilhas;
    int N;
    int C_Max;

    std::string Linha;
    std::getline(arq,Linha);
    std::string aux;
    str_tok(Linha," ",aux);
    C_Max = std::stoi(aux);
    str_tok(Linha," ",aux);
    N = std::stoi(aux);
    
    for (int i = 0; i < N; i++){
        std::getline(arq,Linha);
        str_tok(Linha," ",aux);
        int custo = std::stoi(aux);
        str_tok(Linha," ",aux);
        int valor = std::stoi(aux);

        ilha i1;
        i1.custo = custo;
        i1.valor = valor;
        i1.cdv = (double)custo/(double)valor;

        Ilhas.push_back(i1);
    }

    /* Execução */
    int dias = 0;
    int pontu = 0;
    guloso(pontu, dias, C_Max, N, Ilhas);
    std::cout << pontu << " " << dias << std::endl;
    dias = 0;
    pontu = 0;
    dinamica(pontu, dias, C_Max, N, Ilhas);
    std::cout << pontu << " " << dias << std::endl;

    arq.close();
    return 0;
}