#include <iostream>
#include <format>
#include <string>
#include <optional>
#include <regex>
#include <fstream>
#include <filesystem>

using namespace std;

void print_message(string str) {
	cout << str;
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

struct patient_data_full {
	string name;
	string surname1;
	string surname2;
	string address;
	int id;
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
	bool static is_valid_name(string str) {
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool static is_valid_surname1(string str) {
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool static is_valid_surname2(string str) {
		regex comparison("[а-яА-я]{1,}");
		return regex_match(str, comparison);
	}
	bool static is_valid_address(string str) {
		regex comparison("[а-яА-я0-9,-/. ]{1,}");
		return regex_match(str, comparison);
	}
	bool static is_valid_id(int id) {
		return id > 0;
	}
	bool static is_valid_diagnosis(string str) {
		regex comparison("[а-яА-я0-9 ]{1,}");
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

enum file_type {
	in = 0,
	out = 1
};

class file_worker {
	private:
		enum file_type cl_type;
		ifstream in_file;
		ofstream out_file;
	public:
		file_worker(enum file_type type, string file_name) {
			cl_type = type;
			if (cl_type == in) {
				in_file.open(file_name, ios::in);
			}
			else {
				out_file.open(file_name, ios::out);
			}
		}
		// \r буду ставить как конец строки для getline - надо строку получать целиком
		string get_content() {
			if (cl_type == out) return "";
			string content;
			getline(in_file, content, '\r');
			in_file.close();
			return content;
		}
		bool set_content(string content) {
			if (cl_type == in) return false;
			out_file << content << '\r';
			out_file.close();
			return true;
		}
};

typedef bool (*validation_function)(string);

struct validation {
	string displayed_name;
	validation_function function;
};

struct patient_data enter_patient() {
	struct validation validations[5] = {
		{ "имя",patient::is_valid_name },
		{ "фамилия", patient::is_valid_surname1 },
		{ "отчество", patient::is_valid_surname2 },
		{ "адрес", patient::is_valid_address },
		{ "диагноз", patient::is_valid_diagnosis },
	};
	string recived[5];
	for (int i = 0; i < 5; i++) {
		bool ok = false;
		struct ret_srting tmp = {};
		do {
			print_message(format("\n{} {}: ", "Введите", validations[i].displayed_name));
			tmp = getter::getString();
			if (tmp.ok && validations[i].function(tmp.str)) {
				recived[i] = tmp.str;
				ok = true;
			}
			else {
				print_message(format("\n{}\n", "Введённое вами значение некоректно! Повторите ввод!"));
			}
		} while (!ok);
	}
	return { recived[0], recived[1], recived[2], recived[3], recived[4] };
}

// struct patient_data read_patient(){} // скопировать enter_patient,  но внести необходимые изменения

int main() {
	system("chcp 1251>nul");
	print_message(format("{}\n", "Никита Громов, 4303, 1 контрольная, 8 вариант контрольной, все задания"));
	
	/*print_message(format("\n{}\n{}\n{}\n{}", "Выберите способ ввода исходных данных:", "Клавиатура - 1", "Файл - 2", "Ваш выбор: "));
	switch (getter::getInt().num) {
	case in_keyboard:
		print_message(format("\n{}\n", "Выбран ввод с клавиатуры"));
		break;
	case in_file:
		print_message(format("\n{}\n", "Выбрано считывание файла"));
		break;
	default:
		print_message(format("\n{}\n", "Неккоректное значение! Выбран ввод с клавиатуры"));
		break;
	}*/
	auto a = enter_patient();
	print_message(format("{} {} {} {} {}", a.name, a.surname1, a.surname2, a.address, a.diagnosis));

	return EXIT_SUCCESS;
}