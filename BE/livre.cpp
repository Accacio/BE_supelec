#include "livre.h"

Livre::Livre() : Persistentobject("Livre")
{
*newtable_structure=QString("(Titre text NOT NULL,Auteur text NOT NULL, ISBN integer NOT NULL, Annee integer NOT null)");

}
