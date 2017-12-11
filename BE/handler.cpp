#include "handler.h"
#include <iostream>

Handler::Handler(QString database_name)
{
    db = new QSqlDatabase();
    *db= QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName(database_name);

    objects = new QList<Persistentobject *>();



}
void Handler::save_table()
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


void Handler::removeObject(int index)
{
    if(objects->isEmpty()||index>objects->size()||index<0)
    {
        std::cout<<"Error removing element, index exceeds dimensions."<<std::endl;
    }

    else
    {
        objects->removeAt(index);
    }
}


void Handler::updateObject(int index, Persistentobject * object)
{
    if(objects->at(index)->getTable()!=object->getTable())
    {
        std::cout<<"Error updating element, element is of different type."<<std::endl;
    }

    else
    {
        objects->replace(index,object);
    }
}
