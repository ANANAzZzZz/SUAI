/*31.
Дан текст, составленный из строк. Под словом текста понимается последовательность букв алфавита.
 Между соседними словами - не менее одного пробела. Перед первым и за последним словом каждой
 строки произвольное число пробелов.
Найти и сохранить в каждой строке только те слова, которые встречаются в ней по одному разу.
 Строчные и прописные буквы считать эквивалентными.

Решение с использованием функций библиотеки <stdio.h>*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include<locale.h>
#include <algorithm>
#include "windows.h"

using namespace std;

#define FNAME_I "D:\\st_i.txt\0"    //имя исх. файла задано константной строкой
#define FNAME_R "D:\\st_r.txt\0"    //имя рез. файла задано константной строкой

const int RAZ = 80;            //максимальная длина строки
const char PR_R[] = "r";        //признак открытия файла на чтение
const char PR_W[] = "w";        //признак открытия файла на запись

void makeFile(char*);            //функция создания файла
int checkFile(char*, const char*);    //проверка наличия файла
void processFile(char*, char*);    //обработка содержимого
void outputFile(char*);    //вывод содержимого файла на печать
void removeDuplicates(char st_in[RAZ], char st_out[RAZ]);
bool areEqual(string a, string b);

int main() {
  char fname_i[] = FNAME_I;
  char fname_r[] = FNAME_R;

//  setlocale(LC_ALL,"Russian") ;
  SetConsoleOutputCP(CP_UTF8);

  printf(" Программа создает файл строк.\n");
  printf(" Затем файл построчно читается, при этом в каждой строке,\n");
  printf(" содержащей слова, разделенные произвольным количеством пробелов,\n");
  printf(" остаются только уникальные слова.\n");
  printf(" Создаем исходный файл:\n");
//создаем исходный файл
  makeFile(fname_i);

//выводим его содержимое
  if (!checkFile(fname_i, PR_R)) {
    printf(" Ошибка открытия файла %s", fname_i, " на чтение\n");
    printf(" Нажмите <Enter>\n");
    getchar();
    return 0;            //если исходный файл не создан
  }
  printf(" Содержимое исходного файла:\n");
  outputFile(fname_i);

//обрабатываем файл
  processFile(fname_i, fname_r);

//выводим содержимое результата
  if (!checkFile(fname_r, PR_R)) {
    printf(" Ошибка открытия файла %s", fname_r, " на чтение\n");
    printf(" Нажмите <Enter>\n");
    getchar();
    return 0;            //если результирующий файл не создан
  }
  printf(" Результат (в каждой строке остались только уникальные слова)\n");
  outputFile(fname_r);

  printf("\n Для завершения нажмите <Enter>");
  getchar();
  return 0;
}

void makeFile(char* fname_i) {
  char st[RAZ];        //исходная строка
  FILE* in;            //текстовый файл
  char otv;            //ответ пользователя
/*Открываем файл в режиме чтения (r)
Если файл с таким именем уже есть, то либо пользователь вводит
новое имя, либо новые записи будут дописаны поверх старых*/
  while (checkFile(fname_i, PR_R)) {
    printf("\n Файл с заданным именем уже есть! Зададите новое имя Y/N? ");
    otv = getchar();
    if (otv == 'Y' || otv == 'y') {
      printf(" Введите новое имя:\n");
      gets(fname_i);
    } else {
      getchar();
      break;
    }
  }
/*проверяем возможность открытия файла для записи
поскольку полное имя файла могло быть задано с ошибкой*/
  if (!checkFile(fname_i, PR_W)) {
    printf(" Ошибка открытия файла %s", fname_i, " на запись\n");
    printf(" Нажмите <Enter>\n");
    getchar();
    exit(0);
  }
/*Открываем файл в режиме записи (w) текста (по умолчанию)
Если файл с таким именем уже есть, то новые данные
будут дописаны поверх старых*/
  in = fopen(fname_i, PR_W);
  printf(" Создание файла.\n");
  printf(" Признак окончания ввода - ввод пустой строки\n");
  printf(" Введите строку и нажмите <Enter>\n");
  printf(" ->");
  gets(st);    /*функция вводит строку целиком, включая
			пробелы и символ \n*/
  while (strlen(st)) {
    fprintf(in, "%s\n", st);
    printf(" Введите строку и нажмите <Enter>\n");
    printf(" ->");
    gets(st);
  }
  fclose(in);        //закрываем файл
}

//проверка наличия файла
int checkFile(char* fname, const char* pr) {
//Открываем файл
  if (!(fopen(fname, pr)))    //если файл не существует
    return (0);
  return (1);
}

//обработка содержимого файла
void processFile(char* fname_i, char* fname_r) {
  FILE* in, * out;        //исходный и результирующий файлы (потоки)
  char st_in[RAZ];        //исходная строка
  char st_out[RAZ];        //результирующая строка


  in = fopen(fname_i, PR_R);        //открываем файл на чтение
  out = fopen(fname_r, PR_W);    //открываем файл на запись

  fgets(st_in, RAZ, in);        //читаем строку из файла in

  while (!feof(in)) {
    removeDuplicates(st_in, st_out);

    st_out[strlen(st_out) - 1] = '\0';    //убираем последний пробел

    if (strlen(st_out))
      fprintf(out, "%s\n", st_out);    //записываем строку в новый файл
    fgets(st_in, RAZ, in);        //считываем новую строку из файла
  }
  fclose(in);            //Закрываем файл in
  fclose(out);            //Закрываем файл out
}

void removeDuplicates(char st_in[RAZ], char st_out[RAZ]) {
  char* p;
  char** words;
  size_t size, i, j;

  st_out[0] = '\0';

  // удаляем символ переноса строки
  if (p = strrchr(st_in, '\n')) {
    *p = '\0';
  }

  words = NULL;
  size = 0;

  p = strtok(st_in, " \t");

  words = new char* [size + 1];

  // генерируем массив слов со строками
  for (p; p != NULL; p = strtok(NULL, " \t")) {
    words[size] = new char[size];
    words[size] = strdup(p);

    ++size;
  }

  // ищем и удаляем дубликаты
  for (i = 0; i < size - 1; ++i) {
    for (j = i + 1; j < size; ++j) {
      if (areEqual(words[i], words[j])) {
        *(words[j]) = '\0';
      }
    }
  }

  // заполняем результирующую строку
  for (i = 0; i < size; ++i)
    if (*(words[i])) {
      strcat(st_out, words[i]);    //добавляем слово к результату
      strcat(st_out, " ");    //добавляем пробел между слов
    }

  // очищаем память, задействованную на массив
  for (int i = 0; i != size; ++i)
    delete [] words[i];
  delete [] words;

}

//вывод содержимого файла на экран
void outputFile(char* fname) {
  FILE* in_out;
  char st[RAZ];            //считанная строка

  in_out = fopen(fname, PR_R);    //открываем файл на чтение
  fgets(st, RAZ, in_out);        //читаем строку из файла in_out
  while (!feof(in_out)) {
    printf("%s", st);            //выводим очередную строку на экран
    fgets(st, RAZ, in_out);
  }
  fclose(in_out);
}

bool areEqual(string a, string b) {
  transform(a.begin(), a.end(), a.begin(), ::tolower);
  transform(b.begin(), b.end(), b.begin(), ::tolower);

  if (a == b) {
    return true;
  } else {
    return false;
  }
}
