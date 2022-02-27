#include<iostream>
#include<windows.h>
#include<limits.h>
#include<locale.h>

using namespace std;

double lim_while(double, double, double, double, int& n);
double lim_doWhile(double, double, double, double, int& n);
double lim_for(double, double, double, double, int& n);


int main() {
	int key,
	n1, n2, n3;		        //число итераций для разных циклов
	double first_ans, second_ans, third_ans,	//результаты расчетов
	y,			            //значение предела
	y0, y1, y2;	            //текущие значения элементов последовательности
	double eps;		        //точность вычисления предела
	
//	setlocale(LC_ALL, "Russian");
    SetConsoleOutputCP(CP_UTF8);


	for (;;) {
	    
	    //Ввод исходных данных
		cout << " Вид действия:" << endl;
		cout << " 1 - вычисление предела последовательности" << endl;
		cout << " 2 - завершение задачи" << endl;
		cout << " Введите вид действия -> ";
		cin >> key;
	
		switch (key) {
		case 1:
			//Ввод исходных данных
			cout << " Введите значения y0, y1, y2 -> ";
			cin >> y0 >> y1 >> y2;
	
			cout << " Введите точность вычисления -> ";
			cin >> eps;
	
			if (eps <= 0 || eps > .1) {
				cout << "Ошибка ввода. Значение eps д.б. > 0 и  <=0.1" << endl;
				continue;
			}
	
			//Решение циклом while
			first_ans = lim_while(y0, y1, y2, eps, n1 = 3);
			
			if (n1 != INT_MAX) {
				cout.precision(4); 	//число знаков после десятичной точки
				cout << "Для цикла WHILE рез.    = " << first_ans << " n = " << n1 << endl;
			} else {
			    cout << "Для цикла WHILE точность не достигнута" << endl;
			}
			
			//Решение циклом do..while
			second_ans = lim_doWhile(y0, y1, y2, eps, n2 = 2);

			if (n2 != INT_MAX) {
				cout.precision(4); 	//число знаков после десятичной точки
				cout << "Для цикла DO..WHILE рез.= " << second_ans << " n = " << n2 << endl;
			} else {
			    cout << "Для цикла DO..WHILE точность не достигнута" << endl;
			}
			
			//Решение циклом for
			third_ans = lim_for(y0, y1, y2, eps, n3 = 3);
			
			if (n3 != INT_MAX) {
				cout.precision(4); 	//число знаков после десятичной точки
				cout << "Для цикла FOR рез.      = " << third_ans << " n = " << n3 << endl;
			} else {
			    cout << "Для цикла FOR точность не достигнута" << endl;
			    break;
			}
		
		default: return 0;
		}//switch
	}//for
}


double lim_while(double y0, double y1, double y2, double eps, int& n) {
	double y = (y0 + 0.1 * y2) / (2.5 * n * n * n + 1);
	
	while (abs(y - y2) > eps && n < INT_MAX) {
		y0 = y1;
		y1 = y2;
		y2 = y;
		
		n++;
		
		y = (y0 + 0.1 * y2) / (2.5 * n * n * n + 1);
	}
	return y;
}


double lim_doWhile(double y1, double y2, double y, double eps, int& n) {
	double y0;
	
	do {
		y0 = y1;
		y1 = y2;
		y2 = y;
		
		n++;
		
		y = (y0 + 0.1 * y2) / (2.5 * n * n * n + 1);
	
	} while (abs(y - y2) > eps && n < INT_MAX);
	return y;
}


double lim_for(double y0, double y1, double y2, double eps, int& n) {
	double y = (y0 + 0.1 * y2) / (2.5 * n * n * n + 1);
	for (; abs(y - y2) > eps && n < INT_MAX; ) {
		y0 = y1;
		y1 = y2;
		y2 = y;
	
		n++;
	
		y = (y0 + 0.1 * y2) / (2.5 * n * n * n + 1);
	}
	return y;
}
