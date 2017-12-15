#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include "persistentattribute.h"
#include <QtSql>
#include <QList>
#include <iostream>
#include <sstream>
#include <iomanip>


class Persistentobject
{
public:

    QString getTable();
    virtual ~Persistentobject();

    QList<PersistentAttribute *> * getAttributes();
    int save(QSqlDatabase * db);
    void addAttribute(int ,PersistentAttribute *);
    void updateAttribute(int , PersistentAttribute * );
    virtual void addFromDatabase(QSqlQuery * );
    QString print();

    QStringList * objectStructure;

    enum Types
    {
        noType=0,
        Livre
    };
    QString getData(PersistentAttribute * );
    QString getDataFromAttribute(PersistentAttribute * attribute);
    virtual bool attributesNoValue();
    virtual void updateAttributeData(int , QString data);
protected:
    QString *newtable_structure;
    QString *table;
    Persistentobject(QString className);
    QList<PersistentAttribute *> * attributes;

private:

    int id;
};

#endif // PERSISTENTOBJECT_H
