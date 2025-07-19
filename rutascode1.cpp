#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

enum Terreno {
    LIBRE = 0,
    EDIFICIO = 1,
    AGUA = 2,
    BLOQUEADO_TEMP = 3
};

struct Nodo {
    int x, y;
};

class Ciudad {
private:
    vector<vector<int>> mapa;
    int filas, columnas;
    Nodo inicio, fin;

public:
    Ciudad(int f, int c) : filas(f), columnas(c) {
        mapa.resize(filas, vector<int>(columnas, LIBRE));
        srand(time(nullptr));
    }

    void imprimirMapa(const vector<vector<char>>& visual = {}) const {
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                if (!visual.empty()) {
                    cout << visual[i][j] << ' ';
                } else {
                    switch (mapa[i][j]) {
                        case LIBRE: cout << ". "; break;
                        case EDIFICIO: cout << "# "; break;
                        case AGUA: cout << "~ "; break;
                        case BLOQUEADO_TEMP: cout << "X "; break;
                    }
                }
            }
            cout << endl;
        }
    }

    void configurarTerreno(int x, int y, int tipo) {
        if (esValido(x, y, true)) mapa[x][y] = tipo;
    }

    void setInicio(int x, int y) {
        if (esValido(x, y, false)) inicio = {x, y};
        else cout << "\nInicio invalido.\n";
    }

    void setFin(int x, int y) {
        if (esValido(x, y, false)) fin = {x, y};
        else cout << "\nDestino invalido.\n";
    }

    vector<Nodo> buscarRutaAnimada(bool permitirAgua = false) {
        vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));
        vector<vector<Nodo>> padre(filas, vector<Nodo>(columnas, {-1, -1}));
        queue<Nodo> q;
        q.push(inicio);
        visitado[inicio.x][inicio.y] = true;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        while (!q.empty()) {
            Nodo actual = q.front(); q.pop();

            // Visualización de búsqueda
            vector<vector<char>> visual(filas, vector<char>(columnas));
            for (int i = 0; i < filas; ++i) {
                for (int j = 0; j < columnas; ++j) {
                    if (i == actual.x && j == actual.y)
                        visual[i][j] = 'O'; // Posición actual
                    else if (visitado[i][j])
                        visual[i][j] = '.'; // Visitado
                    else {
                        switch (mapa[i][j]) {
                            case LIBRE: visual[i][j] = '.'; break;
                            case EDIFICIO: visual[i][j] = '#'; break;
                            case AGUA: visual[i][j] = '~'; break;
                            case BLOQUEADO_TEMP: visual[i][j] = 'X'; break;
                        }
                    }
                }
            }
            visual[inicio.x][inicio.y] = 'A';
            visual[fin.x][fin.y] = 'Z';

            system("cls"); // Limpiar pantalla en Windows
            imprimirMapa(visual);
            this_thread::sleep_for(chrono::milliseconds(100));

            if (actual.x == fin.x && actual.y == fin.y)
                return reconstruirRuta(padre);

            for (int d = 0; d < 4; ++d) {
                int nx = actual.x + dx[d], ny = actual.y + dy[d];
                if (esValido(nx, ny, false) && !visitado[nx][ny]) {
                    if (mapa[nx][ny] == LIBRE || (permitirAgua && mapa[nx][ny] == AGUA)) {
                        visitado[nx][ny] = true;
                        padre[nx][ny] = actual;
                        q.push({nx, ny});
                    }
                }
            }
        }
        return {}; // sin camino
    }

    vector<Nodo> reconstruirRuta(const vector<vector<Nodo>>& padre) {
        vector<Nodo> ruta;
        Nodo actual = fin;
        while (!(actual.x == inicio.x && actual.y == inicio.y)) {
            ruta.push_back(actual);
            actual = padre[actual.x][actual.y];
        }
        ruta.push_back(inicio);
        reverse(ruta.begin(), ruta.end());
        return ruta;
    }

    void mostrarRutaFinal(const vector<Nodo>& ruta) {
        vector<vector<char>> visual(filas, vector<char>(columnas));
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                switch (mapa[i][j]) {
                    case LIBRE: visual[i][j] = '.'; break;
                    case EDIFICIO: visual[i][j] = '#'; break;
                    case AGUA: visual[i][j] = '~'; break;
                    case BLOQUEADO_TEMP: visual[i][j] = 'X'; break;
                }
            }
        }
        for (auto p : ruta) {
            if (!(p.x == inicio.x && p.y == inicio.y) && !(p.x == fin.x && p.y == fin.y))
                visual[p.x][p.y] = 'o';
        }
        visual[inicio.x][inicio.y] = 'A';
        visual[fin.x][fin.y] = 'Z';
        imprimirMapa(visual);
    }

    bool esValido(int x, int y, bool ignorarBloqueo = false) const {
        if (x < 0 || x >= filas || y < 0 || y >= columnas) return false;
        int celda = mapa[x][y];
        if (ignorarBloqueo) return true;
        return celda != EDIFICIO && celda != BLOQUEADO_TEMP;
    }
};

int main() {
    int f, c;
    cout << "Tamaño del mapa (filas columnas): ";
    cin >> f >> c;
    Ciudad ciudad(f, c);

    int obs;
    cout << "\nCantidad de obstaculos: ";
    cin >> obs;
    for (int i = 0; i < obs; ++i) {
        int x, y, tipo;
        cout << "Obstaculo " << i + 1 << " - Coordenadas (x y) y tipo [1=Edificio, 2=Agua, 3=Bloqueado]: ";
        cin >> x >> y >> tipo;
        ciudad.configurarTerreno(x, y, tipo);
    }

    int ix, iy, fx, fy;
    cout << "\nIngrese coordenadas de INICIO (x y): ";
    cin >> ix >> iy;
    ciudad.setInicio(ix, iy);

    cout << "Ingrese coordenadas de FIN (x y): ";
    cin >> fx >> fy;
    ciudad.setFin(fx, fy);

    cout << "\nBuscando ruta...\n";
    auto ruta = ciudad.buscarRutaAnimada(false);

    if (ruta.empty()) {
        cout << "\nRuta directa bloqueada. Intentando con AGUA...\n";
        this_thread::sleep_for(chrono::seconds(1));
        ruta = ciudad.buscarRutaAnimada(true);
    }

    if (!ruta.empty()) {
        cout << "\nRuta encontrada:\n";
        ciudad.mostrarRutaFinal(ruta);
        cout << "\nLongitud: " << ruta.size() - 1 << " pasos\n";
    } else {
        cout << "\nNo se encontro ninguna ruta valida.\n";
    }

    return 0;
}
