#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <ctime>

int main(int argc, char* argv[]){
    /* Nomes dos arquivos de teste = <nºilhas><orçamento> */
    std::vector<int> num_ilhas;
    for (int i = 5; i <= 500;){
        if (i < 50){
            num_ilhas.push_back(i);
            i += 5;
        }else{
            num_ilhas.push_back(i);
            i += 50;
        }
    }

    std::vector<int> orcamentos;
    for (int i = 5000; i <= 50000;){
        orcamentos.push_back(i);
        i += 5000;
    }
    int seed = time(NULL);
    srand(seed);

    for (int i = 0; i < num_ilhas.size(); i++){
        std::string nome_arq_base = std::to_string(num_ilhas[i]);
        nome_arq_base += "_";
        srand(seed++);
        for (int j = 0; j < orcamentos.size(); j++){
            std::string nome_arq = nome_arq_base;
            nome_arq += std::to_string(orcamentos[j]);
            std::ofstream out;
            out.open("tst/"+nome_arq+".txt", std::ofstream::out);
            out << orcamentos[j] << " " << num_ilhas[i] << std::endl;

            for (int k = 0; k < num_ilhas[i]; k++){
                int preco = 0;
                srand(seed+2*k);
                while (preco == 0){
                    srand(seed++);
                    preco = rand()%100;
                }
                preco = preco*100;

                int pontuacao = 0;
                srand(seed+k*3);
                while (pontuacao == 0){
                    srand(seed++);
                    pontuacao = rand()%100;
                }
                out << preco << " " << pontuacao << std::endl;
            }
            out.close();
        }
    }
    

    return 0;
}
