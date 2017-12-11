#include "persistentobject.h"


Persistentobject::Persistentobject(QString className)
{
table= new QString(className);
attributes = new QList<PersistentAttribute *>();
newtable_structure = new QString("");
}



void Persistentobject::addAttribute(PersistentAttribute * attribute)
{
    //TODO
    //    if(dontexist)
    {
    attributes->append(attribute);
    }
    // ecrase

}


int Persistentobject::save(QSqlDatabase *db)
{
    QSqlQuery query(*db);
    if(attributes->isEmpty()||attributes->first()->data==nullptr)
    {
        std::cout<<"No value in line";
        return 0;
    }


    QString create_table=QString("CREATE TABLE IF NOT EXISTS ")+*table+*newtable_structure+QString(";");
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
        std::cout<<"Error adding element to table"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    return 1;
}


QString Persistentobject::getTable()
{
    return *table;
}

