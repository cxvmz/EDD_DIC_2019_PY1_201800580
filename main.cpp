#include <QCoreApplication>
#include "EDD_1/Objetos/ColaABB.h"
#include "EDD_1/LDE.h"
#include "EDD_1/LS.h"
#include "EDD_1/LDEC.h"
#include "EDD_1/Objetos/PilaABB.h"
#include "EDD_1/Objetos/Artist.h"
#include "EDD_1/Objetos/Album.h"
#include "EDD_1/Objetos/Song.h"
#include "EDD_1/Objetos/Playlist.h"
#include "EDD_1/Objetos/ShuffleABB.h"
#include "EDD_1/Objetos/CircularABB.h"
#include <QFile>
#include"EDD_1/Objetos/SongsPL.h"
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



ListaDoblementeEnlazada AbrirArchivoLibraryJson(QString filen){
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
    ListaDoblementeEnlazada listaDeArtistas;
    double ratingAlb =0;
    int iteracionesAlb=0;
    double ratingArt =0;
    int iteracionesArt =0;
    QJsonDocument doc =QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["Library"].toArray();
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
            albMatriz->setCanciones(listaCanciones);
            int x = obj1["Year"].toString().toInt();
            int y = MesEnInt(obj1["Month"].toString());
            cuboDeAlbumes.Insertar(x,y,albMatriz);
        }
        art->setRating(ratingArt/iteracionesAlb);
        art->setAlbums(cuboDeAlbumes);
        listaDeArtistas.agregar_ultimo(art);
        //qDebug()<<art.getName()+"  "+QString::number(art.getRating());
        //cuboDeAlbumes.ImprimirColumas();
        //cuboDeAlbumes.ImprimirFilas();
        //cuboDeAlbumes.generarTxT(cuboDeAlbumes.graficar()) ;
    }

    //listaDeArtistas.imprimirLDE();
    //qDebug()<<"\n\n\n\n";
    //qDebug()<<"Odenada xd";
    listaDeArtistas.OrdenarLDE_A_Z();
    //listaDeArtistas.imprimirLDE();
     //qDebug()<<"\n\n\n\n";
    return listaDeArtistas;
}


Playlist *AbrirArchivoPlaylistJson(QString filen){
    QFile file;
    QStringList anio;
    QString tipo;
    QStringList mes;
    QStringList album;
    QStringList song;
    QStringList artist;
    QString val;
    file.setFileName(filen);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    val=file.readAll();
    file.close();
    QJsonDocument doc =QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonObject type = jsonObject["Type"].toObject();
    tipo.append(jsonObject["Type"].toString());
    //Remover para obtener nombre de la playlist
    QString namePL = filen.remove(QString(".json"), Qt::CaseSensitivity());
    Playlist *play = new Playlist(namePL,jsonObject["Type"].toString());
    if(jsonObject.value(QStringLiteral("Type")).toString()=="Stack"){
        PilaABB *stack = new PilaABB();
        QJsonArray asd = jsonObject["Songs"].toArray();
        foreach (const QJsonValue & value, asd) {
            QJsonObject obj = value.toObject();
            anio.append(obj["Year"].toString());
            mes.append(obj["Month"].toString());
            album.append(obj["Album"].toString());
            song.append(obj["Song"].toString());
            artist.append(obj["Artist"].toString());
            SongPL *ns= new SongPL(obj.value(QStringLiteral("Year")).toString().toInt(),obj.value(QStringLiteral("Month")).toString(),obj.value(QStringLiteral("Album")).toString(),obj.value(QStringLiteral("Song")).toString(),obj.value(QStringLiteral("Artist")).toString());
            stack->push(ns);
        }
        play->setPila(stack);
        //stack.ReproducirPila();
    }
    else if(jsonObject.value(QStringLiteral("Type")).toString()=="Queue"){
        ColaABB *Queue= new ColaABB();
        QJsonArray asd = jsonObject["Songs"].toArray();
        foreach (const QJsonValue & value, asd) {
            QJsonObject obj = value.toObject();
            anio.append(obj["Year"].toString());
            mes.append(obj["Month"].toString());
            album.append(obj["Album"].toString());
            song.append(obj["Song"].toString());
            artist.append(obj["Artist"].toString());
            SongPL *ns= new SongPL(obj.value(QStringLiteral("Year")).toString().toInt(),obj.value(QStringLiteral("Month")).toString(),obj.value(QStringLiteral("Album")).toString(),obj.value(QStringLiteral("Song")).toString(),obj.value(QStringLiteral("Artist")).toString());
            Queue->encolar(ns);
        }
        play->setCola(Queue);
        //Queue.ReproducirCola();
    }
    else if(jsonObject.value(QStringLiteral("Type")).toString()=="Shuffle"){
        SuffleABB *suffle = new SuffleABB();
        QJsonArray asd = jsonObject["Songs"].toArray();
        foreach (const QJsonValue & value, asd) {
            int desicion = rand()%2;
            QJsonObject obj = value.toObject();
            anio.append(obj["Year"].toString());
            mes.append(obj["Month"].toString());
            album.append(obj["Album"].toString());
            song.append(obj["Song"].toString());
            artist.append(obj["Artist"].toString());
            SongPL *ns= new SongPL(obj.value(QStringLiteral("Year")).toString().toInt(),obj.value(QStringLiteral("Month")).toString(),obj.value(QStringLiteral("Album")).toString(),obj.value(QStringLiteral("Song")).toString(),obj.value(QStringLiteral("Artist")).toString());
            if(desicion==1){
                suffle->agregar_primero(ns);
            }else if(desicion==0){
                suffle->agregar_ultimo(ns);
            }
        }
        //suffle.imprimirSuffleABB();
        //suffle.ReproducirShuffle("S");
        play->setShuffle(suffle);
    }
    else if(jsonObject.value(QStringLiteral("Type")).toString()=="Circular"){
        CircularABB *circular=new CircularABB();
        QJsonArray asd = jsonObject["Songs"].toArray();
        foreach (const QJsonValue & value, asd) {
            QJsonObject obj = value.toObject();
            anio.append(obj["Year"].toString());
            mes.append(obj["Month"].toString());
            album.append(obj["Album"].toString());
            song.append(obj["Song"].toString());
            artist.append(obj["Artist"].toString());
            SongPL *ns= new SongPL(obj.value(QStringLiteral("Year")).toString().toInt(),obj.value(QStringLiteral("Month")).toString(),obj.value(QStringLiteral("Album")).toString(),obj.value(QStringLiteral("Song")).toString(),obj.value(QStringLiteral("Artist")).toString());
            circular->agregar_ultimo(ns);
        }
        play->setCircular(circular);
        //circular.imprimirCiccukarABB();
        //circular.generarTxt(circular.graficar("A"));
    }
    return play;
}

