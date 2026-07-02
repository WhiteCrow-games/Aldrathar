  #ifndef HIPOGRIFO_H
#define HIPOGRIFO_H

#include "Entidad.h"

class Hipogrifo : public Entidad {
private:
    string colorPlumas;
    string tipoVuelo;
    float envergadura;

public:
    Hipogrifo(
        string n,
        string color,
        string vuelo,
        int v,
        int a,
        int d,
        int vel,
        float p,
        float al,
	int i,
        float env,
        int e,
        int l,
        int mgi
    );

    string getColorPlumas();
    string getTipoVuelo();
    float getEnvergadura();
};

#endif
