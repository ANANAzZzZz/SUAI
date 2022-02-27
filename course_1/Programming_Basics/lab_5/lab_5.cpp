#include<iostream>
#include<cmath>
#include<climits>

// #include<locale.h>
#include "windows.h"

using namespace std;

double row(double, double, int &n);


int main() {
    int vid,
            n;            //число слагаемых, попавших в сумму
    double x, xn, xk,    //текущее, начальное и конечное значения аргумента
    h;            //шаг изменения значения аргумента
    double eps,        //точность вычисления суммы
    result;            //результат вычисления суммы ряда

    // setlocale(LC_ALL,"Russian");
    SetConsoleOutputCP(CP_UTF8);

    for (;;) {
        cout << "\nВид действия:" << endl;
        cout << "1 - получение таблицы значений" << endl;
        cout << "2 - завершение работы программы" << endl;
        cout << "Выберите вид действия -> ";
        cin >> vid;

        if (vid == 1) {

            cout << "Введите начальное значение аргумента ";
            cin >> xn;

            if (xn <= 0) {
                cout << "Ошибка! Значение д.б. 0<xn";
                continue;
            }

            cout << "Введите конечное значение аргумента ";
            cin >> xk;

            if (xk < xn) {
                cout << "Ошибка! Значение д.б. xk>=xn";
                continue;
            }

            cout << "Введите шаг изменения аргумента h ";
            cin >> h;

            if (h <= 0) {
                cout << "Ошибка! Значение h д.б. >0";
                continue;
            }

            cout << "Введите точность вычисления eps ";
            cin >> eps;

            if ((eps <= 0) || (eps > 0.1)) {
                cout << "Ошибка! Значение eps д.б. > 0 и <=0.1";
                continue;
            }

            cout << "\nАргумент|  Сумма |Кол.слаг.|Контрольное значение" << endl;
            x = xn;

            do {
                n = 0;
                result = row(x, eps, n);
                cout.width(7);
                cout.precision(2);
                cout << x;

                if (n < INT_MAX) {
                    cout.width(11);
                    cout.precision(4);
                    cout << result;
                    cout.width(6);
                    cout << n;
                    cout.width(15);
                    cout.precision(4);
                    cout << (sin(x) / x) << endl;
                } else cout << " Точность не достигнута" << endl;
                x += h;
            } while (x <= xk + eps);
        } else break;
    }
    return 1;
}


double row(double x, double eps, int &n) {
    double result = 0;    //результат вычисления
    double CurN = 1;        //величина текущего слагаемого
    n = 0;            //номер текущего слагаемого

    while (abs(CurN) > eps && n < INT_MAX) {
        result += CurN;
        n++;
        CurN *= x * x/ (2 * n + 1.) / (2 * n);
    }
    return result;
}
