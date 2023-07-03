/*Бинарные файлы.
  Ввод/вывод с использованием функций библиотек языка C
  Программа работы с базой данных "Друзья"
  Создание базы
  Добавление новых записей
  Просмотр базы
  Поиск туров по ФИО супруга
  Сортировка по ФИО друга в алфавитном порядке
  Сортировка по году рождения
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "windows.h"

using namespace std;

#define FNAME_I "D:\\bd15.dat"    //имя файла с исходной базой
#define FNAME_R "D:\\bd25.dat"    //имя файла с результатами поиска

typedef struct {
  char day[3];
  char month[3];
  char year[6];
} date;

typedef struct {
  char name[30];    // имя друга
  char address[15];    // адрес друга
  char phoneNumber[15]; // номер телефона друга
  date dateOfBirth; // дата рождения друга
  char nameOfSpouse[15]; // имя супруга
} friendInfo;

bool doesFileExist(const char*, const char*);    //проверка наличия файла
void addElement(const char* fname);
void header_1();
void header_2();
void viewBase(const char* fname);
void viewSearchedDB(const char* fname);
void searchBySpouse(const char* fname1, const char* fname2);
void sortByName(const char* fname);
void sortByBirthday(const char* fname);

const char PR_R[] = "rb";    //признак открытия бинарного файла на чтение
const char PR_S[] = "r+b";    //признак открытия файла на чтение и запись
const char PR_W[] = "wb";    //признак открытия файла на запись
const char PR_A[] = "ab";    //признак открытия файла на добавление

int main() {
  int var;
  char otv;
  char fname_i[20] = FNAME_I;
  char fname_r[20] = FNAME_R;
//  setlocale(LC_ALL, "Russian");
  SetConsoleOutputCP(CP_UTF8);

  for (;;) {//Выбор вида действия
    printf("\n    Вид действия:\n");
    printf("  1 - создание базы данных\n");
    printf("  2 - добавление новых записей\n");
    printf("  3 - сортировка по ФИО друга\n");
    printf("  4 - сортировка друзей по дате рождения\n");
    printf("  5 - поиск друзей по имени супруга\n");
    printf("  6 - просмотр базы данных\n");
    printf("  7 - просмотр базы данных поиска друзей\n");
    printf("  8 - завершение задачи\n");
    printf("  Введите вид действия ->");
    scanf("%i", &var);
    switch (var) {
      default:break;
      case 1:
        if (doesFileExist(fname_i, PR_R)) {
          printf(" Файл базы данных друзей с именем ", fname_i);
          printf(" был создан раньше.\n");
          printf(" Создаём файл с новым именем? [Y/N] ");
          while ((otv = getchar()) == '\n');
          if (otv == 'Y' || otv == 'y') {
            printf(" Задайте имя создаваемого файла: ");
            scanf("%s", fname_i);
          } else break;
        }
        if (!doesFileExist(fname_i, PR_W)) {
          printf("\n Ошибка открытия файла для записи\n");
          break;
        }
        printf(" Создаем базу ", fname_i, '\n');
        getchar();
        addElement(fname_i);
        printf("\n Создание файла закончено.\n");
        if (doesFileExist(fname_i, PR_R))
          printf(" База данных готова к работе\n");
        else printf("\n база не создана\n");
        break;
      case 2:
        if (doesFileExist(fname_i, PR_R)) {
          printf(" Файл базы данных друзей с именем ", fname_i);
          printf(" был создан раньше.\n");
          printf(" Будем добавлять новые записи в него? [Y/N] ");
          while ((otv = getchar()) == '\n');
          if (otv == 'N' || otv == 'n') {
            printf(" Задайте имя файла другой базы: ");
            scanf("%s", fname_i);
            if (!doesFileExist(fname_i, PR_R)) {
              printf(" Такая база данных не создавалась\n");
              break;
            }
          }
        }
        printf(" Добавляем записи в файл ", fname_i, '\n');
        addElement(fname_i);
        printf("\n Изменение файла закончено.");
        break;
      case 3:
        if (!doesFileExist(fname_i, PR_S)) {
          printf("\n Ошибка открытия файла для чтения и записи\n");
          break;
        }
        sortByName(fname_i);
        printf("\n Сортировка по имени друзей закончена.");
        break;
      case 4:
        if (!doesFileExist(fname_i, PR_S)) {
          printf("\n Ошибка открытия файла для чтения и записи\n");
          break;
        }
        sortByBirthday(fname_i);
        printf("\n Сортировка по дате рождения друзей закончена.");
        break;
      case 5:
        if (!doesFileExist(fname_i, PR_R)) {
          printf("\n Ошибка открытия файла для чтения\n");
          break;
        }
        if (!doesFileExist(fname_r, PR_W)) {
          printf("\n Ошибка открытия файла для записи\n");
          break;
        }
        searchBySpouse(fname_i, fname_r);
        printf("\n Поиск по названию страны пребывания закончен.");
        break;
      case 6:
        if (!doesFileExist(fname_i, PR_R)) {
          printf("\n Ошибка открытия файла для чтения\n");
          break;
        }
        viewBase(fname_i);
        break;
      case 7:
        if (!doesFileExist(fname_r, PR_R)) {
          printf("\n Ошибка открытия файла для чтения\n");
          break;
        }
        viewSearchedDB(fname_r);
        break;
      case 8: return 0;
    }
  }
}

//Добавление новых элементов в базу данных
void addElement(const char* fname) {
  char ans;
  friendInfo friendCard;
  FILE* base;
  base = fopen(fname, PR_A);
  rewind(base);
  do {
    printf("\n ФИО друга? ");
    scanf("%s", &friendCard.name);

    printf(" Адрес ? ");
    scanf("%s", &friendCard.address);

    printf(" Номер телефона ? ");
    scanf("%s", &friendCard.phoneNumber);

    printf(" День рождения друга ? ");
    scanf("%s", &friendCard.dateOfBirth.day);

    printf(" Месяц рождения друга ? ");
    scanf("%s", &friendCard.dateOfBirth.month);

    printf(" Год рождения друга ? ");
    scanf("%s", &friendCard.dateOfBirth.year);

    printf(" Имя супруга друга ? ");
    scanf("%s", &friendCard.nameOfSpouse);

    fwrite(&friendCard, sizeof(friendCard), 1, base);

    printf("\n Продолжать?[Y/N]");
    while ((ans = getchar()) == '\n');
  } while (ans == 'Y' || ans == 'y');
  fclose(base);
}

//Вывод заголовка при просмотре исходного файла
void header_1() {
  int i;

  printf("\n");
  for (i = 1; i <= 69; i++)
    printf("-");
  printf("\n");
  printf("|%13s|%13s|%13s|%10s|%10s|\n", "ФИО Друга   ", "Адрес       ",
         "Телефон     ", "Дата рождения  ", "ФИО супруга ");
  for (i = 1; i <= 69; i++)
    printf("-");
}

//Вывод заголовка при просмотре файла поиска тура
void header_2() {
  int i;

  printf("\n");
  for (i = 1; i <= 69; i++)
    printf("-");
  printf("\n");
  printf("|%13s|%13s|%13s|%10s|%10s|\n", "ФИО Друга   ", "Адрес       ",
         "Телефон     ", "Дата рождения  ", "ФИО супруга ");
  for (i = 1; i <= 69; i++)
    printf("-");
}

//Просмотр базы данных друзей
void viewBase(const char* fname) {
  int i;
  string date;

  friendInfo friendCard;
  FILE* baza;
  baza = fopen(fname, PR_R);
  printf("\n     База данных друзей");
  header_1();

  while (fread(&friendCard, sizeof(friendCard), 1, baza) > 0) {
    printf("\n|%11s |%11s |%11s |%3s %3s %6s |%11s |", friendCard.name, friendCard.address,
           friendCard.phoneNumber, friendCard.dateOfBirth.day, friendCard.dateOfBirth.month,
           friendCard.dateOfBirth.year, friendCard.nameOfSpouse);
  }

  printf("\n");
  for (i = 1; i <= 69; i++)
    printf("-");
  fclose(baza);
}

//Просмотр базы данных поиска Друзей по имени супруга
void viewSearchedDB(const char* fname) {
  int i;
  friendInfo friendCard;
  FILE* baza;
  baza = fopen(fname, PR_R);    //открываем файл на чтение
  printf("\n  База данных поиска друзей по имени супруга");
  header_2();

  while (fread(&friendCard, sizeof(friendCard), 1, baza) > 0) {
    printf("\n|%11s |%11s |%11s |%3s %3s %6s |%11s |", friendCard.name, friendCard.address,
           friendCard.phoneNumber, friendCard.dateOfBirth.day, friendCard.dateOfBirth.month,
           friendCard.dateOfBirth.year, friendCard.nameOfSpouse);
  }
  printf("\n");
  for (i = 1; i <= 69; i++)
    printf("-");
  fclose(baza);
}

//Поиск туров по названию страны пребывания
void searchBySpouse(const char* fname1, const char* fname2) {
  char nameOfSpouse[15];
  friendInfo friendCard;
  FILE* in,                    //исходный файл
  * out;                //файл результатов поиска

  in = fopen(fname1, PR_R);        //открываем файл на чтение
  out = fopen(fname2, PR_W);        //открываем файл на запись

  printf("\n имя супруга для поиска? ");
  scanf("%s", &nameOfSpouse);

  while (fread(&friendCard, sizeof(friendCard), 1, in) > 0) {
    if ((strncmp(friendCard.nameOfSpouse, nameOfSpouse, 15) == 0)) {
      fwrite(&friendCard, sizeof(friendCard), 1, out);
    }
  }
  fclose(out);
  fclose(in);
}

//Сортировка по ФИО друзей
void sortByName(const char* fname) {
  int i;
  int fl;
  friendInfo friendCard_2, friendCard_1;
  FILE* base;

  base = fopen(fname, PR_S);    //открываем файл на чтение и запись
  do {
    rewind(base);
    fl = 0;
    for (i = 0; fread(&friendCard_1, sizeof(friendCard_1), 1, base) > 0; i += sizeof(friendCard_1),
        fseek(base, i, SEEK_SET))    //позиция i от НАЧАЛА файла
    {
      if (fread(&friendCard_2, sizeof(friendCard_1), 1, base) > 0) {
        if (strncmp(friendCard_1.name, friendCard_2.name, 15) > 0) {
          fseek(base, i, SEEK_SET);    //позиция i от НАЧАЛА файла
          fwrite(&friendCard_2, sizeof(friendCard_1), 1, base);
          fwrite(&friendCard_1, sizeof(friendCard_1), 1, base);
          fl = 1;
        }
      }
    }
  } while (fl);
  fclose(base);
}

//Сортировка по дате рождения
void sortByBirthday(const char* fname) {
  int i;
  int fl;
  friendInfo friendCard_2, friendCard_1;
  FILE* base;
  base = fopen(fname, PR_S);    //открываем файл на чтение и запись
  do {
    rewind(base);
    fl = 0;
    for (i = 0; fread(&friendCard_1, sizeof(friendCard_1), 1, base) > 0; i += sizeof(friendCard_1),
        fseek(base, i, SEEK_SET)) {
      if (fread(&friendCard_2, sizeof(friendCard_1), 1, base) > 0) {
        if (strcmp(friendCard_1.dateOfBirth.year, friendCard_2.dateOfBirth.year) > 0) {
          fseek(base, i, SEEK_SET);    //позиция i от НАЧАЛА файла
          fwrite(&friendCard_2, sizeof(friendCard_1), 1, base);
          fwrite(&friendCard_1, sizeof(friendCard_1), 1, base);
          fl = 1;
        }
      }
    }
  } while (fl);
  fclose(base);
}

//проверка наличия физического файла
bool doesFileExist(const char* fname, const char* pr) {
  //Открываем файл
  if (!(fopen(fname, pr)))        //файл не существует
    return false;

  return true;
}
