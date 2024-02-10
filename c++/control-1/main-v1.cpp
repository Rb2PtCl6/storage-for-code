#include <iostream>
#include <format>
#include <string>
#include <optional>
#include <regex>

using namespace std;

void print_message(string str) {
	cout << str;//<< endl;
}

enum exit {
	yes = 1,
	no = 2
};

enum input_mode {
	in_keyboard = 1,
	in_file = 2
};
enum output_mode {
	out_console = 1,
	out_file = 2,
	out_combo = 3
};

struct ret_srting {
	string str;
	bool ok;
};

struct ret_int {
	int num;
	bool ok;
};

struct ret_double {
	double num;
	bool ok;
};

struct patient_data {
	string name;
	string surname1;
	string surname2;
	string address;
	string diagnosis;
};

int max_id = 1;

// https://regex101.com/

class patient {
private:
	string name = "Нет данных";
	string surname1 = "Нет данных";
	string surname2 = "Нет данных";
	string address = "Нет данных";
	int id = 0;
	string diagnosis = "Нет данных";
public:
	patient(struct patient_data data) {
		set(data);
	}
	void set(struct patient_data data) {
		name = data.name;
		surname1 = data.surname1;
		surname2 = data.surname2;
		address = data.address;
		id = max_id;
		max_id++;
		diagnosis = data.diagnosis;
	};
	//get() {};
	void show() {
		print_message(format("Имя: {}\nФамилия : {}\nОтчество: {}\nАдресс: {}\nНомер пациента : {}\nДиагноз пациента: {}\n",
			name, surname1, surname2, address, id, diagnosis));
	}
	bool is_valid_name(string str) { 
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_surname1(string str) {
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_surname2(string str) {
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_address(string str) {
		regex comparison("[а-яА-я0-9,-/. ]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_diagnosis(string str) {
		regex comparison("[а-яА-я0-9]{1,}");
		return regex_match(str, comparison);
	}
};

class getter {
	public: 
		struct ret_srting static getString(){
			string str;
			try {
				getline(cin, str);
			}
			catch (...) {
				return { "",false };
			}
			return { str, true };
		}
		struct ret_int static getInt() {
			auto str = getString();
			if (!str.ok) return { 0, false };
			int num;
			try {
				num = stoi(str.str);
			}
			catch (...) {
				return { 0, false };
			}
			return { num, true };
		}
		struct ret_double static getDouble() {
			auto str = getString();
			if (!str.ok) return { 0.0, false };
			double num;
			try {
				num = stod(str.str);
			}
			catch (...) {
				return { 0.0, false };
			}
			return { num, true };
		}
};


int main() {
	system("chcp 1251");
	print_message(format("{}\n", "Никита Громов, 4303, 1 контрольная, 8 вариант контрольной, все задания"));
	
	bool leave_menu = false;
	do {
		// Выберите способ ввода данных
		// Клавиатура - 1
		// Файл - 2
		// 
		// Выбран ввод с клавиатуры
		// Выбрано считываеие файла
		// 
		// Укажите путь для файла ввода данных ( расширение файла csv )
		// Укажите путь для вывода данных
		// 
		// Хотите перезаписать файл?
		// Да - 1
		// Нет - 2
		// 
		// Данный файл не доступен для записи
		// 
		// Выберите способ вывода данных
		// Консоль - 1
		// Фейл - 2
		// Комбинированный - 3
		//
		// Выберите дальнейшее действие
		// Ввод данных - 1
		// Вывод данных - 2
		//
		print_message(format("\n{}\n{}\n{}\n{}\n", "Хотите покинуть меню взаймодествия с данными пациета?", "Да - 1", "Нет - 2", "Ваш выбор:"));
		switch (getter::getInt().num)
		{
		case yes:
			print_message(format("\n{}\n", "Выбран выход из меню"));
			leave_menu = true;
			break;
		case no:
			print_message(format("\n{}\n", "Выбрано остаться в меню"));
			break;
		default:
			print_message(format("\n{}\n", "Выбрано неккоретное значение! Вы остаётесь в меню!"));
			break;
		}
	} while (!leave_menu);

	return EXIT_SUCCESS;
}