#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILAS 10
#define COLUMNAS 10
#define ARCHIVO_GUARDADO "estado_juego.txt"

void inicializarTablero(int **tablero, int filas, int columnas);
void mostrarTablero(int **tablero, int **revelado, int filas, int columnas, int revelarTodo);
int despejarCasilla(int **tablero, int **revelado, int fila, int columna);
void guardarEstadoJuego(int **tablero, int **revelado, int filas, int columnas, int puntos, const char *nombreArchivo);
int cargarEstadoJuego(int **tablero, int **revelado, int filas, int columnas, int *puntos, const char *nombreArchivo);

int main() {
    int **tablero = (int **)malloc(FILAS * sizeof(int *));
    int **revelado = (int **)malloc(FILAS * sizeof(int *));
    for (int i = 0; i < FILAS; i++) {
        tablero[i] = (int *)malloc(COLUMNAS * sizeof(int));
        revelado[i] = (int *)malloc(COLUMNAS * sizeof(int));
        for (int j = 0; j < COLUMNAS; j++) {
            revelado[i][j] = 0; // Inicializar todas las casillas como no reveladas
        }
    }

    int fila, columna;
    int puntos = 0;
    int juegoTerminado = 0;
    char opcion;

    // Verificar si hay una partida guardada
    FILE *archivo = fopen(ARCHIVO_GUARDADO, "r");
    if (archivo != NULL) {
        fclose(archivo);
        printf("Se encontró una partida guardada. ¿Desea cargarla? (s/n): ");
        scanf(" %c", &opcion);
        if (opcion == 's' || opcion == 'S') {
            if (cargarEstadoJuego(tablero, revelado, FILAS, COLUMNAS, &puntos, ARCHIVO_GUARDADO)) {
                printf("Partida cargada exitosamente.\n");
            } else {
                printf("Error al cargar la partida. Iniciando nueva partida.\n");
                inicializarTablero(tablero, FILAS, COLUMNAS);
            }
        } else {
            inicializarTablero(tablero, FILAS, COLUMNAS);
        }
    } else {
        inicializarTablero(tablero, FILAS, COLUMNAS);
    }

    srand(time(NULL));

    while (!juegoTerminado) {
        mostrarTablero(tablero, revelado, FILAS, COLUMNAS, 0);
        printf("Ingrese las coordenadas para despejar (fila columna): ");
        if (scanf("%d %d", &fila, &columna) != 2) {
            printf("Entrada inválida. Por favor ingrese dos números enteros.\n");
            // Limpiar el buffer de entrada
            while (getchar() != '\n');
            continue;
        }

        if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) {
            printf("Coordenadas fuera de rango. Intente nuevamente.\n");
            continue;
        }

        if (despejarCasilla(tablero, revelado, fila, columna) == 1) {
            juegoTerminado = 1;
            printf("¡Has encontrado una mina! Fin del juego.\n");
        } else {
            puntos++;
            // Verificar si todas las casillas vacías han sido despejadas
            int todasDespejadas = 1;
            for (int i = 0; i < FILAS; i++) {
                for (int j = 0; j < COLUMNAS; j++) {
                    if (tablero[i][j] == 0 && revelado[i][j] == 0) {
                        todasDespejadas = 0;
                        break;
                    }
                }
                if (!todasDespejadas) break;
            }
            if (todasDespejadas) {
                juegoTerminado = 1;
                printf("¡Has despejado todas las casillas vacías! Ganaste.\n");
            }
        }
    }

    mostrarTablero(tablero, revelado, FILAS, COLUMNAS, 1);
    printf("Puntuación final: %d\n", puntos);

    // Guardar el estado del juego en un archivo
    guardarEstadoJuego(tablero, revelado, FILAS, COLUMNAS, puntos, ARCHIVO_GUARDADO);

    // Liberar memoria
    for (int i = 0; i < FILAS; i++) {
        free(tablero[i]);
        free(revelado[i]);
    }
    free(tablero);
    free(revelado);

    return 0;
}

void inicializarTablero(int **tablero, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = rand() % 2; // 0 o 1 aleatorio
        }
    }
}

void mostrarTablero(int **tablero, int **revelado, int filas, int columnas, int revelarTodo) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (revelarTodo) {
                if (tablero[i][j] == 0) {
                    printf("0 "); // Mostrar 'X' en lugar de '0'
                } else if (tablero[i][j] == 'X') {
                        printf("X "); // Mostrar 'X' en lugar de '0'
                    } else{
                    printf("%d ", tablero[i][j]);
                }
            } else {
                if (revelado[i][j]) {
                    if (tablero[i][j] == 0) {
                        printf("X "); // Mostrar 'X' en lugar de '0'
                    } else {
                        printf("%d ", tablero[i][j]);
                    }
                } else {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }
}

int despejarCasilla(int **tablero, int **revelado, int fila, int columna) {
    revelado[fila][columna] = 1;
    return tablero[fila][columna];
}

void guardarEstadoJuego(int **tablero, int **revelado, int filas, int columnas, int puntos, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el estado del juego.\n");
        return;
    }

    fprintf(archivo, "Puntos: %d\n", puntos);
    fprintf(archivo, "Tablero:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fprintf(archivo, "%d ", tablero[i][j]);
        }
        fprintf(archivo, "\n");
    }

    fprintf(archivo, "Revelado:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fprintf(archivo, "%d ", revelado[i][j]);
        }
        fprintf(archivo, "\n");
    }

    fclose(archivo);
}

int cargarEstadoJuego(int **tablero, int **revelado, int filas, int columnas, int *puntos, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        return 0;
    }

    if (fscanf(archivo, "Puntos: %d\n", puntos) != 1) {
        fclose(archivo);
        return 0;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), archivo) == NULL || strncmp(buffer, "Tablero:", 8) != 0) {
        fclose(archivo);
        return 0;
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (fscanf(archivo, "%d", &tablero[i][j]) != 1) {
                fclose(archivo);
                return 0;
            }
        }
    }

    if (fgets(buffer, sizeof(buffer), archivo) == NULL || strncmp(buffer, "Revelado:", 9) != 0) {
        fclose(archivo);
        return 0;
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (fscanf(archivo, "%d", &revelado[i][j]) != 1) {
                fclose(archivo);
                return 0;
            }
        }
    }

    fclose(archivo);
    return 1;
}