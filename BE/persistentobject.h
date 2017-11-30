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
    Persistentobject(QString className);

    void addAttribute(PersistentAttribute *);
    PersistentAttribute getAttribute(QString name);
    int save(QSqlDatabase * db);

private:
    QList<PersistentAttribute *> * attributes;
    QString *table;
    int id;
};

#endif // PERSISTENTOBJECT_H
