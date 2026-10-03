ALDRATHAR — PROTOCOLO MAESTRO DE DESARROLLO CON IA

1. PROPÓSITO

Aldrathar es un proyecto de videojuego de desarrollo incremental.

El objetivo de este protocolo es garantizar que cualquier desarrollador humano o IA pueda continuar el proyecto desde el repositorio sin depender del contexto de conversaciones anteriores.

El repositorio es la fuente de verdad del proyecto.

Las decisiones importantes, arquitectura, estado, procedimientos y cambios deben quedar documentados dentro del repositorio.

No asumir información que no esté documentada o verificada.

---

2. OBJETIVO ACTUAL

El proyecto se encuentra en una fase temprana de prototipado.

Prioridad actual

Crear un demo visual funcional que permita validar progresivamente:

- ventana;
- renderizado;
- resolución interna;
- escalado pixelado;
- shaders;
- cámara;
- entidades visuales;
- escenarios;
- personajes;
- efectos;
- interacción básica.

El objetivo inmediato NO es implementar todo el juego final.

No implementar prematuramente:

- economía real;
- marketplace real;
- backend de producción;
- infraestructura multijugador definitiva;
- sistemas de monetización;
- blockchain;
- servidores de producción;
- sistemas complejos de genética;
- sistemas definitivos de mundo abierto;
- funcionalidades que todavía no sean necesarias para validar el demo.

Estas ideas pertenecen al diseño futuro y deben permanecer documentadas sin convertirse prematuramente en código.

---

3. PRINCIPIO FUNDAMENTAL

Construir solamente lo necesario para el siguiente objetivo verificable.

No diseñar sistemas gigantescos anticipando problemas hipotéticos.

No eliminar posibilidades futuras innecesariamente.

La arquitectura debe permitir evolución, pero la implementación debe permanecer pequeña hasta que una necesidad real justifique su expansión.

---

4. FUENTE DE VERDAD

La información válida del proyecto debe encontrarse en:

docs/
src/
include/
tests/
CMakeLists.txt

Las conversaciones con IA no son fuente permanente de verdad.

Si una decisión importante aparece durante una conversación, debe trasladarse al repositorio mediante documentación o código.

---

5. PROCESO OBLIGATORIO DE CADA SESIÓN

Toda sesión de desarrollo debe seguir este orden.

PASO 1 — Leer el estado del proyecto

Revisar:

README.md
docs/Arquitectura.md
docs/Roadmap.md
docs/CHANGELOG.md
docs/AI_DEVELOPMENT_PROTOCOL.md

Si existe documentación específica relacionada con la tarea, leerla también.

No comenzar modificando código sin conocer el estado actual.

---

PASO 2 — Revisar Git

Ejecutar:

git status
git log --oneline -10
git branch

Determinar:

- rama actual;
- cambios sin commit;
- último commit;
- último objetivo completado.

No sobrescribir cambios existentes sin comprobar su origen.

---

PASO 3 — Verificar el entorno

El desarrollo inicial se realiza en Termux sobre Android.

Comprobar las herramientas realmente disponibles:

clang++ --version
cmake --version
ninja --version

Comprobar las dependencias utilizadas por el proyecto mediante CMake.

No asumir que una biblioteca está instalada.

No asumir una API.

Verificar la versión instalada antes de utilizar características específicas.

---

6. REGLA DE NO ESPECULACIÓN

NO SPECULATION

Nunca asumir que una característica es compatible simplemente porque existe en otra versión, tutorial, motor o plataforma.

Si una API o funcionalidad es necesaria:

1. comprobar que está disponible;
2. verificar su versión;
3. probarla;
4. documentar el resultado.

Si no puede verificarse, indicarlo claramente.

No inventar funciones.

No inventar parámetros.

No inventar rutas.

No inventar capacidades de Termux.

No sustituir una prueba real por una suposición.

---

7. ENTORNO ACTUAL

El entorno inicial es:

Android
Termux
clang++
C++20
CMake
Ninja
SFML 3.x
GLM
nlohmann-json
Termux:X11

El código debe mantenerse portable.

La limitación actual de hardware debe ser considerada, pero no debe convertirse en una excusa para diseñar una arquitectura innecesariamente compleja.

---

8. PORTABILIDAD

Aldrathar comenzará en Termux.

Posteriormente podrá utilizar hardware más potente.

La evolución prevista es:

Termux / Android
       ↓
Hardware superior
       ↓
Linux / Windows
       ↓
Posible cambio de tecnología gráfica
       ↓
Posible motor o cliente diferente

El código actual debe evitar dependencias innecesarias del dispositivo.

No diseñar características para hardware futuro que todavía no sean necesarias.

---

9. ARQUITECTURA

Separar claramente:

Core
Graphics
Input
Gameplay
World
Data
Resources

No mezclar lógica de gameplay con código específico de renderizado.

