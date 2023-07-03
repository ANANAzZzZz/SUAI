/*
 * ������� (��� 45)
 * ���� ������������ ������. ��� ������ ����������
 * ������������������ ����. ����� ��������� ������� - ��
 * ����� ������ �������. ����� ������ � �� ���������
 * ������ ������ ������������ ����� ��������.
 * ��������� ���� �������, �� ���� �������� ��������
 * ������ ���������� ������� ��� ����� � ������
 * ��������� ����� �������� � ��� ����, ����� ���
 * ����� � �������� ��������� ����� ����, ��������
 * �������� ������� � ������ ������.
 * ��������:
 *     - �������� ������������������: 15 21 32 48 59 65 76 88 98;
 *     - ���������: 15 48 59 88 21 32 65 76 98.
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

    cout << "������� ����: " << endl;
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

    cout << "�������� ����: " << endl;
    for (string str; getline(fin, str);)
    {
        cout << str << endl;
    }

    return 0;
}