#include<iostream>
#include <cmath>
#include <windows.h>

using namespace std;

float while_recur(int m, float y0, float y1, float y2);
float doWhile_recur(int m, float y0, float y1, float y2);
float for_recur(int m, float y0, float y1, float y2);

int main() {
	int var, m;
	float first_ans, second_ans, third_ans;		//результаты решения задачи
	float y0, y1, y2;		                    //исходные данные

    SetConsoleOutputCP(CP_UTF8);

	for (;;) {//Выбор действия
		cout << "\n  Вид действия:" << endl;
		cout << " 1 - вычисление суммы по рекуррентной формуле" << endl;
		cout << " 2 - завершение задачи" << endl;
		cout << " Введите вид действия -> ";
		cin >> var;
		
		switch (var) {
		
		case 1://Ввод исходных данных
			cout << " Введите m -> ";
			cin >> m;
			
			cout << " Введите y0, y1, y2 -> ";
			cin >> y0 >> y1 >> y2;
			
			first_ans = while_recur(m, y0, y1, y2);
			second_ans = doWhile_recur(m, y0, y1, y2);
			third_ans = for_recur(m, y0, y1, y2);
			
			//Вывод результата
			cout.precision(3);//число знаков после запятой при выводе
			cout << " Для цикла WHILE результат     = " << first_ans << endl;
			cout << " Для цикла DO..WHILE результат = " << second_ans << endl;
			cout << " Для цикла FOR результат       = " << third_ans << endl;
			break;
		
		default: return 1;
		}//switch
	}//for
}

float while_recur(int m, float y0, float y1, float y2) {
	int i = 0;  		//текущий номер слагаемого
	float y,			//очередное значение y[i]
	sum = 0;			//начальное значение суммы

	sum += (i*i*i)/(m + 1.) * y0; i++;
	sum += (i*i*i)/(m + 1.) * y1; i++;
	sum += (i*i*i)/(m + 1.) * y2; i++;
	
	while (i <= m) {
        y = sqrt(abs( (sin(y2) - cos(y0) * cos(y0)) / ((i*i) / 10. - (i + 1)/2. + 1.5)));

		sum += (i*i*i)/(m + 1.) * y;

		y0 = y1;
		y1 = y2;
		y2 = y;

		i++;
	}
	return(sum + m);
}


float doWhile_recur(int m, float y0, float y1, float y2) {
	int   i = 0;		//текущий номер слагаемого
	float y,			//очередное значение y[i]
	
	sum = 0;			//начальное значение суммы
	
	sum += (i*i*i) / (m + 1.) * y0; i++;
	sum += (i*i*i) / (m + 1.) * y1; i++;
	sum += (i*i*i) / (m + 1.) * y2; i++;
	
	do {
        y = sqrt(abs( (sin(y2) - cos(y0) * cos(y0)) / ((i*i) / 10. - (i + 1)/2. + 1.5)));
	
		sum += (i*i*i)/(m + 1.) * y;
	
		y0 = y1;
		y1 = y2;
		y2 = y;
	
		i++;
	} while (i <= m);
    return sum + m;
}

float for_recur(int m, float y0, float y1, float y2) {
	int   i = 0;		//текущий номер слагаемого
	float y,			//очередное значение y[i]
	sum = 0;			//начальное значение суммы

	sum += (i*i*i)/(m + 1.) * y0; i++;
	sum += (i*i*i)/(m + 1.) * y1; i++;
	sum += (i*i*i)/(m + 1.) * y2; i++;

	for (; i <= m; i++) {
		y = sqrt(abs( (sin(y2) - cos(y0) * cos(y0)) / ((i*i) / 10. - (i + 1)/2. + 1.5)));

		sum += (i*i*i)/(m + 1.) * y;

		y0 = y1;
		y1 = y2;
		y2 = y;
	}
	return(sum + m);
}
