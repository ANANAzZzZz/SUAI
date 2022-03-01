/*  Разработать функцию, определяющую координаты центра и радиус описанной окружности для треугольника,
заданного координатами вершин этого треугольника на плоскости.
Ввести координаты вершин трёх треугольников. Используя разработанную функцию найти наибольший радиус
среди окружностей, описывающих эти треугольники.
*/

//Реализованы три функции с одним именем:
//-функция, возвращающая значение;
//-функция с дополнительным аргументом-указателем;
//-функция с дополнительным аргументом-ссылкой.
//Вызов всех функций - из функции main()


#include<iostream>
#include<cmath>
#include <windows.h>


//#include<locale.h>

using namespace std;

double findRadius(double, double, double, double, double, double);
void findRadius(double, double, double, double, double, double, double *);
void findRadius(double, double, double, double, double, double, double &);


int main() {

    double ft_x1, ft_y1, ft_x2, ft_y2, ft_x3, ft_y3,
            st_x1, st_y1, st_x2, st_y2, st_x3, st_y3,
            tt_x1, tt_y1, tt_x2, tt_y2, tt_x3, tt_y3, ft_radius, st_radius, tt_radius, max_radius;

    // setlocale(LC_ALL,"Russian");
    SetConsoleOutputCP(CP_UTF8);

    cout << "Введите координаты вершин первого треугольника:" << endl;
    cin >> ft_x1 >> ft_y1 >> ft_x2 >> ft_y2 >> ft_x3 >> ft_y3;

    cout << "Введите координаты вершин второго треугольника:" << endl;
    cin >> st_x1 >> st_y1 >> st_x2 >> st_y2 >> st_x3 >> st_y3;

    cout << "Введите координаты вершин третьего треугольника:" << endl;
    cin >> tt_x1 >> tt_y1 >> tt_x2 >> tt_y2 >> tt_x3 >> tt_y3;

    cout.precision(4);

    ft_radius = findRadius(ft_x1, ft_y1, ft_x2, ft_y2, ft_x3, ft_y3);
    st_radius = findRadius(st_x1, st_y1, st_x2, st_y2, st_x3, st_y3);
    tt_radius = findRadius(tt_x1, tt_y1, tt_x2, tt_y2, tt_x3, tt_y3);

    if (ft_radius > st_radius && ft_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = ft_radius;
    } else if (st_radius > ft_radius && st_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    } else if (tt_radius > ft_radius && tt_radius > st_radius && isinf(ft_radius) == 0) {
        max_radius = tt_radius;
    } else if (st_radius == ft_radius && ft_radius == tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    }

    cout << "\nФункция, возвращающая значение" << endl;
    cout << "Наибольший радиус описанной окружности: " << max_radius << endl;

    findRadius(ft_x1, ft_y1, ft_x2, ft_y2, ft_x3, ft_y3, &ft_radius);
    findRadius(st_x1, st_y1, st_x2, st_y2, st_x3, st_y3, &st_radius);
    findRadius(tt_x1, tt_y1, tt_x2, tt_y2, tt_x3, tt_y3, &tt_radius);

    if (ft_radius > st_radius && ft_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = ft_radius;
    } else if (st_radius > ft_radius && st_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    } else if (tt_radius > ft_radius && tt_radius > st_radius && isinf(ft_radius) == 0) {
        max_radius = tt_radius;
    } else if (st_radius == ft_radius && ft_radius == tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    }

    cout << "\nФункция c дополнительным аргументом-ссылкой" << endl;
    cout << "Наибольший радиус описанной окружности: " << max_radius << endl;

    findRadius(ft_x1, ft_y1, ft_x2, ft_y2, ft_x3, ft_y3, ft_radius);
    findRadius(st_x1, st_y1, st_x2, st_y2, st_x3, st_y3, st_radius);
    findRadius(tt_x1, tt_y1, tt_x2, tt_y2, tt_x3, tt_y3, tt_radius);

    if (ft_radius > st_radius && ft_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = ft_radius;
    } else if (st_radius > ft_radius && st_radius > tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    } else if (tt_radius > ft_radius && tt_radius > st_radius && isinf(ft_radius) == 0) {
        max_radius = tt_radius;
    } else if (st_radius == ft_radius && ft_radius == tt_radius && isinf(ft_radius) == 0) {
        max_radius = st_radius;
    }

    cout << "\nФункция c дополнительным аргументом-указателем" << endl;
    cout << "Наибольший радиус описанной окружности: " << max_radius << endl;

    return 0;
}

double findRadius(double x1, double y1, double x2, double y2, double x3, double y3) {
    double z, z1, z2, z3, circleX, circleY, radius;

    z1 = x1 * x1 + y1 * y1;
    z2 = x2 * x2 + y2 * y2;
    z3 = x3 * x3 + y3 * y3;

    z = (x1 - x2) * (y3 - y1) - (y1 - y2) * (x3 - x1);

    circleX = -((y1 - y2) * z3 + (y2 - y3) * z1 + (y3 - y1) * z2) / (2 * z);
    circleY = ((x1 - x2) * z3 + (x2 - x3) * z1 + (x3 - x1) * z2) / (2 * z);

    radius = sqrt(pow(x1 - circleX, 2) + pow(y1 - circleY, 2));

    return radius;

}


void findRadius(double x1, double y1, double x2, double y2, double x3, double y3, double *t) {
    double z, z1, z2, z3, circleX, circleY, radius;

    z1 = x1 * x1 + y1 * y1;
    z2 = x2 * x2 + y2 * y2;
    z3 = x3 * x3 + y3 * y3;

    z = (x1 - x2) * (y3 - y1) - (y1 - y2) * (x3 - x1);

    circleX = -((y1 - y2) * z3 + (y2 - y3) * z1 + (y3 - y1) * z2) / (2 * z);
    circleY = ((x1 - x2) * z3 + (x2 - x3) * z1 + (x3 - x1) * z2) / (2 * z);

    radius = sqrt(pow(x1 - circleX, 2) + pow(y1 - circleY, 2));

    *t = radius;
}


void findRadius(double x1, double y1, double x2, double y2, double x3, double y3, double &t) {
    double z, z1, z2, z3, circleX, circleY, radius;

    z1 = x1 * x1 + y1 * y1;
    z2 = x2 * x2 + y2 * y2;
    z3 = x3 * x3 + y3 * y3;

    z = (x1 - x2) * (y3 - y1) - (y1 - y2) * (x3 - x1);

    circleX = -((y1 - y2) * z3 + (y2 - y3) * z1 + (y3 - y1) * z2) / (2 * z);
    circleY = ((x1 - x2) * z3 + (x2 - x3) * z1 + (x3 - x1) * z2) / (2 * z);

    radius = sqrt(pow(x1 - circleX, 2) + pow(y1 - circleY, 2));

    t = radius;
}