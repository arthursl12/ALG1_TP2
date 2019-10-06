#include "operacoes.h"
#include "DFS.h"

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

/* Propõe uma ordenação topológica da DAG que é o grafo em questão, em outras 
palavras, propõe uma ordem de fala na reunião em que um subordinado não pode falar
antes de algum superior direto ou indireto */
void Meeting(Grafo& grafo){
    std::vector<int> result;
    bool ciclo;
    /* A ordenação topológica é feita pelo DFS */
    DFS(grafo, result, ciclo);
    std::cout << "M ";

    /* Temos invertemos a ordem para atender à especificação (o DFS retorna 
    subordinados falando antes dos comandantes*/
    int max = result.size();
    int i = 1;
    for (auto it = result.rbegin(); it != result.rend(); it++){
        std::cout << (*it)+1;
        if (i == max) break;
        std::cout << " ";
        i++;
    }
    std::cout << std::endl;
}

/* Recebe uma pessoa P e imprime qual a pessoa mais jovem que a comanda, direta ou indiretamente
Se P não comandar ninguém, imprime '*' */
void Commander(std::string instr, Grafo& grafo, int N, std::vector<int>& idades){
    std::string aux;
    str_tok(instr," ", aux);
    str_tok(instr," ", aux);
    int P = std::stoi(aux);
    P--;
    Grafo TP = transposto(grafo, N);
    /* Procura a idade */
    int idade = -1;
    DFS(TP, P, idade, idades);
    if (idade == -1){
        /* Aluno não é comandado por ninguém */
        std::cout << "C *" << std::endl;
    }else{
        std::cout << "C " << idade << std::endl;
    }
}

/* Verifica se A comanda B (ou B comanda A). Se sim, inverte-se a direção da aresta. Verifica se a inversão
não cria ciclos. Se não, mantém a inversão. Se sim, não altera a aresta */
void Swap(std::string instr, Grafo& grafo){
    std::string aux;
    str_tok(instr," ", aux);
    str_tok(instr," ", aux);
    int A = std::stoi(aux);
    A--;
    str_tok(instr," ", aux);
    int B = std::stoi(aux);
    B--;
    
    /* Verifica aresta */
    bool AB = vizinhos(grafo,A,B);
    bool BA = vizinhos(grafo,B,A);
    
    if (AB == false && BA == false){
        std::cout << "S N" << std::endl;
        return;
    }
    
    /* Copia o grafo e faz o swap na cópia */
    Grafo C_grafo = grafo;
    if (AB == true){
        remove(C_grafo,A,B);
        C_grafo[B].push_back(A);
    }else{
        Grafo C_grafo = grafo;
        remove(C_grafo,B,A);
        C_grafo[A].push_back(B);
    }
    

    /* Procura ciclos no grafo cópia */
    bool ciclo = false;
    std::vector<int> result;
    DFS(C_grafo, result, ciclo);
    
    if (ciclo == true){
        std::cout << "S N" << std::endl;
    }else{
        std::cout << "S T" << std::endl;
        grafo = C_grafo;
    }
}