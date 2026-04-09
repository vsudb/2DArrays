#include <iostream>
using namespace std;

void printArray(int** arr, int ROW, int COL) {
    printf("----------------\n");
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            //printf("%2d ", arr[i][j]);
            printf("%2d ", *(*(arr + i) + j));
        }
        printf("\n");
    }
    printf("----------------\n");
}

int** createArray(int ROW, int COL) {
    // Массив массивов - двумерный массив
    int** arr = new int* [ROW]; //Указатель на массив указателей arr → [int*][int*][int*] ... [int*]  (ROW элементов)
    for (int i = 0; i < ROW; i++) {
        *(arr + i) = new int[COL];  //созданные массивы будут храняться в разных частях сегмента VirtualMemory (Heap)

        for (int j = 0; j < COL; j++) {
            *(*(arr + i) + j) = i + 1;
        }
    }

    //arr[0] → [1][1][1][1]
    //arr[1] → [2][2][2][2]
    //arr[2] → [3][3][3][3]
    return arr;
}


void deleteArray(int** arr, int ROW) {
    for (int i = 0; i < ROW; i++) {
        delete[] * (arr + i);
    }
    delete[] arr;
}

// быстрая перестановка строк в матрице без копирования самих данных
void transformArray(int** arr, int ROW, int COL) {
    for (int i = 0; i < ROW / 2 * 2; i += 2) {
        swap(*(arr + i), *(arr + i + 1));
    }
}


int** changeArray(int** in, int ROW) {

    int** out = new int* [ROW * 2];

    for (int i = 0; i < ROW * 2; i += 2) {
        *(out + i) = *(in + i / 2);
        *(out + i + 1) = *(in + i / 2);
    }

    return out;
}


int main()
{
    int ROW = 7, COL = 5;

    int** arr = createArray(ROW, COL);

    printArray(arr, ROW, COL);

    //transformArray(arr, ROW, COL);
    //printArray(arr, ROW, COL);

    int** out = changeArray(arr, ROW);

    printArray(out, ROW * 2, COL);

    deleteArray(arr, ROW);
    delete[] out;

    //deleteLineArray(arr);

    //cin.ignore();
    //int arrStatic[3][4] = { {1,2,3,4},{5,5,5,5},{4,4,4,4}}; // stack 1MB
    //int* arrDynamic = new int[5]{ 1,2,3,4,5 }; // heap 4Gb

}