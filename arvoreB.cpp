#include <vector>
#include <iostream>
#include "arvoreB.h"

ArvoreB::ArvoreB (int tamanho){
    m = tamanho;
    mm = 2*tamanho;
    raiz = NULL;
}
ArvoreB::~ArvoreB (){

}
Item* ArvoreB::pesquisa (Item* reg, Pagina* ap){
    std::cout << "inicio comparação." << std::endl;
    if (ap == NULL) { //registro não encontrado
        std::cout << "Registro não existe." << std::endl;
        return NULL;
    }
    else { //caso registro exista
        int i = 0;
        while((i< ap->n-1) && (reg->compara(ap->r[i])))
            i++;
        if (reg->compara(ap->r[i]) == 0) { //registro foi encontrado
            std::cout << "Registro existe." << std::endl;
            return ap->r[i];
        }
        else if (reg->compara (ap->r[i]) < 0) //registro esta para direita (maior)
            return pesquisa (reg, ap->p[i]);
        else                                  //registro esta para esquerda (menor)
            return pesquisa (reg, ap->p[i+1]);
    }
    return NULL;
}

void ArvoreB::insereNaPagina (Pagina* ap, Item* reg, Pagina* apDir){
    int k = ap->n - 1;
    while ((k >= 0) && (reg->compara(ap->r[k]) < 0)) { //procura a posição para inserir o registro e avança uma posição para frente os registros maiores
        ap->r[k+1] = ap->r[k];
        ap->p[k+2] = ap->p[k+1];
        k--;
    }
    ap->r[k+1] = reg; //insere o registro em k+1 e 
    ap->p[k+2] = apDir;
    ap->n++;
}
void ArvoreB::insere (Item* reg){
    std::vector <Item*> regRetorno (2);
    std::vector <bool> cresceu (2);
    Pagina* apRetorno = this->insere (reg, this->raiz, &regRetorno, &cresceu); //começa a procurar recursivamente o registro a partir da raiz
    if(cresceu[0]) { //se verdadeiro a arvore cresceu e tem q adicoinar uma pagina
        Pagina* apTemp = new Pagina (this->mm);
        apTemp->r[0] = regRetorno[0];
        apTemp->p[0] = this->raiz;
        apTemp->p[1] = apRetorno;
        this->raiz = apTemp;
        this->raiz->n++;
    }
    else
        this->raiz = apRetorno;
}
Pagina* ArvoreB::insere (Item* reg, Pagina* ap, std::vector<Item*>* regRetorno, std::vector<bool>* cresceu){
    //inicia a pagina e os iterators
    Pagina* apRetorno = NULL;
    std::vector<bool>::iterator itBool;
    itBool = cresceu->begin();
    std::vector<Item*>::iterator itItem;
    itItem = regRetorno->begin();

    if(ap == NULL) { //chegou numa pagina vazia e retorna no regRetorno o registroe avisa que a pagina tem que crescer
        cresceu->insert(itBool, true);
        regRetorno->insert(itItem, reg);
    }
    else { //chegou numa pagina existente
        int i = 0;
        while((i < ap->n - 1) && (reg->compara(ap->r[i]) > 0)) //percorre o vetor de registros da pagina vendo se tem um valor menor que o registro
            i++;
        if (reg->compara(ap->r[i]) == 0) { //caso verdadeiro foi achado um registro repetido
            std::cout << "Erro: Registro ja existente" << std::endl;
            itBool = cresceu->begin();
            cresceu->insert(itBool, false);
        }
        else { // caso que o registro não existe na pagina
            if(reg->compara(ap->r[i]) > 0)//se o registro na posição i é menor que o registro avança mais uma posição
                i++;
            apRetorno = insere(reg, ap->p[i], regRetorno, cresceu); //avança recursivamente para proxima pagina ate achar uma vazia ou encontrar o registro
            if(cresceu->at(0)) { //ao voltar recursivamente depois de achar uma pagina vazia inicia essa parte do codigo
                if(ap->n < this->mm){ //nesse caso a pagina pode receber mais um registro
                    this->insereNaPagina(ap, regRetorno->at(0), apRetorno);
                    itBool = cresceu->begin();
                    cresceu->insert(itBool, false);
                    apRetorno = ap;
                }
                else { //caso que a pagina já tem o maximo de registros
                    Pagina* apTemp = new Pagina(this->mm);
                    apTemp->p[0] = NULL;
                    if (i <= this->m) {
                        this->insereNaPagina (apTemp, ap->r[this->mm - 1], ap->p[this->mm]);
                        ap->n--;
                        this->insereNaPagina(ap, regRetorno->at(0), apRetorno);
                    }
                    else {
                        this->insereNaPagina (apTemp, regRetorno->at(0), apRetorno);
                    }
                    
                    for(int j = this->m + 1; j < this->mm; j++) {
                        this->insereNaPagina(apTemp, ap->r[j], ap->p[j+1]);
                        ap->p[j+1] = NULL;
                    }
                    ap->n = this->m;
                    apTemp->p[0] = ap->p[this->m + 1];
                    itItem = regRetorno->begin();
                    regRetorno->insert(itItem, ap->r[this->m]);
                    apRetorno = apTemp;
                }
            }
        }
    }
    return (cresceu->at(0) ? apRetorno : ap);
}
