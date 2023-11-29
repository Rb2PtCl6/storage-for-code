#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include <ctype.h>

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
	printf("Введите %s(%d;%d): ", var, num1 + 1, num2 + 1);
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
			printf("%s %s(%d,%d) %s\n", "Error: Введённое вами значение для ", var, num1 + 1, num2 + 1, "неккоректнно. Попробуйте ввести значение снова!");
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
	struct input_data tmp = { ok, (double)(rand() - rand()) + ((double)(rand() % 1000000)) / 1000000 };
	return tmp;
};

struct input_data insert_handy_input_for_m1(char var[2]) {
	struct input_data to_return = { error, 0 };
	bool first_interaction = true;
	do {
		if (first_interaction) {
			first_interaction = false;
		}
		else {
			printf("%s", "Error: m должен быть больше нуля и быть числом!\n");
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

bool is_russian_vowel(int charter) {
	char letters[] = "аоиеёэыуюяАОИЕЁЭЫУЮЯ";
	for (int i = 0; i < 20; i++) {
		if (charter == letters[i]) {
			return true;
		}
	}
	return false;
}

int fold(int* array, int size, int (*action)(int, int)) {
	if (debug && false) {
		for (int i = 0; i < size; i++) {
			printf("\n %d", array[i]);
		}
	}
	int collected = 1;
	for (int i = 0; i < size; i++) {
		collected = action(collected, *(array + i));
	}
	return collected;
}

int mul(int collected, int this_int) {
	if (debug && false) {
		printf("\n %d %d\n", collected, this_int);
	}
	
	int to_return = collected * this_int;
	return to_return;
}

void task_1(void) {
	printf("\n%s\n", "1 задание");

	printf("%s", "Введите размер матрицы (m)");
	int m = (int)insert_handy_input_for_m1("m").value;
	bool is_random = !is_random_input(1);

	int mx2 = m * 2;

	double** a = malloc(mx2 * sizeof(double));
	for (int i = 0; i < mx2; i++) {
		a[i] = malloc(mx2 * sizeof(double));
	}

	double** b = malloc(mx2 * sizeof(double));
	for (int i = 0; i < mx2; i++) {
		b[i] = malloc(mx2 * sizeof(double));
	}

	int i2 = 0;
	int j2 = 0;

	double tmp_dbl = 0.0;

	for (int i = 0; i < mx2; i++) {
		for (int j = 0; j < mx2; j++) {
			tmp_dbl = insert_random_input().value;
			if (is_random) {
				tmp_dbl = insert_handy_input_2("m", i, j).value;
			}

			if (i < m) {
				i2 = i + m;
			}
			else {
				i2 = i - m;
			};
			if (j < m) {
				j2 = j + m;
			}
			else {
				j2 = j - m;
			}
			a[i][j] = tmp_dbl;
			b[i2][j2] = tmp_dbl;
		}
	}
	printf("\n%s\n\n", "Матрица А");
	for (int i = 0; i < mx2; i++) {
		for (int j = 0; j < mx2; j++) {
			printf("%f", a[i][j]);
			if (j == mx2 - 1) {
				printf("\n");
			}
			else {
				printf(" ");
			}
		}
	}

	printf("\n%s\n\n", "Матрица В");
	for (int i = 0; i < mx2; i++) {
		for (int j = 0; j < mx2; j++) {
			printf("%f", b[i][j]);
			if (j == mx2 - 1) {
				printf("\n");
			}
			else {
				printf(" ");
			}
		}
	}

	for (int i = 0; i < mx2; i++) {
		free(a[i]);
		a[i] = NULL;
	}
	for (int i = 0; i < mx2; i++) {
		free(b[i]);
		b[i] = NULL;
	}
	free(a);
	a = NULL;
	free(b);
	b = NULL;
};

void task_2(void) {
	printf("\n%s\n", "2 задание");

	char input[9] = { '0' };
	char output[9] = { '0' };

	printf("\n%s", "Введите 8 символов");
	//scanf_s("%8s", input);
	for (int i = 0; i < 8; i++) {
		printf("\n%s %d %s:", "Введите", i + 1, "символ");
		input[i] = getchar();
		while (getchar() != '\n');
	}
	input[8] = '\0';
	output[8] = '\0';
	if (debug) {
		printf("\n%s\n", &input);
		for (int i = 0; i < 8; i++) {
			printf("\n%c: %d\n", input[i], is_russian_vowel(input[i]));
		}
	}
	for (int i = 0; i < 8; i++) {
		if (is_russian_vowel(input[i])) { // | - побитовый and
			output[i] = input[i] | 1; // 1 - 00000001 - маска для замены
		}
		else {
			output[i] = input[i] | 6; // 6 - 00000110 - маска для замены
		}
	}
	// https://www.rapidtables.org/ru/convert/number/binary-to-decimal.html
	// https://calcus.ru/perevod-sistem-schisleniya/iz-desyatichnoy-v-vosmerichnuyu

	// https://learnc.info/c/formatted_input_output.html
	printf("\n\n%s\n", "Исходная последовательность");
	printf("\n%s %s\n", "Введённая:", input);
	printf("\n%s %s\n", "Преобразованная:", output);
	printf("\n\n%s\n", "Последовательность в восмеричном виде");
	printf("\n%s", "Введённая:");
	for (int i = 0; i < 8; i++) {
		printf(" %o", (unsigned char)input[i]);
	}
	printf("\n");
	printf("\n%s", "Преобразованная:");
	for (int i = 0; i < 8; i++) {
		printf(" %o", (unsigned char)output[i]);
	}
	printf("\n");
};

void task_3(void) {
	printf("\n%s\n", "3 задание");
	printf("%s\n", "Введите размер массива (m)");
	int m = (int)insert_handy_input_for_m1("m").value;

	bool is_random = !is_random_input(3);

	int* a = malloc(m * sizeof(int));
	for (int i = 0; i < m; i++) {
		if (is_random) {
			a[i] = (int)insert_handy_input_1("a", i + 1).value;
		}
		else {
			a[i] = (int)insert_random_input().value;
		}
	}
	if (debug && false) {
		for (int i = 0; i < m; i++) {
			printf("\n %d", a[i]);
		}
	}
	
	printf("\n\n %s %d\n", "Резельтат fold = ", fold(a, m, mul));
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

	printf("%s\n\n", "Никита Громов, 4303, 3 контрольная, 8 вариант контрольной, все задания");

	launcher();
	return EXIT_SUCCESS;
}