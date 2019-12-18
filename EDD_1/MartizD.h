#ifndef MARTIZD_H
#define MARTIZD_H
#include <iostream>
#include <qdebug.h>
using namespace std;

template<class T>
class MatrizDispersa{

    class Nodo{
    public:
        Nodo(T F){
            arriba=0;
            abajo=0;
            izquierda=0;
            derecha=0;
            adelante=0;
            atras=0;
            dato =F;
            x = F->getYear();
            y =F->getMonthNumero();

        }
        Nodo *getArriba(){return arriba;}
        void setArriba(Nodo *n){arriba=n;}
        Nodo *getAbajo(){return abajo;}
        void setAbajo(Nodo *n){abajo=n;}
        Nodo *getIzquierda(){return izquierda;}
        void setIzquierda(Nodo *n){izquierda=n;}
        Nodo *getDerecha(){return derecha;}
        void setDerecha(Nodo *n){derecha=n;}
        Nodo *getAdelante(){return adelante;}
        void setAdelante(Nodo *n){adelante=n;}
        Nodo *getAtras(){return atras;}
        void setAtras(Nodo *n){atras=n;}
        T getDato(){return dato;}
        void setDato(T ndato){dato =ndato;}
        int x;
        int y;
    private:
        Nodo *arriba;
        Nodo *abajo;
        Nodo *izquierda;
        Nodo *derecha;
        Nodo *adelante;
        Nodo *atras;
        T dato;
    };

public:
    MatrizDispersa(){
        root=0;
    }
    void agregar(T dato,T x,T y);
    T buscar_fila(int y);
    T buscar_columna(int x);
    void Insertar(int x,int y, T dato);
    T Ordenado_Columna(Nodo *n,Nodo *CabezaColumna);
    T Ordenado_Fila(Nodo *n,Nodo *CabezaFila);
    void Crear_Columna(int x);
    void Crear_Fila(int y);
private:
    Nodo *root;
};


template<class T>
T MatrizDispersa<T>::buscar_fila(int y){
    Nodo *temp = root;
    while (temp!=0) {
        if(temp->y()==y){
            return temp;
        }
        temp=temp->getAbajo();
    }
    return 0;
}
template<class T>
T MatrizDispersa<T>::buscar_columna(int x){
    Nodo *temp = root;
    while (temp!=0) {
        if(temp->x()== x){
            return temp;
        }
        temp=temp->getDerecha();
    }
    return 0;
}


template<class T>
void MatrizDispersa<T>::Insertar(int x,int y, T dato){
    Nodo *nuevo = new Nodo(dato);
    Nodo *columna = buscar_columna(x);
    Nodo *fila = buscar_fila(y);


    //CASO 1:NO EXISTE COLUMA NO EXISTE FILA
    if(columna==0 && fila==0){
        qDebug()<<"Caso1";
        //crearColumna
        //crearFila
        //InsertarDeFormaOdenadaEnColumna
        //InsertarDeFormaOdernadaEnFila
    }
    //CASO2: NO EXISTE COLUMNA SI FILA
    else if(columna==0 && fila!=0){
        qDebug()<<"Caso2";
        //crearColumna
        //InsertarDeFormaOdenadaEnColumna
        //InsertarDeFormaOdernadaEnFila
    }
    //CASO3: SI EXISTE COLUMNA NO FILA
    else if(columna!=0 && fila==0){
        qDebug()<<"Caso3";
        //crearFila
        //InsertarDeFormaOdenadaEnColumna
        //InsertarDeFormaOdernadaEnFila
    }
    //CASO2: SI EXISTE COLUMNA SI FILA
    else if(columna!=0 && fila!=0){
        qDebug()<<"Caso4";
        //InsertarDeFormaOdenadaEnColumna
        //InsertarDeFormaOdernadaEnFila
    }

























}


template<class T>
T MatrizDispersa<T>::Ordenado_Columna(Nodo *nuevo,Nodo *CabezaColumna){
    Nodo *temp = CabezaColumna;
    bool bandera = false;
    while (true) {
        if(temp->x == nuevo->x){
            //si es la misma sobrescribe
            temp->y =nuevo->y;
            temp->setDato(nuevo->getDato());
            return temp;
        }
        else if(temp->x > nuevo->x){
            //insertar antes de temp
            bandera =true;
            break;
        }
        if(temp->getDerecha() != 0){
            temp= temp->getDerecha();
        }
        else{
            //insertar despues de temp
            break;
        }
    }
    if(bandera==true){
        nuevo->setDerecha(temp);
        temp->getIzquierda()->setDerecha(nuevo);
        nuevo->setIzquierda(temp->getIzquierda());
        temp->setIzquierda(nuevo);
    }
    else{
        temp->setDerecha(nuevo);
        nuevo->setIzquierda(temp);
    }
    return nuevo;}
template<class T>
T MatrizDispersa<T>::Ordenado_Fila(Nodo *nuevo,Nodo *CabezaFila){
    Nodo *temp = CabezaFila;
    bool bandera = false;
    while (true) {
        if(temp->y == nuevo->y){
            //si es la misma sobrescribe
            temp->x =nuevo->x;
            temp->setDato(nuevo->getDato());
            return temp;
        }
        else if(temp->y > nuevo->y){
            //insertar antes de temp
            bandera =true;
            break;
        }
        if(temp->getDerecha() != 0){
            temp= temp->getAbajo();
        }
        else{
            //insertar despues de temp
            break;
        }
    }
    if(bandera==true){
        nuevo->setAbajo(temp);
        temp->getArriba()->setAbajo(nuevo);
        nuevo->setArriba(temp->getArriba());
        temp->setArriba(nuevo);
    }
    else{
        temp->setAbajo(nuevo);
        nuevo->setArriba(temp);
    }
    return nuevo;
}

template <class T>
void MatrizDispersa<T>::Crear_Columna(int x){
    Nodo *cabezaColumna = root;
    Nodo *nodoColumna = new Nodo();
    Nodo *columa = Ordenado_Columna();
}

#endif // MARTIZD_H
