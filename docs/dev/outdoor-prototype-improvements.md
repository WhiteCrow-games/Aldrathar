# Aldrathar — Mejoras del prototipo exterior 3D

## Estado del documento

- Tipo: documentación de cambios de desarrollo.
- Alcance: shader retro, entorno exterior, personaje, dragón,
  controles y visibilidad contextual.
- Archivos de implementación afectados:
  - `assets/shaders/retro.frag`
  - `include/game/Game.hpp`
  - `src/game/Game.cpp`
- Estado de validación: pendiente de compilación y pruebas
  específicas de esta versión.

Este documento describe los cambios observados en el diff.
No implica que todas las funciones hayan sido verificadas
en ejecución.

## 1. Objetivo

Ampliar el prototipo exterior 3D de Aldrathar mediante
mejoras visuales y de interacción, manteniendo raylib y
la arquitectura C++ existente.

Los cambios abarcan la apariencia retro, la representación
de personajes, la vegetación, las colisiones y la adaptación
visual de las paredes cuando el jugador se encuentra dentro
de la casa.

## 2. Shader retro

Archivo: `assets/shaders/retro.frag`

### Cambios

- Conversión parcial de los colores hacia escala de grises
  mediante una aproximación de luminancia.
- Mezcla del resultado con el color original usando un
  factor de saturación de 0.72.
- Incremento moderado del contraste mediante un factor
  de 1.10.
- Ajuste de canales RGB para producir un tinte terroso.
- Limitación de los componentes de color al intervalo
  comprendido entre 0.0 y 1.0.

### Efectos anteriores retirados

- Oscilación de brillo usada para simular scanlines.
- Patrón alternado utilizado como dithering.

### Validación pendiente

Comprobar que el shader se carga correctamente, se aplica
al resultado renderizado y ofrece el aspecto esperado.
La modificación del archivo por sí sola no demuestra
que el efecto esté activo durante el juego.

## 3. Interfaz y estado de Game

Archivo: `include/game/Game.hpp`

Se incorporan métodos privados para separar responsabilidades:

- `updateCamera()`
- `drawTouchControls()`
- `drawOutdoor()`
- `drawHouse()`
- `drawTrees()`
- `drawBushes()`
- `drawCharacter()`
- `drawDragon()`

También se incorporan o explicitan miembros para:

- Posición del jugador.
- Estado de cámara isométrica.
- Joystick virtual y movimiento táctil.
- Identificadores de los puntos de contacto.
- Posición y animación del dragón.
- Estado de presencia del jugador dentro de la casa.

Se añade `getCamera()` para obtener una copia de la cámara.

## 4. Movimiento y colisiones

Archivo: `src/game/Game.cpp`

### Límites y vegetación

Se conservan los límites del terreno y se ajustan las
colisiones circulares de los troncos mediante la constante
`TRUNK_RADIUS`, cuyo valor es 0.28.

La intención es que el tronco bloquee el movimiento,
sin convertir toda la copa del árbol en un obstáculo.

Los arbustos añadidos no tienen una comprobación de
colisión propia en la implementación documentada.

### Casa

Se mantienen comprobaciones de colisión para las paredes
laterales, trasera y frontal. La pared frontal deja un
hueco central para entrar.

La detección de interior se realiza con la función
`isPlayerInsideHouse`, basada en los límites de la
posición del jugador.

Debe verificarse en ejecución que la detección de interior,
el hueco de la puerta y las colisiones coincidan con la
geometría visible.

## 5. Transparencia contextual

Se añaden dos funciones auxiliares:

- `getWallAlpha`: devuelve una opacidad de 85 cuando el
  jugador está dentro de la casa y 255 cuando está fuera.
- `getFoliageAlpha`: asigna valores de opacidad según
  la distancia entre el jugador y un árbol.

Los umbrales de distancia de la vegetación son 1.8 y 2.8
unidades. Se usan valores de opacidad de 90, 170 y 255.

La intención es reducir los elementos que obstruyen la
visión del jugador, sin eliminar la geometría de paredes
ni troncos.

