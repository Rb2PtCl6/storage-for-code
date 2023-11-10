#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool debug = true;

enum input_status
{
	error = 0,
	ok = 1
};

enum my_exit
{
	no = 0,
	yes = 1
};

struct input_data
{
	enum input_status status;
	double value;
};

struct input_data get_input(char var[2]) {
	printf("Введите %s: ", var);
	double input = 0.0;
	//while (!scanf("%lf", &input)) {
	while (!scanf_s("%lf", &input)) {
		while (getchar() != '\n');
		struct input_data to_return = { error, 0 };
		return to_return;
	}
	while (getchar() != '\n');
	struct input_data to_return = { ok, input };
	return to_return;
};

struct input_data get_input_1(char var[2], int num1) {
	printf("Введите %s%d: ", var, num1);
	double input = 0.0;
	//while (!scanf("%lf", &input)) {
	while (!scanf_s("%lf", &input)) {
		while (getchar() != '\n');
		struct input_data to_return = { error, 0 };
		return to_return;
	}
	while (getchar() != '\n');
	struct input_data to_return = { ok, input };
	return to_return;
};

struct input_data get_input_2(char var[2], int num1, int num2) {
	printf("Введите %s(%d;%d): ", var, num1, num2);
	double input = 0.0;
	//while (!scanf("%lf", &input)) {
	while (!scanf_s("%lf", &input)) {
		while (getchar() != '\n');
		struct input_data to_return = { error, 0 };
		return to_return;
	}
	while (getchar() != '\n');
	struct input_data to_return = { ok, input };
	return to_return;
};

struct input_data insert_handy_input_1(char var[2], int num1) {
	struct input_data to_return = { error, 0 };
	bool first_interaction = true;
	do {
		if (first_interaction) {
			first_interaction = false;
		}
		else {
			printf("%s %s%d %s\n", "Error: Введённое вами значение для ", var, num1, "неккоректнно. Попробуйте ввести значение снова!");
		};
		struct input_data tmp = get_input_1(var, num1);
		to_return.value = tmp.value;
		to_return.status = tmp.status;
	} while (to_return.status != ok);
	return to_return;
}

struct input_data insert_handy_input_2(char var[2], int num1, int num2) {
	struct input_data to_return = { error, 0 };
	bool first_interaction = true;
	do {
		if (first_interaction) {
			first_interaction = false;
		}
		else {
			printf("%s %s(%d,%d) %s\n", "Error: Введённое вами значение для ", var, num1, num2 , "неккоректнно. Попробуйте ввести значение снова!");
		};
		struct input_data tmp = get_input_2(var, num1, num2);
		to_return.value = tmp.value;
		to_return.status = tmp.status;
	} while (to_return.status != ok);
	return to_return;
}

bool is_random_input(int number) {
	printf("\n\n%s %d %s?\n", "Вывести случайные значения для", number, "задания");
	printf("%s\n", "q = 1 - да");
	printf("%s\n\n", "q = 2 - нет");

	switch ((int)get_input("q").value)
	{
	case 1:
		printf("%s %d %s\n", "Выбрано случайные числа для", number, "задания");
		return true;
		break;
	case 2:
		printf("%s %d %s\n", "Выбран ручной ввод значений для", number, "задания");
		return false;
		break;
	default:
		printf("%s %d %s\n", "Error: Ваш ввод некоректен! \nВыбран ручной ввод значений для", number, "задания");
		return false;
		break;
	}
}

struct input_data insert_random_input(void) {
	struct input_data tmp = { ok, (double)(rand()) + ((double)(rand() % 1000000)) / 1000000 };
	return tmp;
};

double calculate_1_y(int i);
double calculate_1_x(int i) {
	if (i == 0) {
		return 1.0;
	}
	else {
		double to_return = calculate_1_x(i-1) + calculate_1_y(i - 1);
		return to_return;
	}
};
double calculate_1_y(int i) {
	if (i == 0) {
		return 0.14;
	}
	else {
		double to_return = calculate_1_y(i - 1) + sin(calculate_1_x(i - 1)) - 0.5 * calculate_1_x(i);
		return to_return;
	}
};

