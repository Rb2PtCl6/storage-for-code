#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool debug = false;

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

struct input_data insert_handy_input(char var[2]) {
	struct input_data to_return = { error, 0 };
	bool first_interaction = true;
	do {
		if (first_interaction) {
			first_interaction = false;
		}
		else {
			printf("%s %s %s\n", "Error: Введённое вами значение для ", var, "неккоректнно. Попробуйте ввести значение снова!");
		};
		struct input_data tmp = get_input(var);
		to_return.value = tmp.value;
		to_return.status = tmp.status;
	} while (to_return.status != ok);
	return to_return;
}

struct input_data insert_handy_input_for_x1(char var[2]) {
	struct input_data to_return = { error, 0 };
	bool first_interaction = true;
	do {
		if (first_interaction) {
			first_interaction = false;
		}
		else {
			printf("%s", "Error: x должен быть больше нуля и быть числом!\n");
		};
		struct input_data tmp = get_input(var);
		to_return.value = tmp.value;
		if (to_return.value > 0) {
			to_return.status = tmp.status;
			break;
		};
	} while (to_return.status != ok);
	return to_return;
}

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

bool is_random_input(int number) {
	printf("\n\n%s %d %s?\n", "Вывести случайные значения для",number, "задания");
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
		struct input_data tmp = { ok, (double)(rand()) + ((double)(rand() % 1000000))/1000000};
		return tmp;
};

void task_1(void) {
	printf("\n%s\n", "1 задание");

	struct input_data x = insert_random_input();
	struct input_data y = insert_random_input();
	struct input_data z = insert_random_input();
	if (!is_random_input(1))
	{
		x = insert_handy_input_for_x1("x");
		y = insert_handy_input("y");
		z = insert_handy_input("z");
	}
	if (debug) {
		printf("x: {status: %d, value: %f}\n", x.status, x.value);
		printf("y: {status: %d, value: %f}\n", y.status, y.value);
		printf("z: {status: %d, value: %f}\n", z.status, z.value);
	}
	if (x.status && y.status && z.status) {
		printf("%s", "Все переменные вещественные числа\n");
		if (x.value < 1)
		{
			printf("%s", "Error: x должен быть больше нуля!\n");
		}
		else {
			printf("h = %f\n", calculate(x.value, y.value, z.value));
		}
	}
	else {
		printf("%s", "Error: Какая-то из переменных не вещественное число\n");
	}
	
};

void task_2(void) {
	printf("\n%s\n", "2 задание");

	struct input_data k = insert_random_input();
	struct input_data m = insert_random_input();

	if (!is_random_input(2))
	{
		k = insert_handy_input("k");
		m = insert_handy_input("m");
	}
	if (debug) {
		printf("k: {status: %d, value: %f}\n", k.status, k.value);
		printf("m: {status: %d, value: %f}\n", m.status, m.value);
	}
	if (k.status && m.status) {
		printf("%s", "Все переменные вещественные числа\n");
		printf("j = %f\n", calculate2(k.value, m.value));
	}
	else {
		printf("%s", "Error: Какая-то из переменных не вещественное число\n");
	}
};

void task_3(void) {
	printf("\n%s\n", "3 задание");
	printf("%s\n", "+---------+---------+");
	printf("%s\n", "|    x    |    y    |");
	printf("%s\n", "+---------+---------+");
	for (size_t i = 0; i <= 10; i++)
	{
		double x = ((double)i - 5.0) / 5.0;
		printf("%s %5.1f %s %7.4f %s\n","|", x, "  |", calculate3(x), "|");
	}
	printf("%s\n", "+---------+---------+");
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

	printf("%s\n\n", "Никита Громов, 4303, 1 контрольная, 8 вариант контрольной, все задания");

	launcher();
	return EXIT_SUCCESS;
}