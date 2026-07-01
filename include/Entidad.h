 
#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <iostream>
#include <string>
using namespace std;

class Entidad{
        protected:
                string nombre;
                int ataque;
                int vida;
                int defensa;
                int velocidad;
                float peso;
		float altura;
                int edad;
                int nivel;
		int magia;
        public:
              Entidad(string n, int a, int v, int d, int vel, float p, float al, int e, int l, int mgi);

                string getNombre();
                int getAtaque();
                int getVida();
                int getDefensa();
                int getVelocidad();
                float getPeso();
		float getAltura();
                int getEdad();
                int getLvl();
		int getMana();
		int getMagia();

                void atacar(string nombre_);
                void recibirDanio(int cantidad);
                void mostrarDatosMenu();
                void mostrarDatos();
                void name();
		void morir();
        };

#endif
