#ifndef PAGINA_H
#define PAGINA_H

#include <vector>
#include "item.h"
class Pagina {
    public:
        int n;
        std::vector <Item*> r;
        std::vector <Pagina*> p;
        Pagina (int mm) :
            r(mm), p(mm + 1){
            n = 0;
        }
};


#endif