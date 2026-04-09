
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double>;

//Запуск Visual Studio
//Debug — без оптимизации(по умолчанию).
//Release — с оптимизацией(по умолчанию / O2).

//Настройка оптимизации в Visual Studio:
//Configuration Properties → C / C++ → Optimization.
//Optimization :
//Disabled(/ Od) — отключено(для Debug).
//Maximize Speed(/ O2) — макс.скорость(Release).
//Full Optimization(/ Ox) — агрессивная оптимизация.

//Для настройки оптимизации в VS Code при работе с C++11
//Настройка tasks.json Откройте папку проекта в VS Code
//Перейдите в меню "Terminal" → "Configure Default Build Task"
//Выберите "C/C++: g++ build active file" (или ваш компилятор)
//Откроется файл tasks.json. Измените его:
/*"args": [
                "-fdiagnostics-color=always",
                "-g",
                "-std=c++11",
                "-O2",  // Флаг оптимизации O2
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
*/
//Ускорение : ~1.5–3 раза в пользу указателей.

//Почему указатели быстрее ?
//Меньше операций в цикле :
//Индексы: arr[i] → требует вычисления arr + i * sizeof(int).
//Указатели : *ptr++ → просто разыменование + инкремент адреса.

//Лучшая оптимизация компилятором :
//Указатели часто превращаются в регистровые операции(самые быстрые).
//Индексы могут требовать дополнительных проверок границ(если компилятор не оптимизирует).

//Когда разница заметна ?
//На очень больших массивах(от миллионов элементов)
//В критичных по скорости участках(например, обработка изображений, математические вычисления)

//Важно!
//В современном C++ (C++11 и выше) разница может уменьшаться из - за оптимизаций компилятора.
//Для обычного кода индексы предпочтительнее из - за читаемости.
//В высокопроизводительных задачах(HPC(High Performance Computing), GameDev) указатели всё ещё актуальны.


const int SIZE = 1'000'000'000; // 100 миллионов элементов 
//Запуск
//без оптимизации через debug 
//с оптимизацией(по умолчанию / O2). release


int main() {

    //setlocale(LC_ALL, "Russian");


    int* arr = new int[SIZE];
    /*for (int i = 0; i < SIZE; i++) {
        arr[i] = i % 100;
    }*/

    // Способ 1: Суммирование через индексы
    auto start1 = Clock::now();
    long long sum1 = 0;
    for (int i = 0; i < SIZE; i++) {
        //sum1 += arr[i];
        arr[i] = 1;
    }

    auto end1 = Clock::now();
    Duration elapsed1 = end1 - start1;

    // Способ 2: Суммирование через указатели
    auto start2 = Clock::now();
    long long sum2 = 0;
    for (int* ptr = arr; ptr < arr + SIZE; ptr++) {
        //sum2 += *ptr;
        *ptr = 2;
    }
    auto end2 = Clock::now();
    Duration elapsed2 = end2 - start2;

    // Вывод результатов
    cout << "SUM indexes:   " << sum1 << " | Time: " << elapsed1.count() << " sec.\n";
    cout << "SUM pointers:  " << sum2 << " | Time: " << elapsed2.count() << " sec.\n";

    delete[] arr;
    return 0;
}