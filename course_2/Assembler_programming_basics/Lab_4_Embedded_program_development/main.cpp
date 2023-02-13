#include<iostream>
#include<locale>
using namespace std;
typedef signed char Array_type;
const int mas_size = 20;
int main() {
  int flag = 0;
  setlocale(LC_ALL, "ru");
  int user_size = 0;
  Array_type Arr[mas_size] = { 0 };
  cout << "задание: Задан массив чисел со знаком размером в байт.\n" <<
       " Написать приложение делающее сортировку по убыванию.\n" <<
       "введите размер вводимого массива меньший " << mas_size << endl
       << " -> ";
  cin >> user_size;
  cout << "введите через пробел элементы массива\n" <<
       "в диапазоне от -128 до +127\n";
  for (int i = 0; i < user_size; ++i) {
    int tmp;
    std::cin >> tmp;
    signed char Perem = tmp;
    *(Arr + i) = Perem;
  }

  __asm__  (
  "movl flag, $1h"
  lea ebx, Arr
  _while :
  mov flag, 0
  mov ecx, user_size
  dec ecx
  mov edi, 0
  _L :
  mov dl, [ebx + edi]
  mov dh, [ebx + edi + 1]
  cmp dl, dh
  JA _no_change
  xchg dl, dh
  mov[ebx + edi], dl
  mov[ebx + edi + 1], dh
  mov flag, 1
  _no_change:
  inc di
  Loop _L
  cmp flag, 0
  JNE _while
  )

  cout << "\nОтсортированный массив:\n";
  for (int i = 0; i < user_size; ++i) {
    int Perem = *(Arr + i);
    cout << Perem << " ";
  }
  cout << endl;
  return 0;
}
