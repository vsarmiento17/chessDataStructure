#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Clase para almacenar un movimiento
class Movimiento {
public:
    int xInicial, yInicial, xFinal, yFinal;
    Movimiento* siguiente;

    Movimiento(int xI, int yI, int xF, int yF) : xInicial(xI), yInicial(yI), xFinal(xF), yFinal(yF), siguiente(nullptr) {}
};

// Clase para el historial de movimientos
class Historial {
private:
    Movimiento* cabeza;
public:
    Historial() : cabeza(nullptr) {}

     // Agrega un nuevo movimiento al inicio del historial
    void agregarMovimiento(int xInicial, int yInicial, int xFinal, int yFinal) {
        Movimiento* nuevoMovimiento = new Movimiento(xInicial, yInicial, xFinal, yFinal);
        nuevoMovimiento->siguiente = cabeza; // Añadir al inicio de la lista
        cabeza = nuevoMovimiento;
    }

     // Imprime todos los movimientos almacenados en el historial
    void imprimirHistorial() {
        Movimiento* actual = cabeza;
        cout << "Historial de Movimientos:" << endl;
        while (actual != nullptr) {
            cout << "Desde: (" << actual->xInicial << ", " << actual->yInicial << ") "
                 << "Hasta: (" << actual->xFinal << ", " << actual->yFinal << ")" << endl;
            actual = actual->siguiente;
        }
    }
};

// Clase base para las piezas de ajedrez
class Pieza {
public:
    string color; // Color de la pieza
    char tipo; // Tipo de la pieza (P, K, T, etc.)
    // Constructor que inicializa el color y tipo de la pieza
    Pieza(string color, char tipo) : color(color), tipo(tipo) {}
    // Método virtual puro para validar movimientos específicos de cada pieza
    virtual bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) = 0;
};

// Clases derivadas para cada tipo de pieza
class Peon : public Pieza {
public:
    Peon(string color) : Pieza(color, 'P') {}
    //de ahora en adelante en cada clase de pieza diferente, este motodo verificara si el movimiento es valido segun sus requerimentos especificos
    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        int direccion = (color == "blanco") ? 1 : -1;
        if (yInicial == yFinal) { 
            if (xFinal == xInicial + direccion && matriz[xFinal][yFinal] == nullptr) { 
                return true;
            }
            if ((xInicial == 1 && color == "blanco" && xFinal == xInicial + 2 && matriz[xFinal][yFinal] == nullptr) ||
                (xInicial == 6 && color == "negro" && xFinal == xInicial - 2 && matriz[xFinal][yFinal] == nullptr)) {
                return true;
            }
        } else if (abs(yFinal - yInicial) == 1 && xFinal == xInicial + direccion) { 
            return (matriz[xFinal][yFinal] != nullptr && matriz[xFinal][yFinal]->color != color);
        }
        return false;
    }
};

class Rey : public Pieza {
public:
    Rey(string color) : Pieza(color, 'K') {}

    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        return (abs(xFinal - xInicial) <= 1 && abs(yFinal - yInicial) <= 1);
    }
};

class Torre : public Pieza {
public:
    Torre(string color) : Pieza(color, 'T') {}

    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        if (xInicial != xFinal && yInicial != yFinal) return false;
        int pasoX = (xFinal > xInicial) ? 1 : (xFinal < xInicial) ? -1 : 0;
        int pasoY = (yFinal > yInicial) ? 1 : (yFinal < yInicial) ? -1 : 0;
        int x = xInicial + pasoX, y = yInicial + pasoY;
        while (x != xFinal || y != yFinal) {
            if (matriz[x][y] != nullptr) return false;
            x += pasoX;
            y += pasoY;
        }
        return true;
    }
};

class Alfil : public Pieza {
public:
    Alfil(string color) : Pieza(color, 'A') {}

    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        if (abs(xFinal - xInicial) != abs(yFinal - yInicial)) return false;
        int pasoX = (xFinal > xInicial) ? 1 : -1;
        int pasoY = (yFinal > yInicial) ? 1 : -1;
        int x = xInicial + pasoX, y = yInicial + pasoY;
        while (x != xFinal && y != yFinal) {
            if (matriz[x][y] != nullptr) return false;
            x += pasoX;
            y += pasoY;
        }
        return true;
    }
};

class Caballo : public Pieza {
public:
    Caballo(string color) : Pieza(color, 'C') {}

    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        return ((abs(xFinal - xInicial) == 2 && abs(yFinal - yInicial) == 1) ||
                (abs(xFinal - xInicial) == 1 && abs(yFinal - yInicial) == 2));
    }
};

class Reina : public Pieza {
public:
    Reina(string color) : Pieza(color, 'Q') {}

    bool movimientoValido(int xInicial, int yInicial, int xFinal, int yFinal, Pieza* matriz[8][8]) override {
        if (xInicial == xFinal || yInicial == yFinal) {
            int pasoX = (xFinal > xInicial) ? 1 : (xFinal < xInicial) ? -1 : 0;
            int pasoY = (yFinal > yInicial) ? 1 : (yFinal < yInicial) ? -1 : 0;
            int x = xInicial + pasoX, y = yInicial + pasoY;
            while (x != xFinal || y != yFinal) {
                if (matriz[x][y] != nullptr) return false;
                x += pasoX;
                y += pasoY;
            }
            return true;
        } else if (abs(xFinal - xInicial) == abs(yFinal - yInicial)) {
            int pasoX = (xFinal > xInicial) ? 1 : -1;
            int pasoY = (yFinal > yInicial) ? 1 : -1;
            int x = xInicial + pasoX, y = yInicial + pasoY;
            while (x != xFinal && y != yFinal) {
                if (matriz[x][y] != nullptr) return false;
                x += pasoX;
                y += pasoY;
            }
            return true;
        }
        return false;
    }
};

