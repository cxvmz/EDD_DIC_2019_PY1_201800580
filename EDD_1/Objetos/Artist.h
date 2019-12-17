#ifndef ARTIST_H
#define ARTIST_H
#include<iostream>
#include <QString>

class Artist{
public:
    Artist(QString name){
        this->name=name;
    }
    QString getName() const;
    void setName(const QString &value);

    double getRating() const;
    void setRating(double value);

private:
    QString name;
    double rating;
};


#endif // ARTIST_H

QString Artist::getName() const
{
    return name;
}

void Artist::setName(const QString &value)
{
    name = value;
}

double Artist::getRating() const
{
return rating;
}

void Artist::setRating(double value)
{
rating = value;
}
