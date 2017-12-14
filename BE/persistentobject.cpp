#include "persistentobject.h"




Persistentobject::Persistentobject(QString className)
{
table= new QString(className);
attributes = new QList<PersistentAttribute *>();
newtable_structure = new QString("");
objectStructure=new QStringList();
}

Persistentobject::~Persistentobject()
{
    delete table;
    delete attributes;
    delete newtable_structure;
    delete objectStructure;
}

void Persistentobject::addAttribute(int index,PersistentAttribute * attribute)
{
    attributes->insert(index,attribute);
}

void Persistentobject::updateAttribute(int index, PersistentAttribute * attribute)
{
//    if(attributes->at(index)->getType()!=attribute->getType())
//    {
//        std::cout<<"Error updating attribute, attribute is of different type!"<<std::endl;
//    }

//    else
//    {
        attributes->replace(index,attribute);
//    }
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

        insert_data+=getData(*it);

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


QString Persistentobject::getData(PersistentAttribute * attribute)
{
    if(attribute->getType()==QVariant::Type::String)
    {
        return QString("'")+*((QString *)attribute->getData())+QString("'");
    }

    if(attribute->getType()==QVariant::Type::Int)
    {
        return QString::number(*((unsigned int *)attribute->getData()));
    }

    return QString("");
}




QString Persistentobject::getTable()
{
    return *table;
}

void Persistentobject::addFromDatabase(QSqlQuery * query)
{
    std::cout<<"==============addFromDatabase - Base============"<<std::endl;
    std::cout<<"==============addFromDatabase - Base============"<<std::endl;
}


QString Persistentobject::print()
{
    std::cout<<"==============print============"<<std::endl;
    QString insert_data=QString("");

    for (QList<PersistentAttribute *>::iterator it=attributes->begin();it != attributes->end();++it)
    {
        insert_data+=getData(*it);

        if((it+1)!=attributes->end())
        {

            insert_data+=QString(" | ");
        }
    }

    std::cout<<"PrintData"<<std::endl;
    std::cout<<"==============print============"<<std::endl;
    return insert_data;
}

QList<PersistentAttribute *> * Persistentobject::getAttributes()
{
    return attributes;
}
