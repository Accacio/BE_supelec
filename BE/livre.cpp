#include "livre.h"

Livre::Livre() : Persistentobject("Livre")
{
*newtable_structure=QString("(Titre text NOT NULL,Auteur text NOT NULL, ISBN integer NOT NULL, Annee integer NOT null)");

    QString * titre= new QString("Titre");
    QString * titre_data= new QString("");
    QString * auteur= new QString("Auteur");
    QString * auteur_data= new QString("");
    QString * isbn= new QString("ISBN");
    unsigned int * isbn_data=new unsigned int;
    *isbn_data= (unsigned int) 0;
    QString * annee= new QString("Annee");
    int * annee_data=new int;
    * annee_data=(int) 0;

    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::Int,isbn_data);
    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);

    addAttribute(0,title);
    addAttribute(1,author);
    addAttribute(2,Isbn);
    addAttribute(3,year);


    *objectStructure<<"Titre"<<"Auteur"<<"ISBN"<<"Année";


    delete titre;
    delete titre_data;
    delete auteur;
    delete auteur_data;
    delete isbn;
    delete isbn_data;
    delete annee;
    delete annee_data;
    delete title;
    delete author;
    delete Isbn ;
    delete year;

}

void Livre::addFromDatabase(QSqlQuery * query)
{
    std::cout<<"==============addFromDatabase - Livre============"<<std::endl;
    QString * titre= new QString("Titre");
    QString * auteur= new QString("Auteur");
    QString * isbn= new QString("ISBN");
    unsigned int * isbn_data=new unsigned int;
    QString * annee= new QString("Annee");
    int * annee_data=new int;

    QString * titre_data= new QString(query->value(0).toString());
    QString * auteur_data= new QString(query->value(1).toString());
    *isbn_data= (unsigned int) query->value(2).toInt();
    * annee_data=(int) query->value(3).toInt();

    std::cout<<"Query Data:"<<std::endl;
    qDebug()<<query->value(0).toString()<<QString(" | ")<<query->value(1).toString()<<QString(" | ")<<query->value(2).toString()<<QString(" | ")<<query->value(3).toString();

    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::Int,isbn_data);
    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);

    updateAttribute(0,title);
    updateAttribute(1,author);
    updateAttribute(2,Isbn);
    updateAttribute(3,year);

    //qDebug()<<*((QString *)attributes->at(0)->getData());

    std::cout<<"Data in list"<<std::endl;
    delete titre;
    delete titre_data;
    delete auteur;
    delete auteur_data;
    delete isbn;
    delete isbn_data;
    delete annee;
    delete annee_data;
    delete title;
    delete author;
    delete Isbn ;
    delete year;

    //std::cout<< query.value(0).toString().toStdString()<<QString(" | ").toStdString() <<query.value(1).toString().toStdString() << QString(" | ").toStdString() <<query.value(2).toString().toStdString() << QString(" | ").toStdString()<<query.value(3).toString().toStdString();
    std::cout<<"==============addFromDatabase - Livre============"<<std::endl;
}

