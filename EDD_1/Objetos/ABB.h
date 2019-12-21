#ifndef ABB_H
#define ABB_H
#include "Playlist.h"
#include<QDebug>
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
            qDebug()<<tmp->pl->nombre << "  ";
            enorden(tmp->der);
        }
    }

    void pre(NodoABB* tmp)
    {
        if (tmp!=0)
        {
            qDebug()<<tmp->pl->nombre << "  ";
            pre(tmp->izq);
            pre(tmp->der);
        }
    }
    void post(NodoABB* tmp)
    {
        if (tmp!=0)
        {
            post(tmp->izq);
            post(tmp->der);
            qDebug()<<tmp->pl->nombre << "  ";
        }
    }
    NodoABB*raiz;


};

#endif // ABB_H
