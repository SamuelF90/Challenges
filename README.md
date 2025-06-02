🐱🐭 Juego de Gato y Ratón en Consola
Este es un juego interactivo de consola desarrollado en Python, donde un Gato intenta atrapar a un Ratón antes de que este llegue al Queso o sobreviva una cierta cantidad de turnos. El jugador puede enfrentarse a otro jugador o a la computadora (IA con algoritmo Minimax).

🎮 Cómo jugar
Modos disponibles:
Jugador vs Jugador

Jugador vs IA

Roles:
El Gato intenta atrapar al Ratón.

El Ratón intenta llegar al Queso o sobrevivir 20 turnos.

▶️ Instrucciones de uso
Ejecuta el script con Python:

bash
Copiar
Editar
python gato_raton.py
Elige el modo de juego:

c para jugar contra la computadora.

j para jugar contra otra persona.

Define el tamaño del tablero (mínimo 5x5).

Asigna los roles: Gato (g) o Ratón (r).

⌨️ Controles de movimiento
Se utilizan teclas tipo WASD para moverse, además de teclas diagonales:

Tecla	Dirección
w	Arriba
s	Abajo
a	Izquierda
d	Derecha
q	Arriba izquierda
e	Arriba derecha
z	Abajo izquierda
c	Abajo derecha

🔍 Detalles técnicos
El juego usa emojis para representar los personajes:

🐱 Gato

🐭 Ratón

🧀 Queso

🟥 Obstáculo

⬜ Casilla vacía

El tablero se genera dinámicamente según el tamaño ingresado.

Hay obstáculos fijos en 2 columnas del tablero.

La IA del juego utiliza el algoritmo Minimax para simular decisiones inteligentes.

🧠 Reglas del juego
Si el Gato atrapa al Ratón: pierde el Ratón.

Si el Ratón llega al Queso: gana el Ratón.

Si pasan 20 turnos sin ser atrapado ni llegar al queso: sobrevive el Ratón.

El movimiento está limitado por los bordes del tablero y los obstáculos.

📁 Estructura del código
crear_tablero(): Crea el tablero vacío.

imprimir_tablero(): Muestra el tablero en consola.

mover(): Realiza un movimiento según la tecla.

minimax(): IA para simular la mejor jugada.

jugar(): Controla el flujo principal del juego.

💡 Requisitos
Python 3.6 o superior

No necesita librerías externas

