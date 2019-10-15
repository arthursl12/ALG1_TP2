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
- Preenche linha a linha, coluna a coluna, recursivamente
- A resposta é a célula [5,Max]
*/

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