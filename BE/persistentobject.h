#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include "persistentattribute.h"

class Persistentobject
{
public:
    Persistentobject(QString className);
    void addAtribute(PersistentAttribute *);
    int save();


private:
    QList<PersistentAttribute *> * attributes;
    QString *table;
    int id;
};

#endif // PERSISTENTOBJECT_H
