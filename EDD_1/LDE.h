#ifndef LDE_H
#define LDE_H

#include <iostream>
using namespace std;


template<class T>
class ListaDoblementeEnlazada
{
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
    ListaDoblementeEnlazada(){
        primero = 0;
        ultimo=0;
        size=0; // para que la primera posicion sea 0
    }

    //METODOS DE LA LISTA

    int getsize(){return  size;}
    void agregar_primero(T dato);
    void agregar_ultimo(T dato);
    void agregar_en(T dato, int index);
    void quitar_de(int index); //Este es el Remove_at pero le quise cambien nombre xd
    void imprimirLDE();
    T obtener_Elemento_En(int index);
private:
    bool estaVacia(){return size==0;}
    int size;
    Nodo *primero;
    Nodo *ultimo;
};

//AMPLIACION DE CADA UNO DE LOS METODOS


//Agregar al inicio
template<class T>
void ListaDoblementeEnlazada<T>::agregar_primero(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->estaVacia())
    {
        this->primero=n;
        this->ultimo =n;
        this->size++;
    }
    else{
        n->setSiguiente(this->primero);
        this->primero->setAnterior(n);
        this->primero = n;
        this->size++;
    }
}

//Agregar al final
template<class T>
void ListaDoblementeEnlazada<T>::agregar_ultimo(T dato)
{
    Nodo *n = new Nodo(dato);
    if(this->estaVacia())
    {
        agregar_primero(dato);
    }
    else{
        n->setAnterior(this->ultimo);
        this->ultimo->setSiguiente(n);
        this->ultimo = n;
        this->size++;
    }
}

//Agregar en cualquier parte de la lista
template<class T>
void ListaDoblementeEnlazada<T>::agregar_en(T dato, int index){
    if(index>=0 && index<=this->size)
    {
        if(index==0){this->agregar_primero(dato);return;}
        if(index==this->size){this->agregar_ultimo(dato);return;}
        Nodo *aux = this->primero;
        int recorrido=0;
        while (aux!=0) {
            if(recorrido==index){break;}
            aux = aux->getSiguiente();
            recorrido++;
        }
        Nodo *n = new Nodo (dato);
        aux->getAnterior()->setSiguiente(n);
        n->setAnterior(aux->getAnterior());
        n->setSiguiente(aux);
        aux->setAnterior(n);
        this->size++;
    }

}

//Obtener elemento en
template<class T>
T ListaDoblementeEnlazada<T>::obtener_Elemento_En(int index){
    if(index >=0 && index >size){
        Nodo *temp = this->primero;
        int  recorrido =0;
        while (temp!=0)
        {
            if(index==recorrido){return temp->getDato();}
            temp = temp->getSiguiente();
            recorrido++;
        }
    }
    return 0;
}


//Eliminar En
template <class T>
void ListaDoblementeEnlazada<T>::quitar_de(int index){

    if(primero!=0){
        if(index>=0 && index<= this->size){
            if(index==0){
                Nodo *aux = this->primero->getSiguiente(); //Obtengo el siguiente del primero
                primero->setSiguiente(0);      // el siguiente de la cabeza actual le digo que le sigue nulo
                primero = aux; //cambio el primero a el nuevo primero
                primero->setAnterior(0); //El anteriro del primero va a ser null
                this->size--;//le quito 1 al tamaño de la lista
            }
            if(index==this->size){
                Nodo *aux = this->ultimo->getAnterior(); //Obtengo el anterior del ultimo
                ultimo->setAnterior(0);      // el anteiror del ultimo actual le digo que le antecede nulo
                ultimo = aux; //cambio el ultimo a el nuevo ultimo
                ultimo->setSiguiente(0); //El siguiente del ultimo va a ser null
                this->size--;//le quito 1 al tamaño de la lista
            }

            if(index >0 && index <this->size){
                Nodo *aux = this->primero;
                int recorrido = 0;
                while (aux!=0) {
                    if(recorrido == index){break;}
                    aux = aux->getSiguiente();
                    recorrido++;
                }

                aux->getAnterior()->setSiguiente(aux->getSiguiente());// Al anterior de mi auxiliar le digo que su siguiente va a ser el siguiente de mi aux
                aux->getSiguiente()->setAnterior(aux->getAnterior());//al siguiente de mi auxiliar le dio que su anterior va a ser en anterro de mi aux
                aux ->setSiguiente(0);//suelta su relacion siguiente para   que "quede en el aire"
                aux ->setAnterior(0); //Suelta su relacion anterior para que "quede en el aire""
                this->size--;//le quito 1 al tamaño de la lista
            }
        }
    }
}


//imprimir
template <class T>
void ListaDoblementeEnlazada<T>::imprimirLDE(){
    Nodo *aux = primero;
    cout << aux->getDato() << endl;
    while (aux!=ultimo) {
        aux = aux->getSiguiente();
        cout << aux->getDato() << endl;
    }
}

#endif // LDE_H
