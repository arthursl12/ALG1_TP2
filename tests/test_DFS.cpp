#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <fstream>
#include <string>
#include "doctest.h"
#include "../DFS.h"
#include "../operacoes.h"

Grafo constroi_grafo(){
    /* Vetor de idades e inicialização do grafo (lista de adjacências) */
    Grafo grafo;
    std::vector<int> idades = {21, 33, 34, 18, 42, 22, 26};
    std::vector<std::string> linhas_arestas = {"1 2","1 3","2 5","3 5","3 6","4 6","4 7","6 7"};
    for (int i = 0; i < 7; i++){
        std::vector<int> n1;
        grafo.push_back(n1);
    }
    
    /* Cria as arestas: X comanda Y, lembrando que no programa os índices dos 
    integrantes começam no 0 e no arquivo de entrada começam de 1*/
    for (int i = 0; i < 8; i++){
        std::string Linha = linhas_arestas[i];
        std::string aux;
        str_tok(Linha," ",aux);
        int X = std::stoi(aux) - 1;
        str_tok(Linha," ",aux);
        int Y = std::stoi(aux) - 1;
        grafo[X].push_back(Y);
    }
    return grafo;
}

TEST_CASE("Construtor"){
    Grafo g = constroi_grafo();
    std::vector<int> result;
    bool ciclo;
    CHECK_NOTHROW(DFS(g,result, ciclo));
}

TEST_CASE("DFS"){
    Grafo g = constroi_grafo();
    std::vector<int> result;
    bool ciclo;
    DFS(g,result, ciclo);
    std::vector<int> resp = {4,1,6,5,2,0,3};
    for (int i = 0; (unsigned int) i < result.size(); i++){
        CHECK(result[i] == resp[i]);
    }
    CHECK(ciclo == false);
}

TEST_CASE("DFS_idade"){
    Grafo g = constroi_grafo();
    Grafo TP = transposto(g, 7);
    std::vector<int> idades = {21, 33, 34, 18, 42, 22, 26};

    /* Pessoa mais jovem que comanda I */
    int idade0 = -1;
    DFS(TP, 0, idade0, idades);
    CHECK(idade0 == -1);

    int idade1 = -1;
    DFS(TP, 1, idade1, idades);
    CHECK(idade1 == 21);

    int idade2 = -1;
    DFS(TP, 2, idade2, idades);
    CHECK(idade2 == 21);

    int idade3 = -1;
    DFS(TP, 3, idade3, idades);
    CHECK(idade3 == -1);

    int idade4 = -1;
    DFS(TP, 4, idade4, idades);
    CHECK(idade4 == 21);

    int idade5 = -1;
    DFS(TP, 5, idade5, idades);
    CHECK(idade5 == 18);

    int idade6 = -1;
    DFS(TP, 6, idade6, idades);
    CHECK(idade6 == 18);
}


