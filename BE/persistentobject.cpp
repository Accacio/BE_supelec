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
    QString newtable_name=*table;
    QString create_table=QString("CREATE TABLE IF NOT EXISTS ")+*table+QString("(Titre text NOT NULL,Auteur text NOT NULL, ISBN integer NOT NULL unique primary key, Annee integer NOT null);");
    if(!query.exec(create_table))
    {
        std::cout<<"Error creating table"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    QString insert_struct=QString("(");
    QString insert_data=QString("(");

    for (QList<PersistentAttribute *>::iterator it=attributes->begin();it != attributes->end();++it)
    {
        insert_struct+=(*it)->name;

        if((*it)->type==QVariant::Type::String)
        {
            insert_data+=QString("'")+*((QString *)(*it)->data)+QString("'");
        }

        if((*it)->type==QVariant::Type::Int)
        {
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

    QString add_object_to_table=QString("INSERT INTO ")+*table+insert_struct+QString("VALUES")+insert_data+QString(";");

    if(!query.exec(add_object_to_table))
    {
        std::cout<<"Error executing query"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    return 1;
}
