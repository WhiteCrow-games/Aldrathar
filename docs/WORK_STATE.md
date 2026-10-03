# ALDRATHAR — CURRENT WORK STATE

## Version
0.0.5

## Phase
Prototipo inicial / infraestructura

## Current Objective
Establecer una base de desarrollo reproducible y portable para el demo visual.

## Completed

- CMake configurado para C++20.
- Clang 21.1.8 verificado.
- Ninja verificado.
- SFML 3.1.0 verificado.
- Build limpio mediante CMake + Ninja.
- Proyecto original de gameplay conservado.
- Estructura Git existente conservada.

## Current Build

```bash
cmake -S . -B build -G Ninja
ninja -C build
