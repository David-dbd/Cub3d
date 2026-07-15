# Informe de edge tests - cub3D

Fecha: 2026-07-15  
Artefacto probado: `Cub3d-prueba (4).zip`  
Referencia: `en.subject.pdf`, versión 12.0

## Veredicto

**No apto para entrega/evaluación todavía.** El ZIP falla la compilación desde cero, incumple Norminette y contiene errores críticos de parsing que permiten mapas inválidos y rechazan sintaxis válida del subject.

No se modificó el proyecto original. Las únicas modificaciones realizadas fueron sobre una copia temporal para poder aislar el parser y el núcleo gráfico.

## Resumen de resultados

| Área | Resultado |
|---|---|
| Compilación directa del ZIP | Falla: falta `minilibx-linux/` |
| Compilación tras añadir MiniLibX temporalmente | Falla: firma incompatible de `build_scene` |
| Compilación tras corregir temporalmente esa firma | Pasa con `-Wall -Wextra -Werror` |
| `make` sin relink innecesario del ejecutable | Pasa |
| `make clean` / `make fclean` | Pasan en la copia completada |
| `make bonus` | Falla: no existe la regla |
| Norminette (`src` + `includes`) | Falla: 81 errores |
| Argumentos incorrectos | Pasan: 0, extensión incorrecta y 2 argumentos se rechazan |
| Parser bajo ASan/UBSan | Ejecutado en 19 escenarios; se detectan varios falsos positivos/negativos |
| Núcleo gráfico aislado | Pasa: raycasting N/S/E/W y colisiones, bajo ASan/UBSan |
| Ventana, teclas, ESC y cruz roja | No verificable: el display WSLg tampoco aceptó `xeyes` en esta sesión |

## Fallos bloqueantes

### 1. El ZIP no compila

- El Makefile exige `minilibx-linux`, pero el directorio no está incluido.
- Al añadir una MiniLibX solo en la copia temporal, aparece el siguiente error:

```text
src/bridge.c:32: error: conflicting types for 'build_scene'
includes/cub3d.h:103: previous declaration ... int(...)
src/bridge.c:32: definition ... void(...)
```

- El ejecutable se llama `cub3d`, pero el subject exige `cub3D`.
- Falta la regla `bonus`, requerida expresamente por el subject.

### 2. Norminette falla

`norminette src includes` devuelve **81 errores**. Afecta, entre otros, a `bridge.c`, `main.c`, casi todo el parser, el sistema de búsqueda y los headers. Hay errores de guardas de header, líneas largas, declaraciones/asignaciones, indentación y comentarios en scope no permitido.

Con errores de Norma el proyecto puede recibir 0 según las instrucciones comunes del subject.

### 3. Se aceptan mapas inválidos

Casos confirmados por ejecución del parser real:

| Caso | Esperado | Resultado real |
|---|---|---|
| Mapa sin jugador | Rechazar | **Acepta** (`PARSED_WITHOUT_PLAYER`) |
| Mapa sin pared inferior | Rechazar | **Acepta** |
| Mapa abierto por la izquierda | Rechazar | **Acepta** |

La causa principal está en `parse_map.c`: el bucle de `is_mid_line` empieza comprobando el índice 1 por el `while ((i++) < distance)`, por lo que no valida correctamente el primer carácter. Además, al terminar `parse_map` no se comprueba que haya exactamente un jugador ni que exista una última línea de cierre.

### 4. Se rechaza el RGB canónico del subject

El formato válido del subject, por ejemplo:

```text
F 10,20,30
C 40,50,60
```

es rechazado como `Error: Wrong Colors`. `parse_colors.c` exige exactamente cuatro palabras separadas por whitespace (`word_counter(...) != 4`), lo cual solo admite variantes como `F 10, 20, 30`.

### 5. Una línea vacía antes del mapa se incorpora al mapa

El subject permite líneas vacías entre elementos y antes del mapa. El fichero se acepta, pero la línea vacía se almacena como una fila adicional:

```text
PARSED_OK height=5 player_y=2.5
```

El mismo mapa sin esa línea tiene altura 4 y `player_y=1.5`. Esto desplaza la escena y no es un parseo fiel.

### 6. Error de textura sin mensaje

Una ruta `.xpm` inexistente se rechaza con código no cero, pero sin escribir `Error\n` ni explicación. El subject exige `Error\n` seguido de un mensaje explícito para cualquier misconfiguración.

### 7. Fugas y código de éxito al fallar la escena

Con un mapa sin jugador, el parser lo acepta, el motor detecta después `invalid player direction`, pero `main` ignora el retorno de `cub3d_engine_start` y termina con código **0**.

LeakSanitizer confirma:

```text
SUMMARY: AddressSanitizer: 214 byte(s) leaked in 11 allocation(s).
```

Las fugas incluyen paths, grid, metadatos de líneas y `row_lengths`.

## Otros incumplimientos de entrega

- El README se llama `readme.md`; el subject pide `README.md` y Linux distingue mayúsculas.
- El `hell.cub` incluido no es ejecutable: referencia extensiones `.xmp`, mientras que el parser exige `.xpm`.
- El ZIP contiene artefactos compilados (`libft_plus.a` y numerosos `.d`), aunque esto no es por sí solo el fallo principal.

## Casos que sí pasan

- Mapa básico válido y mapa mínimo 3x3.
- Mapa válido con indentación.
- Void interno completamente aislado por paredes.
- Rechazo de dos jugadores.
- Rechazo de ID duplicado.
- Rechazo de RGB fuera de rango y RGB alfabético.
- Rechazo de carácter de mapa inválido.
- Rechazo de textura con extensión `.png`.
- Rechazo de apertura por la derecha y de void conectado a suelo.
- Argumentos incorrectos: sin argumento, extensión distinta de `.cub` y más de un argumento.
- Raycasting aislado en las cuatro orientaciones, más movimiento contra paredes durante 200 actualizaciones, sin hallazgos ASan/UBSan.

## Prioridad recomendada de corrección

1. Hacer que el ZIP compile desde cero: incluir MiniLibX, unificar `build_scene`, usar nombre `cub3D` y añadir `bonus`.
2. Reescribir las invariantes del mapa: exactamente un jugador, cierre real por todos los lados, última fila válida y filas irregulares seguras.
3. Corregir colores para aceptar el formato canónico sin espacios y variantes válidas de whitespace.
4. Saltar líneas vacías antes del inicio del mapa sin incorporarlas al grid.
5. Garantizar `Error\n` + mensaje y retorno no cero en todas las rutas de fallo.
6. Centralizar cleanup para todos los fallos de validación/motor.
7. Corregir los 81 errores de Norminette y los nombres/casing de entrega.
8. Repetir después las pruebas manuales de ventana, W/A/S/D, flechas, ESC, cruz roja, cambio de foco y minimización en un display gráfico funcional.

## Nota de alcance

La validación visual del subject se hizo renderizando sus 19 páginas, además de extraer el texto. La imposibilidad de abrir una ventana en esta sesión es una limitación del display del entorno: `xeyes` también falla. Por ello, los controles de ventana quedan como **no verificados**, no como aprobados ni suspendidos.
