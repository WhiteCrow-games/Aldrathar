#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
using namespace std;

class Entidad{
        protected:
                string nombre;
                int ataque;
		int vida;
                int defensa;
                int velocidad;
                float peso;
                int edad;
        public:
                Entidad(sting n, int a, int v, int d, int vl, float p, int e);

                string getNombre();
                int getAtaque();
		int getVida();
                int getDefensa();
                int getVelocidad();
                float getPeso();
                int getEdad();
        	void atacar(string nombre_);
		void recibirDanio(int cantidad);
		void mostrarDatosMenu();
		void name();
		void mostarDatos();

	};

#endif
