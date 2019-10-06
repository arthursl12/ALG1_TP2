#ifndef ILHA_H
#define ILHA_H

typedef struct ilha{
    int custo;
    int valor;
    double cdv;

    bool operator<(const ilha outra){
        return valor < outra.valor;
    }
} ilha;


#endif /* ILHA_H */