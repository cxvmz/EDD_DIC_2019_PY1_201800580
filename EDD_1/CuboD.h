#ifndef CUBOD_H
#define CUBOD_H
#include "EDD_1/Objetos/Album.h"
#include "EDD_1/LDE.h"
#include <iostream>
#include<fstream>
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
    Album *getAlbum(){return album;}
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

    Nodo *buscarElemento(int x,int y){
        Nodo *temp = root;
        while (temp!=0) {
            Nodo *aux = temp;
            if(temp->getAlbum()->getYear() == x){

                while (temp!=0) {
                    if(temp->getAlbum()->getMonthNumero()==y){
                        return temp;
                    }
                    temp= temp->getAbajo();
                }
            }
            temp=aux;
            temp= temp->getDerecha();
        }
    }

    void Insertar(int x,int y,Album *album){

        Nodo *nuevo = new Nodo(album);
        Nodo *columna = buscarColumna(x);
        Nodo *fila = buscarFila(y);

        //CASO 1:NO EXISTE COLUMA NO EXISTE FILA
        if(columna==0 && fila==0){
            //qDebug()<<"Caso1";
            //crearColumna
            columna = CrearColumna(x);
            //crearFila
            fila = CrearFila(y);
            //InsertarDeFormaOdenadaEnColumna
            nuevo = Insertar_Ordenado_Columna(fila,nuevo);
            //InsertarDeFormaOdernadaEnFila
            nuevo = Insertar_Ordenado_Fila(columna,nuevo);

        }
        //CASO2: NO EXISTE COLUMNA SI FILA
        else if(columna==0 && fila!=0){
            //crearColumna.
            columna = CrearColumna(x);
            //InsertarDeFormaOdenadaEnColumna
            nuevo = Insertar_Ordenado_Columna(fila,nuevo);
            //InsertarDeFormaOdernadaEnFila
            nuevo = Insertar_Ordenado_Fila(columna,nuevo);
            //qDebug()<<"Caso2";
        }
        //CASO3: SI EXISTE COLUMNA NO FILA
        else if(columna!=0 && fila==0){
            //crearFila
            fila = CrearFila(y);
            //InsertarDeFormaOdenadaEnColumna
            nuevo = Insertar_Ordenado_Columna(fila,nuevo);
            //InsertarDeFormaOdernadaEnFila
            nuevo = Insertar_Ordenado_Fila(columna,nuevo);
            //qDebug()<<"Caso3";
        }
        //CASO2: SI EXISTE COLUMNA SI FILA
        else if(columna!=0 && fila!=0){
            //InsertarDeFormaOdenadaEnColumna
            nuevo = Insertar_Ordenado_Columna(fila,nuevo);
            //InsertarDeFormaOdernadaEnFila
            nuevo = Insertar_Ordenado_Fila(columna,nuevo);
            //qDebug()<<"Caso4";
        }
    }


    Nodo *Insertar_Ordenado_Columna(Nodo *CabezaColumna,Nodo *nuevo){
        Nodo *temp = CabezaColumna;
        bool bandera = false;
        while (true) {
            if(temp->getAlbum()->getYear() > nuevo->getAlbum()->getYear()){
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
        return  nuevo;
    }

    Nodo *Insertar_Ordenado_Fila(Nodo *CabezaFila,Nodo *nuevo){
        Nodo *temp = CabezaFila;
        bool bandera = false;
        while (true) {
            if(temp->getAlbum()->getMonthNumero()> nuevo->getAlbum()->getMonthNumero()){
                bandera = true;
                break;
            }
            if(temp->getAbajo()!=0){
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
        return  nuevo;
    }

    Nodo *CrearColumna(int x){
        Nodo *cabeza_columna = root;
        Album *albFila = new Album("","",x);
        Nodo * nuevo= new Nodo(albFila);
        Nodo *columna = Insertar_Ordenado_Columna(cabeza_columna,nuevo);
        return columna;
    }
    Nodo *CrearFila(int y){
        Nodo *cabeza_fila = root;
        QString mesEnString = getMonthString(y);
        Album *albFila = new Album("",mesEnString,-1);
        Nodo * nuevo= new Nodo(albFila);
        Nodo *fila = Insertar_Ordenado_Fila(cabeza_fila,nuevo);
        return fila;
    }

    QString getMonthString(int mes)
    {
        if(mes==1){
            return "Enero";
        }
        else if(mes==2){
            return "Febrero";
        }
        else if(mes==3){
            return "Marzo";
        }
        else if(mes==4){
            return "Abril";
        }
        else if(mes==5){
            return "Mayo";
        }
        else if(mes==6){
            return "Junio";
        }
        else if(mes==7){
            return "Julio";
        }
        else if(mes==8){
            return "Agosto";
        }
        else if(mes==9){
            return "Septiembre";
        }
        else if(mes==10){
            return "Octubre";
        }
        else if(mes==11){
            return "Noviembre";
        }
        else if(mes==12){
            return "Diciembre";
        }
        else{
            return "F";
        }
    }

    void ImprimirColumas(){
        Nodo *aux = root;
        while (aux!=0) {
            qDebug()<<"Anio  "<<aux->getAlbum()->getYear();
            aux= aux->getDerecha();
        }
    }
    void ImprimirFilas(){
        Nodo *aux = root;
        while (aux!=0) {
            qDebug()<<"Mes  "<<aux->getAlbum()->getMonth();
            aux= aux->getAbajo();
        }
    }
    void imprimirElementos(){
        Nodo *aux = root;
        if(aux->getAlbum()->getYear()!=0 && aux->getAlbum()->getMonth()!="")
        while (aux!=0) {
            qDebug()<<aux->getAlbum()->getMonth();
            aux= aux->getAbajo();
        }
    }

    QString graficar(){
        QString codigoG="";

        codigoG+="digraph Cubo { \n node [shape = record]\n graph [nodesep = 1]\n\n";

        Nodo *n =root;
        Nodo *aux = root;


        //FILAS
        codigoG += " \" "+n->getAlbum()->getName()+" \" ";
        n=n->getDerecha();
        while (n!=0) {
            codigoG+= "->" +QString::number( n->getAlbum()->getYear());
            n =n->getDerecha();
        }
        n=aux;
        codigoG+="[dir=both];\n {rank=same ";
        codigoG+=" \" "+aux->getAlbum()->getName()+" \" ";
        n = n->getDerecha();
        while (n!=0) {
            codigoG+=QString::number(n->getAlbum()->getYear())+" ";
            n =n->getDerecha();
        }
        codigoG+="} \n\n";
        aux=aux->getAbajo();
        n= aux;
        while (aux!=0) {
            codigoG += aux->getAlbum()->getMonth();
            n = n->getDerecha();
            while (n!=0) {
                codigoG+="-> \" "+n->getAlbum()->getName()+" \" ";
                n =n->getDerecha();
            }
            codigoG+="[constraint=same,dir=both];\n {rank=same "+aux->getAlbum()->getMonth()+" ";
            n= aux->getDerecha();
            while (n!=0) {
                codigoG+=" \" "+n->getAlbum()->getName()+" \"  ";
                n =n->getDerecha();
            }
                    codigoG+="} \n\n";
            aux =aux->getAbajo();
            n=aux;
        }


        //COLUMNAS
        aux = root;
        n=root;
        codigoG += " \" "+n->getAlbum()->getName()+" \" ";
        n=n->getAbajo();
        while (n!=0) {
            codigoG +="->"+n->getAlbum()->getMonth();
            n=n->getAbajo();
        }
        codigoG+="[dir=both];\n";
        aux = aux->getDerecha();
        n=aux;
        while (aux!=0) {
            codigoG+=QString::number(n->getAlbum()->getYear())+"->";
            n = n->getAbajo();
            while (n!=0) {
                codigoG+=" \" "+n->getAlbum()->getName()+" \" ";
                n=n->getAbajo();
            }
            codigoG+="[dir=both];\n";
            aux=aux->getDerecha();
            n=aux;
        }
        codigoG +="}";

        return codigoG;
    }


    void generarTxT(QString txt){
        ofstream cube;
        cube.open("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt",ios::out);
        cube<<txt.toStdString();
        cube.close();
        system("cd C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/");
        //string cmd= "dot -Tpng C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png";
        //system(cmd.c_str());
        //system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.png");
        string cmd= "dot -Tpdf C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.txt -o C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.pdf";
        system(cmd.c_str());
        system("start C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/cube.pdf");
    }
private:
    Album *alb= new Album("Root","F",-1);
    Nodo *root;
};















#endif // CUBOD_H
