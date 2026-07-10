Rules for the proyect:

1. Always push to your branch (never to main)
2. Only push to main when both of us agree
3. Comments on every function to explain the logic and easy read

TODO:

* DAVID: Infraestructure and Backend

Parsing

Inicializar MLX

Cargar texturas XPM

Crear framebuffer

* Pep: Matemathics, visual engine - frontend

Raycasting DDA

Loop del juego:

(eventos + render)

Movimiento y colisiones


The fix for paths is just to add a rule for skipping \n. And also a function to iterate over the orientation arr
to match it with any orientation. Once an orientation is picked up, it automatically becomes unavelaible to compare again against the next lines.
the same with the colors

The MAIN OBSTACLE right now is how to difirientciate both.