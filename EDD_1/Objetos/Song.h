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
    QString getName() const;
    void setName(const QString &value);

    QString getFile() const;
    void setFile(const QString &value);

    double getRating() const;
    void setRating(double value);

private:
    QString name;
    QString file;
    double rating;
};

#endif // SONG_H

QString Song::getName() const
{
return name;
}

void Song::setName(const QString &value)
{
name = value;
}

QString Song::getFile() const
{
return file;
}

void Song::setFile(const QString &value)
{
file = value;
}

double Song::getRating() const
{
return rating;
}

void Song::setRating(double value)
{
rating = value;
}
