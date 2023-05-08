#include "item.h"

Item::Item(int chave) 
    : m_chave(chave) {
}

Item::~Item () {
}

int Item::compara(Item* it) {
    Item* item = it;
    if (item->m_chave > this->m_chave)
        return -1;
    else if(item->m_chave < this->m_chave)
        return 1;
    return 0;
}

int Item::getChave() {
    return m_chave;
}
