#ifndef SONGSPL_H
#define SONGSPL_H
#include<iostream>
#include <QString>
using namespace std;

class SongPL{


public:
    SongPL(int year, QString month,QString album,QString song,QString artist){
        this->year=year;
        this->month=month;
        this->album=album;
        this->song=song;
        this->artist=artist;
    }
    int getYear(){
        return year;
        }
    void setYear(int value){
        year = value;
        }

    QString getMonth(){
        return month;
        }
    void setMonth(  QString &value){
        month = value;
        }

    QString getAlbum() {
        return album;
        }
    void setAlbum(  QString &value){
        album = value;
        }

    QString getSong() {
        return song;
        }
    void setSong(  QString &value){
        song = value;
        }

    QString getArtist() {
        return artist;
        }
    void setArtist(  QString &value){
        artist = value;
        }

private:
    int year;
    QString month;
    QString album;
    QString song;
    QString artist;
};


#endif // SONGSPL_H

