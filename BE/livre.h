#ifndef LIVRE_H
#define LIVRE_H

#include "persistentobject.h"

class Livre : public Persistentobject
{
public:
    Livre();

    void addFromDatabase(QSqlQuery * );
    bool attributesNoValue();
    void updateAttributeData(int , QString );

};

#endif // LIVRE_H

