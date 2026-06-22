 
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
                int edad;
                int nivel;
        public:
              Entidad(string n, int a, int v, int d, int vel, float p, int e, int l);

                string getNombre();
                int getAtaque();
                int getVida();
                int getDefensa();
                int getVelocidad();
                float getPeso();
                int getEdad();
                int getLvl();

                void atacar(string nombre_);
                void recibirDanio(int cantidad);
                void mostrarDatosMenu();
                void mostrarDatos();
                void name();

        };

#endif
