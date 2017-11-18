#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <QVariant>
class PersistentAttribute
{
public:
    PersistentAttribute(QString *, QVariant::Type,void *);
    QString name;
    QVariant::Type type;
    void *data;
};

#endif // PERSISTENTATTRIBUTE_H
