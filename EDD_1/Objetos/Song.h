#ifndef SONG_H
#define SONG_H
#include<iostream>
#include <QString>
using namespace std;

class Song{
public:
    Song(QString name,QString file,double rating){
        this->name=name;
        this->file=file;
        this->rating=rating;
    }
    QString getName(){return name;}
    void setName(QString value){name = value;}

    QString getFile(){return file;}
    void setFile( QString value){file = value;}

    double getRating(){return rating;}
    void setRating(double value){rating = value;}

private:
    QString name;
    QString file;
    double rating;
};

#endif // SONG_H
