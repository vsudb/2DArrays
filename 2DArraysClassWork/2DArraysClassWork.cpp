#include <stdio.h>
const int ROW = 5;
const int COL = 5;

void print(int m[ROW][COL], int ROW, int COL);  //стандарт C99 и выше
int sum_of_diagonals(int m[ROW][COL], int ROW, int COL);
void transponse(int m[ROW][COL], int ROW, int COL);
void add_matrix(int A[ROW][COL], int B[ROW][COL], int ROW, int COL);

void print(int m[ROW][COL], int ROW, int COL) {
    printf("----------\n");

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("----------\n");
}


int sum_of_diagonals(int m[ROW][COL], int ROW, int COL) {
    int sum = 0;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) {
            if (i == j || (i + j) == ROW - 1) {
                sum += m[i][j];
            }
        }
    }
    return sum;
}

void transponse(int m[ROW][COL], int ROW, int COL) {
    int temp;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) {
            temp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = temp;
            if (i == j) {
                break;
            }
        }
    }

}


// Финальный результат сложения матриц записать в матрицу А
void add_matrix(int A[ROW][COL], int B[ROW][COL], int ROW, int COL) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) {
            A[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    //-------------------------------------------------------------
    // 1) Подсчитайте сумму чисел главной и побочной диагонали матрицы 25 баллов
    //-------------------------------------------------------------
    printf("1)---SUM_OF_DIAGONALS\n");

    int m[][COL] = { {1, 5, 5, 5, 1},
                    {5, 1, 5, 1, 5},
                    {5, 5, 9, 5, 5},
                    {5, 1, 5, 1, 5},
                    {1, 5, 5, 5, 1} };



    print(m, ROW, COL);
    int sum = sum_of_diagonals(m, ROW, COL);

    printf("---------------------\n");
    printf("SUM_OF_DIAGONALS = %d\n", sum);
    printf("---------------------\n");


    //-------------------------------------------------------------
    // 2) Транспонирование матрицы 
    //    Поменяйте строки и столбцы местами 
    //    (работаем в тойже матрице, без создания новой матрицы) + 10 баллов
    //-------------------------------------------------------------
    printf("2)------------\n");
    printf("--TRANSPONSE--\n");
    //printf("--------------\n");

    int t[][COL] = { {1, 1, 1, 1, 1},
                    {2, 2, 2, 2, 2},
                    {3, 3, 3, 3, 3},
                    {4, 4, 4, 4, 4},
                    {5, 5, 5, 5, 5} };

    print(t, ROW, COL);
    
    int temp;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < ROW; j++) {
            temp = t[i][j];
            t[i][j] = t[j][i];
            t[j][i] = temp;
            if (i == j) {
                break;
            }
        }
    }
    
    //transponse(t, ROW, COL);
    print(t, ROW, COL);

    //-------------------------------------------------------------
    // 3) Сложение матриц  + 10 баллов
    //-------------------------------------------------------------
    printf("3)------------\n");
    printf("--ADD_MATRIX--\n");


    int A[][COL] = { {5, 5, 5, 5, 5},
                    {5, 5, 5, 5, 5},
                    {5, 5, 5, 5, 5},
                    {5, 5, 5, 5, 5},
                    {5, 5, 5, 5, 5} };

    int B[][COL] = { {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 3, 8, 8},
                    {8, 8, 8, 8, 8},
                    {8, 8, 8, 8, 8} };

    print(A, ROW, COL);
    print(B, ROW, COL);
    add_matrix(A, B, ROW, COL);
    print(A, ROW, COL);


    //-------------------------------------------------------------
    // 4) Умножение матриц !!!(Для отчаянных на 50 баллов)
    //    количество столбцов первой матрицы должно совпадать с количеством строк второй.
    //    Если матрица АA имеет размер IxK, а матрица BB KxJ
    //    , то их произведение будет иметь размер IxJ
    //-------------------------------------------------------------
    printf("4)------------\n");
    printf("--MULT_MATRIX--\n");


    int const ROW_A = 5, COL_A = 3,
        ROW_B = 3, COL_B = 4;

    int AA[ROW_A][COL_A] = { {5, 5, 5},
                            {5, 5, 5},
                            {5, 5, 5},
                            {5, 5, 5},
                            {5, 5, 5} };

    int BB[ROW_B][COL_B] = { {7, 7, 7, 7},
                            {8, 8, 8, 8},
                            {9, 9, 9, 9} };

    int C[ROW_A][COL_B];

    //------------------------------------------------------------------------
    // AA(5x3) * BB(3x4) = C(5x4)
    // Здесь пишим перемножение матриц AA[5][3] и BB[3][4] и записываем в C[5][4]
    //------------------------------------------------------------------------




    /*printf("----------\n");

    for (int i = 0; i < ROW_A; i++) {
        for (int j = 0; j < COL_B; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    printf("----------\n");*/


    return 0;
}