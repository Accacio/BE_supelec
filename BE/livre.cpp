#include "livre.h"

Livre::Livre() : Persistentobject("Livre")
{
    std::cout<<" >>>>>>>>>> Livre::Livre >>>>>>>>>> "<<std::endl;


    *newtable_structure=QString("(Titre text NOT NULL,Auteur text NOT NULL, ISBN integer NOT NULL, Annee integer NOT null)");

    QString * titre= new QString("Titre");
    QString * titre_data= new QString("");
    QString * auteur= new QString("Auteur");
    QString * auteur_data= new QString("");
    QString * isbn= new QString("ISBN");
    qint64 * isbn_data=new qint64;
    *isbn_data= (qint64) 0;
    QString * annee= new QString("Annee");
    int * annee_data=new int;
    * annee_data=(int) 0;

    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::LongLong,isbn_data);
    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);

    addAttribute(0,title);
    addAttribute(1,author);
    addAttribute(2,Isbn);
    addAttribute(3,year);


    *objectStructure<<"Titre"<<"Auteur"<<"ISBN"<<"Année";


//    delete titre;
//    delete titre_data;
//    delete auteur;
//    delete auteur_data;
//    delete isbn;
//    delete isbn_data;
//    delete annee;
//    delete annee_data;
//    delete title;
//    delete author;
//    delete Isbn ;
//    delete year;

    std::cout<<" <<<<<<<<<< Livre::Livre <<<<<<<<<< "<<std::endl;
}

void Livre::addFromDatabase(QSqlQuery * query)
{
    std::cout<<" >>>>>>>>>> Livre::addFromDatabase >>>>>>>>>> "<<std::endl;
            std::cout<<"Table of tempObj"<<std::endl;
            qDebug()<<getTable();
    QString * titre= new QString("Titre");
    QString * auteur= new QString("Auteur");
    QString * isbn= new QString("ISBN");
    qint64 * isbn_data=new qint64;
    QString * annee= new QString("Annee");
    int * annee_data=new int;

    QString * titre_data= new QString(query->value(0).toString());
    QString * auteur_data= new QString(query->value(1).toString());
    *isbn_data=  query->value(2).toLongLong();
    * annee_data=(int) query->value(3).toInt();

    std::cout<<"Query Data:"<<std::endl;
    qDebug()<<query->value(0).toString()<<QString(" | ")<<query->value(1).toString()<<QString(" | ")<<query->value(2).toString()<<QString(" | ")<<query->value(3).toString();
//    std::cout<<"Query Data:"<<std::endl;
//    qDebug()<<query->value(0).toString()<<QString(" | ")<<query->value(1).toString()<<QString(" | ")<<query->value(2).toUInt()<<QString(" | ")<<query->value(3).toString();
    std::cout<<"Attributes Data:"<<std::endl;
    qDebug()<<* titre_data<<QString(" | ")<<* auteur_data<<QString(" | ")<<*isbn_data<<QString(" | ")<<* annee_data;

    PersistentAttribute * title = new PersistentAttribute(titre,QVariant::Type::String,titre_data);
    PersistentAttribute * author = new PersistentAttribute(auteur,QVariant::Type::String,auteur_data);
    PersistentAttribute * Isbn = new PersistentAttribute(isbn,QVariant::Type::LongLong,isbn_data);
    PersistentAttribute * year = new PersistentAttribute(annee,QVariant::Type::Int,annee_data);

    updateAttribute(0,title);
    updateAttribute(1,author);
    updateAttribute(2,Isbn);
    updateAttribute(3,year);

    //qDebug()<<*((QString *)attributes->at(0)->getData());

    std::cout<<"Data in list:"<<std::endl;
    qDebug()<<*(QString *)attributes->at(0)->getData()<<QString(" | ")<<*(QString *)attributes->at(1)->getData()<<QString(" | ")<<*(qint64 *)attributes->at(2)->getData()<<QString(" | ")<<*(int *)attributes->at(3)->getData();
//    delete titre;
//    delete titre_data;
//    delete auteur;
//    delete auteur_data;
//    delete isbn;
//    delete isbn_data;
//    delete annee;
//    delete annee_data;
//    delete title;
//    delete author;
//    delete Isbn ;
//    delete year;

    //std::cout<< query.value(0).toString().toStdString()<<QString(" | ").toStdString() <<query.value(1).toString().toStdString() << QString(" | ").toStdString() <<query.value(2).toString().toStdString() << QString(" | ").toStdString()<<query.value(3).toString().toStdString();
    std::cout<<" <<<<<<<<<< Livre::addFromDatabase <<<<<<<<<< "<<std::endl;
}


bool Livre::attributesNoValue()
{
    std::cout<<" >>>>>>>>>> Livre::attributesNoValue >>>>>>>>>> "<<std::endl;
    bool title=true;
    if(*(QString *)attributes->at(0)->getData()!=QString(""))
    {
        title=false;
    }

    bool author=true;

    if(*(QString *)attributes->at(1)->getData()!=QString(""))
    {
        author=false;
    }

    bool isbn=true;


    if(*(qint64 *)attributes->at(2)->getData()!=(qint64) 0)
    {
        isbn=false;
    }
//    bool year=true;

//    if(*(int *)attributes->at(3)->getData()!=QString(""))
//    {
//        year=false;
//    }


    std::cout<<" <<<<<<<<<< Livre::attributesNoValue <<<<<<<<<< "<<std::endl;
    return title||author||isbn;
};
