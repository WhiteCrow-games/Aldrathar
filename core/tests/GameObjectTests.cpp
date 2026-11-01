#include "aldrathar/objects/GameObject.hpp"

#include <iostream>

using namespace Aldrathar;

bool Check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "[FALLO] " << message << '\n';
        return false;
    }

    return true;
}

int main() {

    GameObject object;

    // Prueba 1: posicion inicial
    if (!Check(object.GetPosition().x == 0.0F, "Posicion inicial X")) return 1;
    if (!Check(object.GetPosition().y == 0.0F, "Posicion inicial Y")) return 1;
    if (!Check(object.GetPosition().z == 0.0F, "Posicion inicial Z")) return 1;

    // Prueba 2: establecer posicion
    object.SetPosition({10.0F, 5.0F, 3.0F});

    // Prueba 3: comprobar posicion
    if (!Check(object.GetPosition().x == 10.0F, "Asignacion X")) return 1;
    if (!Check(object.GetPosition().y == 5.0F, "Asignacion Y")) return 1;
    if (!Check(object.GetPosition().z == 3.0F, "Asignacion Z")) return 1;

    // Prueba 4: actualizar posicion
    object.SetPosition({2.0F, 4.0F, 6.0F});

    if (!Check(object.GetPosition().x == 2.0F, "Actualizacion X")) return 1;
    if (!Check(object.GetPosition().y == 4.0F, "Actualizacion Y")) return 1;
    if (!Check(object.GetPosition().z == 6.0F, "Actualizacion Z")) return 1;

    std::cout << "[OK] Todas las pruebas de GameObject pasaron.\n";

    return 0;
}
