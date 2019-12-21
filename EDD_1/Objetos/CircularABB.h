#ifndef CIRCULAR_H
#define CIRCULAR_H
#include<stdlib.h>
#include<fstream>
#include<QDebug>
#include "EDD_1/Objetos/SongsPL.h"
#include <iostream>
using namespace std;

class CircularABB{
public:
    class Nodo{

    public:
        Nodo(SongPL *x){
            siguiente=0;
            anterior=0;
            dato = x;
        }
     //METODOS DEL NODO
        Nodo *getSiguiente(){return siguiente;}
        Nodo *getAnterior(){return  anterior;}
        void setSiguiente(Nodo *n){siguiente=n;}
        void setAnterior(Nodo *n){anterior=n;}
        SongPL *getDato(){return dato;}
        void setDato(SongPL *value){dato = value;}

    private:
        Nodo *siguiente;
        Nodo *anterior;
        SongPL *dato;
    };

    CircularABB(){
        primero = 0;
        ultimo=0;
        size=0;
    }


    void agregar_ultimo(SongPL *dato)
    {
        Nodo *n = new Nodo(dato);
        if(this->estaVacia())
        {
            this->primero=n;
            this->ultimo =n;
            this->size++;
        }
        else{
            n->setAnterior(this->ultimo);
            this->ultimo->setSiguiente(n);
            this->ultimo = n;
            this->size++;
        }
    }


    QString graficar(QString asd){
        QString codigoG="";
        codigoG += "digraph Pila { \n   node [shape = record]\n graph [nodesep = 1]\n";
        Nodo *n = this->primero;
        codigoG += " \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" ";
        n=n->getSiguiente();
        while (n!=0) {
            codigoG+=" -> \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" " ;
            n=n->getSiguiente();
        }
        codigoG+="\n [dir=both];";

        Nodo *repro = primero;
        if(asd=="S"){
            reproducirIndex++;
        }else if(asd=="A"){
            reproducirIndex--;
        }
        int count = 0;

        while (repro!=0 && reproducirIndex > 0) {
            if(count == reproducirIndex){
                codigoG+= " \" " +repro->getDato()->getArtist()+"-"+repro->getDato()->getSong()+" \" ";
                codigoG+="[fillcolor=\"red\", style=\"filled\"];\n";
            }
            count++;
            repro=repro->getSiguiente();
        }



        Nodo *p= this->primero;
        Nodo *u = this->ultimo;
        codigoG+= " \" " +p->getDato()->getArtist()+"-"+p->getDato()->getSong()+" \" ->"+" \" " +u->getDato()->getArtist()+"-"+u->getDato()->getSong()+" \" " ;
        codigoG+="}";
        return  codigoG;
    }

    void imprimirCiccukarABB(){
        Nodo *n = primero;
        while (n!=0) {
            qDebug()<<"F"<<n->getDato()->getSong();
            n=n->getSiguiente();
        }
    }

    void generarTxt(QString txt){
        ofstream circular;
        circular.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/circular.txt",ios::out);
        circular<<txt.toStdString();
        circular.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/circular.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/circular.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/circular.pdf");
    }
    bool estaVacia(){return size==0;}
    int size;
    int reproducirIndex =0;
private:

    Nodo *primero;
    Nodo *ultimo;

};

#endif // CIRCULAR_H
