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

    QString pointer_to_qstring(void *ptr)
    {
        std::ostringstream oss;
        oss << std::setw(8) << std::setfill('0') << std::hex << ptr;
        return QString(oss.str().c_str());
    }

private:
    QList<PersistentAttribute *> * attributes;
    QString *table;
    int id;
};

#endif // PERSISTENTOBJECT_H
