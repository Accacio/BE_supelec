#include "persistentobject.h"




Persistentobject::Persistentobject(QString className)
{
table= new QString(className);
attributes = new QList<PersistentAttribute *>();
newtable_structure = new QString("");
}

Persistentobject::~Persistentobject()
{
    delete table;
    delete attributes;
    delete newtable_structure;
}

void Persistentobject::addAttribute(int index,PersistentAttribute * attribute)
{
    attributes->insert(index,attribute);
}

void Persistentobject::updateAttribute(int index, PersistentAttribute * attribute)
{
    if(attributes->at(index)->getType()!=attribute->getType())
    {
        std::cout<<"Error updating attribute, attribute is of different type!"<<std::endl;
    }

    else
    {
        attributes->replace(index,attribute);
    }
}

int Persistentobject::save(QSqlDatabase *db)
{
    QSqlQuery query(*db);
    if(attributes->isEmpty()||attributes->first()->getData()==nullptr)
    {
        std::cout<<"No value in line";
        return 0;
    }


    QString create_table=QString("CREATE TABLE IF NOT EXISTS ")+*table+*newtable_structure+QString(";");
    if(!query.exec(create_table))
    {
        std::cout<<"Error creating table!"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    QString insert_struct=QString("(");
    QString insert_data=QString("(");

    for (QList<PersistentAttribute *>::iterator it=attributes->begin();it != attributes->end();++it)
    {
        insert_struct+=(*it)->getName();

        if((*it)->getType()==QVariant::Type::String)
        {
            insert_data+=QString("'")+*((QString *)(*it)->getData())+QString("'");
        }

        if((*it)->getType()==QVariant::Type::Int)
        {
            insert_data+=QString::number(*((unsigned int *)(*it)->getData()));
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

void Persistentobject::addFromDatabase(QSqlDatabase * db)
{
    std::cout<<"I just read the file, truste me.";
}
