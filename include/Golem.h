#ifndef GOLEM_H
#define GOLEM_H

#include "Entidad.h"

	class Golem : public Entidad{
	private:
		string elemento;
		string material;
		string cristal;
	public:
	Golem(
	string ele,
	string n,
	string m,
	string c,
	int v,
	int a,
	int d,
	int  vel,
	float p,
	float al,
	int i,
	int e,
	int l,
	int mgi
	);

	string getElemento();
	string getMaterial();
	string getCristal();

};
#endif
