#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 *  ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ: обмен двух указателей int*
 * ========================================================= */
void swapPtr(int** a, int** b) {
    int* tmp = *a;
    *a = *b;
    *b = tmp;
}

/* =========================================================
 *  ВЫВОД МАССИВА
 *  Работает одинаково для jagged-массива и linear-массива
 *  (оба передаются как int**).
 * ========================================================= */
void printArray(int** arr, int ROW, int COL) {
    printf("----------------\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%2d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("----------------\n");
}

/* =========================================================
 *  JAGGED-МАССИВ (массив указателей)
 *
 *  Схема памяти:
 *    arr → [ int* | int* | int* | ... ]   (ROW указателей, Heap)
 *               |      |      |
 *             [int]  [int]  [int]          (каждая строка — отдельный блок Heap)
 *
 *  Строки расположены в РАЗНЫХ местах кучи.
 *  Достоинство: можно менять строки местами за O(1) (swap указателей).
 *  Недостаток: нет гарантии непрерывности памяти между строками.
 * ========================================================= */

 /* Создание jagged-массива */
int** createArray(int ROW, int COL) {
    /* Выделяем массив из ROW указателей */
    int** arr = (int**)malloc(ROW * sizeof(int*));
    if (!arr) { perror("malloc"); exit(1); }

    for (int i = 0; i < ROW; i++) {
        /* Каждая строка — отдельный блок в куче */
        *(arr + i) = (int*)malloc(COL * sizeof(int));
        if (!*(arr + i)) { perror("malloc"); exit(1); }

        for (int j = 0; j < COL; j++) {
            *(*(arr + i) + j) = i + 1;   /* строка i заполняется значением i+1 */
        }
    }
    /* arr[0] → [1][1][1][1][1]
       arr[1] → [2][2][2][2][2]
       arr[2] → [3][3][3][3][3] */
    return arr;
}

/* Удаление jagged-массива */
void deleteArray(int** arr, int ROW) {
    for (int i = 0; i < ROW; i++) {
        free(*(arr + i));   /* освобождаем каждую строку */
    }
    free(arr);              /* освобождаем массив указателей */
}

/* Быстрая перестановка соседних строк (swap указателей, данные не копируются) */
void transformArray(int** arr, int ROW) {
    for (int i = 0; i < (ROW / 2) * 2; i += 2) {
        swapPtr(arr + i, arr + i + 1);
    }
}

/* Дублирование каждой строки: строка i → строки 2i и 2i+1 (shallow copy) */
int** changeArray(int** in, int ROW) {
    int** out = (int**)malloc(ROW * 2 * sizeof(int*));
    if (!out) { perror("malloc"); exit(1); }

    for (int i = 0; i < ROW * 2; i += 2) {
        *(out + i) = *(in + i / 2);   /* обе строки указывают на один блок */
        *(out + i + 1) = *(in + i / 2);
    }
    return out;
    /* Внимание: out не владеет данными строк — их освобождает deleteArray(in).
       Поэтому освобождаем только сам массив указателей: free(out). */
}

/* =========================================================
 *  LINEAR-МАССИВ (contiguous 2D array)
 *
 *  Схема памяти:
 *    data → [ int | int | int | int | int | int | ... ]   (ROW*COL int подряд, один блок Heap)
 *    ptrs → [ int* | int* | int* | ... ]                  (ROW указателей, один блок Heap)
 *              |        |        |
 *           data+0  data+COL  data+2*COL
 *
 *  Все элементы лежат в ОДНОМ непрерывном блоке памяти.
 *  Достоинства:
 *    - кэш-дружественный обход;
 *    - одно выделение памяти для данных (меньше фрагментации);
 *    - можно передавать в функции, ожидающие плоский int*.
 *  Недостаток: swap строк требует копирования данных (или отдельного массива ptrs).
 * ========================================================= */

 /* Создание linear-массива.
  * Возвращает int** — массив указателей на строки единого блока данных.
  * Для освобождения используйте deleteLinearArray(). */
int** createLinearArray(int ROW, int COL) {
    /* 1. Один непрерывный блок для всех данных */
    int* data = (int*)malloc(ROW * COL * sizeof(int));


    /* 2. Массив указателей на начало каждой строки */
    int** ptrs = (int**)malloc(ROW * sizeof(int*));
 
    for (int i = 0; i < ROW; i++) {
        *(ptrs + i) = data + i * COL;   /* ptrs[i] указывает на i-ю строку блока data */

        for (int j = 0; j < COL; j++) {
            *(*(ptrs + i) + j) = i + 1; /* строка i заполняется значением i+1 */
        }
    }
    return ptrs;
}

/* Удаление linear-массива.
 * ptrs[0] хранит начало единого блока данных — освобождаем его первым. */
void deleteLinearArray(int** ptrs) {
    free(*ptrs);   /* free(ptrs[0]) — освобождает весь блок данных */
    free(ptrs);    /* освобождает массив указателей */
}

/* =========================================================
 *  MAIN
 * ========================================================= */
int main(void) {
    int ROW = 7, COL = 5;

    /* --- Jagged-массив Зазубренный--- */
    printf("=== Jagged-массив (createArray) ===\n");
    int** arr = createArray(ROW, COL);
    printArray(arr, ROW, COL);

    printf("=== После transformArray (swap соседних строк) ===\n");
    transformArray(arr, ROW);
    printArray(arr, ROW, COL);

    printf("=== changeArray: каждая строка продублирована ===\n");
    int** out = changeArray(arr, ROW);
    printArray(out, ROW * 2, COL);
    free(out);          /* освобождаем только массив указателей */
    deleteArray(arr, ROW);

    /* --- Linear-массив --- */
    printf("=== Linear-массив (createLinearArray) ===\n");
    int** lin = createLinearArray(ROW, COL);
    printArray(lin, ROW, COL);

    /* Демонстрация: данные лежат непрерывно — можно обойти плоским указателем */
    printf("=== Плоский обход linear-массива ===\n");
    int* flat = *lin;   /* flat = lin[0] = начало блока данных */
    for (int k = 0; k < ROW * COL; k++) {
        printf("%2d%c", flat[k], (k + 1) % COL == 0 ? '\n' : ' ');
    }

    deleteLinearArray(lin);

    return 0;
}
