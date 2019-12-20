#ifndef ALBUM_H
#define ALBUM_H
#include<iostream>
#include <QString>
#include"EDD_1/LS.h"
#include"EDD_1/Objetos/Song.h"
using namespace std;

class Album{
public:
    Album(QString name, QString month,int year){
            this->name=name;
            this->month=month;
            this->year=year;
            this->rating=0;
        }
    QString getName(){return name;}
    void setName( QString value){name = value;}

    QString getMonth(){return month;}
    void setMonth( QString value){month = value;}
    int getMonthNumero(){
        if(this->month=="Enero"){
            return 1;
        }
        else if(this->month=="Febrero"){
            return 2;
        }
        else if(this->month=="Marzo"){
            return 3;
        }
        else if(this->month=="Abril"){
            return 4;
        }
        else if(this->month=="Mayo"){
            return 5;
        }
        else if(this->month=="Junio"){
            return 6;
        }
        else if(this->month=="Julio"){
            return 7;
        }
        else if(this->month=="Agosto"){
            return 8;
        }
        else if(this->month=="Septiembre"){
            return 9;
        }
        else if(this->month=="Octubre"){
            return 10;
        }
        else if(this->month=="Noviembre"){
            return 11;
        }
        else if(this->month=="Diciembre"){
            return 12;
        }
        else if(this->month=="F"){
            return -1;
        }
        else{
            return 0;
        }
    }

    int getYear(){return year;}
    void setYear(int value){year = value;}

    double getRating(){return rating;}
    void setRating(double value){rating = value;}

    ListaSimple<Song> *getCanciones(){return canciones;}
    void setCanciones(ListaSimple<Song> *value){canciones = value;}

private:
    QString name;
    QString month;
    int year;
    double rating;
    ListaSimple<Song> *canciones;
};

#endif // ALBUM_H

