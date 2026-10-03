v0.0.1
- Creada la clase base Entidad.
- Implementadas las clases Humano, Goblin, Dragon, Golem e Hipogrifo.
- Sistema básico de combate por turnos.
- Selección de personajes y enemigos.
- Proyecto compila correctamente.

## [0.0.2] - 2026-07-12

### Added
- Implementación inicial de la clase `Mapa`.
- Creación del sistema básico de filas y columnas.
- Implementación de matriz `char[10][20]` para representar el mundo.
- Creación del constructor de `Mapa` para inicializar el terreno.
- Implementación del método `dibujar()` para mostrar el mapa en consola.
- Integración de `Mapa` dentro de la clase `Juego`.
- El juego ahora genera y muestra un mundo básico al iniciar.

## [0.0.3] 2026-07-21

### Added

- Implementado el método "colocarElemento()" para modificar posiciones específicas del mapa.
- Se agregaron muros en los bordes utilizando algoritmos basados en filas y columnas.
- Integrado el jugador inicial ("@") dentro del mapa.
- El mapa ahora representa un escenario delimitado listo para futuras mecánicas de movimiento y exploración.
- Se implemento `seleccionarHeroe();` y `seleccionarEnemigo();` preparando funcion para combatir.
- Se creo `Juego::limpiarPantalla();` para mejor efecto visual en consola.
- creacion de  `colocarHeroe` y `colocarEnemigo`
 
 [0.0.4] -En desarrollo-

 Added
- Movimiento a heroe

## 2026-10-03

### Added

- Added the AI development protocol.
- Added current project work state documentation.

### Changed

- Migrated CMake project from C++17 to C++20.
- Updated project version to 0.0.5.
- Added SFML 3.1.0 through CMake package discovery.
- Improved CMake source and include configuration.

### Tested

- CMake configuration: PASS.
- Ninja build: PASS.
- Clang 21.1.8: PASS.
- SFML 3.1.0: PASS.
