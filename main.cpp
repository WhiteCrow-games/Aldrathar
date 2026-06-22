#include "Goblin.h"
#include "Humano.h"
#include "Entidad.h"

using namespace std;

        void limpiarPantalla(){
                system("clear");
}

        int main(){
//---------------     -nonbre--apellido-profecion--ataque-vid--def-vel-altura--peso-edad--lvl--
    Humano humano1("Atheon","Cristals", "Guerrero", 136, 100, 67, 7, 189.5, 58.7, 35, 26);
    Humano humano2("Rose","Mor", "Guerrero", 110, 100, 61, 6, 150.5, 48.7, 25, 16);



    //-----------------------------------------
//                     tipo      nombre     a    v   d   v  p    al    e   lvl
    Goblin goblin[2] = {
    Goblin("Goblin", "de Montaña", 35, 190, 45, 5, 45.8, 1.23, 16, 5),
    Goblin("Goblin", "de Pantano", 35, 170, 45, 5, 45.8, 1.23, 16, 5)
};

       //-----------------------------------------
   cout << "-----------Sistema de juego ------------\n" << endl;
   cout << "Lista Heroes: " << endl;
   cout << "\n Selecciona tu heroe: " << endl;
  cout << "1. ";
humano1.mostrarDatosMenu();

cout << "\n2. ";
humano2.mostrarDatosMenu();
  Humano *heroActual = nullptr; //creacion de puntero
   int seleccion;

   cin >> seleccion;
       switch(seleccion){
       case 1:
               heroActual = &humano1;
           break;
       case 2:
               heroActual = &humano2;
           break;
       }
           limpiarPantalla();
   Goblin *objetivoActual = nullptr;
           cout << "tu personaje es: " << endl;
   if(heroActual != nullptr){
       heroActual->mostrarDatos();}
    else{
       cout<< "no valido" << endl;

       cin.get();
       cin.get();
    }
                limpiarPantalla();

           cout << "Selecciona tu oponente: " << endl;
   for(int i = 0; i < 2; i++){
           cout << i+1 << "  -------------------------------------\n" <<endl;
    goblin[i].mostrarDatosMenu();
}
   int b;
   cin >> b;
        switch(b){
        case 1:
            objetivoActual = &goblin[0];
        break;
        case 2:
            objetivoActual = &goblin[1];
        break;
        }
    
       limpiarPantalla();
      cout << "\n------------Iniciar combate------------" << endl;

    int turno = 1;
   if(heroActual == nullptr || objetivoActual == nullptr){
    cout << "Seleccion invalida." << endl;
    return 0;
}
    while (heroActual->getVida() > 0 && objetivoActual->getVida() > 0) {
        cout << "\n---------------Turno " << turno <<  "----------------\n" << endl;
        heroActual->atacar(objetivoActual->getNombre());
        objetivoActual->recibirDanio(heroActual->getAtaque());

       if (objetivoActual->getVida() <= 0) {
            cout << objetivoActual->getNombre() << " ha sido derrotado." << endl;
            break;
            }
       objetivoActual->atacar(heroActual->getNombre());
       heroActual->recibirDanio(objetivoActual->getAtaque());

       if (heroActual->getVida() <= 0) {
            cout << heroActual->getNombre() << " ha sido derrotado." << endl;
            break;
        }

       cout << "Vida de " << heroActual->getNombre() << ": " << heroActual->getVida() << endl;

       cout << "Vida de " << objetivoActual->getNombre() << ": " << objetivoActual->getVida() << endl;

        turno++;
       }

   return 0;
   }