### Limitaciones conocidas por revisar

La transparencia no garantiza por sí sola que el resultado
sea correcto: deben comprobarse el orden de dibujo, el
depth buffer, la mezcla alfa y la visibilidad desde
distintos ángulos de cámara.

También debe verificarse que el comportamiento de las
paredes permita ver el interior sin perder la lectura
espacial del edificio.

## 6. Personaje

Se sustituye la representación sencilla anterior por
un personaje construido con primitivas 3D de raylib.

Los componentes incluyen:

- Torso y cinturón.
- Cabeza y pelo o casco.
- Brazos y piernas.
- Ojos y sombra en el suelo.
- Desplazamiento oscilatorio de extremidades.

La animación utiliza el tiempo acumulado y una función
senoidal.

Debe comprobarse que la detección de movimiento considere
tanto los controles táctiles como el teclado.

## 7. Dragón

Se añade `drawDragon()`, que construye un dragón mediante
cubos y esferas.

La representación incluye cuerpo, cuello, cabeza, ojos,
alas, patas, cola segmentada y púas.

La animación aplica:

- Oscilación de la cabeza mediante una función seno.
- Escalado leve del cuerpo para simular respiración.

La velocidad angular se configura con
`DRAGON_IDLE_SPEED`, expresada en grados por segundo y
convertida a radianes para el cálculo de la oscilación.

Es un modelo de prototipo construido con primitivas,
no un modelo artístico final ni una animación esquelética.

## 8. Vegetación y escenario

Se reorganiza la representación del terreno, la casa
y los árboles.

Se añaden arbustos con transparencia contextual y se
mantienen las paredes y el techo de la casa.

La geometría de la casa continúa siendo real en el
renderizado; la transparencia es una estrategia visual,
no una eliminación física de las paredes.

## 9. Cámara y controles

Se conserva el cambio entre cámara en perspectiva y
cámara ortográfica isométrica.

Se mantienen los controles de teclado y el joystick
virtual, con conversión de coordenadas de pantalla a
las coordenadas internas de referencia 320x240.

Se debe verificar el cambio de cámara con toques
multitáctiles, pulsaciones rápidas y dispositivos que
emulan el ratón.

## 10. Rendimiento y arquitectura

La escena utiliza primitivas de raylib y cálculos
geométricos sencillos.

Antes de considerar finalizada esta versión se recomienda
comprobar el rendimiento en Android Termux, especialmente
por el número de primitivas dibujadas por fotograma.

No se ha demostrado mediante este diff una mejora
cuantificada de rendimiento.

## 11. Plan de validación

Registrar cada comprobación por separado:

- [ ] Compilación C++20 correcta.
- [ ] Ejecución de la versión compilada.
- [ ] Movimiento con teclado.
- [ ] Movimiento con joystick táctil.
- [ ] Entrada y salida de la casa.
- [ ] Colisiones con troncos y paredes.
- [ ] Transparencia de paredes desde el interior.
- [ ] Transparencia gradual de la vegetación.
- [ ] Cambio de cámara táctil e isométrica.
- [ ] Animaciones del personaje y del dragón.
- [ ] Aplicación efectiva del shader retro.
- [ ] Rendimiento aceptable en el dispositivo objetivo.

No marcar una prueba como superada hasta observar
su resultado en la versión correspondiente.

## 12. Relación con la arquitectura de Aldrathar

Estas mejoras pertenecen al prototipo exterior 3D.
No sustituyen la arquitectura general del motor ni
establecen que el sistema definitivo de interiores,
cámaras fijas o paredes inteligentes esté terminado.

La futura evolución deberá mantener separadas la
geometría física, la lógica del juego y las decisiones
de presentación visual.

## 13. Resumen

El cambio reúne ajustes de color, reorganización del
código de escena, nuevas representaciones de personajes,
vegetación y mecanismos de transparencia contextual.

La compilación y las pruebas de comportamiento siguen
siendo necesarias antes de declarar esta versión validada.
