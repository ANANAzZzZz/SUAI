/*Файл modSp.cpp
Исходный файл
Реализация набора функций для обработки списка*/
#include "modSp.h"

using namespace std;

//Обработка списка
void processing(list* first, telem E1, telem E2) {
  list* exceptAddress;

  exceptAddress = nullptr;

  while (first) {
    if (first->data == E1) {
        exceptAddress = first;
    }

    first = first->address;
  }

  if (exceptAddress) {
    exceptAddress->data = E2;
  }
}

//Просмотр содержимого списка
void viewList(list* current) {
  do {
    cout << current->data;
    current = current->address;
  } while (current);
}

//Добавление нового элемента в конец списка
void addElementToTheEnd(telem listElements, list** first) {
  list* tmp;
  list* newElement = new list;    //выделяем память под элемент списка

  newElement->data = listElements;        //заполняем информационную часть
  newElement->address = nullptr;            //в ссылочную - NULL

  if (*first) {            //если список не пуст
    tmp->address = newElement;
  } else {
    *first = newElement;        //если список пока пуст
  }
  tmp = newElement;
}

//Инициализация списка
void initList(list** first) {
  *first = nullptr;
}

//Освобождение динамической памяти
void deleteList(list** first) {
  list* current;
  while (*first) {
    current = *first;            //запоминаем его адрес
    *first = (*first)->address;    /*удаляем из списка и переходим
						к следующему элементу*/
    delete current;            //освобождаем память
  }
}