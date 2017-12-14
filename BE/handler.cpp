#include "handler.h"

Handler::Handler(QString database_name)
{
    db = new QSqlDatabase();
    *db= QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName(database_name);

    objects = new QList<Persistentobject *>();

}

Handler::~Handler()
{
    delete db;
    delete objects;
}

void Handler::saveTable()
{
    if(!db->open())
    {
        std::cout<<"Error: "<< db->databaseName().toStdString() << "not found"<<std::endl;
    }

    for (QList<Persistentobject *>::iterator it=objects->begin();it != objects->end();++it)
    {
        (*it)->save(db);
    }

    db->close();

}

void Handler::addObject(int index, Persistentobject * object)
{
    std::cout<<"==============addObject - Handler============"<<std::endl;
    objects->insert(index,object);
    qDebug()<<objects->at(index)->print();
    std::cout<<"==============addObject - Handler============"<<std::endl;
}

void Handler::updateObject(int index, Persistentobject * object)
{
    if(objects->at(index)->getTable()!=object->getTable())
    {
        std::cout<<"Error updating element, element is of different type!"<<std::endl;
    }

    else
    {
        objects->replace(index,object);
    }
}

void Handler::removeObject(int index)
{
    if(objects->isEmpty()||index>objects->size()||index<0)
    {
        std::cout<<"Error removing element, index exceeds dimensions!"<<std::endl;
    }

    else
    {
        objects->removeAt(index);
    }
}


void Handler::readDatabase()
{
    std::cout<<"==============readDatabase============"<<std::endl;
    objects->clear();
    std::cout<<"Objects cleared"<<std::endl;


    //Lecture BD
    db->open();
    QSqlQuery * query = new QSqlQuery(*db);

    //TODO Choose typeDB Use Radio Button
    typeDB=Persistentobject::Types::Livre;


    QString tableName;
    switch(typeDB)
    {
    case Persistentobject::Types::Livre:
        tableName=QString("Livre");
        break;

    case Persistentobject::Types::noType:
        std::cout<<"Error! No Type defined!"<<std::endl;
        return;
    }


    QString getTable=QString("select * from ")+tableName;
    if(!query->exec(getTable))
    {
        std::cout<<"Error getting table!"<<std::endl;
        qDebug()<<query->lastError();
        return;
    }

    int index=0;
    while(query->next())
    {
    Persistentobject * tempObj;
        switch(typeDB)
        {
        case Persistentobject::Types::Livre:
            tempObj = new Livre();
            break;

        case Persistentobject::Types::noType:
            std::cout<<"Error! No Type defined!"<<std::endl;
            return;
        }

        tempObj->addFromDatabase(query);
        std::cout<<"tempobj created from database"<<std::endl;
        qDebug()<<tempObj->print();

        std::cout<<"tempobj printed"<<std::endl;
        objects->append(tempObj);

        std::cout<<"tempobj added to objects"<<std::endl;

        std::cout<<"Contents of the object:"<<std::endl;
        //qDebug()<<*(QString *)objects->at(index)->getAttributes()->at(0)->getData();
//                    addObject(index,tempObj);
        std::cout<<"tempobj added to objects"<<std::endl;

        index+=1;
        delete tempObj;

        if(!objects->isEmpty())
        {


            std::cout<<"Last object printed"<<std::endl;
            std::cout<<std::endl;
        }

        //std::cout<< query.value(0).toString().toStdString()<<QString(" | ").toStdString() <<query.value(1).toString().toStdString() << QString(" | ").toStdString() <<query.value(2).toString().toStdString() << QString(" | ").toStdString()<<query.value(3).toString().toStdString();

    }


    delete query;

    db->close();

    std::cout<<"==============readDatabase============"<<std::endl;
}



void Handler::setDatabaseName(QString newDatabaseName)
{
    db->setDatabaseName(newDatabaseName);
}

QString Handler::getDatabaseName()
{
    return db->databaseName();
}

QList<Persistentobject *> * Handler::getObjectList()
{
return objects;
}
