#include <stdio.h>
#include <stdlib.h>

/* =========================================================
 *  СТРУКТУРА Matrix
 *
 *  Инкапсулирует указатель на данные и размеры массива.
 *  Теперь функциям не нужно принимать ROW и COL отдельно —
 *  всё хранится внутри структуры.
 *
 *  Поле `data`  — массив указателей на строки (int**).
 *  Поле `rows`  — количество строк.
 *  Поле `cols`  — количество столбцов.
 *
 *  Для jagged-массива каждая строка выделяется отдельно.
 *  Для linear-массива все данные лежат в одном блоке,
 *  а data[0] указывает на его начало.
 * ========================================================= */
typedef struct {
    int** data;   /* массив указателей на строки */
    int   rows;
    int   cols;
} Matrix;

/* =========================================================
 *  ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ
 * ========================================================= */
static void swapPtr(int** a, int** b) {
    int* tmp = *a; 
    *a = *b; 
    *b = tmp;
}

/* =========================================================
 *  JAGGED-МАССИВ
 *  Строки расположены в разных местах кучи.
 * ========================================================= */

 /* Создание: возвращает структуру Matrix по значению */
Matrix createJagged(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;

    m.data = (int**)malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        m.data[i] = (int*)malloc(cols * sizeof(int));
        
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = i + 1;   /* строка i заполняется значением i+1 */
        }
    }
    return m;
}

/* Удаление jagged-матрицы */
void deleteJagged(Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

/* =========================================================
 *  LINEAR-МАССИВ (contiguous)
 *  Все данные лежат в одном непрерывном блоке.
 *  data[0] == начало блока данных.
 * ========================================================= */

 /* Создание: возвращает структуру Matrix по значению */
Matrix createLinear(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;

    /* Один блок для всех данных */
    int* block = (int*)malloc(rows * cols * sizeof(int));
    
    /* Массив указателей на начало каждой строки */
    m.data = (int**)malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        m.data[i] = block + i * cols;   /* указатель на i-ю строку блока */
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = i + 1;
        }
    }
    return m;
}

/* Удаление linear-матрицы:
   data[0] — начало единого блока данных */
void deleteLinear(Matrix* m) {
    free(m->data[0]);   /* освобождаем блок данных */
    free(m->data);      /* освобождаем массив указателей */
    m->data = NULL;
    m->rows = 0;
    m->cols = 0;
}

/* =========================================================
 *  ОПЕРАЦИИ НАД Matrix
 *  Все функции принимают Matrix* (указатель на структуру).
 *  Это позволяет избежать копирования и изменять поля.
 * ========================================================= */

 /* Вывод матрицы */
void printMatrix(const Matrix* m) {
    printf("Matrix [%d x %d]:\n", m->rows, m->cols);
    printf("----------------\n");
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%3d ", m->data[i][j]);
        }
        printf("\n");
    }
    printf("----------------\n");
}

/* Перестановка соседних пар строк (swap указателей, O(1) на пару) */
void transformMatrix(Matrix* m) {
    for (int i = 0; i < (m->rows / 2) * 2; i += 2) {
        swapPtr(&m->data[i], &m->data[i + 1]);
    }
}

/* Дублирование каждой строки: строка i → строки 2i и 2i+1.
   Возвращает новую Matrix (shallow copy строк — данные не копируются).
   Вызывающий код обязан освободить только result.data через free(). */
Matrix changeMatrix(const Matrix* m) {
    Matrix result;
    result.rows = m->rows * 2;
    result.cols = m->cols;

    result.data = (int**)malloc(result.rows * sizeof(int*));
    if (!result.data) { perror("malloc"); exit(1); }

    for (int i = 0; i < m->rows; i++) {
        result.data[i * 2] = m->data[i];  /* shallow: указатель на ту же строку */
        result.data[i * 2 + 1] = m->data[i];
    }
    return result;
}

/* Плоский обход linear-матрицы через data[0] */
void printFlat(const Matrix* m) {
    printf("Flat [%d элементов]:\n", m->rows * m->cols);
    int* flat = m->data[0];   /* начало единого блока */
    for (int k = 0; k < m->rows * m->cols; k++) {
        printf("%3d%c", flat[k], (k + 1) % m->cols == 0 ? '\n' : ' ');
    }
}

/* =========================================================
 *  MAIN
 * ========================================================= */
int main(void) {
    int ROWS = 7, COLS = 5;

    /* --- Jagged --- */
    printf("=== Jagged-matrix ===\n");
    Matrix jag = createJagged(ROWS, COLS);
    printMatrix(&jag);

    printf("=== transformMatrix ===\n");
    transformMatrix(&jag);
    printMatrix(&jag);

    printf("=== changeMatrix: Doublicate every row ===\n");
    Matrix doubled = changeMatrix(&jag);
    printMatrix(&doubled);
    free(doubled.data);   /* только массив указателей; данные принадлежат jag */

    deleteJagged(&jag);

    /* --- Linear --- */
    printf("=== Linear-matrix ===\n");
    Matrix lin = createLinear(ROWS, COLS);
    printMatrix(&lin);

    printf("=== Print Line-Matrix ===\n");
    printFlat(&lin);

    deleteLinear(&lin);

    return 0;
}
