#include "persistentattribute.h"

PersistentAttribute::PersistentAttribute(QString * attribute_name, QVariant::Type attribute_type, void * attribute_data)
{
    name = *attribute_name;
    type = attribute_type;
    data = attribute_data;

}


QString PersistentAttribute::getName()
{
    return name;
}

QVariant::Type PersistentAttribute::getType()
{
    return type;
}
void * PersistentAttribute::getData()
{
    return data;
}
