#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#define M_Pi
#include<locale.h>
#include "windows.h"

using namespace std;

typedef double(* Tfun)(double);

double integral(double, double, int, double, Tfun, double);
double fun0(double x);
double fun1(double x);
double fun2(double x);
double fun3(double x);
double fun4(double x);
double fun5(double x);
double fun6(double x);
double fun7(double x);
double fun8(double x);
double fun9(double x);
double fun10(double x);
double fun11(double x);
double fun12(double x);
double fun13(double x);
double fun14(double x);

int main() {
  int i = 0, //номер области на рисунке
  n = 10;
  float x, y,            //координаты точки
  s1, s2, s3, s4, s5;        //площади областей
  double eps = .0001,                //точность вычисления
  s = 0;                    //вычисленная площадь области

//  setlocale(LC_ALL, "Russian");

  SetConsoleOutputCP(CP_UTF8);

  cout << "\nВведите координаты точки: x, y ";
  cin >> x >> y;

  if ((x - 1) * (x - 1) + y * y > 1 && (x - 1) * (x - 1) + y * y > 1 &&
      (x - 1) * (x - 1) + (y - 1) * (y - 1) < 1) {
    cout << "Точка в области M1. " << endl;
    i = 1;
  } else if ((y - 1) * (y - 1) + x * x > 1 && x * x + y * y > 1 &&
      (x + 1) * (x + 1) + (y - 1) * (y - 1) < 1 &&
      (x + 1) * (x + 1) + y * y < 1) {
    cout << "Точка в области М2. " << endl;
    i = 2;
  } else if ((x * x) + y * y < 1 && (x + 1) * (x + 1) + y * y > 1 &&
      (x - 1) * (x - 1) + (y - 1) * (y - 1) > 1 &&
      (x * x) + (y - 1) * (y - 1) < 1) {
    cout << "Точка в области М3. " << endl;
    i = 3;
  } else if ((x * x) + y * y < 1 && (x - 1) * (x - 1) + y * y < 1 &&
      (x - 1) * (x - 1) + (y + 1) * (y + 1) < 1 &&
      (x * x) + (y + 1) * (y + 1) < 1) {
    cout << "Точка в области М4. " << endl;
    i = 4;
  } else if ((y < -1) && (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 &&
      (x - 1) * (x - 1) + (y + 1) * (y + 1) > 1 &&
      (x * x) + (y + 1) * (y + 1) < 1) {
    cout << "Точка в области М5. " << endl;
    i = 5;
  } else cout << "Точка вне выделенных областей";

  cout.precision(4);        //число знаков после дес. точки
  switch (i) {
    case 1: cout << "Formula: S1 = " << (s1 =M_PI / 4. + (sqrt(3) / 2) - M_PI / 6) << endl;
      cout << "Integral:S1 = " <<
           fabs((fabs(integral(.5, 2, n, eps, fun9, s))
           - fabs(integral(1 + sqrt(3) / 2, 2, n, eps, fun11, s))
           - fabs(integral(.5, 1, n, eps, fun12, s))
           - fabs(integral(1, 1 + sqrt(3) / 2, n, eps, fun10, s)))) << endl;
      break;

    case 2: cout << "Formula: S2 = " << (s2 = 1 - sqrt(3)/2 + M_PI / 6) << endl;
      cout << "Integral:S2 = " <<
          fabs(integral((- sqrt(3) / 2), -1, n, eps, fun7, s) -
          fabs(integral((-sqrt(3) / 2), -1, n, eps, fun8, s) +
          fabs(integral((-1 - sqrt(3) / 2), -1, n, eps, fun14, s) -
          fabs(integral((-1 - sqrt(3) / 2), -1, n, eps, fun13, s))))) << endl;
      break;
    case 3: cout << "Formula: S3= " << (s3 = (sqrt(3) / 2) - M_PI / 6) << endl;
      cout << "Integral:S3 = " <<
          fabs((integral(.5, 0, n, eps, fun7, s))
          + fabs(integral(0, -.5, n, eps, fun8, s)))
          - (fabs((integral(.5, 0, n, eps, fun11, s))
          + fabs(integral(0, -.5, n, eps, fun13, s)))) << endl;

      break;
    case 4: cout << "Formula: S4= " << (s4 =  M_PI/3 + 1 - sqrt(3)) << endl;
      cout << "Integral:S4 = " <<
          fabs(integral(.5, (sqrt(3) / 2), n, eps, fun3, s)) +
          fabs(integral(.5, .134, n, eps, fun4, s)) -
          fabs(integral(.5, .134, n, eps, fun5, s)) -
          fabs(integral(.5, (sqrt(3) / 2), n, eps, fun6, s)) << endl;
      break;
    case 5: cout << "Formula: S5 = " << (s5 = (sqrt(3) / 2) - M_PI / 6) << endl;
      cout << "Integral:S5 = " <<
          fabs(integral(-.5, .5, n, eps, fun0, s))
          - ((fabs(integral(-.5, 0, n, eps, fun1, s))
          + fabs(integral(0, .5, n, eps, fun2, s)))) << endl;

  }
  return 0;
}

//нахождение определенного интеграла методом криволинейных трапеций
double integral(double a, double b, int n, double eps, Tfun fun, double s1) {
  double x,
      h,
      s = 0;
  int i;

  h = (b - a) / n;

  for (i = 0; i < n; i++) {
    x = a + i * h + h / 2;
    s += fun(x);
  }

  s *= h;

  if (fabs(s - s1) > eps) {
    s = integral(a, b, 2 * n, eps, fun, s);
  }
    return s;
}

double fun0(double x) {
  return (-sqrt(1 - x * x) - 1);
}
double fun1(double x) {
  return (-sqrt(-2 * x - x * x) - 1);
}
double fun2(double x) {
  return (-sqrt(2 * x - x * x) - 1);
}
double fun3(double x) {
  return (-sqrt(1 - x * x));
}
double fun4(double x) {
  return (-sqrt(2 * x - x * x));
}
double fun5(double x) {
  return (sqrt(2 * x - x * x) - 1);
}
double fun6(double x) {
  return (sqrt(1 - x * x) - 1);
}
double fun7(double x) {
  return (-sqrt(1 - x * x) + 1);
}
double fun8(double x) {
  return (sqrt(1 - x * x));
}
double fun9(double x) {
  return (sqrt(2 * x - x * x) + 1);
}
double fun10(double x) {
  return (sqrt(2 * x - x * x));
}
double fun11(double x) {
  return (-sqrt(2 * x - x * x) + 1);
}
double fun12(double x) {
  return (sqrt(1 - x * x) + 1);
}
double fun13(double x) {
  return (sqrt(-2 * x - x * x));
}
double fun14(double x) {
  return (-sqrt(-2 * x - x * x) + 1);
}