#include <QCoreApplication>
#include "EDD_1/Cola.h"
#include "EDD_1/LDE.h"
#include "EDD_1/LS.h"
#include "EDD_1/LDEC.h"
#include "EDD_1/Pila.h"
#include "EDD_1/Objetos/Artist.h"
#include "EDD_1/Objetos/Album.h"
#include "EDD_1/Objetos/Song.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <fstream>
#include <qdebug.h>


void AbrirArchivoLibraryJson(QString filen){
    QFile file;
    QStringList nombre;
    QStringList nombreAlbum;
    QStringList mes;
    QStringList anio;
    QStringList nombreCancion;
    QStringList archivoCancion;
    QStringList ratingCancion;
    QString val;
    file.setFileName(filen);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    val=file.readAll();
    file.close();
    double ratingAlb =0;
    double ratingArt =0;
    QJsonDocument doc =QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["Library"].toArray();
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject artista = obj["Artist"].toObject();
        nombre.append(artista["Name"].toString());
        qDebug()<<"---------Artista--------";
        qDebug()<< artista.value(QStringLiteral("Name")).toString();
        QJsonArray arrayAlbums = artista["Albums"].toArray();
        Artist art(artista.value(QStringLiteral("Name")).toString());
        foreach(const QJsonValue & value1, arrayAlbums){
            QJsonObject obj1 =value1.toObject();
            nombreAlbum.append(obj1["Name"].toString());
            mes.append(obj1["Month"].toString());
            anio.append(obj1["Year"].toString());
            qDebug()<<"         ---------Album--------";
            qDebug()<< "         "<<obj1.value(QStringLiteral("Name")).toString();
            Album alb(obj1.value(QStringLiteral("Name")).toString(),obj1.value(QStringLiteral("Month")).toString(),obj1.value(QStringLiteral("Year")).toString().toInt());
            QJsonArray arrayCanciones = obj1["Songs"].toArray();
            ListaSimple<Song> listaCanciones;
            foreach(const QJsonValue & value2, arrayCanciones){
                QJsonObject obj2 = value2.toObject();
                nombreCancion.append(obj2["Name"].toString());
                archivoCancion.append(obj2["File"].toString());
                ratingCancion.append(obj2["Rating"].toString());
                ratingAlb += obj2.value(QStringLiteral("Rating")).toString().toDouble();
                qDebug()<<"         "<<"         "<<"---------Cancion--------";
                qDebug()<< "         "<<"         "<<obj2.value(QStringLiteral("Name")).toString();
                qDebug()<<"         "<<"         "<< obj2.value(QStringLiteral("File")).toString();
                qDebug()<< "         "<<"         "<<obj2.value(QStringLiteral("Rating")).toString();
                Song son(obj2.value(QStringLiteral("Name")).toString(),obj2.value(QStringLiteral("File")).toString(),obj2.value(QStringLiteral("Rating")).toString().toDouble());
                listaCanciones.agregarFinal(son);
            }
            alb.setRating(ratingAlb);
            ratingArt+=alb.getRating();
        }
        art.setRating(ratingArt);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //AbrirArchivoLibraryJson("C:/Users/Christian/Desktop/Library.json");
    return a.exec();
}



