#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include <windows.h>

enum input_statuss
{
	error = 0,
	ok = 1
};

enum my_exit
{
	no = 0,
	yes = 1
};

enum all_allowed_symbols
{
	n0 = 48,
	n1 = 49,
	n2 = 50,
	n3 = 51,
	n4 = 52,
	n5 = 53,
	n6 = 54,
	n7 = 55,
	n8 = 56,
	n9 = 57,
	s_minus = 45,
	s_dot = 46
};

struct input_data
{
	enum input_statuss statuss;
	double value;
};

enum all_allowed_symbols allowed_symbols[] = {n0,n1,n2,n3,n4,n5,n6,n7,n8,n9,s_minus,s_dot};

bool check(char this_char) {
	for (size_t j = 0; j < sizeof(allowed_symbols); j++)
	{
		//printf("%d\n", this_char);
		//printf("%d\n", allowed[j]);
		if (this_char == allowed_symbols[j])
		{
			//printf("%s", "there");
			return true;
		}
		//printf("%s", "raw");
	};
	return false;
};

double calculate(double x, double y, double z) {
	double result = 2 + (pow(x,2)/sqrt(2)) + (fabs(pow(y, 3)) /sqrt(2)) + (pow(z, 4)*(log(x)+1)* sqrt(2) /sqrt(3));
	return result;
};

double calculate2(double k, double m) {
	double j = 0;
	if (k < m) {
		j = sin(5 * k + 3 * m * fabs(k));
	} else if (k> m) {
		j = cos(5 * k + 3 * m * fabs(k));
	} else {
		j = pow(k, 3);
	}
	return j;
}

double calculate3(double x) {
	double y = 0;
	if (x > 0) {
		y = pow(tan(x), 2);
	}
	else {
		y = pow(x, 2) * sin(x);
	};
	return y;
}

struct input_data get_input(char var[2]) {
	printf("Введите %s: ", var);
	char raw[13];
	gets_s(raw,12);
	//printf("%s\n", raw);
	for (size_t i = 0; i < strlen(raw); i++)
	{
		if (!check(raw[i])) {
			struct input_data to_return = { error, 0 };
			return to_return;
		}
	}
	struct input_data to_return = { ok, atof(raw)};
	return to_return;
}

struct input_data random_input(char var[2]) {
	printf("\n\n%s %s ?\n", "Вывести случайное значение для",var);
	printf("%s\n", "q = 1 - да");
	printf("%s\n\n", "q = 2 - нет");

	switch ((int)get_input("q").value)
	{
	case 1:
		printf("%s %s\n", "Выбрано случайное число для",var);
		struct input_data to_return1 = { ok, 0 };
		return to_return1;
		break;
	case 2:
		printf("%s %s\n", "Выбран ручной ввод для",var);
		struct input_data to_return2 = { error, 0 };
		return to_return2;
		break;
	default:
		printf("%s %s\n", "Ваш ввод некоректен! Выбран ручной ввод", var);
		struct input_data to_return3 = { error, 0 };
		return to_return3;
		break;
	}
}

struct input_data insert_input(char var[2]) {
	if (random_input(var).statuss) {
		struct input_data tmp = { ok, (double)rand() };
		return tmp;
	}
	else {
		struct input_data tmp = get_input(var);
		return tmp;
	}
};

void task_1(void) {
	printf("\n%s\n", "1 задание");

	struct input_data x = insert_input("x");
	struct input_data y = insert_input("y");
	struct input_data z = insert_input("z");
	printf("x: {statuss: %d, value: %f}\n", x.statuss, x.value);
	printf("y: {statuss: %d, value: %f}\n", y.statuss, y.value);
	printf("z: {statuss: %d, value: %f}\n", z.statuss, z.value);

	if (x.statuss && y.statuss && z.statuss) {
		printf("%s", "Все переменные вещественные числа\n");
		printf("h = %f\n", calculate(x.value, y.value, z.value));
	}
	else {
		printf("%s", "Какая-то из переменных не вещественное число\n");
	}
	
};
void task_2(void) {
	printf("\n%s\n", "2 задание");
	struct input_data k = insert_input("k");
	struct input_data m = insert_input("m");
	printf("k: {statuss: %d, value: %f}\n", k.statuss, k.value);
	printf("m: {statuss: %d, value: %f}\n", m.statuss, m.value);
	if (k.statuss && m.statuss) {
		printf("%s", "Все переменные вещественные числа\n");
		printf("j = %f\n", calculate2(k.value, m.value));
	}
	else {
		printf("%s", "Какая-то из переменных не вещественное число\n");
	}
};
void task_3(void) {
	printf("\n%s\n", "3 задание");
	printf("%s  %s\n", "x","y");
	for (size_t i = 0; i <= 10; i++)
	{
		double x = ((double)i - 5.0) / 5.0;
		printf("%f  %f\n", x, calculate3(x));
	}
};
void launcher(void) {
	enum my_exit exit_action = no;
	printf("%s\n", "Программа запущена");
	do {
		printf("\n\n%s\n\n", "Выберите действие:");
		printf("%s\n", "n = 1 - 1 задание");
		printf("%s\n", "n = 2 - 2 задание");
		printf("%s\n", "n = 3 - 3 задание");
		printf("%s\n\n", "n = 4 - выход");
		printf("%s\n", "Ваш выбор:");

		struct input_data state = get_input("n");

		switch ((int)state.value)
		{
		case 1:
			task_1();
			exit_action = no;
			break;
		case 2:
			task_2();
			exit_action = no;
			break;
		case 3:
			task_3();
			exit_action = no;
			break;
		case 4:
			exit_action = yes;
			break;
		default:
			printf("%s\n", "Ваш ввод некоректен!");
			exit_action = no;
			break;
		}
	} while (exit_action != 1);
	printf("%s\n", "Программа завершена");
};

int main(void) {
	//system("chcp 1251");
	//system("chcp");
	//system("cls");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*char eng[] = "english\n";
	char ru[] = "русский\n";

	printf("%s", eng);
	printf("%s", ru);*/

	printf("%s\n\n", "Никита Громов, 4303, 1 контрольная, 8 вариант контрольной, все задания");

	launcher();
	printf("%s", "Конец кода\n");
	return 0; // костыльно-ориентированный код
}