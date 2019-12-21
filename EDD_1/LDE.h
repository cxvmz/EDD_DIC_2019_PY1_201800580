#ifndef LDE_H
#define LDE_H

#include <iostream>
#include "EDD_1/Objetos/Artist.h"
using namespace std;


class ListaDoblementeEnlazada
{
    class Nodo{

    public:
        Nodo(Artist *x){
            siguiente=0;
            anterior=0;
            dato = x;
        }
     //METODOS DEL NODO
        Nodo *getSiguiente(){return siguiente;}
        Nodo *getAnterior(){return  anterior;}
        void setSiguiente(Nodo *n){siguiente=n;}
        void setAnterior(Nodo *n){anterior=n;}
        Artist *getDato(){return dato;}
        void setDato(Artist *value){dato = value;}

    private:
        Nodo *siguiente;
        Nodo *anterior;
        Artist *dato;
    };

public:
    ListaDoblementeEnlazada(){
        primero = 0;
        ultimo=0;
        size=0; // para que la primera posicion sea 0
    }

    //METODOS DE LA LISTA

    int getsize(){return  size;}
    void agregar_primero(Artist *dato){
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
    void agregar_ultimo(Artist *dato){
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
    void agregar_en(Artist *dato, int index){
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
    } //Este es el Remove_at pero le quise cambien nombre xd
    void imprimirLDE(){
        int numero = 1;
        Nodo *aux = primero;
        qDebug()<<numero<<"  " <<aux->getDato()->getName();
        while (aux!=ultimo) {
            aux = aux->getSiguiente();
            numero ++;
            qDebug()<<numero<<"  " <<aux->getDato()->getName();
        }
    }
    Artist obtener_Elemento_En(int index){if(index >=0 && index <size){
            Nodo *temp = this->primero;
            int  recorrido =0;
            while (temp!=0)
            {
                if(index==recorrido){return *temp->getDato();}
                temp = temp->getSiguiente();
                recorrido++;
            }
        }
                                         }
    void OrdenarLDE_A_Z(){
        Nodo *aux1,*aux2;
        aux1=this->primero;
        Artist *temporal;
        while (aux1->getSiguiente()!=0) {
            aux2=aux1->getSiguiente();
            while (aux2!=0) {
                if(aux2->getDato()->getName() < aux1->getDato()->getName()){
                    temporal = aux1->getDato();
                    aux1->setDato(aux2->getDato());
                    aux2->setDato(temporal);
                }
                aux2=aux2->getSiguiente();
            }
            aux1=aux1->getSiguiente();
        }
    }

    void OrdenarLDE_MA_ME(){
        Nodo *aux1,*aux2;
        aux1=this->primero;
        Artist *temporal;
        while (aux1->getSiguiente()!=0) {
            aux2=aux1->getSiguiente();
            while (aux2!=0) {
                if(aux2->getDato()->getRating() > aux1->getDato()->getRating()){
                    temporal = aux1->getDato();
                    aux1->setDato(aux2->getDato());
                    aux2->setDato(temporal);
                }
                aux2=aux2->getSiguiente();
            }
            aux1=aux1->getSiguiente();
        }
    }


    QString graficarRating(){
        QString codigoG="";
        codigoG += "digraph Pila { \n   node [shape = record]\n graph [nodesep = 1]";
        Nodo *n = this->primero;
        codigoG += " \" " +n->getDato()->getName()+" \" ";
        n=n->getSiguiente();
        try {
            for(int i=0;i<5;i++){
                codigoG+=" -> \" " +n->getDato()->getName()+" \" " ;
                n=n->getSiguiente();
            }
        } catch(int i) {
            qDebug()<<"F F F"<<i;
        }

        codigoG+="}";
        return  codigoG;
    }


    QString graficar(){
        QString codigoG="";
        codigoG += "digraph LDA { \n   node [shape = record]\n graph [nodesep = 1]";
        Nodo *n = this->primero;
        codigoG += " \" " +n->getDato()->getName()+" \" ";
        n=n->getSiguiente();
        while (n!=0) {
            codigoG+=" -> \" " +n->getDato()->getName()+" \" " ;
            n=n->getSiguiente();
        }
        codigoG+="[dir=both];";
        codigoG+="}";
        return  codigoG;
    }
    void generarTxt(QString txt){
        ofstream suffle;
        suffle.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/LDA.txt",ios::out);
        suffle<<txt.toStdString();
        suffle.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/LDA.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/LDA.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/LDA.pdf");
    }




private:
    bool estaVacia(){return size==0;}
    int size;
    Nodo *primero;
    Nodo *ultimo;
};


#endif // LDE_H

