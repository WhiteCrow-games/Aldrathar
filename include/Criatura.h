#ifndef CRIATURA_H
#define CRIATURA_H

#include "Entidad.h"


class Criatura : public Entidad
{

private:

    string especie;


public:

    Criatura(
        string n,
		string e,
        int v,
        int a
    );

  string getEspecie();

};


#endif
