#ifndef GOBLIN_H
#define GOBLIN_H

#include "Entidad.h"

class Goblin : public Entidad {
private:
    string tipo;
    float altura;

public:
    Goblin(
        string t,
        string n,
        int v,
        int a,
        int d,
        int vel,
        float p,
        float al,
        int e,
        int l
    );

    string getTipo();
    float getAltura();
};

#endif

