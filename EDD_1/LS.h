#ifndef LS_H
#define LS_H
#include <QDebug>
#include "EDD_1/Objetos/Song.h"
template <class T>
class ListaSimple{
    class Nodo{
    public:
        Nodo(Song *x){
            siguiente = 0;
            dato = x;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente=n;}
        Song *getDato(){return dato;}
    private:
        Nodo *siguiente;
        Song* dato;
    };
public:
    ListaSimple(){
        primero=0;
        ultimo=0;
        size=0;
    }
    int getSize(){return size;}
    void agregarFinal(Song *dato);
    void imprimirLS();
private:
    bool estaVacia(){return size==0;}
    int size;
    Nodo *primero;
    Nodo *ultimo;
};

template <class T>
void ListaSimple<T>::agregarFinal(Song * dato){
    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->primero=n;
        this->ultimo =n;
        this->size++;
    }
    else
    {
        this->ultimo->setSiguiente(n);
        this->ultimo=n;
        this->size++;
    }
}


template <class T>
void ListaSimple<T>::imprimirLS(){
    Nodo *aux =primero;
    qDebug()<< aux->getDato()->getName();
    while (aux!=0) {
        if(aux->getSiguiente()==0){
            qDebug()<<"Fin de lista canciones";
            break;
        }
        aux = aux->getSiguiente();
        qDebug()<< aux->getDato()->getName();
    }

}
#endif // LS_H
