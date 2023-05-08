// -- Trabalho de AED2 - Arvore Binaria SBB --
// Aluno : Samuel Correa Lucas Pereira

#include <iostream>
#include <cstdlib>
#include "arvoreSBB.h"

ArvoreSBB::ArvoreSBB() {
    raiz = NULL;
    propSBB = true;
}
ArvoreSBB::~ArvoreSBB() {
    //deleteNo(raiz);
}

//void ArvoreBinaria::deleteNo(No* p) {
    /*if(p->getEsq() != NULL) {
        deleteNo(p->getEsq());
    } 
    if(p->getDir() != NULL) {
        deleteNo(p->getDir());
    }
    delete p;*/
//}

No* ArvoreSBB::ee(No*ap) {
    No* ap1 = ap->getEsq();
    ap->setEsq(ap1->getDir());
    ap1->setDir(ap);
    ap1->setIncE(No::VERTICAL);
    ap->setIncE(No::VERTICAL);
    ap = ap1;
    return ap;
}
No* ArvoreSBB::ed(No*ap) {
    No* ap1 = ap->getEsq();
    No* ap2 = ap1->getDir();
    ap1->setIncD(No::VERTICAL);
    ap->setIncE(No::VERTICAL);
    ap1->setDir(ap2->getEsq());
    ap2->setEsq(ap1);
    ap->setEsq(ap2->getDir());
    ap2->setDir(ap);
    ap = ap2;
    return ap;
}
No* ArvoreSBB::dd(No*ap) {
    No* ap1 = ap->getDir();
    ap->setDir(ap1->getEsq());
    ap1->setEsq(ap);
    ap1->setIncE(No::VERTICAL);
    ap->setIncE(No::VERTICAL);
    ap = ap1;
    return ap;
}
No* ArvoreSBB::de(No*ap) {
    No* ap1 = ap->getDir();
    No* ap2 = ap1->getEsq();
    ap1->setIncE(No::VERTICAL);
    ap->setIncD(No::VERTICAL);
    ap1->setEsq(ap2->getDir());
    ap2->setDir(ap1);
    ap->setDir(ap2->getEsq());
    ap2->setEsq(ap);
    ap = ap2;
    return ap;
}

void ArvoreSBB::insere(Item *reg) {
    if(raiz == NULL) {                          //se raiz estiver vazia, o item vai para raiz
        raiz = new No(reg);
        raiz->setIncE(No::VERTICAL);
        raiz->setIncD(No::VERTICAL);
    } else {                                    //caso contrario
        switch (raiz->getItem()->compara(reg))  //compara-se reg com a raiz para saber se o valor vai para esq ou dir
        {
        case -1:                                //valor vai para dir
            raiz->setEsq(insereAux(reg, raiz, raiz->getDir(), false));
            break;
        case 1:                                 //valor vai para esq
            raiz->setDir(insereAux(reg, raiz, raiz->getEsq(), true));
            break;
        }
    }
}
No* ArvoreSBB::insereAux(Item* reg, No* pai, No* filho, bool filhoEsq) {
    if(filho == NULL){                             //caso que o filho é NULL e o reg é inserido
        filho = new No(reg);
        filho->setIncE(No::VERTICAL);
        filho->setIncD(No::VERTICAL);
        if(pai != NULL)
            if(filhoEsq)
                pai->setIncE(No::HORIZONTAL);
            else
                pai->setIncD(No::HORIZONTAL);
        this->propSBB = false;
    } else if(filho->getItem()->compara(reg) > 0){ //avanço para arvore esquerda
        filho->setEsq(insereAux(reg, filho, filho->getEsq(), true));
        if(!this->propSBB)                         //condição para fazer balanceamento da arvore
            if(filho->getIncE() == No::HORIZONTAL){
                if(filho->getEsq()->getIncE() == No::HORIZONTAL){
                    filho = ee(filho);             //transformação esquerda-esquerda
                    if(pai != NULL)
                        if(filhoEsq)
                            pai->setIncE(No::HORIZONTAL);
                        else
                            pai->setIncD(No::HORIZONTAL);
                }
                else if(filho->getEsq()->getIncD() == No::HORIZONTAL){
                    filho = ed(filho);             //transformação esquerda-direita
                    if(pai != NULL)
                        if(filhoEsq)
                            pai->setIncE(No::HORIZONTAL);
                        else
                            pai->setIncD(No::HORIZONTAL);
                }
            } 
            else this->propSBB = true;
    } else if(filho->getItem()->compara(reg) < 0){ //avanço para arvore direita
        filho->setDir(insereAux(reg, filho, filho->getDir(), false));
        if(!this->propSBB)                         //condição para fazer balanceamento da arvore
            if(filho->getIncD() == No::HORIZONTAL) {
                if(filho->getDir()->getIncD() == No::HORIZONTAL) {
                    filho = dd(filho);             //transformação direita-direita
                    if(pai != NULL)
                        if(filhoEsq)
                            pai->setIncE(No::HORIZONTAL);
                        else
                            pai->setIncD(No::HORIZONTAL);
                }
                else if(filho->getDir()->getIncE() == No::HORIZONTAL) {
                    filho = de(filho);              //transformação direita-esquerda
                    if(pai != NULL)
                        if(filhoEsq)
                            pai->setIncE(No::HORIZONTAL);
                        else
                            pai->setIncD(No::HORIZONTAL);
                }
            }
            else this->propSBB = true;
    } else {                                        //o registro já existe na arvore
        std::cout << "Erro: Registro ja existente" << std::endl;
        this->propSBB = true;
    }
    return filho;
}

Item* ArvoreSBB::pesquisa(Item *reg, No *p) {
    std::cout << "inicio comparação" << std::endl;
    switch (p->getItem()->compara(reg)) {
    case -1:                                  //reg é maior que p, logo a pesquisa tem que avançar para direita
        if(p->getEsq() == NULL) {             //Nesse caso reg não existe na arvore
            std::cout << "Erro: Falha na pesquisa" << std::endl;
            return NULL;
        } else {                              //função avança recursivamente para direita
            pesquisa(reg, p->getEsq());
        }
        break;
    case 0:                                   //reg é igual a p, a pesquisa foi um sucesso e retorna o item do nó p
        std::cout << "Pesquisa com sucesso" << std::endl;
        return p->getItem();
        break;
    case 1:                                   //reg é menor que p, logo a pesquisa tem que avançar para esquerda
        if(p->getDir() == NULL) {             //Nesse caso reg não existe na arvore
            std::cout << "Erro: Falha na pesquisa" << std::endl;
            return NULL;
        } else {                              //função avança recursivamente para esquerda
            pesquisa(reg, p->getDir());
        }
        break;
    }
    return raiz->getItem();
}