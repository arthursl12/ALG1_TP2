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
- Ordena ilhas em ordem crescente de custo
- Monta matriz: [5,MAX/100]
- Preenche linha a linha, coluna a coluna, a partir do [0,0]
- A resposta é a última célula
*/

/* Particiona a string 'str' pelo delimitador 'delimiter' e guarda o token particionado na string 'token' (o token é removido da string original);
Se não encontrar o token, apenas coloca a string original no 'token';
Retorna 'True' se foi possível fazer a operação, 'False' se não encontrar o delimitador e não conseguir fazer o particionamento; */
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
    
    /*
    for (int i = 0; i < N; i++){
        std::cout << i << " - " << Ilhas[i].custo << "  " << Ilhas[i].valor << "  " << Ilhas[i].cdv << std::endl;
    }

    std::cout << "Custo Total: " << C_Max << std::endl;
    std::cout << "#ilhas: " << N << std::endl << std::endl;
    */

    /* Execução */
    int dias = 0;
    int pontu = 0;
    guloso(pontu, dias, C_Max, N, Ilhas);
    std::cout << pontu << " " << dias << std::endl;

    
    arq.close();
    return 0;
}