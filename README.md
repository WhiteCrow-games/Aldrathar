# Aldrathar

**Retro Survival Horror Engine**

Aldrathar es un proyecto de motor de juego en desarrollo,
con el objetivo de construir progresivamente una experiencia
de supervivencia y exploración con estética retro.

## Estado actual

Prototipo visual 3D en desarrollo.

El proyecto cuenta con una estructura inicial para el motor,
el juego y el renderizado. La prioridad actual es consolidar
una base funcional y desarrollar la primera demostración visual.

## Tecnologías oficiales

- C++20
- raylib: gráficos, ventana y entrada
- CMake: configuración de compilación
- Ninja: generador de compilación recomendado
- GLM: matemáticas
- nlohmann-json: manejo de JSON

**raylib es la biblioteca gráfica oficial del proyecto.**
SFML pertenece a una etapa anterior y no debe mezclarse
con la implementación actual.

## Entorno de desarrollo

El desarrollo inicial se realiza en Android mediante Termux.
La arquitectura debe mantenerse portable para facilitar
una futura migración a PC.

## Compilación

Con las dependencias instaladas:

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

Para ejecutar el programa:

```bash
./build/Aldrathar
```

Los comandos pueden requerir ajustes según el sistema
y la instalación de las dependencias.

## Documentación

- [Instrucciones para asistentes de IA](AGENTS.md)
- [Decisiones técnicas](docs/DECISIONS.md)

## Filosofía de desarrollo

Priorizar cambios pequeños, código comprensible y pruebas
reproducibles. Las nuevas funcionalidades deben responder
a objetivos definidos y no introducir complejidad prematura.
