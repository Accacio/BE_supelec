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


//    for (QList<PersistentAttribute *>::iterator it=attributes->begin();it != attributes->end();++it)
//    {
//        std::cout<<(*it)->name.toStdString()<<" ";
//        //std::cout<<pit->type<<std::endl;
//        if((*it)->type==QVariant::Type::String)
//        {
//            std::cout<<((QString *)(*it)->data)->toStdString()<<"|"<<std::endl;
//        }
//        if((*it)->type==QVariant::Type::Int)
//        {
//            std::cout<<*((unsigned int *)(*it)->data)<<"|"<<std::endl;
//        }
//    }

    QString insert_struct=QString("(");
    QString insert_data=QString("(");
    for (QList<PersistentAttribute *>::iterator it=attributes->begin();it != attributes->end();++it)
    {
        //std::cout<<(*it)->name.toStdString()<<" ";
        insert_struct+=(*it)->name;

        //std::cout<<pit->type<<std::endl;
        if((*it)->type==QVariant::Type::String)
        {
            std::cout<<((QString *)(*it)->data)->toStdString()<<"|"<<std::endl;

            insert_data+=QString("'")+=*((QString *)(*it)->data)+=QString("'");
        }
        if((*it)->type==QVariant::Type::Int)
        {
            std::cout<<*((unsigned int *)(*it)->data)<<"|"<<std::endl;
            insert_data+=QString::number(*((unsigned int *)(*it)->data));
        }

        if((it+1)!=attributes->end())
        {
            insert_struct+=QString(",");
            insert_data+=QString(",");
        }
    }
    insert_struct+=QString(")");
    insert_data+=QString(")");

    std::cout<<insert_struct.toStdString()<<" "<<insert_data.toStdString()<<std::endl;



    QString add_object_to_table=QString("INSERT INTO Livre(Titre,Auteur,ISBN,Annee) VALUES('A historia sem fim','Michael Ende',3522128001,1979);");

    if(!query.exec(add_object_to_table))
    {
        std::cout<<"Error executing query"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }
    return 1;
}
