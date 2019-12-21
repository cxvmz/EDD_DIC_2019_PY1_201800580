#ifndef COLA_H
#define COLA_H
#include <iostream>
#include"EDD_1/Objetos/SongsPL.h"
#include<windows.h>
#include<fstream>
#include<stdlib.h>


using namespace std;

class ColaABB{
public:

    ColaABB(){
size=0;
inicio=0;
fin=0;
    }
    class Nodo{
    public:
        Nodo(SongPL *x){
            siguiente = 0;
            dato = x;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente = n;}
        SongPL *getDato(){return dato;}
    private:
        Nodo *siguiente;
        SongPL *dato;
    };

    int getSize(){return size;}
    void encolar(SongPL *dato){
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

    void desencolar(){
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

    void mostrarCola(){
        Nodo *n = inicio;
        while(n!=0){
            cout << n->getDato() << endl;
            n=n->getSiguiente();
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
            Nodo *n=inicio;
            codigoG+= " \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \"" ;
            codigoG+="[fillcolor=\"red\", style=\"filled\"];\n";
            codigoG+= " \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" " ;
            n=n->getSiguiente();
            while(n!=0){
                codigoG+=" -> \" " +n->getDato()->getArtist()+"-"+n->getDato()->getSong()+" \" " ;
                n=n->getSiguiente();
            }
            codigoG+="}";
        }
        return  codigoG;
    }

    void generarTxt(QString txt){
        ofstream ColaABB;
        ColaABB.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/colaABB.txt",ios::out);
        ColaABB<<txt.toStdString();
        ColaABB.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/colaABB.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/colaABB.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/colaABB.pdf");
    }


    void ReproducirCola(){
        for(int f=this->size;f>-1;f--){
            if(f==0){
    generarTxt("digraph Pila {\" Fin de la reproduccion \" }");        }
            else
            {
                generarTxt(graficar());
                desencolar();
                Sleep(3000);
            }
        }

    }
    int size;
    bool estaVacia(){return  size ==0;}

private:
    Nodo *inicio;
    Nodo *fin;

};




#endif // COLA_H
