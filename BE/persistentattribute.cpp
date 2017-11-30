#include "persistentattribute.h"

PersistentAttribute::PersistentAttribute(QString * attribute_name, QVariant::Type attribute_type, void * attribute_data)
{
    name = *attribute_name;
    type = attribute_type;
    data = attribute_data;

}
