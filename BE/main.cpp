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
    QString * titre_data= new QString("A historia sem fim");
    QString * auteur= new QString("Auteur");
    QString * auteur_data= new QString("Michael Ende");
    QString * isbn= new QString("ISBN");
    unsigned int * isbn_data=new unsigned int;
    *isbn_data= (unsigned int) 3522128001;
    QString * annee= new QString("Annee");
    int * annee_data=new int;
    * annee_data=(int) 1979;


    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::Int,isbn_data);
    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);
    Persistentobject * object= new Persistentobject("Livre");
    object->addAttribute(title);
    object->addAttribute(author);
    object->addAttribute(Isbn);
    object->addAttribute(year);
    object->save(db);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();



}
