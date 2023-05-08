#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#include "item.h"
#include "no.h"

class ArvoreSBB {
    public:
        ArvoreSBB();
        virtual ~ArvoreSBB();
        void insere(Item *reg);
        Item *pesquisa(Item* reg, No* p);
        No* raiz;
    private:
        No* insereAux(Item* reg, No* pai, No* filho, bool filhoEsq);
        No* ee(No*ap);
        No* ed(No*ap);
        No* dd(No*ap);
        No* de(No*ap);
        bool propSBB;
        //void deleteNo(No* p);
};

#endif
