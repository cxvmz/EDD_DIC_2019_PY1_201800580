#ifndef LS_H
#define LS_H
#include <QDebug>
#include<fstream>
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

    void elementat(int x){
        Nodo *aux =primero;
        int cout =0;
        while (aux!=0) {
            if(cout == x){
                qDebug()<<"Reproduciendo"<< aux->getDato()->getName();
            }
                            aux = aux->getSiguiente();
                            cout++;
        }
    }

    QString graficar(){
        QString codigoG="";
        codigoG += "digraph Pila { \n";
        if(estaVacia()){
            codigoG = "";
           generarTxt("digraph Pila {\" Fin de la reproduccion \" }");
        }
        else{
            Nodo *n=primero;
            codigoG+= " \" "+n->getDato()->getName()+" \" " ;
            n=n->getSiguiente();
            while(n!=0){
                codigoG+=" -> \" "+n->getDato()->getName()+" \" " ;
                n=n->getSiguiente();
            }
            codigoG+="}";
        }
        return  codigoG;
    }

    void generarTxt(QString txt){
        ofstream ColaABB;
        ColaABB.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Albumreport.txt",ios::out);
        ColaABB<<txt.toStdString();
        ColaABB.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Albumreport.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Albumreport.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Albumreport.pdf");
    }
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
    int asd=1;
    Nodo *aux =primero;
    qDebug()<< "0." <<aux->getDato()->getName();
    while (aux!=0) {
        if(aux->getSiguiente()==0){
            qDebug()<<"Fin de lista canciones";
            break;
        }
        aux = aux->getSiguiente();
        qDebug()<<asd<<". "<< aux->getDato()->getName();
        asd++;
    }


}
#endif // LS_H
