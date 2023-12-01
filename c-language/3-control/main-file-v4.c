#define _CRT_SECURE_NO_WARNINGS

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

double absd(double num) {
	if (num > 0) {
		return num;
	} if (num == 0.0) {
		return 0.0;
	}
	else {
		double to_ruturn = num * -1;
		return to_ruturn;
	}
}

double get_int_part(double num) {
	double a = 0.0;
	double b = modf(num, &a);
	return a;
}

int number_size(double max, double min) {
	int size = 0;

	double this_max = get_int_part(absd(max));
	double this_min = get_int_part(absd(min));

	double val = 0;
	if (this_max > this_min) {
		val = this_max;
	}
	else {
		val = this_min;
	}

	while (get_int_part(val) != 0) {
		size++;
		val = val / 10;
		
	}
	return size;
}

struct mask_return
{
	char *mask;
};

struct mask_return generate_mask(int size) {
	char pattern1[7] = "% 0.3f";
	char pattern2[8] = "% 00.3f";
	char pattern3[9] = "% 000.3f";

	if (size < 10) {
		char tmp1[2] = "0";
		sprintf(tmp1, "%d", size);
		printf("%s", tmp1);
		pattern1[2] = tmp1[0];
		printf("%s", pattern1);

		struct mask_return to_return = { malloc(7*sizeof(char))};
		
		for (int i = 0; i < 7; i++) {
			to_return.mask[i] = pattern1[i];
		}

		printf("%s", to_return.mask);
		return to_return;
	}
	else if (size < 100) {
		char tmp2[3] = "00";
		sprintf(tmp2, "%d", size);
		printf("%s", tmp2);
		pattern2[2] = tmp2[0];
		pattern2[3] = tmp2[1];
		printf("%s", pattern2);
		
		struct mask_return to_return = { malloc(7 * sizeof(char)) };

		for (int i = 0; i < 8; i++) {
			to_return.mask[i] = pattern2[i];
		}
		printf("%s", to_return.mask);
		return to_return;

	}
	else {
		char tmp3[4] = "000";
		sprintf(tmp3, "%d", size);
		printf("%s", tmp3);
		pattern3[2] = tmp3[0];
		pattern3[3] = tmp3[1];
		pattern3[4] = tmp3[2];
		printf("%s", pattern3);

		struct mask_return to_return = { malloc(7 * sizeof(char)) };
		
		for (int i = 0; i < 9; i++) {
			to_return.mask[i] = pattern3[i];
		}
		printf("%s", to_return.mask);
		return to_return;
	}
}

//Введите m(1;1): 88888888888888888888888
//Введите m(1;2): -8888888888888888888888888
//Введите m(2;1): 99999999999999
//Введите m(2;2): -99999999999999
void task_1(void) {
	printf("\n%s\n", "1 задание");

	printf("%s\n", "Введите размер матрицы (m)");
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
				tmp_dbl = insert_handy_input_2("M", i, j).value;
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

	double a_max = a[0][0];
	double a_min = a[0][0];

	for (int i = 0; i < mx2; i++) {
		for (int j = 0; j < mx2; j++) {
			if (a[i][j] > a_max) {
				a_max = a[i][i];
			}
			if (a[i][j] < a_min) {
				a_min = a[i][j];
			}
		}
	}

	int max_print_size = number_size(a_max, a_min) + 1 + 3 + 2;
	//printf("\nyyyy\n%d\n\n", max_print_size);

	
	struct mask_return mask0 = generate_mask(max_print_size);
	//char mask[] = mask0.mask;
	printf("%s", mask0.mask);

	printf("\n%s\n\n", "Матрица А");
	for (int i = 0; i < mx2; i++) {
		for (int j = 0; j < mx2; j++) {
			printf(mask0.mask, a[i][j]);
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
			printf(mask0.mask, b[i][j]);
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