Evitar acoplamiento innecesario.

Las entidades del juego no deben depender directamente de detalles del renderer cuando no sea necesario.

Los datos persistentes importantes deben poder evolucionar independientemente del motor gráfico.

---

10. C++ — REGLAS

Utilizar:

C++20
RAII
std::unique_ptr
std::shared_ptr solamente cuando exista una necesidad real
std::optional
std::array
std::vector
std::string
const correctness

Preferir tipos concretos y ownership claro.

Evitar asignaciones dinámicas innecesarias dentro del game loop.

Evitar globales mutables.

Evitar sistemas complejos antes de necesitarlos.

Mantener headers limpios.

Separar:

.hpp
.cpp

---

11. SFML

Utilizar exclusivamente la API correspondiente a la versión instalada.

Para SFML 3 respetar las APIs modernas, incluyendo cuando corresponda:

std::optional<sf::Event>
sf::Vector2u
sf::Vector2f

No copiar código de SFML 2.x sin verificar compatibilidad.

Si existe una diferencia entre versiones, utilizar la API instalada y documentarla cuando sea relevante.

---

12. DEMO VISUAL

El objetivo inmediato del proyecto es construir progresivamente una demostración visual.

Pipeline inicial:

Game
 ↓
Renderer
 ↓
RenderTexture
 ↓
Resolución interna
 ↓
Shader
 ↓
Nearest Neighbor
 ↓
Window

Resolución interna inicial:

320x240

Debe poder modificarse posteriormente sin reescribir el renderer.

---

13. GAME LOOP

La simulación debe utilizar timestep fijo.

Conceptualmente:

Input
 ↓
Fixed Update
 ↓
Fixed Update
 ↓
Render
 ↓
Interpolation

El objetivo es separar la frecuencia de simulación de la frecuencia de renderizado.

No implementar sistemas de física complejos hasta que exista una necesidad real.

---

14. DESARROLLO INCREMENTAL

Cada tarea debe producir un cambio pequeño y verificable.

Ejemplo:

OBJETIVO
Agregar cámara.

IMPLEMENTACIÓN
Camera.hpp
Camera.cpp

VALIDACIÓN
Compilar.
Ejecutar.
Mover cámara.

DOCUMENTACIÓN
Actualizar Arquitectura.md.

GIT
Commit.

PUSH
Enviar al repositorio.

No mezclar múltiples objetivos no relacionados dentro del mismo cambio.

---

15. CRITERIO DE FINALIZACIÓN

Una tarea solamente se considera terminada cuando:

Código
  +
Compilación
  +
Prueba
  +
Documentación
  +
Git

están completos.

No utilizar la palabra "PASS" si solamente se escribió código.

"PASS" significa que el comportamiento fue realmente comprobado.

---

16. BUILD

La compilación principal debe poder realizarse mediante:

cmake -S . -B build -G Ninja
ninja -C build

Si existe un problema de compilación:

1. identificar el error;
2. corregirlo;
3. recompilar;
4. repetir hasta obtener una compilación limpia.

No ocultar errores mediante modificaciones innecesarias del sistema de build.

---

17. PRUEBAS

Cada funcionalidad nueva debe tener una prueba apropiada.

Dependiendo del sistema puede ser:

compilación
prueba automática
ejecución
prueba visual
prueba manual reproducible

Para funcionalidades gráficas, documentar una prueba manual reproducible cuando una prueba automática no sea apropiada.

Ejemplo:

TEST:
Ejecutar Aldrathar.

EXPECTED:
Ventana 960x720.
Render interno 320x240.
Escalado pixelado.
Shader activo.

---

18. DOCUMENTACIÓN

Documentar específicamente.

No llenar los documentos con explicaciones innecesarias.

La documentación debe permitir que otro desarrollador pueda continuar.

Cada documento debe responder:

¿Qué existe?
¿Por qué existe?
¿Cómo se utiliza?
¿Qué está pendiente?
¿Qué no debe modificarse?

---

19. ROADMAP

"docs/Roadmap.md" contiene únicamente objetivos.

Cada objetivo debe tener un estado:

[ ] Pendiente
[~] En progreso
[x] Completado

No marcar algo como completado hasta que haya sido validado.

---

20. CHANGELOG

Registrar cambios significativos.

Formato:

## [fecha]

### Added
- ...

### Changed
- ...

### Fixed
- ...

### Tested
- ...

No registrar cada modificación trivial.

Registrar cambios que permitan reconstruir la evolución del proyecto.

---

21. COMMITS

Los commits deben ser pequeños y descriptivos.

Formato recomendado:

feat: add internal resolution renderer
fix: correct SFML event handling
refactor: separate renderer from game loop
docs: update architecture
test: validate pixel scaling

No utilizar commits genéricos como:

update
changes
final
stuff
test

---

22. GIT WORKFLOW

Proceso normal:

