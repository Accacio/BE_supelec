#ifndef HANDLER_H
#define HANDLER_H

#include <QtSql>
#include <QList>
#include "persistentobject.h"

class Handler
{
public:
    Handler(QString database_name);
    void save_table();
    void addObject(int index, Persistentobject *);
    void removeObject(int index);
    void updateObject(int index, Persistentobject *);
private:
    QList<Persistentobject *> * objects;
    public:
    QSqlDatabase * db;
};

#endif // HANDLER_H
