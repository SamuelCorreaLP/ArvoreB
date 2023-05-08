#ifndef NO_H
#define NO_H

#include "item.h"

class No {
    public:
        enum inc {
            HORIZONTAL = 0,
            VERTICAL = 1
        };

        No(Item *item) 
            : m_reg(item) {
                esq = NULL;
                dir = NULL;
        }
        virtual ~No() {
            //delete m_reg;
            //delete esq;
            //delete dir;
        }
        Item* getItem() {return m_reg;}
        No* getEsq() {return esq;}
        No* getDir() {return dir;}
        inc getIncE() {return incE;}
        inc getIncD() {return incD;}
        void setEsq (No* no) {this->esq = no;}
        void setDir (No* no) {this->dir = no;}
        void setIncE (inc inc) {this->incE = inc;}
        void setIncD (inc inc) {this->incD = inc;}
    private:
        Item *m_reg;
        No *esq, *dir;
        enum inc incE, incD;
};

#endif
