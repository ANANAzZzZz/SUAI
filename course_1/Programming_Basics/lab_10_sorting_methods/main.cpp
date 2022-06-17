#include<iostream>
#include "windows.h"

using namespace std;

typedef int telem;    /*определение типа значений элементов массива*/
typedef telem* tstr;    /*определение типа "указатель на telem"*/
typedef tstr* tmatr;    /*определение типа "указатель на указатель на telem"*/

void inputMatrix(tmatr a, int n);
void autoInputMatrix(tmatr a, int n);
void outputMatrix(tmatr a, int n);
void matrixHandling(tmatr a, int n);
void fillMatrixZeroes(tmatr a, int n, int zero, int j);

int main() {
  int n;
  tmatr a;

  SetConsoleOutputCP(CP_UTF8);

  cout << "Введите исходное значение n (матрица вида 2n)" << endl;
  cin >> n;
  n *= 2;

  a = new tstr[n];

  cout << "Введите построчно элементы матрицы через пробел" << endl;
  autoInputMatrix(a, n);
  //  inputMatrix(a, n);

  cout << "исходная матрица:" << endl;
  outputMatrix(a, n);

  matrixHandling(a, n);
  cout << "отсортированная матрица:" << endl;
  outputMatrix(a, n);

  //Освобождение динамической памяти
  for (int i = 0; i < n; i++)
    delete a[i];
  delete[] a;

  return 0;
}

void inputMatrix(tmatr a, int n) {
  for (int i = 0; i < n; i++) {
    *(a + i) = new telem[n];
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> a[i][j];
}

void autoInputMatrix(tmatr a, int n) {
  for (int i = 0; i < n; i++) {
    *(a + i) = new telem[n];
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      *(*(a + i) + j) = 10 * i + j;
}

void matrixHandling(tmatr a, int n) {
  telem temp;
  int j, i, k;
  int zero;
  int flag;

  for (j = 0; j < n; j++) {
    /*начальное количество не сортированных элементов строки*/
    if (j < n / 2.) {
      k = j;
    } else {
      k = n - j - 1;
    }
    //запоминаем изначальное количество неотсортированных элементов
    zero = k + 1;
    do {
      flag = 0;
      for (i = n - 1; i > n - k - 1; i--) {
        if (*(*(a + i) + j) > *(*(a + i - 1) + j)) {
          temp = *(*(a + i) + j);
          *(*(a + i) + j) = *(*(a + i - 1) + j);
          *(*(a + i - 1) + j) = temp;
          flag = 1;
        }
      }
      k--;
    } while (flag);
    // обнуляем элементы, которые не вошли в область сортировки
    fillMatrixZeroes(a, n, zero, j);
  }
}

void outputMatrix(tmatr a, int n) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      cout.width(3);
      cout << *(*(a + i) + j) << ' ';
    }
    cout << endl;
  }
}

void fillMatrixZeroes(tmatr a, int n, int zero, int j) {
  int i;

  for (i = 0; i < n - zero; i++) {
    *(*(a + i) + j) = 0;
  }
}