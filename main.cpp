#include <QCoreApplication>
#include "EDD_1/Cola.h"
#include "EDD_1/LDE.h"
#include "EDD_1/LDEC.h"
#include "EDD_1/Pila.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <fstream>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}

void ArchivoJson(QString filen){
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
    QJsonDocument doc =QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();
    QJsonArray jsonArray = jsonObject["Library"].toArray();

    foreach (const QJsonValue & value, jsonArray) {
        QJsonObject obj = value.toObject();
        QJsonObject artista = obj["Artist"].toObject();
    }
}



