﻿#include <iostream>
#include <format>
#include <string>
#include <optional>
#include <regex>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>

using namespace std;

void print_message(string str) {
	cout << str;
}

enum input_file {
	yes = 1,
	no = 2
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
	int id;
	string name;
	string surname1;
	string surname2;
	string address;
	string diagnosis;
};

int max_id = 1;

// https://regex101.com/

map<string, string> regexes = {
	{"номер пациента","[0-9]{1,}"},
	{"имя","[а-яА-я]{1,}"},
	{"фамилия","[а-яА-я]{1,}"},
	{"отчество","[а-яА-я]{1,}"},
	{"адрес","[а-яА-я0-9,-/. ]{1,}"},
	{"диагноз","[а-яА-я0-9 ]{1,}"}
};

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
		name = data.name;
		surname1 = data.surname1;
		surname2 = data.surname2;
		address = data.address;
		id = max_id;
		max_id++;
		diagnosis = data.diagnosis;
	}
	struct patient_data_full get() {
		return { id, name, surname1, surname2, address,  diagnosis };
	}
	struct patient_data_full get_by_id(int min, int max) {
		if (max < min) {
			return {};
		}
		else if ((max == min && max == id) || (id >= min && id <= max)) {
			return get();
		}
		return {};
	}
	struct patient_data_full get_by_diadnosis(string sort_diagnosis) {
		if (!patient::is_valid_field(sort_diagnosis, regexes["диагноз"])) {
			return {};
		}
		if (sort_diagnosis == diagnosis) return get();
		return {};
	}
	string static form_message(struct patient_data_full data) {
		return format("Номер пациента : {}\nИмя: {}\nФамилия : {}\nОтчество: {}\nАдресс: {}\nДиагноз пациента: {}\n",
			data.id, data.name, data.surname1, data.surname2, data.address,  data.diagnosis);
	}
	string static form_csv_header() {
		return "id\tname\tsurname1\tsurname2\taddress\tdiagnosis";
	}
	bool static is_valid_csv_header(string str) {
		return str == "id\tname\tsurname1\tsurname2\taddress\tdiagnosis";
	}
	string static form_csv_string(struct patient_data_full data) {
		return format("\n{}\t{}\t{}\t{}\t{}\t{}",
			data.id, data.name, data.surname1, data.surname2, data.address,  data.diagnosis);
	}
	bool static is_valid_field(string str, string mask) {
		regex comparison(mask);
		return regex_match(str, comparison);
	}
	bool static is_filled_patient_data_full(struct patient_data_full data) {
		return (data.name != "");
	}
	bool static is_filled_patient_data(struct patient_data data) {
		return (data.name != "");
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

// https://en.cppreference.com/w/cpp/filesystem/is_regular_file

class file_worker { // запись файла работает точно
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

// мб разделитель строк вызывает ошибку
// https://favtutor.com/blogs/split-string-cpp

vector<string> split_string(string str, char delimiter) {
	vector<string> tmp;
	print_message(str);
	if (str == "") return tmp;
	string tmp2;
	for (int i = 0; i < str.size(); i++) {
		if (i == str.size() - 1) {
			if (str[i] != delimiter) {
				tmp2 += str[i];
			}
		tmp.push_back(tmp2);
		tmp2 = "";
		}
		else if (str[i] != delimiter) {
			tmp2 += str[i];
		}
		else {
			tmp.push_back(tmp2);
			tmp2 = "";
		}
	}
	return tmp;
}

struct patient_data enter_patient() {
	string validations[5] = { "имя", "фамилия", "отчество", "адрес", "диагноз" };
	string recived[5];
	for (int i = 0; i < 5; i++) {
		bool ok = false;
		struct ret_srting tmp = {};
		do {
			print_message(format("\n{} {}: ", "Введите", validations[i]));
			tmp = getter::getString();
			if (tmp.ok && patient::is_valid_field(tmp.str,regexes[validations[i]])) {
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

struct patient_data read_patient(string str){
	string validations[6] = { "номер пациента", "имя", "фамилия", "отчество", "адрес", "диагноз" };
	auto splitted_string = split_string(str,'\t');
	if (splitted_string.size() != 6) return {};
	string recived[6];
	for (int i = 0; i < 6; i++) {
		if (patient::is_valid_field(splitted_string[i], regexes[validations[i]])) {
			recived[i] = splitted_string[i];
		}
		else {
			return {};
		}
	}
	return { recived[1], recived[2], recived[3], recived[4], recived[5] };
}

vector<patient_data> read_csv(string str) {
	auto splitted_csv = split_string(str, '\n'); // где-то тут падает
	vector<patient_data> to_return;
	if (patient::is_valid_csv_header(splitted_csv[0])) return to_return;
	struct patient_data tmp;
	for (int i = 1; i < splitted_csv.size(); i++) {
		tmp = read_patient(splitted_csv[i]);
		if (patient::is_filled_patient_data(tmp)) to_return.push_back(tmp);
	}
	return to_return;
}

string writible_content_for_csv(vector<patient_data_full> data) {
	string to_return = patient::form_csv_header();
	if (data.empty()) return to_return;
	for (int i = 0; i < data.size(); i++) {
		to_return += patient::form_csv_string(data[i]);
	}
	return to_return;
}

string writible_content_for_console(vector<patient_data_full> data) {
	if (data.empty()) return "Нечего выводить!";
	string to_return;
	for (int i = 0; i < data.size(); i++) {
		to_return += patient::form_message(data[i]);
	}
	return to_return;
}

enum write_to_file {
	wrire_yes = 1,
	write_no = 2
};

enum replace_content {
	replace_yes = 1,
	replace_no = 2
};

vector<patient_data> file_reader() {
	print_message(format("\n{}: ", "Введите имя файла"));
	auto filename = getter::getString().str;
	print_message(format("\n{}: ", "1"));
	auto content_from = file_worker(out, filename);
	print_message(format("\n{}: ", "2"));
	auto content = content_from.get_content();
	print_message(content);
	print_message(format("\n{}: ", "3"));
	return read_csv(content);
}
void file_writer(string content) {
	print_message(content);
	print_message(format("\n{}\n{}\n{}\n{}", "Хотите вывести данные в файла?", "Да - 1", "Нет - 2", "Ваш выбор: "));
	switch (getter::getInt().num) {
	case wrire_yes:
		print_message(format("\n{}\n", "Выбран вывод в файла."));
		break;
	case write_no:
		print_message(format("\n{}\n", "Шаг с выбором файла для вывода пропущен."));
		return;
	default:
		print_message(format("\n{}\n", "Неккоректное значение! Шаг с выбором файла для вывода пропущен."));
		return;
	}
	print_message(format("\n{}: ", "Введите имя файла"));
	auto filename = getter::getString().str;
	print_message(format("\n{}: ", "true/false"));
	if (getter::getInt().num) {
		print_message(format("\n{}\n{}\n{}\n{}", "Хотите перезаписать файл?", "Да - 1", "Нет - 2", "Ваш выбор: "));
		switch (getter::getInt().num) {
		case replace_yes:
			print_message(format("\n{}\n", "Выбрана перезапись файла."));
			break;
		case replace_no:
			print_message(format("\n{}\n", "Перезапись файла пропущена."));
			return;
		default:
			print_message(format("\n{}\n", "Неккоректное значение! Шаг с перезаписью файла пропущен."));
			return;
		}
	}
	else {
		print_message(format("\n\n{}\n\n", "Просто пишем в  файл, перезаписывать не надо"));
		auto target = file_worker(out, filename);
		target.set_content(content);
	}
}

enum menu {
	error = 0,
	enter = 1,
	no_sort = 2,
	id_sort = 3,
	diadnosis_sort = 4,
	my_exit = 5
};

void no_sort_launch(vector<patient> patients) {
	vector<patient_data_full> tmp_vector;
	for (int i = 0; i < patients.size(); i++) {
		tmp_vector.push_back(patients[i].get());
	}
	print_message(writible_content_for_console(tmp_vector));
	//auto a = file_worker(out, "f2.csv");
	//a.set_content(writible_content_for_csv(tmp_vector));
	file_writer(writible_content_for_csv(tmp_vector));
};
void id_sort_launch(vector<patient> patients) {
	print_message(format("\n\n{}", "Введите нижную границу: "));
	int min = getter::getInt().num;
	print_message(format("\n\n{}", "Введите верхную границу: "));
	int max = getter::getInt().num;
	struct patient_data_full tmp_data = {};
	vector<patient_data_full> tmp_vector;
	for (int i = 0; i < patients.size(); i++) {
		tmp_data = patients[i].get_by_id(min, max);
		if (patient::is_filled_patient_data_full(tmp_data)) tmp_vector.push_back(tmp_data);
	}
	print_message(writible_content_for_console(tmp_vector));
	file_writer(writible_content_for_csv(tmp_vector));
};
void diagnosis_sort_launch(vector<patient> patients) {
	print_message(format("\n\n{}", "Введите диагноз для сортировки: "));
	string sort_diagnosis = getter::getString().str;
	struct patient_data_full tmp_data = {};
	vector<patient_data_full> tmp_vector;
	for (int i = 0; i < patients.size(); i++) {
		tmp_data = patients[i].get_by_diadnosis(sort_diagnosis);
		if (patient::is_filled_patient_data_full(tmp_data)) tmp_vector.push_back(tmp_data);
	}
	print_message(writible_content_for_console(tmp_vector));
	file_writer(writible_content_for_csv(tmp_vector));
};

void launcher() {
	print_message(format("\n{}\n{}\n{}\n{}", "Хотите ввести данные из файла?", "Да - 1", "Нет - 2", "Ваш выбор: "));
	vector<patient> patients;
	vector<patient_data> tmp;
	switch (getter::getInt().num) {
	case yes:
		print_message(format("\n{}\n", "Выбрано считывание файла."));
		tmp = file_reader();
		for (int i = 0; i < tmp.size(); i++) {
			patients.push_back(patient(tmp[i]));
		}
		break;
	case no:
		print_message(format("\n{}\n", "Шаг с выбором файла для считывания пропущен."));
		break;
	default:
		print_message(format("\n{}\n", "Неккоректное значение! Шаг с выбором файла для считывания пропущен."));
		break;
	}
	enum menu action = enter;
	do {
		print_message(format("\n{}\n{}\n{}\n{}\n{}\n{}\n{}", "Что хотите сделать далее?",
			"Добавление пациента - 1", 
			"Вывод всех пациентов без сортировки - 2", 
			"Вывод пациентов с их сортировкой по номеру - 3", 
			"Вывод пациентов с их сортировкой по диагнозу - 4", 
			"Выход из программы - 5", 
			"Ваш выбор: "));
		switch (getter::getInt().num) {
		case enter:
			print_message(format("\n{}\n", "Выбрано добавление пациента."));
			action = enter;
			patients.push_back(patient(enter_patient()));
			break;
		case no_sort:
			print_message(format("\n{}\n\n", "Выбран вывод всех пациентов."));
			action = no_sort;
			no_sort_launch(patients);
			break;
		case id_sort:
			print_message(format("\n{}\n\n", "Выбрана сортировка по номеру пациента."));
			action = id_sort;
			id_sort_launch(patients);
			break;
		case diadnosis_sort:
			print_message(format("\n{}\n\n", "Выбрана сортировка по диагнозу."));
			action = diadnosis_sort;
			diagnosis_sort_launch(patients);
			break;
		case my_exit:
			print_message(format("\n{}\n\n", "Выбран выход из программы."));
			action = my_exit;
			break;
		default:
			print_message(format("\n{}\n\n", "Неккоректное значение! Шаг с выбором файла для считывания пропущен."));
			action = error;
			continue;
		}
		//print_message(format("{}\n", "Что-то делаем"));
	} while (action != my_exit);
}

int main() {
	system("chcp 1251>nul");
	print_message(format("{}\n", "Никита Громов, 4303, 1 контрольная, 8 вариант контрольной, все задания"));
	
	launcher();
	
	return EXIT_SUCCESS;
}