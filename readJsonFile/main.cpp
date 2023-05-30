#include "mainwindow.h"
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile file("C:/Users/PIVview/Documents/NET_PowerControl_Home_V3/17.json");
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();

    QJsonParseError errPar;
    QJsonDocument doc = QJsonDocument::fromJson(ba, &errPar);
    QString errstr = errPar.errorString();
    QJsonObject obj = doc.object();


    QMap<QString, QVariant> maps = w.extractJsonObject("", obj);

     qDebug()  << maps;
    return a.exec();
}