// Clase para el tablero
class Tablero {
private:
    Pieza* matriz[8][8]; // Matriz de 8x8 que representa el tablero de ajedrez
    Historial historial; // Agregamos el historial de movimientos
public:
    Tablero() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                matriz[i][j] = nullptr; // Inicializa todas las posiciones como vacías
            }
        }
        // Coloca las piezas en su posición inicial
        for (int i = 0; i < 8; i++) {
            matriz[1][i] = new Peon("blanco");
            matriz[6][i] = new Peon("negro");
        }
        matriz[0][4] = new Rey("blanco");
        matriz[7][4] = new Rey("negro");
        matriz[0][0] = new Torre("blanco");
        matriz[0][7] = new Torre("blanco");
        matriz[7][0] = new Torre("negro");
        matriz[7][7] = new Torre("negro");
        matriz[0][1] = new Caballo("blanco");
        matriz[0][6] = new Caballo("blanco");
        matriz[7][1] = new Caballo("negro");
        matriz[7][6] = new Caballo("negro");
        matriz[0][2] = new Alfil("blanco");
        matriz[0][5] = new Alfil("blanco");
        matriz[7][2] = new Alfil("negro");
        matriz[7][5] = new Alfil("negro");
        matriz[0][3] = new Reina("blanco");
        matriz[7][3] = new Reina("negro");
    }
    // Imprime el tablero de ajedrez en consola
    void imprimirTablero() {
        cout << "  a b c d e f g h" << endl;
        for (int i = 0; i < 8; i++) {
            cout << 8 - i << " ";
            for (int j = 0; j < 8; j++) {
                if (matriz[i][j] == nullptr) {
                    cout << ". ";
                } else {
                    if (matriz[i][j]->color == "blanco")
                        cout << "\033[1;37m" << matriz[i][j]->tipo << " \033[0m";
                    else
                        cout << "\033[1;30m" << matriz[i][j]->tipo << " \033[0m";
                }
            }
            cout << 8 - i << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }
    // Mueve una pieza en el tablero, si el movimiento es válido
    bool moverPieza(int xInicial, int yInicial, int xFinal, int yFinal, string turno) {
        Pieza* pieza = matriz[xInicial][yInicial];
        if (pieza == nullptr) {
            cout << "No hay una pieza en la posición inicial." << endl;
            return false;
        }
        if (pieza->color != turno) {
            cout << "Solo puedes mover tus propias piezas." << endl;
            return false;
        }
        if (pieza->movimientoValido(xInicial, yInicial, xFinal, yFinal, matriz)) {
            matriz[xFinal][yFinal] = pieza;
            matriz[xInicial][yInicial] = nullptr;
            historial.agregarMovimiento(xInicial, yInicial, xFinal, yFinal); // Guardamos el movimiento
            return true;
        }
        cout << "Movimiento inválido." << endl;
        return false;
    }
    // Comprueba si hay un rey de un color específico en el tablero
    bool hayRey(string color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (matriz[i][j] != nullptr && matriz[i][j]->tipo == 'K' && matriz[i][j]->color == color) {
                    return true;
                }
            }
        }
        return false;
    }
    // Imprime el historial de movimientos realizados en el tablero
    void imprimirHistorial() {
        historial.imprimirHistorial(); // Imprimimos el historial de movimientos
    }
};

// Función principal del juego
int main() {
    Tablero tablero;
    string turno = "blanco"; // Inicia el turno con las piezas blancas
    bool juegoTerminado = false; // Variable para verificar si el juego ha terminado

    while (!juegoTerminado) {
        tablero.imprimirTablero(); // Muestra el tablero
        cout << "Turno de " << turno << ". Ingrese su movimiento (ejemplo: e2 e4): ";
        string inicio, destino;
        cin >> inicio >> destino; // lee el movimiento

        // Convierte coordenadas de letras a índices de la matriz
        int xInicial = 8 - (inicio[1] - '0');
        int yInicial = inicio[0] - 'a';
        int xFinal = 8 - (destino[1] - '0');
        int yFinal = destino[0] - 'a';

        if (tablero.moverPieza(xInicial, yInicial, xFinal, yFinal, turno)) {
            tablero.imprimirHistorial(); // Mostramos el historial después de cada movimiento
            if (!tablero.hayRey("negro")) {
                cout << "¡Victoria para el jugador blanco!" << endl;
                juegoTerminado = true;
            } else if (!tablero.hayRey("blanco")) {
                cout << "¡Victoria para el jugador negro!" << endl;
                juegoTerminado = true;
            }
            turno = (turno == "blanco") ? "negro" : "blanco"; // Cambia el turno
        } else {
            cout << "Movimiento inválido. Intente de nuevo." << endl;
        }
    }

    return 0;
}
