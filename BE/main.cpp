#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "persistentattribute.h"
#include "QString"
#include "livre.h"
#include <QtSql>
#include "handler.h"

int main(int argc, char *argv[])
{
    //Handler * myhandler= new Handler("untitled.db");

//    std::cout<<QDir::currentPath().toStdString()<<std::endl;


//    QString * titre= new QString("Titre");
//    QString * titre_data= new QString("The neverending story");
//    QString * auteur= new QString("Auteur");
//    QString * auteur_data= new QString("Michael Ende");
//    QString * isbn= new QString("ISBN");
//    unsigned int * isbn_data=new unsigned int;
//    *isbn_data= (unsigned int) 3522128001;
//    QString * annee= new QString("Annee");
//    int * annee_data=new int;
//    * annee_data=(int) 1979;


//    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
//    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
//    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::Int,isbn_data);
//    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);
//    Livre * object= new Livre();
//    object->addAttribute(title);
//    object->addAttribute(author);
//    object->addAttribute(Isbn);
//    object->addAttribute(year);

//    myhandler->addObject(0,object);
//    myhandler->addObject(1,object);
//    myhandler->save_table();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();



}
