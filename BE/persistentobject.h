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


    void addAttribute(PersistentAttribute *);
    PersistentAttribute getAttribute(QString name);
    int save(QSqlDatabase * db);
    QString getTable();

protected:
    QString *newtable_structure;
    QString *table;
    Persistentobject(QString className);

private:
    QList<PersistentAttribute *> * attributes;
    int id;
};

#endif // PERSISTENTOBJECT_H
