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


int MesEnInt(QString mes)
{
    if(mes=="Enero"){
        return 1;
    }
    else if(mes=="Febrero"){
        return 2;
    }
    else if(mes=="Marzo"){
        return 3;
    }
    else if(mes=="Abril"){
        return 4;
    }
    else if(mes=="Mayo"){
        return 5;
    }
    else if(mes=="Junio"){
        return 6;
    }
    else if(mes=="Julio"){
        return 7;
    }
    else if(mes=="Agosto"){
        return 8;
    }
    else if(mes=="Septiembre"){
        return 9;
    }
    else if(mes=="Octubre"){
        return 10;
    }
    else if(mes=="Noviembre"){
        return 11;
    }
    else if(mes=="Diciembre"){
        return 12;
    }
    else if(mes=="F"){
        return -1;
    }
    else{
        return 0;
    }
}



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
    int iteracionesAlb=0;
    double ratingArt =0;
    int iteracionesArt =0;
    QJsonDocument doc =QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["Library"].toArray();
    ListaDoblementeEnlazada listaDeArtistas;
    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject artista = obj["Artist"].toObject();
        nombre.append(artista["Name"].toString());
        //qDebug()<<"---------Artista--------";
        //qDebug()<< artista.value(QStringLiteral("Name")).toString();
        QJsonArray arrayAlbums = artista["Albums"].toArray();
        Artist *art = new Artist(artista.value(QStringLiteral("Name")).toString());
        CuboDisperso cuboDeAlbumes;
        foreach(const QJsonValue & value1, arrayAlbums){
            QJsonObject obj1 =value1.toObject();
            nombreAlbum.append(obj1["Name"].toString());
            mes.append(obj1["Month"].toString());
            anio.append(obj1["Year"].toString());
            //qDebug()<<"         ---------Album--------";
            //qDebug()<< "         "<<obj1.value(QStringLiteral("Name")).toString();
            Album alb(obj1.value(QStringLiteral("Name")).toString(),obj1.value(QStringLiteral("Month")).toString(),obj1.value(QStringLiteral("Year")).toString().toInt());
            QJsonArray arrayCanciones = obj1["Songs"].toArray();
            ListaSimple<Song> *listaCanciones =new ListaSimple<Song>();
            foreach(const QJsonValue & value2, arrayCanciones){
                QJsonObject obj2 = value2.toObject();
                nombreCancion.append(obj2["Name"].toString());
                archivoCancion.append(obj2["File"].toString());
                ratingCancion.append(obj2["Rating"].toString());
                ratingAlb += obj2.value(QStringLiteral("Rating")).toString().toDouble();
                iteracionesArt++;
                //qDebug()<<"         "<<"         "<<"---------Cancion--------";
                //qDebug()<< "         "<<"         "<<obj2.value(QStringLiteral("Name")).toString();
                //qDebug()<<"         "<<"         "<< obj2.value(QStringLiteral("File")).toString();
                //qDebug()<< "         "<<"         "<<obj2.value(QStringLiteral("Rating")).toString();
                Song *son = new Song(obj2.value(QStringLiteral("Name")).toString(),obj2.value(QStringLiteral("File")).toString(),obj2.value(QStringLiteral("Rating")).toString().toDouble());
                //qDebug()<< son.getFile()<<son.getName();
                listaCanciones->agregarFinal(son);
                //listaCanciones.imprimirLS();
            }
            alb.setRating(ratingAlb/iteracionesArt);
            ratingArt+=alb.getRating();
            iteracionesAlb++;
            alb.setCanciones(listaCanciones);
            //alb.getCanciones()->imprimirLS();
            Album *albMatriz = new Album(obj1["Name"].toString(),obj1["Month"].toString(),obj1["Year"].toString().toInt());
            int x = obj1["Year"].toString().toInt();
            int y = MesEnInt(obj1["Month"].toString());
            cuboDeAlbumes.Insertar(x,y,albMatriz);
        }
        art->setRating(ratingArt/iteracionesAlb);
        art->setAlbums(cuboDeAlbumes);
        listaDeArtistas.agregar_ultimo(art);
        //qDebug()<<art.getName()+"  "+QString::number(art.getRating());
        //listaDeArtistas.agregar_ultimo(art);
        //cuboDeAlbumes.ImprimirColumas();
        //cuboDeAlbumes.ImprimirFilas();
        //cuboDeAlbumes.generarTxT(cuboDeAlbumes.graficar()) ;
    }
    listaDeArtistas.imprimirLDE();
    qDebug()<<"\n\n\n\n";
    qDebug()<<"Odenada xd";
    listaDeArtistas.OrdenarLDE_A_Z();
    listaDeArtistas.imprimirLDE();
     qDebug()<<"\n\n\n\n";

}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    AbrirArchivoLibraryJson("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Library_test.json");
    //AbrirArchivoLibraryJson("C:/Users/Christian/Documents/Proyecto1/EDD_Proyecto1_201800580/Library.json");
    return a.exec();


}




