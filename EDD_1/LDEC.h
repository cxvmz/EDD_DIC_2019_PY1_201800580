#ifndef LDEC_H
#define LDEC_H
#include <iostream>
using namespace std;

template<class T>
class ListaDoblementeEnlazadaC{
    class Nodo{
    public:
        Nodo(T x){
            siguiente=0;
            anterior=0;
            dato = x;
        }

     //METODOS DEL NODO
        Nodo *getSiguiente(){return siguiente;}
        Nodo *getAnterior(){return  anterior;}
        void setSiguiente(Nodo *n){siguiente=n;}
        void setAnterior(Nodo *n){anterior=n;}
        T getDato(){return dato;}
    private:
        Nodo *siguiente;
        Nodo *anterior;
        T dato;
    };
public:
    ListaDoblementeEnlazadaC(){
        primero = 0;
        ultimo=0;
        size=0;
    }

    int getsize(){return  size;}
    void agregar_primero(T dato);
    void agregar_ultimo(T dato);
    void agregar_en(T dato, int index);
    void imprimirLDE();
    T obtener_Elemento_En(int index);

private:
    bool estaVacia(){return size==0;}
    int size;
    Nodo *primero;
    Nodo *ultimo;
};


//Agregar Al inicio
template<class T>
void ListaDoblementeEnlazadaC<T>::agregar_primero(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->estaVacia())
    {
        this->agregar_ultimo(dato);
    }
    else{
        n->setSiguiente(this->primero);
        this->primero->setAnterior(n);
        n->setAnterior(this->ultimo);
        this->ultimo->setSiguiente(n);
        this->primero = n;
        this->size++;
    }
}

//Agregar Al final
template<class T>
void ListaDoblementeEnlazadaC<T>::agregar_ultimo(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->estaVacia())
    {
        this->primero=n;
        this->ultimo =n;
        this->primero->setSiguiente(this->ultimo);
        this->ultimo->setSiguiente(this->primero);
        this->size++;
    }
    else{
        n->setAnterior(this->ultimo);
        this->ultimo->setSiguiente(n);
        n->setAnterior(this->primero);
        this->primero->setSiguiente(n);
        this->ultimo = n;
        this->size++;
    }
}

#endif // LDEC_H
