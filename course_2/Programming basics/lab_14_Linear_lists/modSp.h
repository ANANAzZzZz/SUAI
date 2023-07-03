#include <iostream>

//Определения типов
typedef char telem;    //определение типа информационного поля
#include "windows.h"

struct list {   //определение типа элемента списка
  telem data;        //информационное поле
  list* address;        //поле адреса
};

//Объявления (прототипы) функций
void initList(list** first);        //инициализация списка
void addElementToTheEnd(telem listElements, list** first);    //добавление элемента
void processing(list* first, telem E1, telem E2);            //обработка списка
void viewList(list* current);            //просмотр списка
void deleteList(list** first);        //освобождение памяти