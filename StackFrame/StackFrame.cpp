#include <stdio.h>
#include <corecrt_malloc.h>

//void f() { f(); }
//
//int main() { f(); }
//https://www.codevisualizer.app/playground
//https://cs-visualizer.com/?utm_source=chatgpt.com#
//https://algocraft.vikshalabs.in/complexity-cheatsheet

//https://pythontutor.com/visualize.html#mode=display
//https://circuitlabs.net/labs/c-stack-heap-memory-visualizer-learning-tool/

void f3(int x) {
    int z = x + 3;
    printf("f3: z = %d\n", z);
}

void f2(int x) {
    int y = x + 2;
    f3(y);
}

void f1(int x) {
    int a = x + 1;
    f2(a);
}

int main() {
    f1(5);
    return 0;
}


//┌──────────────┐
//│ f3           │
//│ x = 8        │
//│ z = ? │
//│ return->f2
//└──────────────┘
//┌──────────────┐
//│ f2           │
//│ x = 6        │
//│ y = 8        │
//└──────────────┘
//┌──────────────┐
//│ f1           │
//│ x = 5        │
//│ a = 6        │
//└──────────────┘
//┌──────────────┐
//│ main         │


//void f() {
//    int a = 5;
//    int* p = &a;
//}
//
//int main() {
//    int* q = nullptr;
//    //f();
//    *q = 10; // ❌ segfault
//}

//❌ Ошибка новичка
//int** f() {
//    int a[3][3];
//    return (int**)a; 
//}
//
//int main() {
//    int** p = f();
//    p[1][1] = 5; // segfault
//}


//✅ Правильный вариант
//int** f() {
//    int** a = (int**)malloc(3 * sizeof(int*));
//    for (int i = 0;i < 3;i++)
//        a[i] = (int*)malloc(3 * sizeof(int));
//    return a;
//}
//
//int main() {
//    int** p = f();
//    p[1][1] = 5; // OK
//}