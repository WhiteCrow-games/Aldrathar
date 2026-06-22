#ifndef HUMANO_H
#define HUMANO_H

#include "Entidad.h"
#include <iostream>
using namespace std;


  class Humano : public Entidad {
    private:
        string apellido;
        float altura;
        string prof;

    public:
        Humano(string n,string ap, string pr, int a, int v, int d, int vel, float p, float al, int e, int l);

    string getApellido();
    float getAltura();
    string getProf();
};

#endif
