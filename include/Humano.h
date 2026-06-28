#ifndef HUMANO_H
#define HUMANO_H

#include "Entidad.h"
#include <iostream>
using namespace std;


  class Humano : public Entidad {
    private:
        string apellido;
        string prof;

    public:
        Humano(
		string n,
		string ap,
		string pr,
		int v,
		int a,
		int d,
		int vel,
		float p,
		float al,
		int e,
		int l,
		int mgi
			);

    string getApellido();
    string getProf();
};

#endif

