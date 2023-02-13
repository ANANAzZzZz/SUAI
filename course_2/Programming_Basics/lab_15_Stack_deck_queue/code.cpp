/*
 * Задание (Вар 45)
 * Дана произвольная строка. Под словом понимается
 * последовательность цифр. Между соседними словами - не
 * менее одного пробела. Перед первым и за последним
 * словом строки произвольное число пробелов.
 * Используя одну очередь, за один просмотр исходной
 * строки напечатать сначала все слова с четным
 * значением суммы входящих в нее цифр, затем все
 * слова с нечетным значением суммы цифр, сохраняя
 * исходный порядок в каждой группе.
 * Например:
 *     - исходная последовательность: 15 21 32 48 59 65 76 88 98;
 *     - результат: 15 48 59 88 21 32 65 76 98.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "solution.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    cout << "Входной файл: " << endl;
    for (string str; getline(fin, str);)
    {
        cout << str << endl;
    }

    fin.close();
    fin.open("input.txt");

    for (string line; getline(fin, line);)
    {
        for (string_view word : solution(line))
        {
            fout << word << " ";
        }
        fout << endl;
    }

    fin.close();
    fout.close();
    fin.open("output.txt");

    cout << "Выходной файл: " << endl;
    for (string str; getline(fin, str);)
    {
        cout << str << endl;
    }

    return 0;
}