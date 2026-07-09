#ifndef HUMANO_H
#define HUMANO_H

#include "Entidad.h"


class Humano : public Entidad
{

private:

    string profesion;


public:

    Humano(
        string n,
        int v,
        string p
    );


    string getProfesion();

};


#endif
