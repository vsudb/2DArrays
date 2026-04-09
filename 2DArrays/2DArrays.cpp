#include <iostream>


// Универсальный макрос для статических массивов:
#define ARRAY_ROWS(a)  (sizeof(a) / sizeof(a[0]))
#define ARRAY_COLS(a)  (sizeof(a[0]) / sizeof(a[0][0]))

using namespace std;


int main() {
    int arr[5] = { 1, 2, 3, 4, 5 };
    int (*p)[5] = &arr;   // p хранит адрес массива arr целиком

    printf("%d\n", (*p)[2]);
    // Доступ к элементам:
    // (*p)[0]  // → 1
    // (*p)[2]  // → 3

    // Или через двойную индексацию (если p указывает на строку матрицы):
    //p[0][2]  // → 3


    int matrix[3][5] = {
    {1,  2,  3,  4,  5},
    {6,  7,  8,  9, 10},
    {11, 12, 13, 14, 15}
    };

    int (*pM)[5] = matrix;  // p указывает на первую строку

    pM++;                   // теперь p указывает на вторую строку (сдвиг на 5*sizeof(int) байт)
    printf("%d\n", pM[0][1]); // → 7


    printf("ROW = %d\n", (int)ARRAY_ROWS(matrix));
    printf("COL = %d\n", (int)ARRAY_COLS(matrix));

}