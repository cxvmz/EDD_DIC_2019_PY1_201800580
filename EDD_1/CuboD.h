#ifndef CUBOD_H
#define CUBOD_H
#include "EDD_1/Objetos/Album.h"
#include "EDD_1/LDE.h"
#include <iostream>
#include <qdebug.h>
using namespace std;


class Nodo{
public:
    Nodo(Album *dato){
        arriba=0;
        abajo=0;
        izquierda=0;
        derecha=0;
        adelante=0;
        atras=0;
        this->album = dato;
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
    Album* getAlbum(){return album;}
    void setAlbum(Album *ndato){album =ndato;}
private:
    Nodo *arriba;
    Nodo *abajo;
    Nodo *izquierda;
    Nodo *derecha;
    Nodo *adelante;
    Nodo *atras;
    Album *album;
};



class CuboDisperso{


public:
    CuboDisperso(){
        root = new Nodo(alb);
    }
    Nodo *buscarFila(int y){
        Nodo *temp = root;
        while (temp!=0) {
            if(temp->getAlbum()->getMonthNumero() == y){
                return temp;
            }
            temp= temp->getAbajo();
        }
        return 0;
    }

    Nodo *buscarColumna(int x){
        Nodo *temp = root;
        while (temp!=0) {
            if(temp->getAlbum()->getYear() == x){
                return temp;
            }
            temp= temp->getDerecha();
        }
        return 0;
    }

    void Insertar(int x,int y,Album *album){

        Nodo *nuevo = new Nodo(album);
        Nodo *columna = buscarColumna(x);
        Nodo *fila = buscarFila(y);
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


    Nodo Insertar_Ordenado_Columna(Nodo *CabezaColumna,Nodo *nuevo){
        Nodo *temp = CabezaColumna;
        bool bandera = false;
        while (true) {
            if(temp->getAlbum()->getYear()== nuevo->getAlbum()->getYear()){
                temp->getAlbum()->setMonth(nuevo->getAlbum()->getMonth());
                temp->setAlbum(nuevo->getAlbum());//Esto aun no lo entiendo al 100 :c
                return *temp;
            }
            else if(temp->getAlbum()->getYear() > nuevo->getAlbum()->getYear()){
                bandera = true;
                break;
            }
            if(temp->getDerecha()!=0){
                temp = temp->getDerecha();
            }else{
                break;
            }
        }
        if(bandera==true){
            nuevo->setDerecha(temp);
            temp->getIzquierda()->setDerecha(nuevo);
            nuevo->setIzquierda(temp->getIzquierda());
            temp->setIzquierda(nuevo);
        }else{
            temp->setDerecha(nuevo);
            nuevo->setIzquierda(temp);
        }
        return  *nuevo;
    }

    Nodo Insertar_Ordenado_Fila(Nodo *CabezaFila,Nodo *nuevo){
        Nodo *temp = CabezaFila;
        bool bandera = false;
        while (true) {
            if(temp->getAlbum()->getMonthNumero()== nuevo->getAlbum()->getMonthNumero()){
                temp->getAlbum()->setYear(nuevo->getAlbum()->getYear());
                temp->setAlbum(nuevo->getAlbum());//Esto aun no lo entiendo al 100 :c
                return *temp;
            }
            else if(temp->getAlbum()->getMonthNumero()> nuevo->getAlbum()->getMonthNumero()){
                bandera = true;
                break;
            }
            if(temp->getDerecha()!=0){
                temp = temp->getAbajo();
            }else{
                break;
            }
        }
        if(bandera==true){
            nuevo->setAbajo(temp);
            temp->getArriba()->setAbajo(nuevo);
            nuevo->setArriba(temp->getArriba());
            temp->setArriba(nuevo);
        }else{
            temp->setAbajo(nuevo);
            nuevo->setArriba(temp);
        }
        return  *nuevo;
    }

    Nodo CrearColumna(int x){
        Nodo *cabeza_columna = root;
        Album *albColum = new Album("","",x);
        Nodo * nuevo= new Nodo(albColum);
        Nodo columna = Insertar_Ordenado_Columna(cabeza_columna,nuevo);
        return columna;
    }
private:
    Album *alb= new Album("Root","F",1);
    Nodo *root;
};















#endif // CUBOD_H
