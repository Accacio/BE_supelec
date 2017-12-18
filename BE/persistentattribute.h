#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <QVariant>
class PersistentAttribute
{
public:
    PersistentAttribute(QString *, QVariant::Type,void *);

    QString getName();
    QVariant::Type getType();
    void * getData();

private:
    QString name;
    QVariant::Type type;
    void *data;
};

#endif // PERSISTENTATTRIBUTE_H
