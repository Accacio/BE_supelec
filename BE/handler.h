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
    void removeObject(int index);
    void updateObject(int index, Persistentobject *);
    void readDatabase();

private:
    QList<Persistentobject *> * objects;
    QSqlDatabase * db;
    Persistentobject::Types typeDB = Persistentobject::Types::noType;
};

#endif // HANDLER_H
