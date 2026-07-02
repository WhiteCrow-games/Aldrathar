#ifndef GOBLIN_H
#define GOBLIN_H

#include "Entidad.h"

class Goblin : public Entidad {
private:
    string tipo;

public:
    Goblin(
        string t,	//tipo-goblin
        string n,
        int v,
        int a,
        int d,
        int vel,
        float p,
        float al,
	int i,
        int e,
        int l,
	int mgi
    );

    string getTipo();
};

#endif

