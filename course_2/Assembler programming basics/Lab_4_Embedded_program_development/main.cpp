#include<iostream>
#include<locale>

using namespace std;
typedef signed char arrayType;
const int maxArraySize = 20;

int main() {
  setlocale(LC_ALL, "ru");

  int* maxEl = 0;
  int inputSize = 0;

  arrayType arr[maxArraySize] = {0};

  cout << "задание: Задан массив чисел размером в байт.\n" <<
       "Найти максимальный элемент массива.\n" <<
       "введите размер вводимого массива меньший " << maxArraySize << endl
       << " -> ";

  cin >> inputSize;

  cout << "введите через пробел элементы массива\n" <<
       "в диапазоне от -128 до +127\n";

  for (int i = 0; i < inputSize; ++i) {
    int tmp;
    std::cin >> tmp;
    signed char a = tmp;
    *(arr + i) = a;
  }
  __asm {
  mov ecx, inputSize
  lea esi, arr
  mov ebx, 0
  _m1:
    lodsb
    cmp al, bh
    jg _max
    jmp _m2
  _max:
    mov bh, al
  _m2:
    loop _m1
    mov maxEl, ebx
  }
  cout << "\n Максимальный элемент массива: \n" << maxEl;
  return 0;
}