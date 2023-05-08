#ifndef ITEM_H
#define ITEM_H

class Item {
    public:
        Item(int chave);
        virtual ~Item();
        int compara(Item* it);
        int getChave();
    private:
        int m_chave;
};

#endif
