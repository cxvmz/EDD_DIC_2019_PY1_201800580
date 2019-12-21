#ifndef PLAYLIST_H
#define PLAYLIST_H
#include<iostream>
#include <QString>
#include"EDD_1/Objetos/ColaABB.h"
#include"EDD_1/Objetos/PilaABB.h"
#include"EDD_1/Objetos/ShuffleABB.h"
#include"EDD_1/Objetos/CircularABB.h"


using namespace std;


class Playlist{
public:
    Playlist(QString name,QString tipo){
        this->nombre=name;
        this->tipo=tipo;
    }
    void setPila(PilaABB *value);

    void setCola(ColaABB *value);

    void setShuffle(SuffleABB *value);

    void setCircular(CircularABB *value);

private:
    QString nombre;
    QString tipo;
PilaABB *pila;
ColaABB *cola;
SuffleABB *shuffle;
CircularABB *circular;






};

#endif // PLAYLIST_H

void Playlist::setPila(PilaABB *value)
{
pila = value;
}

void Playlist::setCola(ColaABB *value)
{
cola = value;
}

void Playlist::setShuffle(SuffleABB *value)
{
shuffle = value;
}

void Playlist::setCircular(CircularABB *value)
{
circular = value;
}
