#include <string>
#include "Entidad.h"

Entidad::Entidad(string n, int a,  int v, int d, int vel, float p, float al, int i, int e, int l, int mgi
){
    nombre = n;
    ataque = a;
    vida = v;
    defensa = d;
    velocidad = vel;
    peso = p;
    altura = al;
	inteligencia = i;
    edad = e;
    nivel = l;
    magia = mgi;
}
        int Entidad::getDefensa(){
                return defensa;
        }
        float Entidad::getPeso(){
        return peso;
        }
        string Entidad::getNombre() {
        return nombre;
        }
        int Entidad::getVida() {
        return vida;
        }
        int Entidad::getVelocidad(){
        return velocidad;
        }
        int Entidad::getAtaque() {
        return ataque;
        }
        int Entidad::getEdad(){
        return edad;
        }
	int Entidad::getInteligencia(){
	return inteligencia;
	}
	float Entidad::getAltura(){
	return altura;
	}
        int Entidad::getLvl(){
        return nivel;
        }
	int Entidad::getMagia(){
	return magia;
	}
        int Entidad::getMana(){
	return inteligencia + ataque + velocidad;
	}

// metodos puros
	void Entidad::ataqueEspecial(){
		cout << "\n" << nombre << "ha usado ataque especial" << endl;
	}
	void Entidad::morir(){
		cout << "\n" << nombre << " ha muerto!!!" << endl;

}
    void Entidad::atacar(string nombre_) {
            cout << "\n-" << nombre << " ataca a " << nombre_ << endl;
}

        void Entidad::mostrarDatosMenu() {
    cout << nombre << endl;
    cout << "    Vida: " << vida << "	Atk: " << ataque
       << "\n Defensa: " << defensa << "	Lvl: " << nivel << endl;
}

        void Entidad::mostrarDatos() {
    cout << "\n" << nombre
         << " " << vida << endl;
}

        void Entidad::name() {
    cout << nombre << endl;
}

        void Entidad::recibirDanio(int cantidad) {
    vida -= cantidad;

    cout << nombre << " ha recibido "
         << cantidad << " pts de daño\n";

    if (vida <= 0) {
        vida = 0;
       morir();
    }
}
