/*
Дан массив b0, b1,…, bn-1. Определить сумму, произведение и количество компонент этого массива,
принадлежащих отрезку [x, y].
*/

#include<iostream>
#include<clocale>

using namespace std;

const int RAZ = 10;        //предельный размер массива
typedef int tElem;        //определение типа значений элементов массива
typedef tElem tMas[RAZ];    //определение типа массива

void arrayInput(tMas a, int n);

void arrayOutput(const tMas a, int n);

void arrayHandle(tMas a, int n, int *elCount, tElem *elProduct, tElem *elSum, tElem x, tElem y);

int main() {
    tMas a;          // массив
    int n;     // колличетсво элементов массива, граница x, граница y
    int elCount = 0;     // колличество элементов массива, приналдежащих отрезку [x,y]
    tElem x, y, elSum = 0, elProduct = 1;

    setlocale(LC_ALL, "Russian");

    //Ввод исходных данных
    cout << "Введете размер массива <= " << RAZ << " : " << endl;
    cin >> n;

    //Контроль ввода размера массива
    if (n > RAZ || n <= 0) {
        cout << "Введено недопустимое значение размера массива" << endl;
        return 1;
    }

    cout << "\nВведите границы отрезка [x,y]" << endl;
    cin >> x >> y;

    arrayInput(a, n);

    //Вывод исходного массива
    cout << "Исходный массив:" << endl;
    arrayOutput(a, n);

    arrayHandle(a, n, &elCount, &elProduct, &elSum, x, y);

    cout << "\nСумма элементов, принадлежащих отрезку: " << elSum << endl;
    cout << "Произведение элементов, принадлежащих отрезку: " << elProduct << endl;
    cout << "Колличество элементов, принадлежащих отрезку: " << elCount << endl;
    return 0;
}

void arrayInput(tMas a, int n) {
    cout << "Введите в одной строке элементы массива, состоящего из " << n;
    cout << "\nчисел, и нажмите <Enter>" << endl;
    for (int i = 0; i < n; i++)
        cin >> a[i];
}

void arrayOutput(const tMas a, int n) {
    for (int i = 0; i < n; i++) {
        cout.width(2);    //ширина поля для вывода значения элемента массива
        cout << a[i] << " ";
    }
}

void arrayHandle(tMas a, int n, int *elCount, tElem *elProduct, tElem *elSum, tElem x, tElem y) {

    for (int i = 0; i < n; i++) {
        if (a[i] >= x && a[i] <= y) {
            *elCount += 1;
            *elProduct *= a[i];
            *elSum += a[i];
        }
    }
}