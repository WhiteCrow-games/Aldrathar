#ifndef CRIATURA_H
#define CRIATURA_H

#include "Entidad.h"


class Criatura : public Entidad
{

protected:

    int ataque;


public:

    Criatura(
        string n,
        int v,
        int a
    );


    int getAtaque();

};


#endif
