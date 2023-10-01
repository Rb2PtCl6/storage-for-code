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

struct input_data
{
	enum input_statuss statuss;
	double value;
};

int allowed[] = {48,49,50,51,52,53,54,55,56,57,45,46};

bool check(char this_char) {
	for (size_t j = 0; j < sizeof(allowed); j++)
	{
		//printf("%d\n", this_char);
		//printf("%d\n", allowed[j]);
		if (this_char == allowed[j])
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
	printf("������� %s: ", var);
	char raw[13];
	gets_s(raw,12);
	//printf("%s\n", raw);
	for (size_t i = 0; i < strlen(raw); i++)
	{
		char this_char = raw[i];
		char next_char = raw[i + 1];
		if (!check(this_char)) {
			struct input_data to_return = { error, 0 };
			return to_return;
		}
	}
	struct input_data to_return = { ok, atof(raw)};
	return to_return;
}

struct input_data random_input(char var[2]) {
	printf("\n\n%s %s ?\n", "������� ��������� �������� ���",var);
	printf("%s\n", "q = 1 - ��");
	printf("%s\n\n", "q = 2 - ���");

	struct input_data state = get_input("q");
	switch ((int)state.value)
	{
	case 1:
		printf("%s %s\n", "������� ��������� ����� ���",var);
		struct input_data to_return1 = { ok, 0 };
		return to_return1;
		break;
	case 2:
		printf("%s %s\n", "������ ������ ���� ���",var);
		struct input_data to_return2 = { error, 0 };
		return to_return2;
		break;
	default:
		printf("%s %s\n", "��� ���� ����������! ������ ������ ����", var);
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
	printf("\n%s\n", "1 �������");

	struct input_data x = insert_input("x");
	struct input_data y = insert_input("y");
	struct input_data z = insert_input("z");
	printf("x: {statuss: %d, value: %f}\n", x.statuss, x.value);
	printf("y: {statuss: %d, value: %f}\n", y.statuss, y.value);
	printf("z: {statuss: %d, value: %f}\n", z.statuss, z.value);

	if (x.statuss && y.statuss && z.statuss) {
		printf("%s", "��� ���������� ������������ �����\n");
		printf("h = %f\n", calculate(x.value, y.value, z.value));
	}
	else {
		printf("%s", "�����-�� �� ���������� �� ������������ �����\n");
	}
	
};
void task_2(void) {
	printf("\n%s\n", "2 �������");
	struct input_data k = insert_input("k");
	struct input_data m = insert_input("m");
	printf("k: {statuss: %d, value: %f}\n", k.statuss, k.value);
	printf("m: {statuss: %d, value: %f}\n", m.statuss, m.value);
	if (k.statuss && m.statuss) {
		printf("%s", "��� ���������� ������������ �����\n");
		printf("j = %f\n", calculate2(k.value, m.value));
	}
	else {
		printf("%s", "�����-�� �� ���������� �� ������������ �����\n");
	}
};
void task_3(void) {
	printf("\n%s\n", "3 �������");
	printf("%s  %s\n", "x","y");
	for (size_t i = 0; i <= 10; i++)
	{
		double x = ((double)i - 5.0) / 5.0;
		printf("%f  %f\n", x, calculate3(x));
	}
};
void launcher(void) {
	int exit_action = 0;
	printf("%s\n", "��������� ��������");
	do {
		printf("\n\n%s\n\n", "�������� ��������:");
		printf("%s\n", "n = 1 - 1 �������");
		printf("%s\n", "n = 2 - 2 �������");
		printf("%s\n", "n = 3 - 3 �������");
		printf("%s\n\n", "n = 4 - �����");
		printf("%s\n", "��� �����:");

		struct input_data state = get_input("n");

		switch ((int)state.value)
		{
		case 1:
			task_1();
			exit_action = 0;
			break;
		case 2:
			task_2();
			exit_action = 0;
			break;
		case 3:
			task_3();
			exit_action = 0;
			break;
		case 4:
			exit_action = 1;
			break;
		default:
			printf("%s\n", "��� ���� ����������!");
			exit_action = 0;
			break;
		}
	} while (exit_action != 1);
	printf("%s\n", "��������� ���������");
};

int main(void) {
	//system("chcp 1251");
	//system("chcp");
	//system("cls");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	/*char eng[] = "english\n";
	char ru[] = "�������\n";

	printf("%s", eng);
	printf("%s", ru);*/

	printf("%s\n\n", "name, 4303, 1 �����������, 8 ������� �����������, ��� �������");

	launcher();
	printf("%s", "����� ����\n");
	return 0; // ���������-��������������� ���
}