git status

git add <archivos>

git commit -m "tipo: descripción"

git push

Antes del commit:

git diff
git status

Después:

git status
git log --oneline -3

El repositorio debe quedar limpio después de completar una tarea.

---

23. REGLA DE CONTINUIDAD ENTRE IAS

Una IA nueva debe poder continuar el proyecto sin acceso a conversaciones anteriores.

Para ello debe obtener la información desde:

README.md
docs/AI_DEVELOPMENT_PROTOCOL.md
docs/Arquitectura.md
docs/Roadmap.md
docs/CHANGELOG.md
git log
git status

La IA debe continuar desde el último estado confirmado.

No reiniciar el proyecto por preferencia personal.

No reemplazar sistemas existentes sin necesidad.

No realizar una reescritura arquitectónica completa sin una decisión documentada.

---

24. CAMBIOS ARQUITECTÓNICOS

Un cambio arquitectónico importante requiere:

1. identificar el problema;
2. explicar brevemente la alternativa;
3. seleccionar la solución;
4. actualizar "Arquitectura.md";
5. implementar;
6. probar;
7. registrar en "CHANGELOG.md";
8. realizar commit.

No introducir una arquitectura completamente nueva dentro de una tarea pequeña.

---

25. DEPENDENCIAS

Antes de agregar una dependencia:

1. comprobar si el problema puede resolverse con C++20 o dependencias existentes;
2. comprobar disponibilidad en Termux;
3. comprobar compatibilidad con CMake;
4. comprobar impacto de portabilidad;
5. justificar la dependencia.

No agregar librerías solamente porque podrían resultar útiles en el futuro.

---

26. RECURSOS DEL ENTORNO

Utilizar primero las herramientas ya disponibles:

clang++
CMake
Ninja
SFML
GLM
nlohmann-json
Termux:X11
Git

Si una nueva herramienta es necesaria, comprobar primero que puede utilizarse realmente en el entorno actual.

No diseñar soluciones basadas en herramientas no disponibles sin documentar explícitamente que pertenecen a una fase futura.

---

27. ESTADO VS FUTURO

Separar estrictamente:

IMPLEMENTADO

Funcionalidades que realmente existen y fueron verificadas.

EN DESARROLLO

Funcionalidades actualmente implementadas pero no terminadas.

PLANIFICADO

Ideas aceptadas para el futuro.

EXPLORATORIO

Ideas todavía no aprobadas para implementación.

Nunca presentar una idea futura como funcionalidad existente.

---

28. DISEÑO FUTURO DE ALDRATHAR

El proyecto puede llegar a incorporar:

- mundo abierto;
- supervivencia;
- misiones;
- eventos canónicos;
- combate 3v3;
- personajes;
- NPC;
- mascotas;
- genética y crianza;
- inventario;
- objetos únicos;
- Tower;
- marketplace;
- contenido creado por la comunidad;
- profesiones;
- economía;
- clientes adicionales;
- aplicaciones complementarias;
- integración con diferentes plataformas.

Estas funcionalidades pertenecen al diseño futuro.

No implementarlas hasta que el roadmap las active.

---

29. REGLA DE ESCALABILIDAD

Diseñar para que el sistema pueda crecer.

No implementar todo desde el principio.

La escalabilidad se consigue mediante:

interfaces claras
módulos independientes
datos separados de presentación
IDs estables
ownership claro
documentación
tests
commits pequeños

No mediante una cantidad excesiva de abstracciones.

---

30. PRIORIDAD DE DECISIONES

Cuando existan varias soluciones posibles, priorizar:

1. funcionamiento comprobado;
2. simplicidad;
3. mantenibilidad;
4. rendimiento apropiado para el hardware actual;
5. portabilidad;
6. escalabilidad futura.

No sacrificar una solución simple y funcional por una arquitectura teóricamente perfecta.

---

31. PROTOCOLO ANTE INCERTIDUMBRE

Si una decisión no puede verificarse:

NO INVENTAR

Registrar:

UNKNOWN

o:

TODO: VERIFY

y realizar una prueba o investigación antes de implementar una dependencia crítica.

---

32. REGLA FINAL

Aldrathar debe crecer mediante pasos pequeños:

IDEA
 ↓
DOCUMENTACIÓN
 ↓
OBJETIVO
 ↓
IMPLEMENTACIÓN
 ↓
BUILD
 ↓
TEST
 ↓
DOCUMENTACIÓN
 ↓
COMMIT
 ↓
PUSH
 ↓
SIGUIENTE OBJETIVO

Cada commit debe representar un estado comprensible del proyecto.

Cada versión debe poder reconstruirse.

Cada IA debe poder leer el repositorio y continuar.

El objetivo no es avanzar rápido a cualquier costo.

El objetivo es construir un proyecto que pueda seguir creciendo durante años sin perder el control de su arquitectura.
