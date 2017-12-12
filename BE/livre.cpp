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
