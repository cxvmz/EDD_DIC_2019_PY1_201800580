#ifndef SHUFFLE_H
#define SHUFFLE_H
#include<stdlib.h>
#include<fstream>
#include <iostream>
#include<QDebug>
#include "EDD_1/Objetos/SongsPL.h"
using namespace std;


class SuffleABB
{
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

public:
    SuffleABB(){
        primero = 0;
        ultimo=0;
        size=0; // para que la primera posicion sea 0
    }

    //METODOS DE LA LISTA

    int getsize(){return  size;}
    void agregar_primero(SongPL *dato){
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
    void agregar_ultimo(SongPL *dato){
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
    void agregar_en(SongPL *dato, int index){
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
    void quitar_de(int index){
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
    SongPL *obtener_Elemento_En(int index){
        if(index >=0 && index >size){
            Nodo *temp = this->primero;
            int  recorrido =0;
            while (temp!=0)
            {
                if(index==recorrido){return temp->getDato();}
                temp = temp->getSiguiente();
                recorrido++;
            }
        }else{
            return 0;
        }
        return 0;
    }


    QString graficar(QString asd){
        QString codigoG="";
        codigoG += "digraph Shuffle { \n   node [shape = record]\n graph [nodesep = 1]";
        Nodo *n = this->primero;
        codigoG += " \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" ";
        n=n->getSiguiente();
        while (n!=0) {
            codigoG+=" -> \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" " ;
            n=n->getSiguiente();
        }
        Nodo *repro = this->primero;
        if(asd=="S"){
            reproducirIndex++;
        }else if(asd=="A"){
            reproducirIndex--;
        }
        while (reproducirIndex>-1) {
            if(this->count == this->reproducirIndex){
        codigoG+= " \" " +repro->getDato()->getArtist()+"-"+repro->getDato()->getSong()+" \" ";
        codigoG+="[fillcolor=\"red\", style=\"filled\"];\n";
            }
            count++;
            repro=repro->getSiguiente();
        }
        codigoG+="}";
        this->count=0;
        return  codigoG;
    }

    void generarTxt(QString txt){
        ofstream suffle;
        suffle.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/suffle.txt",ios::out);
        suffle<<txt.toStdString();
        suffle.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/suffle.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/suffle.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/suffle.pdf");
    }

    void ReproducirShuffle(QString x){

                generarTxt(graficar(x));
    }


    void imprimirSuffleABB(){
        Nodo *n = this->primero;
        qDebug()<<" \" " <<n->getDato()->getArtist()<<"-"<<n->getDato()->getSong()<<" \" ";
        n=n->getSiguiente();
        while (n!=0) {
qDebug()<<" \" " <<n->getDato()->getArtist()<<"-"<<n->getDato()->getSong()<<" \" ";            n=n->getSiguiente();
        }
    }
    int reproducirIndex=0;
    bool estaVacia(){return size==0;}
    int size;
            int count = 0;
private:

    Nodo *primero;
    Nodo *ultimo;
};


#endif // SHUFFLE_H
