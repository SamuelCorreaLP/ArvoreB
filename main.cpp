#include <iostream>
#include <cstdlib>

#include "arvoreB.h"
#include "arvoreSBB.h"
#include "item.h"

int main(int argc, char* argv[]) {
    Item* reg;

    ArvoreSBB arvSBB;
    std :: cout << "-- ArvoreSBB --" << std::endl << std::endl;

    for(int i = 10000; i <= 100000; i = i + 10000){
        reg = new Item(i);
        arvSBB.insere(reg);

        reg = new Item(101000);
        arvSBB.pesquisa(reg, arvSBB.raiz);

        std :: cout << "i = " << i/10000 << std::endl << std::endl;
    }

    std :: cout  << std::endl;

    ArvoreB arv1 (2);
    std :: cout << "-- ArvoreB ordem 2 --" << std::endl << std::endl;

    for(int i = 10000; i <= 100000; i = i + 10000){
        reg = new Item(i);
        arv1.insere(reg);

        reg = new Item(101000);

        arv1.pesquisa(reg, arv1.raiz);

        std :: cout << "i = " << i/10000 << std::endl << std::endl;
    }

    std :: cout  << std::endl;

    ArvoreB arv2 (4);
    std :: cout << "-- ArvoreB ordem 4 --" << std::endl << std::endl;
    for(int i = 10000; i <= 100000; i = i + 10000){
        reg = new Item(i);
        arv2.insere(reg);

        reg = new Item(101000);

        arv2.pesquisa(reg, arv2.raiz);

        std :: cout << "i = " << i/10000 << std::endl << std::endl;
    }

    std :: cout  << std::endl;

    ArvoreB arv3 (6);
    std :: cout << "-- ArvoreB ordem 6 --" << std::endl << std::endl;
    for(int i = 10000; i <= 100000; i = i + 10000){
        reg = new Item(i);
        arv3.insere(reg);

        reg = new Item(101000);

        arv3.pesquisa(reg, arv3.raiz);

        std :: cout << "i = " << i/10000 << std::endl << std::endl;
    }

    return 0;
}