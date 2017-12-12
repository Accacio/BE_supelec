#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include "persistentattribute.h"
#include <QtSql>
#include <iostream>
#include <sstream>
#include <iomanip>





class Persistentobject
{
public:

    QString getTable();
    ~Persistentobject();

    PersistentAttribute getAttribute(QString name);
    int save(QSqlDatabase * db);
    void addAttribute(int index,PersistentAttribute *);
    void updateAttribute(int index, PersistentAttribute * attribute);
    void addFromDatabase(QSqlDatabase * db);


    enum Types
    {
        noType=0,
        Livre
    };

protected:
    QString *newtable_structure;
    QString *table;
    Persistentobject(QString className);

private:
    QList<PersistentAttribute *> * attributes;
    int id;
};

#endif // PERSISTENTOBJECT_H
