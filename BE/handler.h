#ifndef HANDLER_H
#define HANDLER_H

#include <QtSql>
#include <QList>
#include <iostream>
#include "persistentobject.h"
#include "livre.h"

class Handler
{
public:
    Handler(QString );
    ~Handler();

    void setDatabaseName(QString );
    QString getDatabaseName();


    void saveTable();
    void addObject(int index, Persistentobject *);
    void addObject(Persistentobject * object);
    void removeObject(int index);
    void clearObjects();
    void updateObject(int index, Persistentobject *);
    void readDatabase();

    void setTypeDB(Persistentobject::Types);
    Persistentobject::Types getTypeDB();

    QList<Persistentobject *> * getObjectList();
    QList<Persistentobject *> * objects;

    Persistentobject * newObject();
private:

    QSqlDatabase * db;
    Persistentobject::Types typeDB = Persistentobject::Types::noType;
};

#endif // HANDLER_H
