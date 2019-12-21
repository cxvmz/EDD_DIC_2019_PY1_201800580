#ifndef PILA_H
#define PILA_H
#include <iostream>
#include<stdlib.h>
#include<fstream>
#include"EDD_1/Objetos/SongsPL.h"
#include<windows.h>
using namespace std;

class PilaABB{
    class Nodo{
    public:
        Nodo(SongPL *cancion){
            this->cancion=cancion;
            siguiente = 0;
        }
        Nodo *getSiguiente(){return siguiente;}
        void setSiguiente(Nodo *n){siguiente=n;}
        SongPL *getDato(){return cancion;}
    private:
        Nodo *siguiente;
        SongPL *cancion;
    };
public:

    PilaABB(){
        cabeza =0;
        size = 0;
    }

    void push(SongPL *dato){
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

    void pop(){
        if(this->estaVacia()){
            cout << "La pila esta Vacia" << endl;
        }
        else
        {
            //cout << "Guardado Bien" << endl;
            //SongPL *aux = this->cabeza->getDato();
            Nodo *temp = cabeza;
            this->size--;
            cabeza = cabeza->getSiguiente();
            temp->setSiguiente(0);
            delete temp;
        }
    }


    QString graficar(){
        QString codigoG="";
        codigoG += "digraph Pila { \n";
        if(estaVacia()){
            codigoG = "";
generarTxt("digraph Pila {\" Fin de la reproduccion \" }");        }
        else
        {
            Nodo *n = this->cabeza;
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

    void imprimirEnConsola(){
        Nodo *n = cabeza;
        while (n!=0) {
            cout << n->getDato()->getSong().toStdString()<<endl;
            n=n->getSiguiente();
        }

    }

    void generarTxt(QString txt){
        ofstream cube;
        cube.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/pila.txt",ios::out);
        cube<<txt.toStdString();
        cube.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/pila.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/pila.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/pila.pdf");
    }

    void ReproducirPila(){
        for(int f=this->size;f>-1;f--){
            if(f==0){
    generarTxt("digraph Pila {\" Fin de la reproduccion \" }");        }
            else
            {
                generarTxt(graficar());
                pop();
                Sleep(2000);
            }
        }

    }
    bool estaVacia(){return  size ==0;} // vacio en 0;
     int size;
private:
    Nodo *cabeza;

};



#endif // PILA_H
