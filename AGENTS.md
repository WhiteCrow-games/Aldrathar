# Instrucciones para asistentes de IA — Aldrathar

## Fuente de verdad

Antes de modificar código, leer:
1. `docs/DECISIONS.md`
2. `docs/WORK_STATE.md`, si existe y está actualizado
3. `CMakeLists.txt`
4. El código relacionado con la tarea solicitada

El repositorio es la fuente de verdad del proyecto.
No asumir que una conversación anterior describe el estado
más reciente del código.

## Tecnología oficial

- Lenguaje: C++20
- Biblioteca gráfica principal: raylib
- Construcción: CMake
- Generador recomendado: Ninja
- Bibliotecas auxiliares configuradas: GLM y nlohmann-json

SFML pertenece a una etapa anterior. No introducir SFML,
no migrar a SFML y no mezclar sus APIs con raylib sin una
decisión explícita del responsable del proyecto.

## Objetivo actual

Priorizar una base compilable y una demostración visual
funcional de Aldrathar. El alcance futuro incluye un RPG
de supervivencia de mundo abierto con interiores de
perspectiva controlada, pero no inventar sistemas de juego
que todavía no hayan sido definidos.

## Reglas de trabajo

- Comprender el código existente antes de editarlo.
- Hacer cambios pequeños, concretos y verificables.
- Evitar reescrituras innecesarias.
- No eliminar respaldos ni archivos sin comprobar su utilidad.
- Mantener CMake y el código portables a futuro PC.
- No afirmar que una compilación o prueba pasó si no se ejecutó.
- No añadir dependencias sin justificar su necesidad.
- No incluir ejecutables, directorios de compilación ni logs
  en los commits.
- Documentar decisiones técnicas relevantes.
- Actualizar el estado y las tareas cuando el trabajo cambie.
- Si hay contradicciones entre documentos y código, señalarlas
  y pedir aclaración cuando afecten la dirección del proyecto.

## Cierre de cada tarea

Informar brevemente:
1. Qué cambió.
2. Qué archivos se modificaron.
3. Qué pruebas se ejecutaron y sus resultados.
4. Qué queda pendiente.
5. Qué documentación se actualizó.

No hacer push, cambiar la rama principal ni reemplazar el
historial remoto sin autorización explícita.
