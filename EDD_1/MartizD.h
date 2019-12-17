#ifndef MARTIZD_H
#define MARTIZD_H
#include <iostream>
using namespace std;

template<class T>
class MatrizDispersa{

    class Nodo{
    public:
        Nodo(T x){
            arriba=0;
            abajo=0;
            izquierda=0;
            derecha=0;
            adelante=0;
            atras=0;
            dato =x;
        }

    private:
        Nodo *arriba;
        Nodo *abajo;
        Nodo *izquierda;
        Nodo *derecha;
        Nodo *adelante;
        Nodo *atras;
        T dato;
    };
};

#endif // MARTIZD_H
