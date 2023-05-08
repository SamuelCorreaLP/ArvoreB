#ifndef ARVOREB_H
#define ARVOREB_H

#include "item.h"
#include "pagina.h"
#include <vector>

class ArvoreB {
    private:
        void insereNaPagina (Pagina* ap, Item* reg, Pagina* apDir);
        Pagina* insere (Item* reg, Pagina* ap, std::vector<Item*>* regRetorno, std::vector<bool>* cresceu);
        int m,mm;
    public:
        ArvoreB (int tamanho);
        ~ArvoreB ();
        Item* pesquisa (Item* reg, Pagina* ap);
        void insere (Item* reg);
        Pagina* raiz;
};

#endif