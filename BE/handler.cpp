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
    objects->insert(index,object);
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
    objects->clear();



    //Lecture BD
    db->open();
    QSqlQuery query(*db);

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


    QString getTable=QString("select * from ")+tableName;// Change 'Livre'
    if(!query.exec(getTable))
    {
        std::cout<<"Error getting table!"<<std::endl;
        qDebug()<<query.lastError();
        return;
    }
    QSqlRecord rec=query.record();
    int index=0;
    while(query.next())
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

        tempObj->addFromDatabase(db);
        addObject(index,tempObj);
        index+=1;
        delete tempObj;

        //std::cout<< query.value(0).toString().toStdString()<<QString(" | ").toStdString() <<query.value(1).toString().toStdString() << QString(" | ").toStdString() <<query.value(2).toString().toStdString() << QString(" | ").toStdString()<<query.value(3).toString().toStdString();

    }




    db->close();

}



void Handler::setDatabaseName(QString newDatabaseName)
{
    db->setDatabaseName(newDatabaseName);
}

QString Handler::getDatabaseName()
{
    return db->databaseName();
}
