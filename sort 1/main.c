#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Función para ordenar usando Selection Sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
    // Iteramos sobre el arreglo
    for (i = 0; i < n-1; i++) {
        min_idx = i;  // Suponemos que el primer elemento no ordenado es el mínimo
        // Buscamos el elemento más pequeño en la parte no ordenada
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;  // Actualizamos el índice del elemento más pequeño
        // Intercambiamos el elemento más pequeño con el primer elemento no ordenado
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Función para ordenar usando Bubble Sort
void bubbleSort(int arr[], int n) {
    int i, j;
    // Recorremos el arreglo varias veces
    for (i = 0; i < n-1; i++) {
        // Comparamos e intercambiamos elementos adyacentes si están en el orden incorrecto
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Función para ordenar usando Insertion Sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    // Iteramos desde el segundo elemento hasta el último
    for (i = 1; i < n; i++) {
        key = arr[i];  // Guardamos el valor actual
        j = i - 1;
        // Movemos los elementos que son mayores que la clave un lugar hacia adelante
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;  // Insertamos la clave en su lugar correcto
    }
}

// Función auxiliar para combinar dos subarreglos en Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    // Tamaños de los subarreglos
    int n1 = m - l + 1;
    int n2 = r - m;

    // Arreglos temporales
    int L[n1], R[n2];

    // Copiamos los datos en los subarreglos temporales
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Mezclamos los subarreglos de vuelta al arreglo original
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiamos los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiamos los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal de Merge Sort
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;  // Encontramos el punto medio
        mergeSort(arr, l, m);     // Ordenamos la primera mitad
        mergeSort(arr, m + 1, r); // Ordenamos la segunda mitad
        merge(arr, l, m, r);      // Mezclamos ambas mitades
    }
}

// Función auxiliar para intercambiar dos elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Función auxiliar para dividir el arreglo en Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Elegimos el último elemento como pivote
    int i = (low - 1);      // Índice del elemento más pequeño

    // Recorremos el arreglo y colocamos los elementos menores al pivote a la izquierda
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // Intercambiamos
        }
    }
    swap(&arr[i + 1], &arr[high]);  // Colocamos el pivote en su lugar
    return (i + 1);
}

// Función principal de Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Obtenemos el índice de partición
        quickSort(arr, low, pi - 1);  // Ordenamos los elementos a la izquierda del pivote
        quickSort(arr, pi + 1, high); // Ordenamos los elementos a la derecha del pivote
    }
}

// Función de comparación para qsort estándar de la biblioteca
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Función que usa qsort de la biblioteca estándar
void sortStandard(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare);  // qsort con la función de comparación definida
}

// Función para imprimir el arreglo
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Función para perfilar un algoritmo de ordenamiento
void profileSort(void (*sortFunc)(int[], int), int arr[], int n, const char* name) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();  // Inicia el cronómetro
    sortFunc(arr, n); // Ejecuta la función de ordenamiento
    end = clock();    // Termina el cronómetro

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // Calcula el tiempo usado
    printf("%s took %f seconds to execute\n", name, cpu_time_used);  // Imprime el tiempo
    printf("Sorted array using %s: ", name);  // Imprime el arreglo ordenado
    printArray(arr, n);
}

// Variante de la función profile para algoritmos que requieren índices (como Quick y Merge Sort)
void profileSortWithIndices(void (*sortFunc)(int[], int, int), int arr[], int l, int r, const char* name) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();  // Inicia el cronómetro
    sortFunc(arr, l, r);  // Ejecuta la función de ordenamiento
    end = clock();    // Termina el cronómetro

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // Calcula el tiempo usado
    printf("%s took %f seconds to execute\n", name, cpu_time_used);  // Imprime el tiempo
    printf("Sorted array using %s: ", name);  // Imprime el arreglo ordenado
    printArray(arr, r + 1);
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);  // Lee la cantidad de elementos

    int arr[n];  // Crea un arreglo de tamaño n
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);  // Lee los elementos del arreglo
    }

    // Clonamos el arreglo original para que cada algoritmo opere sobre los mismos datos.
    int arrSelection[n], arrBubble[n], arrInsertion[n], arrMerge[n], arrQuick[n], arrStandard[n];
    memcpy(arrSelection, arr, n * sizeof(int));  // Copiamos el arreglo original
    memcpy(arrBubble, arr, n * sizeof(int));
    memcpy(arrInsertion, arr, n * sizeof(int));
    memcpy(arrMerge, arr, n * sizeof(int));
    memcpy(arrQuick, arr, n * sizeof(int));
    memcpy(arrStandard, arr, n * sizeof(int));


    profileSort(selectionSort, arrSelection, n, "Selection Sort");


    profileSort(bubbleSort, arrBubble, n, "Bubble Sort");


    profileSort(insertionSort, arrInsertion, n, "Insertion Sort");


    profileSortWithIndices(mergeSort, arrMerge, 0, n - 1, "Merge Sort");


    profileSortWithIndices(quickSort, arrQuick, 0, n - 1, "Quick Sort");


    profileSort(sortStandard, arrStandard, n, "Standard Library Sort");

    return 0;
}
