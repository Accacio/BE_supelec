#include "persistentobject.h"


Persistentobject::Persistentobject(QString className)
{
table= new QString(className);
attributes = new QList<PersistentAttribute *>();
}



void Persistentobject::addAttribute(PersistentAttribute * attribute)
{
    attributes->append(attribute);
}


int Persistentobject::save(QSqlDatabase *db)
{
    QSqlQuery query(*db);
    if(attributes->isEmpty())
    {
        std::cout<<"No value in line";
        return 0;
    }

    QString create_table=QString("CREATE TABLE IF NOT EXISTS ")+=QString("Livre")+=QString("(Titre text NOT NULL,Auteur text NOT NULL, ISBN integer NOT NULL unique primary key, Annee integer NOT null);");
    if(!query.exec(create_table))
    {
        std::cout<<"Error creating table"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    QString add_object_to_table=QString("INSERT INTO Livre(Titre,Auteur,ISBN,Annee) VALUES('A historia sem fim','Michael Ende',3522128001,1979);");

    if(!query.exec(add_object_to_table))
    {
        std::cout<<"Error executing query"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

//    query.prepare("insert into Livre(" + attributes->first()->name +") values (" + pointer_to_qstring(attributes->first()->data) + ") ;");

//    if(!query.exec())
//    {
//        std::cout<<"Error executing query"<<std::endl;
//        qDebug()<<query.lastError();
//        return 0;
//    }
    return 1;
}