void switch_row(double *h_row, double *h_row_changed) {
	if (h_row[0] != 0) {
		for (int i = 0; i < 5; i++) {
			h_row_changed[i] = h_row[i];
		}
	}
	else {
		int h_row_index = 4;
		int h_row_changed_index = 0;

		enum my_exit exit_action = no;
		while (exit_action != 1) {
			h_row_changed[h_row_changed_index] = h_row[h_row_index];
			h_row_changed_index++;
			h_row_index--;
			if (h_row_changed_index == 5 || h_row_index == -1) {
				exit_action = yes;
			}
		}
	}
}

void task_1(void) {
	printf("\n%s\n", "1 задание");

	double x_max = calculate_1_x(0);
	double y_min = calculate_1_y(0);

	for (int i = 0; i < 15; i++) {
		double x_this = calculate_1_x(i);
		double y_this = calculate_1_y(i);
		if (debug) {
			printf("%d: {x: %f, y: %f}\n", i, x_this, y_this);
		}
		if (x_this > x_max) {
			x_max = x_this;
		}
		if (y_this < y_min) {
			y_min = y_this;
		}
	}

	printf("x_max = %f, y_min = %f\n", x_max, y_min);
};

void task_2(void) {
	printf("\n%s\n", "2 задание");

	struct input_data a[20] = { 0 };
	struct input_data b[20] = { 0 };

	for (int i = 0; i < 20; i++) {
		a[i] = insert_random_input();
		b[i] = insert_random_input();
	}

	if (!is_random_input(2)) {
		for (int i = 0; i < 20; i++) {
			a[i] = insert_handy_input_1("a",i+1);
		}
		for (int i = 0; i < 20; i++) {
			b[i] = insert_handy_input_1("b", i+1);
		}
	}

	if (debug) {
		for (int i = 0; i < 20; i++) {
			printf("%d:{a:%f, b:%f}\n", i, a[i].value, b[i].value);
		}
	}

	enum my_exit exit_action = no;
	int a_current = 0;
	int b_current = 19;

	double result = 1.0;

	while (exit_action != 1)
	{
		result *= (a[a_current].value + b[b_current].value);
		a_current++;
		b_current--;
		if (a_current == 20 || b_current == -1) {
			exit_action = yes;
		}
	}

	printf("%s %f", "Результат вычисления:", result);
};

void task_3(void) {
	printf("\n%s\n", "3 задание");
	
	double h[4][5] = { 0.0 };
	double h_changed[4][5] = { 0.0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			h[i][j] = insert_random_input().value;
		}
	}

	if (!is_random_input(3)) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				h[i][j] = insert_handy_input_2("h", i+1, j+1).value;
			}
		}
	}

	if (debug) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				printf("h(%d,%d) = %f\n", i, j, h[i][j]);
			}
		}
	}

	int less_then_0 = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (h[i][j] < 0) {
				less_then_0++;
			}
		}
	}

	int less_then_0_arr_index = 0;
	double* less_then_0_arr = malloc(less_then_0 * sizeof(double));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			if (h[i][j] < 0) {
				less_then_0_arr[less_then_0_arr_index] = h[i][j];
				less_then_0_arr_index++;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		switch_row(h[i], h_changed[i]);
	}
	printf("\n\n%s\n\n", "Исходная матрица");
	for (int i = 0; i < 4; i++) {
		printf("%f %f %f %f %f\n", h[i][0], h[i][1], h[i][2], h[i][3], h[i][4]);
	}
	printf("\n\n%s\n\n", "Переобразованная матрица");
	for (int i = 0; i < 4; i++) {
		printf("%f %f %f %f %f\n", h_changed[i][0], h_changed[i][1], h_changed[i][2], h_changed[i][3], h_changed[i][4]);
	};

	printf("\n\n%s\n\n%s", "Вектор","a = ( ");
	for (int i = 0; i < less_then_0; i++) {
		printf("%f, ", less_then_0_arr[i]);
	}
	printf("%d )\n\n", less_then_0);
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

		switch ((int)get_input("n").value)
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
			printf("%s\n", "Ваш ввод некоректен! Возврат в меню!");
			exit_action = no;
			break;
		}
	} while (exit_action != 1);
	printf("%s\n", "Программа завершена");
};

int main(void) {
	system("chcp 1251");

	printf("%s\n\n", "Никита Громов, 4303, 2 контрольная, 8 вариант контрольной, все задания");

	launcher();
	return EXIT_SUCCESS;
}