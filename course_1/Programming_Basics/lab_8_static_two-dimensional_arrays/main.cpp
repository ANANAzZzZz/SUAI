/*
 В заданной квадратной матрице размера (2n+1)×(2n+1) найти элементы с наибольшим по абсолютной величине
 и с наименьшим по абсолютной величине значениями. Если хотя бы один из них находится в области правее
 главной и побочной диагоналей найти сумму значений элементов, лежащих ниже главной диагонали.
 В противном случае поменять найденные значения местами.
 */

#include<iostream>
#include <windows.h>

using namespace std;
const int RAZ = 10;            // максимальный размер квадратной матрицы
typedef int telem;            // определение типа значений элементов массива
typedef telem tmatr[RAZ][RAZ];    // определение типа массива

bool input_matr(tmatr a, int&);
void output_matr(tmatr a, int);
void findAbs(tmatr a, int n, telem& maxDigit, telem& minDigit, int& minPI, int& minPJ, int& maxPI, int& maxPJ);
void swapValues(tmatr a, int minDigit, int maxDigit, int& minPI, int& minPJ, int& maxPI, int& maxPJ);
void sumMatr(tmatr a, int n, telem& amount);
bool isBelong(int minPI, int minPJ, int maxPI, int maxPJ, int n);

int main() {
  tmatr a;                           // двумерный массив
  int n;                            // половина размера квадратной матрицы
  int minPI = 0;
  int minPJ = 0;
  int maxPI = 0;
  int maxPJ = 0;
  telem amount = 0;                // сумма элементов ниже главной диагонали
  telem maxDigit;       // максимальное число по модулю
  telem minDigit;      // минимальное число по модулю

//  setlocale(LC_ALL, "Russian");
  SetConsoleOutputCP(CP_UTF8);

  if (!input_matr(a, n)) {
    cout << "Введено неверное значение n < 5";

    return 1;
  }

  cout << "Исходная матрица:" << endl;
  output_matr(a, n);

  findAbs(a, n, maxDigit, minDigit, minPI, minPJ, maxPI, maxPJ);

  if (isBelong(minPI, minPI, maxPI, maxPJ, n)) {
    sumMatr(a, n, amount);
    cout << "Сумма элементов, находящихся ниже главной диагонали: " << amount;

  } else {
    swapValues(a, minDigit, maxDigit, minPI, minPJ, maxPI, maxPJ);
    cout << "Матрица после преобразования:" << endl;
    output_matr(a, n);
  }

  return 0;
}

//Ввод исходных данных
bool input_matr(tmatr a, int& n) {
  cout << "Введите n  < 5, (матрица размера (2*n+1)x(2*n+1)):" << endl;
  cin >> n;

  if (n >= 5) {
    return false;
  }
  cout << "Введите построчно через пробел элементы" << endl;
  cout << "Матрицы размера " << 2 * n + 1 << "x" << 2 * n + 1 << endl;
  cout << "После ввода строки нажимайте <Enter>" << endl;

  for (int i = 0; i < 2 * n + 1; i++)
    for (int j = 0; j < 2 * n + 1; j++)
      cin >> a[i][j];

  return true;
}

//Вывод матрицы
void output_matr(tmatr a, int n) {
  for (int i = 0; i < 2 * n + 1; i++) {
    for (int j = 0; j < 2 * n + 1; j++) {
      cout.width(3);
      cout << a[i][j];
    }
    cout << endl;
  }
}

// Поиск сумм значений элементов ниже главной диагонали матрицы
void sumMatr(tmatr a, int n, telem& amount) {
  for (int i = 1; i < 2 * n + 1; i++) {
    for (int j = 0; i > j; j++) {
      amount += a[i][j];
    }
  }
}

// Перестановка минимального и максимального значений
void swapValues(tmatr a, int minDigit, int maxDigit, int& minPI, int& minPJ, int& maxPI, int& maxPJ) {
  a[minPI][minPJ] = maxDigit;
  a[maxPI][maxPJ] = minDigit;
}

// Поиск минимального и максимального числа по модулю и определение их принадлежности области
void findAbs(tmatr a, int n, telem& maxDigit, telem& minDigit, int& minPI, int& minPJ, int& maxPI, int& maxPJ) {
  minDigit = a[0][0];
  minPI = 0;
  minPJ = 0;

  maxDigit = a[0][0];
  maxPI = 0;
  maxPJ = 0;

  for (int i = 0; i < 2 * n + 1; i++) {
    for (int j = 0; j < 2 * n + 1; j++) {
      if (abs(maxDigit) < abs(a[i][j])) {
        maxDigit = a[i][j];
        maxPI = i;
        maxPJ = j;
      }

      if (abs(minDigit) > abs(a[i][j])) {
        minDigit = a[i][j];
        minPI = i;
        minPJ = j;
      }
    }
  }
}

bool isBelong(int minPI, int minPJ, int maxPI, int maxPJ, int n) {
  bool isBelong = false;

  if (maxPI < maxPJ && maxPI > 2 * n - maxPJ) {
    isBelong = true;
  }
  if (minPI < minPJ && minPI > 2 * n - minPJ) {
    isBelong = true;
  }

  return isBelong;
}