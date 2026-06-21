#include <iostream>
#include "Personaje.h"
#include "Enemigo.h"
#include "Entidad.h"

using namespace std;

	void limpiarPantalla(){
		system("clear");
}

	int main(){
//-----------------------------------edad-pv--pa--nivel---
    Personaje personaje1("Atheon",136, 39, 56, 1.97 ,26,"Cristals",26);
//    Personaje personaje2("Georgina","Yellow", 20, 120, 46, 27);  //mago
  //  Personaje personaje3("Mirceades", "Torres", 56,145, 67, 48); // Chinobi nivel56
 // Personaje personaje4("Aurelian", "Valedorn",78, 150,95, 67); //principe, hijo de la nivel 15
// Héroes
   // Personaje personaje5("Ragnar","Bloodfang",45,220,70, 10);
    Personaje personaje6("Leon",128,32,180,1.90, 80,"Brightblade", 19);

// Héroes - Arqueros
    //Personaje personaje7("Elena","Stormwind",21,130,120, 24);
// Héros - Asesinos
 //   Personaje personaje8("Kai","Whisperblade",30,140,150, 14);

  
// Villanos - Guerreros
   // Personaje personaje9("Tharok","Ironfist",41,210,65,25);
   // Personaje personaje10("Hector","Darkshield",35,190,80, 22); .

    //-----------------------------------------

    Enemigo enemigo[8] = {
       Enemigo("🐉 Dragon", 500, 200),
       Enemigo("🧌 Goblin", 50, 26),
       Enemigo("💀 Caminante", 75, 35),
       Enemigo("🪽 Arpia", 85, 46),
       Enemigo("🐺 Licantropo", 95, 56),
       Enemigo("☠️ Caminante toxico", 145, 54),
       Enemigo("🗿 Golem de piedra" ,300, 120),
       Enemigo("🎃 Mandragora Gigante",115, 47)
       };
       //-----------------------------------------
   cout << "-----------Sistema de juego ------------\n" << endl;
   cout << "Lista Heroes: " << endl;
   personaje1.mostrarDatos();
   personaje2.mostrarDatos();
   personaje3.mostrarDatos();
//   personaje4.mostrarDatos();
//   personaje5.mostrarDatos();
//   personaje6.mostrarDatos();
//   personaje7.mostrarDatos();
//   personaje8.mostrarDatos();
//   personaje9.mostrarDatos();
//   personaje10.mostrarDatos();
   cout << "\n Selecciona tu heroe: " << endl;
   Personaje *heroActual = nullptr; //creacion de puntero
   int seleccion;
   cin >> seleccion;
       switch(seleccion){
       case 1:
               heroActual = &personaje1; //Cazador
           break;
       case 2:
               heroActual = &personaje6;  //mago
           break;
//       case 3:
 //              heroActual = &personaje3; //Chinobi
           break;
   //    case 4:
      //         heroActual = &personaje4;
     //      break;
 //      case 5:
   //            heroActual = &personaje5;
     //      break;
  //     case 6:
    //           heroActual = &personaje6; //Cazador
      //     break;
 //      case 7:
    //           heroActual = &personaje7;  //mago
  //         break;
      // case 8:
      //         heroActual = &personaje8; //Chinobi
    //       break;
      // case 9:
        //       heroActual = &personaje9;
          // break;
      // case 10:
        //       heroActual = &personaje10;
          // break;
       }
	   limpiarPantalla();
   Enemigo *objetivoActual = nullptr;
	   cout << "tu personaje es: " << endl;
   if(heroActual != nullptr){
       heroActual->mostrarDatos();}
    else{
       cout<< "no valido" << endl;
    }
		limpiarPantalla();

  	   cout << "Selecciona tu oponente: " << endl;
   for(int i = 0; i < 8; i++){
   	   cout << i+1 << "  -------------------------------------\n" <<endl;
    enemigo[i].mostrarDatosMenu();
};
   int b;
   cin >> b;
        switch(b){
        case 1:
            objetivoActual = &enemigo[0];
        break;
        case 2:
            objetivoActual = &enemigo[1];
        break;
        case 3:
            objetivoActual = &enemigo[2];
        break;
        case 4:
            objetivoActual = &enemigo[3];
        break;
        case 5:
            objetivoActual = &enemigo[4];
        break;
        case 6:
            objetivoActual = &enemigo[5];
        break;
        case 7:
            objetivoActual = &enemigo[6];
        break;
        case 8:
            objetivoActual = &enemigo[7];
        break;
        }
        if(objetivoActual != nullptr){
            objetivoActual->getNombre();
        }
       else{
cout << "no valido." << endl;
       }
       limpiarPantalla();
      cout << "\n------------Iniciar combate------------" << endl;

    int turno = 1;

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
