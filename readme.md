Simulador de Ajedrez en C++

IMPORTANTE para compilar el codigo que esta en el documento ajedrez de este repositorio, se DEBE utilizar un compilador interactivo como este: https://www.onlinegdb.com/online_c++_compiler#

Este simulador de ajedrez en C++ permite a dos jugadores mover piezas en un tablero de 8x8 siguiendo las reglas del ajedrez. A continuación se detallan las instrucciones para empezar a jugar, cómo controlar las piezas, sus movimientos y cómo ganar.

Cómo Mover las Piezas

Introduce los movimientos usando el formato estándar de ajedrez. Por ejemplo, para mover una pieza desde la posición e2 a e4, escribe: e2 e4 Este formato indica:

• e2: La casilla inicial donde se encuentra la pieza.

• e4: La casilla de destino de la pieza.

• Cambio de Turno: El juego alterna automáticamente entre el turno del jugador blanco y el del jugador negro después de cada movimiento válido.

Movimientos de las Piezas
Cada tipo de pieza se mueve de acuerdo a las reglas del ajedrez:

• Peón:

Avanza un paso hacia adelante (o dos si es su primer movimiento).

Captura en diagonal.

• Rey:

Se mueve un cuadro en cualquier dirección (vertical, horizontal, diagonal).

No puede moverse a una posición que lo pondría en jaque.

• Torre:

Se mueve en línea recta, horizontal o verticalmente, a cualquier distancia.

• Alfil:

Se mueve en cualquier dirección diagonal a cualquier distancia.

• Caballo:

Se mueve en forma de "L" (dos pasos en una dirección y luego un paso perpendicular).

Puede "saltar" sobre otras piezas.

• Reina:

Combina los movimientos de la Torre y el Alfil, permitiendo movimiento recto o diagonal en cualquier dirección.

Condiciones para Ganar

• El objetivo del juego es capturar al Rey del oponente.

• El juego termina inmediatamente cuando uno de los reyes es capturado:

o Si el Rey negro es capturado, el jugador blanco gana.

o Si el Rey blanco es capturado, el jugador negro gana.

Consejos para Controlar el Juego

• Introduce movimientos válidos y sigue las reglas de movimiento de cada pieza.

• Después de cada turno, revisa el tablero y planea estrategias para proteger a tu rey y atacar al rey del oponente.

• Puedes visualizar el historial de movimientos en consola para revisar jugadas previas.
