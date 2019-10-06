#include <fstream>
#include <chrono>
#include <cmath>
#include <bits/stdc++.h> 
#include "operacoes.h"
#include "DFS.h"

#define N_TESTES 30

/* Inicializa o grafo, lendo as entradas do arquivo */
void inicializacao(Grafo& grafo, std::ifstream& arq, std::vector<int>& idades, int& N, int& Instr){
    /* Parâmetros da primeira linha */
    std::string Linha;
    std::getline(arq,Linha);
    std::string aux;
    str_tok(Linha," ",aux);
    N = std::stoi(aux);
    str_tok(Linha," ",aux);
    int Arestas = std::stoi(aux);
    str_tok(Linha," ",aux);
    Instr = std::stoi(aux);

    
    /* Vetor de idades e inicialização do grafo (lista de adjacências) */
    std::getline(arq,Linha);
    for (int i = 0; i < N; i++){
        str_tok(Linha," ",aux);
        idades.push_back(std::stoi(aux));
        std::vector<int> n1;
        grafo.push_back(n1);
    }
    
    /* Cria as arestas: X comanda Y, lembrando que no programa os índices dos 
    integrantes começam no 0 e no arquivo de entrada começam de 1*/
    for (int i = 0; i < Arestas; i++){
        std::getline(arq,Linha);
        str_tok(Linha," ",aux);
        int X = std::stoi(aux) - 1;
        str_tok(Linha," ",aux);
        int Y = std::stoi(aux) - 1;
        grafo[X].push_back(Y);
    }
}

double media(int tempos[]){
    double soma = 0;
    for (int i = 0; i < N_TESTES; i++){
        soma += tempos[i];
    }
    return soma/N_TESTES;
}

double mediana(int tempos[]){
    std::sort(tempos, tempos+N_TESTES);
    if (N_TESTES % 2 != 0) 
       return (double)tempos[N_TESTES/2]; 
      
    return (double)(tempos[(N_TESTES-1)/2] + tempos[N_TESTES/2])/2.0; 
}

double dev(int tempos[], double med){
    double soma = 0;
    for (int i = 0; i < N_TESTES; i++){
        soma += pow((tempos[i]-med),2);
    }
    double var = soma/(N_TESTES-1);
    return sqrt(var);
}

int main(int argc, char* argv[]){
    /* Coleta o argumento: nome do arquivo a ser lido e abre o arquivo*/
    if (argc != 2){std::cout << "Argumento faltando"; exit(1);}
    std::string nome_arq = argv[1];
    std::ifstream arq;

    /* Execução do programa: leitura e processamento */
    std::chrono::duration<double> tempos[N_TESTES];
    
    int N;
    int Instr;
    
    int tempos_int[N_TESTES];
    for (int i = 0; i < N_TESTES; i++){
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

        arq.open(nome_arq, std::ios::in);
        Grafo grafo;
        std::vector<int> idades;
        inicializacao(grafo, arq, idades, N, Instr);
        /* Leitura das instruções e execução de cada uma delas */
        std::string Linha;
        for (int i = 0; i < Instr; i++){
            std::getline(arq,Linha);
            if (Linha[0] == 'C') Commander(Linha, grafo, N, idades);
            if (Linha[0] == 'M') Meeting(grafo);
            if (Linha[0] == 'S') Swap(Linha, grafo);
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        tempos[i] = elapsed_time;
        arq.close();
    }
    
    /* Finalização e tomada de testes */
    
    std::ofstream out;
    out.open("tempo/tempos.txt", std::ofstream::out | std::ofstream::app);
    for (int i = 0; i < N_TESTES; i++){
        double x = tempos[i].count();
        x = x*pow(10,6);
        int y = (int) x;
        tempos_int[i] = y;
    }
    double med = media(tempos_int);
    double st = dev(tempos_int,med);
    double md = mediana(tempos_int);
    out << nome_arq << " N:" << N << " I:" << Instr << " Média:" << med << " STD:" << st << " Mediana:" << md << std::endl;
    return 0;
}