int main(int argc, char *argv[])
{
    ListaDoblementeEnlazada listaDeArtistas;
    QCoreApplication a(argc, argv);
    while (true) {
        qDebug()<<"1. Ingresar Archivo Library";
        qDebug()<<"2. Artist Report";
        qDebug()<<"3. Elegir Artista";
        qDebug()<<"4. Top 5 Artista";
        string o1;
        cin>>o1;
        if(o1=="1")
        {
            string rutaLibrry;
            qDebug()<<"Inserte Ruta";
            cin>>rutaLibrry;
            QString qstr = QString::fromStdString(rutaLibrry);
            try {
                listaDeArtistas = AbrirArchivoLibraryJson(qstr);
                qDebug()<<"Abierto Correctamente";
                o1="";
            } catch(int i) {
                qDebug()<<"F F F"<<i;
            }

        }else if(o1=="2")
        {
            listaDeArtistas.generarTxt(listaDeArtistas.graficar());
            o1="";
        }else if(o1=="3"){
            listaDeArtistas.imprimirLDE();
            int o2;
            qDebug()<<"Eliger Artista";
            cin>>o2;
            Artist mArt=listaDeArtistas.obtener_Elemento_En(o2);
            mArt.getAlbums().generarTxT(mArt.getAlbums().graficar());
            qDebug()<<"Ingrese año y mes";
            int x,y;
            cin>>x>>y;
            Album *f= mArt.getAlbums().buscarElemento(x,y)->getAlbum();
            f->getCanciones()->imprimirLS();
            f->getCanciones()->generarTxt(f->getCanciones()->graficar());
            qDebug()<<"Eliger Cacnion a reproducir";
            int fcan;
            cin>>fcan;
            f->getCanciones()->elementat(fcan);
        }else if(o1=="4"){
            ListaDoblementeEnlazada f1 = listaDeArtistas;
            f1.OrdenarLDE_MA_ME();
            f1.generarTxt(f1.graficarRating());
        }

    }



    //AbrirArchivoLibraryJson("Library_test.json",listaDeArtistas;);
    //AbrirArchivoLibraryJson("Library.json",listaDeArtistas);








    //AbrirArchivoPlaylistJson("Playlist_Rock.json");
    //qDebug()<<"F";
    return a.exec();
/*
    SongPL *ns= new SongPL(1,"a","a","a","a");
    SongPL *ns1= new SongPL(2,"b","b","b","b");
    SongPL *ns2= new SongPL(3,"c","c","c","c");
    SongPL *ns3= new SongPL(4,"d","d","d","d");
    SongPL *ns4= new SongPL(5,"e","e","e","e");
    PilaABB nuevaPila;
    nuevaPila.push(ns);
    nuevaPila.push(ns1);
    nuevaPila.push(ns2);
    nuevaPila.push(ns3);
    nuevaPila.push(ns4);
    nuevaPila.ReproducirPila();
*/




}




