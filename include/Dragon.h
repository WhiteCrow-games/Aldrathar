#ifndef DRAGON_H
#define  DRAGON_H
#include "Entidad.h"

class Dragon : public Entidad {
	private:
		string elemento;
		string subElemento;
		string tipo;
		float longitud;
	public:
			Dragon(
		string n,
		string ele, 	//dragon
		string t, 	//dragon
		string sub,	//dragon
		int v,
		int a,
		int d,
		int vel,
		float p,
		float al,
		float log,	//dragon
		int e,
		int l,
		int mgi);

	string getElemento();
	string getTipo();
	string getSub();
	float getLongitud();
};
#endif
