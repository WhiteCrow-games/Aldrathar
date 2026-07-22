#ifndef GOBLIN_H
#define GOBLIN_H

#include "Criatura.h"


class Goblin : public Criatura
{
private:
	string region;

public:

    Goblin(
        string n,
	string e,		// Criatura
		string r,
        int v,
        int a

    );
string getRegion();

};


#endif
