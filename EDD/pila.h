#ifndef PILA_H
#define PILA_H
#include <iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;

template <class T>
class Pila
{
    class Nodo{
    public:
        Nodo(T x){
            siguiente =0; // siguiente null
            dato = x;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente=n;}
        T getDato(){return dato;}
    private:
        Nodo *siguiente;
        T dato;
    };


public:
    Pila<T>(){
        cabeza =0; // la cabeza de la pila sera null
        size=0;
    }

    //Metodos de la Pila
    int getSize(){return size;}
    void push(T dato);
    T pop();
    T peek();
    void mostarPila();
    string graficar();
    void generarTxt(string txt);
private:
    Nodo *cabeza;
    int size;
    bool estaVacia(){return  size ==0;} // vacio en 0;
};


//agregar al final
template <class T>
void Pila<T>::push(T dato){
    Nodo *n = new Nodo(dato);
    if(this->estaVacia()){
        this->cabeza=n;
        this->size++;
    }
    else
    {
        n->setSiguiente(this->cabeza);
        this->cabeza=n;
        this->size++;
    }
}
//Eliminar y devolver el eliminado
template <class T>
T Pila<T>::pop(){
    if(this->estaVacia()){
        cout << "La pila esta Vacia" << endl;
        return 0;
    }
    else
    {

        cout << "Guardado Bien" << endl;
        T aux = this->cabeza->getDato();
        Nodo *temp = cabeza;
        cabeza = cabeza->getSiguiente();
        temp->setSiguiente(0);
        delete temp;
        return aux;
    }
}
// ver la cabeza de la pila
template <class T>
T Pila<T>::peek(){
    if(this->estaVacia()){
        cout << "La pila esta Vacia" << endl;
        return 0;
    }
    else
    {
        T aux = this->cabeza->getDato();
        return aux;
    }
}

// ver la pila
template <class T>
void Pila<T>::mostarPila(){
    Nodo *n = cabeza;
    while(n!=0){
        cout << n->getDato() << endl;
        n=n->getSiguiente();
    }
}

//mostrar Pila
template <class T>
string  Pila<T>::graficar(){
    string codigoG="";
    codigoG += "digraph Pila { \n";
    if(this->estaVacia()){
        cout << "La Pila esta vacia" << endl;
    }
    else
    {
        Nodo *n = cabeza;
        codigoG+= to_string( n->getDato())+ "->"+to_string( n->getSiguiente()->getDato()) +";\n";
        codigoG+= to_string( n->getDato())+"[fillcolor=\"lightblue\", style=\"filled\"];\n";
        n=n->getSiguiente();
        while(n->getSiguiente()!=0){
            codigoG+= to_string( n->getDato()) + "->"+to_string( n->getSiguiente()->getDato()) +";\n";
            n=n->getSiguiente();
        }
        codigoG+="}";
    }
    return  codigoG;
}
template <class T>
void  Pila<T>::generarTxt(string txt){
    ofstream pila;
    pila.open("C:/Users/Christian/Documents/build-EDD_Proyecto1-Desktop_Qt_5_12_6_MinGW_32_bit-Debug/pila.txt",ios::out);
    pila<<txt;
    pila.close();
    cout << "Wena se guardo" << endl;
    string cmd= "dot -Tpng Pila.txt -o pila.png";
    system(cmd.c_str());
    ofstream imgPila;
    imgPila.open("C:/Users/Christian/Documents/build-EDD_Proyecto1-Desktop_Qt_5_12_6_MinGW_32_bit-Debug/pila.png",ios::out);
}





#endif // PILA_H
