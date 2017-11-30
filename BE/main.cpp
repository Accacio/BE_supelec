#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "persistentattribute.h"
#include "persistentobject.h"
#include "QString"

#include <QtSql>

int main(int argc, char *argv[])
{
    QSqlDatabase * db = new QSqlDatabase();
    *db= QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("teste.db");

//    std::cout<<QDir::currentPath().toStdString()<<std::endl;
    if(!db->open())
    {
        std::cout<<"Error: "<< db->databaseName().toStdString() << "not found"<<std::endl;
    }



    QString * titre= new QString("Titre");
    QString * data= new QString("A historia sem fim");


    PersistentAttribute * atributo = new PersistentAttribute(titre,QVariant::Type::String,data);
    Persistentobject * object= new Persistentobject("Livre");
    object->addAttribute(atributo);
    object->save(db);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();



}
