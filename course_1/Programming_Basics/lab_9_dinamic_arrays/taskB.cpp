/*
Б. В заданной квадратной матрице размера 2n×2n поменять местами значения элементов строк области [5+6+7]
 и элементов столбцов области [2+3+4] (см. рисунок) с одинаковыми номерами.
 */

#include<iostream>
#include "windows.h"
//#include<locale.h>

using namespace std;

typedef int telem;        //определение типа элементов массива
typedef telem* tstr;        //определение типа "указатель на telem"
typedef tstr* tmatr;        //тип "указатель на указатель на telem"
void input_matrix(tmatr a, int n);
void output_matrix(tmatr a, int n);
void swapEl(tmatr a, int n);

int main() {

  int n;                  //число строк (столбцов) матрицы
  tmatr a;                //переменная-указатель на указатель на telem

  SetConsoleOutputCP(CP_UTF8);
//  setlocale(LC_ALL, "Russian");

  cout << "Введите размерность матрциы (матрица вида 2n*2n)" << endl;
  cin >> n;

  a = new tstr[2 * n];        /*выделение динамической памяти под массив
					          указателей на строки массива*/
  for (int i = 0; i < 2 * n; i++)    //выделение памяти под каждую строку:
    *(a + i) = new telem[2 * n];    /*каждому элементу массива указателей
                                    на строки присваивается адрес начала
                                    области памяти, выделяемой под строку*/

  input_matrix(a, n);

  cout << " Исходная матрица:\n";
  output_matrix(a, n);

  swapEl(a, n);

  cout << " Результирующая матрица:\n";
  output_matrix(a, n);
  cout << endl << " Для завершения нажмите <Enter>";

  //Освобождение динамической памяти
  for (int i = 0; i < 2 * n; i++)
    delete *(a + i);
  delete[]a;

  return 0;
}

void input_matrix(tmatr a, int n) {
  cout << " Значения элементов";
  cout << " массива размера " << n << "x" << n;
  cout << "\n при тестировании вводятся автоматически:" << endl;
  for (int i = 0; i < 2 * n; i++)
    for (int j = 0; j < 2 * n; j++)
      *(*(a + i) + j) = 10 * i + j;
}

void output_matrix(tmatr a, int n) {
  for (int i = 0; i < 2 * n; i++) {
    for (int j = 0; j < 2 * n; j++) {
      cout.width(3);    //ширина поля выводимого параметра
      cout << *(*(a + i) + j) << ' ';
    }
    cout << '\n';
  }
}

void swapEl(tmatr a, int n) {
  telem z;

  for (int i = 0; i < 2 * n - 1; i++)
    for (int j = i; j < 2 * n - 1; j++) {
      if (j >= n - 1) {
        z = *(*(a + i) + j + 1);
        *(*(a + i) + j + 1) = *(*(a + j + 1) + i);
        *(*(a + j + 1) + i) = z;
      }
    }
}