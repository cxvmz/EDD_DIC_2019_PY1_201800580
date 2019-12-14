#ifndef COLA_H
#define COLA_H
#include <iostream>
using namespace std;

template <class T>
class Cola
{
    class Nodo{
    public:
        Nodo(T x){
            siguiente = 0;
            dato = x;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente = n;}
        T getDato(){return dato;}
    private:
        Nodo *siguiente;
        T dato;
    };
public:
    Cola(){
        inicio = 0;
        fin = 0;
        size =0;
    }

    //Metodos de la Cola

    int getSize(){return size;}
    void encolar(T dato);
    T desencolar();
    T font();
    void mostrarCola();
private:
    Nodo *inicio;
    Nodo *fin;
    int size;
    bool estaVacia(){return  size ==0;}
};


//Encolar al final
template<class T>
void Cola<T>::encolar(T dato){

    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->inicio = n;
        this->fin=n;
        this->size++;
    }
    else
    {
        this->fin->setSiguiente(n);
        this->fin = n;
        this->size++;
    }
}
//Desencolar el inicio de la cola
template<class T>
T Cola<T>::desencolar(){
    if(this->estaVacia()){
        cout << "La cola esta Vacia" << endl;
    }
    else
    {
         Nodo *tem = this->inicio->getSiguiente();
         this->inicio->setSiguiente(0);
         this->inicio = tem;
         this->size--;
    }
}
//Obtener el primer dato de la cola
template <class T>
T Cola<T>::font(){
    if(this->estaVacia()){
        cout << "La cola esta Vacia" << endl;
        return NULL;
    }
    else
    {
         T aux = this->inicio->getDato();
         return aux;
    }
}

template <class T>
void Cola<T>::mostrarCola(){
    Nodo *n = inicio;
    while(n!=0){
        cout << n->getDato() << endl;
        n=n->getSiguiente();
    }
}


#endif // COLA_H
