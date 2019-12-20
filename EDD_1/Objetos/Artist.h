#ifndef ARTIST_H
#define ARTIST_H
#include<iostream>
#include <QString>
#include "EDD_1/CuboD.h"

class Artist{
public:
    Artist(QString name){
        this->name=name;
    }
    QString getName(){return name;}
    void setName(const QString &value){name = value;}


    double getRating(){return rating;}
    void setRating(double value){rating = value;  }

    CuboDisperso getAlbums(){return albums;}
    void setAlbums(const CuboDisperso &value){albums = value;}


private:
    QString name;
    CuboDisperso albums;
    double rating;
};


#endif // ARTIST_H

