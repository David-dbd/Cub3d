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


T/*
	La idea es muy sencilla: Itero sobre el mapa buscando espacios. Si encuentro un espacio, verifico las 4 direciones: derecha, izquierda,
	arriba y abajo. La idea es que hayan 1's en cada una de ellas (dependiendo del contexto). Esto hace que el espacio sea valido. La manera
	en la que se comprueba es muy sencilla, se verifican las mismas posiciones del index del espacio en las linea de arriba y abajo, derecha
	e izquierda hasta encontrar un 0 (no sería valido el mapa), un 1 (sería valido el mapa) o mas espacios (dependiendo del contexto es valido).
	Ahora bien, aunque se verifican las 4 direcciones, con solo tener 3 direcciones validas es suficiente para que el mapa sea valido. De esas 3,
	la derecha e izquierda SIEMPRE tienen que ser validas (porque en teoria una linea debe ser contenida en 1's), lo cual deja la opción 
	de arriba o abajo. Si por ejemplo, derecha, izquierda y arriba estan bien, igual se verifica abajo; Por alguna razón solo hay espacios, lo cual
	podría querer decir que es el final del mapa, con lo cual no esta mal. Sin embargo, si hubiese un 0, si estaria mal, y aunque las otras 3
	estuviensen bien, un espacio nunca puede estar rodeado de 0(s).

	En el parseo del mapa estoy pensando que cuando haya espacios en una linea pero que arriba de esa linea este cerrado con 1, por ejemplo: 
"100011001
11111    1111"
Para verificar si es valido, simplemente cuando llegue a la linea que contiene espacios hago un sistema que verifique la linea anterior en 
el mismo index del espacio, de modo que si encuentro un 1, entonces lo doy por bien visto, sigo con el siguiente espacio y vuelvo a verificar 
la linea de arriba en el siguiente index. Asi hasta que haya pasado sobre los espacios. Si por alguna razon me encuentro mas espacios, entonces
 sigo buscando una linea anterior (de una en una hasta hayar 1 o 0). Si la primera linea que encuentre tiene 0's en el mismo index que los espacios
  entonces lo reconozco como un error del mapa porque tiene una fuga.

Lo que quiero decir es que al menos tres direcciones deben ser correctas por regla general. Sin embargo, hay otra regla, y es que dos de esas 
direcciones TIENEN que ser derecha e izquierda. Es decir, si las tres direcciones validas terminan siendo arriba, derecha y abajo, eso estaria 
mal, ya que se necesitan que las direcciones laterales sean validas ya que cada linea del mapa deberia de estar contenida en 1 al menos al inicio 
y al final. Esto quiere decir que no necesariamente se necesitan verificar las 4 direcciones porque habran casos en los que arriba o abajo no seran
 validas pero eso no quiere decir que esten mal. Por ejmplo:
"1111111111
100011001
111111  11111"
En este ejemplo la direccion de abajo del espacio no es valida porque no hay nada, pero eso no quiere decir que el mapa sea invalido. De hecho el mapa ES VALIDO en este caso.



111111 ->INVALIDO (se encuentra un 0)
1    1
10   1
111111

111111 ->INVALIDO (se encuentra un 0)
1    1
1  0 1
1    1
111111

111111111111 ->VALIDO (encuentra solo 1's a su alrededor)
1          1
1   11111  1
1   10001  1
1   10001  1
1   11111  1
111111111111

11111111111111111111111111111 ->VALIDO (los espacios encuentran 1's. Aunque la direccion SUR esolo encuentra espacios, mientras no encuentren 0's)
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111


Reglas basicas:
1. La primera y u´ltima linea deben ser 1's (pueden tener espacios entre ellas siempre y cuando otras lineas cierren esos espacios)
2. Debe haber un caracter para el jugador - Se considera como un 0 (psición jugable)
3. Deber haber almenos un 0 (y/o un caracter). Si hay 2 o mas, pueden estar separados por 1's pero no espacios.



Estoy pensando en verificar primero que cada linea del mapa sea valida en terminos de saber si esta cerrada o no:
Luego, si la linea es valida (Full_line o middle_line), entonces la guardo tal cual (esta vez sin eliminar espacios). 
Y asi voy linea a linea. Si al final del dia todo era valido entonces guardare el mapa tal cual me lo dio el usuario.
 Luego, duplicare ese mapa: tendre el original y la copia la editare para normalizar. Cuando normalize, aplicare mi sistema 
 de validacion direccional que podrá ser aplicado sobre los espacios del mapa y no sobre los espacios exteriores. Si todo esta 
 bien, entonces utilizo el mapa original para la mlx. Podría eliminar la copia editada sin espacios luego de eso o podría almacenar
 la si la llegase a necesitar en el futuro, da igual por ahora



 PLAN: 
 1. Hayar el inicio absoluto y final absoluto
 2. Hayar el inicio y final de cada linea con la funcion de omitir espacios
 3. Iterar sobre el mapa buscando espacios.

 Reglas de espacios:
 * Si es la primera linea y esta antes del inicio entonces NO se revisa izquierda (0 - 1) ni tampoco arriba
 * Si es la primera linea y esta después del final entonces NO se revisa derecha ni tampoco arriba
 * Si es la ultima linea y esta antes del inicio entonces NO se revisa izquierda (0 - 1) ni tampoco abajo
 * Si es la ultima linea y esta después del inicio entonces NO se revisa dercha ni tampoco abajo

