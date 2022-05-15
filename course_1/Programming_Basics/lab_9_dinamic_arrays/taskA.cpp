/*А. Дан массив b0, b1, b2,…, b2n-1. Определить произведение значений элементов массива с чётными номерами,
лежащих между первым элементом с наибольшим по абсолютной величине значением и последним элементом с
отрицательным значением, имеющим номер меньше, чем n..*/

//  -2 2 4 8 16 32 64 128 10000 1010 1 1 1 1 1 1 1 1 1

#include<iostream>
#include "windows.h"
// #include<locale.h>

using namespace std;

typedef int telem;    //объявление типа элемента массива
typedef telem* tmas;    //объявление типа "указатель на telem"
void inputArr(tmas& a, int n);
void outputArr(const tmas& a, int n);
int findAbsMaxPos(const tmas& a, int n);
int findMinusPos(const tmas& a, int n);
telem findProduct(const tmas& a, int absMaxPos, int lastMinusPos);

int main() {
  int n;                //размер массива
  int lastMinusPos;
  int absMaxPos;
  telem product;

  SetConsoleOutputCP(CP_UTF8);
//  setlocale(LC_ALL, "Russian");

//Ввод исходных данных
  cout << "Массив вида 2*n" << endl;
  cout << "\nВведите количество элементов массива: ";
  cin >> n;
  tmas a = new telem[2 * n];    /*создание переменной-указателя на telem,
					выделение динамической памяти под массив
					адрес начала области заносится в a*/
  inputArr(a, n);

  absMaxPos = findAbsMaxPos(a, n);
  lastMinusPos = findMinusPos(a, n);

  if (lastMinusPos == -1) {
    cout << "Ошибка. Элементов с отрицательным значением, имеющих номер меньше n не найдено.";
    return 1;
  }

  if (abs(absMaxPos - lastMinusPos) == 1) {
    cout << "Промежутка нет, элементы являются соседними";
    return 1;
  }

  cout << "исходный массив:" << endl;
  outputArr(a, n);

  product = findProduct(a, absMaxPos, lastMinusPos);
  cout << "произведение: " << product;


  delete[] a;            //освобождение динамической памяти
  return 0;
}

void inputArr(tmas& a, int n) {
  cout << "Введите одной строкой элементы массива из ";
  cout << 2 * n<< " чисел и нажмите <Enter>" << endl;
  for (int i = 0; i < 2 * n; i++)
    cin >> *(a + i);
}

int findAbsMaxPos(const tmas& a, int n) {
  telem maxEl = *(a);
  int absMaxPos = 0;

  for (int i = 1; i < 2 * n; i++)
    if (abs(*(a + i)) > abs(maxEl)) {
      absMaxPos = i;
      maxEl = *(a + i);
    }
  return absMaxPos;
}

int findMinusPos(const tmas& a, int n) {
  int lastMinusPos = -1;

  for (int i = n - 1; i > 0; i--) {
    if (*(a + i) < 0) {
      lastMinusPos = i;
      break;
    }
  }
  return lastMinusPos;
}

telem findProduct(const tmas& a, int absMaxPos, int lastMinusPos) {
  telem product = 1;

  if (absMaxPos < lastMinusPos) {
    if (absMaxPos % 2 == 0) {
      for (int i = absMaxPos + 2; i < lastMinusPos; i += 2) {
        product *= *(a + i);
      }
    } else {
      for (int i = absMaxPos + 1; i < lastMinusPos; i += 2) {
        product *= *(a + i);
      }
    }

  } else if (lastMinusPos < absMaxPos) {
    if (lastMinusPos % 2 == 0) {
      for (int i = lastMinusPos + 2; i < absMaxPos; i += 2) {
        product *= *(a + i);
      }
    } else {
      for (int i = lastMinusPos + 1; i < absMaxPos; i += 2) {
        product *= *(a + i);
      }
    }
  }
  return product;
}

void outputArr(const tmas& a, int n) {
  for (int i = 0; i < 2 * n; i++) {
    cout << (*(a + i)) << " ";
  }
  cout << endl;
}