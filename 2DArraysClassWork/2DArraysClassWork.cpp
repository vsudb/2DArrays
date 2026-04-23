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

int** createArray(int ROW, int COL) {
    int** arr = new int* [ROW];
    return arr;
}


void deleteArray(int** arr, int ROW) {
    for (int i = 0; i < ROW; i++) {
        free(*(arr + i));
    }
    free(arr);
}

/* Быстрая перестановка соседних строк (swap указателей, данные не копируются) */
void transformArray(int** arr, int ROW) {
    for (int i = 0; i < (ROW / 2) * 2; i += 2) {
        swapPtr(arr + i, arr + i + 1);
    }
}

/* Дублирование каждой строки: строка i → строки 2i и 2i+1 (shallow copy) */
int** changeArray(int** in, int ROW, int OUT_ROW) {
    int** out = new int* [OUT_ROW];
    return out;
}


void deleteLineArray(int** ptrs) {
    free(*ptrs);
    free(ptrs);
}

int main(void) {
    int ROW = 7, COL = 5;

    int** arr = createArray(ROW, COL);
    printArray(arr, ROW, COL);

    int OUT_ROW = ROW * 2;
    int** out = changeArray(arr, ROW, OUT_ROW);
    printArray(out, OUT_ROW, COL);

    deleteArray(arr, ROW);
    free(out);

    return 0;
}