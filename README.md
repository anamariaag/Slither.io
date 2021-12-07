# experiments Slither.io
Implementación en C del juego de internet Slither.io, usando librería gráfica Raylib. 
## Comenzando 🚀

### Pre-requisitos 📋
Tener la librería gráfica de Raylib instalada y un compilador de C, en nuestro caso usamos Visual Studio. 

## Wiki 📖
Constantes | Descripción 
--- | --- 
valorInicial | Tamaño inicial de gusanos, default 10.
nFood | Cantidad de comida durante el juego, considere que es el doble ya que hay dos arreglos de comida. 
nGusanos | Cantidad de gusanos de I.A. en el juego, recomendamos entre 10-50 pero funciona perfectamente hasta con 80
worldSize | Radio (en pixeles) del mundo en el que se podra jugar.
speed | Velocidad (en pixeles por frame) a la que se mueven los gusanos.
screenWidth | Ancho de la pantalla (en pixeles) recomendamos 1800.
screenHeight | Alto de la pantalla (en pixeles) recomendamos 900.
maxInputChars | Cantidad de caracteres disponible para el nombre de jugador.
growth  | Crecimiento del radio del gusano (en pixeles) recomendamos 1.
radioInicial | Radio inicial de los gusanos (en pixeles) recomendamos 20.
radioFindFood | Radio de deteccion de comida (en pixeles) recomendamos 100. 
radioAvoidGusano | Radio de detección y evasión entre gusanos I.A. (en pixeles) recomendamos 30.



Estructuras | Descripción 
--- | --- 
Bloque | Elementos que componen el gusano, cada uno tiene color, posición, radio. 



Funciones | Descripción 
--- | --- 
Vector2 getPosicionGusano(List* gusano,int index); | Recibe lista dinámica del cuerpo del gusano y índice para seleccionar el elemento que regresará la posición. 
void inicializarBloque(Vector2 initialPositions[valorInicial], List* gusano); | Recibe un arreglo de posiciones y lista dinámica del cuerpo de gusano original, inicializa bloque del cuerpo del gusano con las posiciones del arreglo, color random y radioInicial. 
void inicializarPosiciones(List* posiciones,Vector2 initialPositions[valorInicial],Vector2 pInicial);| Inicializa posiciones para gusano original.
void inicializarFakeGusanos(List* fakeGusanos[],List* posicionesFakeGusanos[],Vector2 randomPos[nGusanos][valorInicial]);| Inicializa cuerpo de gusanos I.A. y sus posiciones con listas dinámicas.
Vector2 mouseMovement(Vector2 mouse, List* posiciones);  |
void checkBoundaries(List* posiciones, List* gusano, int* play);  |
void updateGusano(List* gusano,List* posiciones);  |
Vector2 updatePosFakeGusano(List* posiciones, Vector2* target);  |
void checkCollisionGusanos(List* gusano, List* posiciones, List* fakeGusanos[], List* fakeGusanosPos[],int* play,int* count,Vector2 foodPosTodo[]);  |
void fakeGusanoFollowFood(List* fakeGusanos,Vector2 randomPosTodo[],Vector2 randomPosCentro[],Vector2* target);  |
void fakeGusanoAvoidGusanos(List* fakeGusanos[],List* fakeGusano, Vector2* target,int i, List* gusano,int* flag);  |



## Versionado 📌

Para todas las versiones disponibles, mira los [commits en este repositorio](https://github.com/anamariaag/experiments/commits/master).

## Autores ✒️

* **Valeria Ramírez** - *Developer* - [valrmzl](https://github.com/valrmzl)
* **Ana María Anaya** - *Developer* - [anamariaag](https://github.com/anamariaag)


## Licencia 📄
Si nos van a copiar mínimo pidan permiso, grax.

## Expresiones de Gratitud 🎁

* Gracias Josean por ayudarnos este semestre y debuggearnos todo el proyecto, vales mil. 
* Agradecimientos adicionales a nuestros compañeros @sebas, @pablito. @iker, @tia, @chris, @lolo por no dejarnos morir este semestre los tqm.


---
⌨️ con ❤️ por [anamariaag7](https://www.instagram.com/anamariaag7/) &&  [valrmzl](https://www.instagram.com/valrmzl/) 😊

