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
        string p,   //+add humano
	int v
	int x,
	int y,
	char s
    );


    string getProfesion();

};


#endif

