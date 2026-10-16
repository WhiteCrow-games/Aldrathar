# Decisiones técnicas de Aldrathar

## DEC-001: Motor gráfico principal

- Estado: Aprobada
- Fecha: 2026-10-16
- Motor oficial: raylib
- Lenguaje: C++20
- Sistema de construcción: CMake
- Generador de construcción recomendado: Ninja

### Decisión

Aldrathar utilizará raylib como biblioteca principal para
ventanas, entrada, gráficos y renderizado.

El prototipo actual utiliza raylib para representar interiores
en 3D con cámara en perspectiva.

### Motivos

- Permite desarrollar gráficos 2D y 3D.
- Es apropiado para construir progresivamente un prototipo
  visual y experimentar con distintas perspectivas.
- Se puede utilizar desde C++ y mantener un proyecto basado
  en CMake.
- Encaja con el entorno inicial de desarrollo en Termux
  y con el objetivo de portar el proyecto a PC.

### Tecnologías complementarias

- GLM: operaciones matemáticas y tipos auxiliares cuando
  sean necesarios.
- nlohmann-json: lectura y escritura de datos JSON cuando
  sean necesarias.

Estas bibliotecas no sustituyen a raylib como biblioteca
gráfica principal.

### Relación con SFML

SFML se utilizó en una etapa anterior del proyecto.
No es el motor gráfico principal de la versión actual.

El código heredado de SFML no debe incorporarse al prototipo
raylib sin una decisión explícita y una revisión técnica.

### Revisión de la decisión

Solo se cambiará el motor mediante una decisión documentada,
con sus motivos, consecuencias y tareas de migración.

No se cambiará por iniciativa de un asistente de IA sin
autorización del responsable del proyecto.
