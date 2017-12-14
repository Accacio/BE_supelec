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
    std::cout<<" >>>>>>>>>> Persistentobject::save >>>>>>>>>> "<<std::endl;
    std::cout<<" Saving object:"<<std::endl;
    qDebug()<<print();

    QSqlQuery query(*db);
    std::cout<<"Query created"<<std::endl;
//    if(attributes->isEmpty())
//    {
//        std::cout<<"No value in line";
//        return 0;
//    }


    std::cout<<"Query created"<<std::endl;
//    qDebug()<<*table;

//    QString create_table=QString("CREATE TABLE IF NOT EXISTS ")+*table+*newtable_structure+QString(";");
    QString create_table=QString("CREATE TABLE IF NOT EXISTS ");
    std::cout<<"string create_table created 1/3"<<std::endl;

    create_table=create_table+this->getTable();
    std::cout<<"string create_table created 2/3"<<std::endl;
    create_table=create_table+*newtable_structure+QString(";");

    std::cout<<"string create_table created 3/3"<<std::endl;
    if(!query.exec(create_table))
    {
        std::cout<<"Error creating table!"<<std::endl;
        qDebug()<<query.lastError();
        return 0;
    }

    std::cout<<"Create Table Query executed"<<std::endl;

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

    std::cout<<" <<<<<<<<<< Persistentobject::save <<<<<<<<<< "<<std::endl;
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
        return QString::number(*((int *)attribute->getData()));
    }

    if(attribute->getType()==QVariant::Type::LongLong)
    {
        return QString::number(*((qint64 *)attribute->getData()));
    }



    return QString("");
}

QString Persistentobject::getDataFromAttribute(PersistentAttribute * attribute)
{
    if(attribute->getType()==QVariant::Type::String)
    {
        return *((QString *)attribute->getData());
    }

    if(attribute->getType()==QVariant::Type::Int)
    {
        return QString::number(*((int *)attribute->getData()));
    }

    if(attribute->getType()==QVariant::Type::LongLong)
    {
        return QString::number(*((qint64 *)attribute->getData()));
    }



    return QString("");
}



QString Persistentobject::getTable()
{
    return *table;
}

void Persistentobject::addFromDatabase(QSqlQuery * query)
{
    std::cout<<" >>>>>>>>>> Persistentobject::addFromDatabase >>>>>>>>>> "<<std::endl;
    std::cout<<" <<<<<<<<<< Persistentobject::addFromDatabase <<<<<<<<<< "<<std::endl;
}


QString Persistentobject::print()
{
    QString insert_data=QString("");

    for (QList<PersistentAttribute *>::iterator it=this->attributes->begin();it != attributes->end();++it)
    {
        insert_data+=this->getData(*it);

        if((it+1)!=this->attributes->end())
        {

            insert_data+=QString(" | ");
        }
    }

    std::cout<<"PrintData:"<<std::endl;

    return insert_data;
}

QList<PersistentAttribute *> * Persistentobject::getAttributes()
{
    return attributes;
}
