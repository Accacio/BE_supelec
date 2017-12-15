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

    if(objects->isEmpty())
    {
       std::cout<<"No Object"<<std::endl;
       return;
    }


    std::cout<<" >>>>>>>>>> Handler::saveTable >>>>>>>>>> "<<std::endl;
    if(!db->open())
    {
        std::cout<<"Error: "<< db->databaseName().toStdString() << "not found"<<std::endl;
        return;
    }

    std::cout<<"Database Opened."<<std::endl;


    QSqlQuery query(*db);

    if(!query.exec(QString("DROP TABLE IF EXISTS ")+objects->at(0)->getTable()))
    {
        std::cout<<"Error deleting table!"<<std::endl;
        qDebug()<<query.lastError();
        return;
    }




    for (int i=0;i < objects->size();++i)
    {
        objects->at(i)->save(db);
        std::cout<<"Object Saved"<<std::endl;
    }


//    for (QList<Persistentobject *>::iterator it=objects->begin();it != objects->end();++it)
//    {
//        (*it)->save(db);
//        std::cout<<"Object Saved"<<std::endl;
//    }

    db->close();
    std::cout<<"Database Closed."<<std::endl;

    std::cout<<" <<<<<<<<<< Handler::saveTable <<<<<<<<<< "<<std::endl;
}

void Handler::addObject(int index, Persistentobject * object)
{
    std::cout<<" >>>>>>>>>> Handler::addObject >>>>>>>>>> "<<std::endl;
    objects->insert(index,object);
    std::cout<<"==============print============"<<std::endl;
    qDebug()<<objects->at(index)->print();
    std::cout<<"==============print============"<<std::endl;
    std::cout<<" <<<<<<<<<< Handler::addObject <<<<<<<<<< "<<std::endl;
}

void Handler::addObject(Persistentobject * object)
{
    std::cout<<" >>>>>>>>>> Handler::addObject >>>>>>>>>> "<<std::endl;
    objects->append(object);
    std::cout<<"============== appended object ============"<<std::endl;
    qDebug()<<objects->at(objects->size()-1)->print();
    std::cout<<"============== appended object ============"<<std::endl;
    std::cout<<" <<<<<<<<<< Handler::addObject <<<<<<<<<< "<<std::endl;
}

void Handler::updateObject(int index, Persistentobject * object)
{
    std::cout<<" >>>>>>>>>> Handler::updateObject >>>>>>>>>> "<<std::endl;
    if(objects->at(index)->getTable()!=object->getTable())
    {
        std::cout<<"Error updating element, element is of different type!"<<std::endl;
    }

    else
    {
        objects->replace(index,object);
    }
    std::cout<<" <<<<<<<<<< Handler::updateObject <<<<<<<<<< "<<std::endl;
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
    std::cout<<" >>>>>>>>>> Handler::readDatabase >>>>>>>>>> "<<std::endl;
    //this->objects->clear();
    std::cout<<"Objects cleared"<<std::endl;


    //Lecture BD
    db->open();
    QSqlQuery * query = new QSqlQuery(*db);

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
    Persistentobject * tempObj = newObject();

//        std::cout<<"Table of tempObj"<<std::endl;
//        qDebug()<<tempObj->getTable();

        tempObj->addFromDatabase(query);
        std::cout<<"tempobj created from database"<<std::endl;
        qDebug()<<tempObj->print();

        std::cout<<"tempobj printed"<<std::endl;
        this->addObject(tempObj);




        std::cout<<" !!!!!!!!! Objects after appending(outside loop)"<<std::endl;
        for(int i=0;i<this->objects->size();i++)
        {
            qDebug()<<this->objects->at(i)->print();
        }



        std::cout<<"tempobj added to objects"<<std::endl;
        std::cout<<"Contents of the object:"<<std::endl;
        qDebug()<<this->objects->at(this->objects->size()-1)->print();

        /*std::cout<<"Table of tempObj in objects before delete"<<std::endl;
        qDebug()<<objects->at(objects->size()-1)->getTable();
*/
  //      delete tempObj;
  /*      std::cout<<"Table of tempObj in objects after delete"<<std::endl;
        qDebug()<<objects->at(objects->size()-1)->getTable();*/
        index+=1;



        //std::cout<< query.value(0).toString().toStdString()<<QString(" | ").toStdString() <<query.value(1).toString().toStdString() << QString(" | ").toStdString() <<query.value(2).toString().toStdString() << QString(" | ").toStdString()<<query.value(3).toString().toStdString();

    }
    std::cout<<"Table of tempObj in objects after delete (outside loop)"<<std::endl;
    qDebug()<<objects->at(index-1)->getTable();

    std::cout<<"Objects (outside loop)"<<std::endl;
    for(int i=0;i<objects->size();i++)
    {
        qDebug()<<objects->at(i)->print();
    }


    delete query;

    db->close();

    std::cout<<" <<<<<<<<<< Handler::readDatabase <<<<<<<<<< "<<std::endl;
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

void Handler::clearObjects()
{
    objects->clear();
}

void Handler::setTypeDB(Persistentobject::Types newTypeDB)
{
    typeDB=newTypeDB;
}

Persistentobject::Types Handler::getTypeDB()
{
    return typeDB;
}



Persistentobject * Handler::newObject()
{
    Persistentobject * tempObj;
    switch(typeDB)
    {
    case Persistentobject::Types::Livre:
        tempObj = new Livre();
        return tempObj;

    case Persistentobject::Types::noType:
        std::cout<<"Error! No Type defined!"<<std::endl;
    default:
        return nullptr;
    }
}
