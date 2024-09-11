#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Función para medir el tiempo
double getTime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

// Algoritmo cúbico tradicional
void multiplicacionCubicaTradicional(int **A, int **B, int **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Algoritmo cúbico optimizado (transposición)
void transponerMatriz(int **B, int **BT, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            BT[j][i] = B[i][j];
        }
    }
}

void multiplicacionCubicaOptimizada(int **A, int **B, int **C, int N) {
    int **BT = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        BT[i] = (int *)malloc(N * sizeof(int));
    }

    transponerMatriz(B, BT, N);  // Transponer la matriz B

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        free(BT[i]);
    }
    free(BT);
}

// Algoritmo de Strassen para multiplicación de matrices
void sumarMatrices(int **A, int **B, int **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void restarMatrices(int **A, int **B, int **C, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int **A, int **B, int **C, int N) {
    if (N == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = N / 2;
    int **A11 = (int **)malloc(newSize * sizeof(int *));
    int **A12 = (int **)malloc(newSize * sizeof(int *));
    int **A21 = (int **)malloc(newSize * sizeof(int *));
    int **A22 = (int **)malloc(newSize * sizeof(int *));
    int **B11 = (int **)malloc(newSize * sizeof(int *));
    int **B12 = (int **)malloc(newSize * sizeof(int *));
    int **B21 = (int **)malloc(newSize * sizeof(int *));
    int **B22 = (int **)malloc(newSize * sizeof(int *));
    int **C11 = (int **)malloc(newSize * sizeof(int *));
    int **C12 = (int **)malloc(newSize * sizeof(int *));
    int **C21 = (int **)malloc(newSize * sizeof(int *));
    int **C22 = (int **)malloc(newSize * sizeof(int *));
    int **M1 = (int **)malloc(newSize * sizeof(int *));
    int **M2 = (int **)malloc(newSize * sizeof(int *));
    int **M3 = (int **)malloc(newSize * sizeof(int *));
    int **M4 = (int **)malloc(newSize * sizeof(int *));
    int **M5 = (int **)malloc(newSize * sizeof(int *));
    int **M6 = (int **)malloc(newSize * sizeof(int *));
    int **M7 = (int **)malloc(newSize * sizeof(int *));
    int **temp1 = (int **)malloc(newSize * sizeof(int *));
    int **temp2 = (int **)malloc(newSize * sizeof(int *));

    for (int i = 0; i < newSize; i++) {
        A11[i] = (int *)malloc(newSize * sizeof(int));
        A12[i] = (int *)malloc(newSize * sizeof(int));
        A21[i] = (int *)malloc(newSize * sizeof(int));
        A22[i] = (int *)malloc(newSize * sizeof(int));
        B11[i] = (int *)malloc(newSize * sizeof(int));
        B12[i] = (int *)malloc(newSize * sizeof(int));
        B21[i] = (int *)malloc(newSize * sizeof(int));
        B22[i] = (int *)malloc(newSize * sizeof(int));
        C11[i] = (int *)malloc(newSize * sizeof(int));
        C12[i] = (int *)malloc(newSize * sizeof(int));
        C21[i] = (int *)malloc(newSize * sizeof(int));
        C22[i] = (int *)malloc(newSize * sizeof(int));
        M1[i] = (int *)malloc(newSize * sizeof(int));
        M2[i] = (int *)malloc(newSize * sizeof(int));
        M3[i] = (int *)malloc(newSize * sizeof(int));
        M4[i] = (int *)malloc(newSize * sizeof(int));
        M5[i] = (int *)malloc(newSize * sizeof(int));
        M6[i] = (int *)malloc(newSize * sizeof(int));
        M7[i] = (int *)malloc(newSize * sizeof(int));
        temp1[i] = (int *)malloc(newSize * sizeof(int));
        temp2[i] = (int *)malloc(newSize * sizeof(int));
    }

    // Dividir matrices A y B en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular M1 = (A11 + A22) * (B11 + B22)
    sumarMatrices(A11, A22, temp1, newSize);
    sumarMatrices(B11, B22, temp2, newSize);
    strassen(temp1, temp2, M1, newSize);

    // Calcular M2 = (A21 + A22) * B11
    sumarMatrices(A21, A22, temp1, newSize);
    strassen(temp1, B11, M2, newSize);

    // Calcular M3 = A11 * (B12 - B22)
    restarMatrices(B12, B22, temp2, newSize);
    strassen(A11, temp2, M3, newSize);

    // Calcular M4 = A22 * (B21 - B11)
    restarMatrices(B21, B11, temp2, newSize);
    strassen(A22, temp2, M4, newSize);

    // Calcular M5 = (A11 + A12) * B22
    sumarMatrices(A11, A12, temp1, newSize);
    strassen(temp1, B22, M5, newSize);

    // Calcular M6 = (A21 - A11) * (B11 + B12)
    restarMatrices(A21, A11, temp1, newSize);
    sumarMatrices(B11, B12, temp2, newSize);
    strassen(temp1, temp2, M6, newSize);

    // Calcular M7 = (A12 - A22) * (B21 + B22)
    restarMatrices(A12, A22, temp1, newSize);
    sumarMatrices(B21, B22, temp2, newSize);
    strassen(temp1, temp2, M7, newSize);

    // Calcular C11 = M1 + M4 - M5 + M7
    sumarMatrices(M1, M4, temp1, newSize);
    restarMatrices(temp1, M5, temp2, newSize);
    sumarMatrices(temp2, M7, C11, newSize);

    // Calcular C12 = M3 + M5
    sumarMatrices(M3, M5, C12, newSize);

    // Calcular C21 = M2 + M4
    sumarMatrices(M2, M4, C21, newSize);

    // Calcular C22 = M1 - M2 + M3 + M6
    restarMatrices(M1, M2, temp1, newSize);
    sumarMatrices(temp1, M3, temp2, newSize);
    sumarMatrices(temp2, M6, C22, newSize);

    // Unir submatrices en C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Liberar memoria
    for (int i = 0; i < newSize; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(C11[i]); free(C12[i]); free(C21[i]); free(C22[i]);
        free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]); free(M5[i]);
        free(M6[i]); free(M7[i]); free(temp1[i]); free(temp2[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
    free(M1); free(M2); free(M3); free(M4); free(M5);
    free(M6); free(M7); free(temp1); free(temp2);
}

// Función para leer las matrices desde un archivo
void leerMatriz(FILE *file, int ***matriz, int N) {
    *matriz = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        (*matriz)[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &(*matriz)[i][j]);
        }
    }
}

// Función para imprimir matrices
void imprimirMatriz(int **matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int N;  // Tamaño de la matriz
    int **A, **B, **C;

    // Leer matrices desde archivo
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Leer el tamaño de la matriz
    fscanf(file, "%d", &N);

    // Asignar memoria para la matriz de resultados
    C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        C[i] = (int *)malloc(N * sizeof(int));
    }

    // Leer las matrices A y B desde el archivo
    printf("Leyendo matrices...\n");
    leerMatriz(file, &A, N);
    leerMatriz(file, &B, N);
    fclose(file);

    // Medir tiempo de multiplicación cúbica tradicional
    double start = getTime();
    multiplicacionCubicaTradicional(A, B, C, N);
    double end = getTime();
    printf("\nResultado de la multiplicación cúbica tradicional:\n");
    imprimirMatriz(C, N);
    printf("Tiempo: %.8f segundos\n", end - start);

    // Medir tiempo de multiplicación cúbica optimizada
    start = getTime();
    multiplicacionCubicaOptimizada(A, B, C, N);
    end = getTime();
    printf("\nResultado de la multiplicación cúbica optimizada:\n");
    imprimirMatriz(C, N);
    printf("Tiempo: %.8f segundos\n", end - start);

    // Medir tiempo de multiplicación de Strassen
    start = getTime();
    strassen(A, B, C, N);
    end = getTime();
    printf("\nResultado de la multiplicación de Strassen:\n");
    imprimirMatriz(C, N);
    printf("Tiempo: %.8f segundos\n", end - start);

    // Liberar memoria
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
