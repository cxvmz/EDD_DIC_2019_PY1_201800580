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
    QString getName() const;
    void setName(const QString &value);

    QString getMonth() const;
    void setMonth(const QString &value);
    int getMonthNumero();

    int getYear() const;
    void setYear(int value);

    double getRating() const;
    void setRating(double value);

    ListaSimple<Song> *getCanciones() const;
    void setCanciones(ListaSimple<Song> *value);

private:
    QString name;
    QString month;
    int year;
    double rating;
    ListaSimple<Song> *canciones;
};

#endif // ALBUM_H
int Album::getMonthNumero()
{
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
    else{
        return 0;
    }
}

QString Album::getName() const
{
return name;
}

void Album::setName(const QString &value)
{
name = value;
}

QString Album::getMonth() const
{
return month;
}

void Album::setMonth(const QString &value)
{
month = value;
}

int Album::getYear() const
{
return year;
}

void Album::setYear(int value)
{
year = value;
}

double Album::getRating() const
{
return rating;
}

void Album::setRating(double value)
{
rating = value;
}

ListaSimple<Song> *Album::getCanciones() const
{
return canciones;
}

void Album::setCanciones(ListaSimple<Song> *value)
{
canciones = value;
}
