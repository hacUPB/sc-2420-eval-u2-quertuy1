[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/C5iNLRra)
# Documentación del Proyecto
## Unidad 2

## Actividad 1

En el ciclo de vida de un juego, funciones como Setup(), Update(), y Render() son clave para controlar el flujo y comportamiento del juego en cada "frame" o iteración del ciclo.

### Setup():

Su propósito es inicializar todo lo que necesita el juego antes de que comience a ejecutarse el bucle principal. Aquí se configura el estado inicial, se cargan recursos como imágenes, sonidos, o datos necesarios, y se inicializan variables o componentes importantes.
Solo se ejecuta una vez, justo al inicio del juego.

### Update():

Esta función actualiza el estado lógico del juego en cada frame. Se encarga de mover personajes, procesar las entradas del usuario (como pulsaciones de teclas o toques en pantalla), y calcular la física o las colisiones.
Update() es donde se toman las decisiones que afectan el estado del juego. Se ejecuta constantemente en cada iteración del bucle de juego, normalmente muchas veces por segundo.

### Render():

Su objetivo es dibujar en la pantalla lo que el jugador debe ver. Es donde se representan los elementos gráficos actualizados, como personajes, objetos o fondos.
Se ejecuta después de Update() para mostrar los cambios en el estado del juego. Se encarga de renderizar gráficos y todo lo que deba verse actualizado en pantalla.
Interacción en el Game Loop:
Setup() se ejecuta una sola vez al comienzo.
Luego, el ciclo del juego alterna entre Update() y Render():
En cada frame, primero se llama a Update(), que actualiza la lógica del juego.
Después se llama a Render(), que se encarga de dibujar los cambios visuales en la pantalla.
Este ciclo se repite hasta que el juego se detiene.

## Actividad 2
Rapid roll

Estudiante: Jhonier Mosquera
Id:  369010
---
