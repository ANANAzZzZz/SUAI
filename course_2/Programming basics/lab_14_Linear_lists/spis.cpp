/*Основной файл spis.cpp
Создать линейный список L.
Заменить в списке L последнее вхождение элемента со значением E1 на E2.
Многофайловый проект*/

#include "modSp.h"

using namespace std;

//основная программа
int main() {
  list* first;
  telem listElements;

  telem E1;
  telem E2;

  initList(&first);

  SetConsoleOutputCP(CP_UTF8);

  //создание исходного списка
  cout << "\n Заменить в списке L последнее вхождение элемента со значением E1 на E2." << endl;

  cout << "\n Введите значение элемента E1: ";
  cin >> E1;

  cout << "\n Введите значение элемента E2: ";
  cin >> E2;

  cout << " Введите элементы списка сплошной строкой;"
       << " в конце - точка:" << endl;

  cin >> listElements;
  while (listElements != '.') {
    addElementToTheEnd(listElements, &first);
    cin >> listElements;
  }
//вывод исходного списка
  if (first && first->address && first->address->address) { //список создан правильно
    cout << " Исходный список:" << endl;
    viewList(first);

//обработка списка
    processing(first, E1, E2);
    cout << "\nРезультат получен:\n";
    viewList(first);

//освобождение памяти
    deleteList(&first);
  }
  return 1;
}
