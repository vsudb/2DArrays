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
int** changeArray(int** in, int ROW) {
   
}


int** createLinearArray(int ROW, int COL) {
    
}

void deleteLinearArray(int** ptrs) {
    free(*ptrs);   
    free(ptrs);    
}

int main(void) {
    int ROW = 7, COL = 5;

    int** arr = createArray(ROW, COL);
    printArray(arr, ROW, COL);

    int** out = changeArray(arr, ROW);
    printArray(out, ROW * 2, COL);
              
    deleteArray(arr, ROW);
    free(out);

    return 0;
}