#include <stdio.h>

void change_ptr(int* p, int* newValue) {
    
    printf("change_ptr(int* p, int* newValue) \n");
    printf("Address %p : [%p] <-- pointer p (copy of pointer myPtr &p != &myPtr)\n", &p, p);

    p = newValue; // Мы поменяли адрес ВНУТРИ функции у КОПИИ указателя. 


    // Адрес 0x100 : [10]    ← Переменная х
    // Адрес 0x200 : [0x100] ← Указатель myPtr, который находится в фугкции main() (хранит адрес x) 
    
    // Адрес 0x300 : [0x100] ← Указатель p (копия указателя myPtr), находится в функции change_ptr (хранит адрес х).
    //                         Исчезнет после того как функция change_ptr завершиться

    // Что означает Указатель p (копия указателя myPtr)?
    // &p != &myPtr
}

void change_ptr_real(int** pp, int* newValue) {
    printf("change_ptr(int** pp, int* newValue) \n");
    printf("Address %p : [%p] <-- pointerToPointer pp store adress myPtr\n", &pp, pp);

    *pp = newValue; // Мы идем по адресу и меняем ОРИГИНАЛЬНЫЙ указатель
    
    // pp хранит адрес указателя myPtr. 
    // *pp разыменовав его мы получим адрес переменной х или
    // указатель p из функции main() и присвоили ему новое значение(адрес переменной y)
}

int main() {
    int treasure = 5000;  // treasure хранит 5000
    int* p= &treasure;    // p хранит адрес переменной treasure 0x100
    int** pp = &p;       //  pp хранит адрес указателя p


    // Адрес 0x100 : [5000]  ← Переменная treasure
    // Адрес 0x200 : [0x100] ← Указатель p (хранит адрес treasure)
    // Адрес 0x300 : [0x200] ← Указатель pp (хранит адрес p)

    printf("Address %p : [%d] <-- Variable treasure\n",                   &treasure, treasure);
    printf("Address %p : [%p] <-- Pointer p (stores treasure address)\n", &p,        p);
    printf("Address %p : [%p] <-- Pointer pp (stores p address)\n",       &pp,       pp);


   
    //ЗАЧЕМ НУЖЕН УКАЗАТЕЛЬ НА УКАЗАТЕЛЬ (int**)?
    int x = 10, y = 20;
    int* myPtr = &x;

    printf("Address %p : [%d] <-- Variable y\n", &y, y);
    printf("Address %p : [%d] <-- Variable x\n", &x, x);
    printf("Address %p : [%p] <-- Pointer myPtr (stores x address)\n", &myPtr, myPtr);

     
    //1. Передаем(int* p) :
    change_ptr(myPtr, &y);
    // myPtr всё еще указывает на x! 
    // Функция поменяла свою локальную переменную p, а не наш myPtr.

    printf("*myPtr = %d\n", *myPtr);

     
    //2. Передаем(int** pp) :
    change_ptr_real(&myPtr, &y);
    // Теперь myPtr указывает на y!
    
    printf("*myPtr = %d\n", *myPtr);

    /**
    * КЛЮЧЕВОЙ ИНСАЙТ: ЗАЧЕМ НУЖЕН УКАЗАТЕЛЬ НА УКАЗАТЕЛЬ (int**)
    *
    * [ Чтобы иметь возможность изменить, куда указывает обычный указатель, находясь внутри другой функции. ]
    * 
    * [ Применение в функциях ]
    *
    * 1. Передаем (int* p):
    *    Если мы передадим в функцию просто int* p, мы сможем изменить число.
    *    Так как функция работает с копией адреса.
    *
    * 2. Передаем (int** pp):
    *    Если передадим int** pp, мы сможем заставить p смотреть на совсем другой участок памяти.
    *    (например, при перевыделении массива).
    */
    return 0;
}
