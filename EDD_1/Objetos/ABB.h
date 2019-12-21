#ifndef ABB_H
#define ABB_H
#include "Playlist.h"
class NodoABB
{
public:
    NodoABB (Playlist *pls){
        this->pl=pls;
    }
    Playlist *pl;
    NodoABB* izq;
    NodoABB* der;
private:

};

class ABB{
public:
    ABB(){
        raiz=0;
    }

    void agregar(Playlist *pls){
        if(raiz!=0){
            agregar(pls,raiz);
        }else{
            raiz = new NodoABB(pls);
        }
    }

    void agregar(Playlist *pls, NodoABB* tmp){
        if (pls<tmp->pl)
        {
            if (tmp->izq!=0) agregar(pls, tmp->izq);
            else tmp->izq = new NodoABB(pls);
        }
        else
        {
            if (tmp->der!=0) agregar(pls, tmp->der);
            else tmp->der = new NodoABB(pls);
        }
    }
    void enorden(NodoABB* tmp)
    {
        if (tmp!=0)
        {
            enorden(tmp->izq);
            std::cout << tmp->val << " ";
            enorden(tmp->der);
        }
    }


private:
    NodoABB*raiz;

};

#endif // ABB_H
