#include <iostream>
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
	void static show(struct patient_data_full data) {
		print_message(form_message(data));
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

class file_worker {
	private:
		enum file_type cl_type;
		string file_name;
		bool ok = false;
		ifstream in_file;
		ofstream out_file;
		void open() {
			if (cl_type == in) {
				try {
					in_file.open(file_name, ios::in);
				}
				catch (...) {
					ok = false;
				}
				
			}
			else {
				try {
					out_file.open(file_name, ios::out);
				}
				catch (...) {
					ok = false;
				}
				
			}
		}
	public:
		file_worker(enum file_type type, string ext_file_name) {
			file_name = ext_file_name;
			cl_type = type;
			if (filesystem::is_regular_file(file_name)) {
				ok = true;
				open();
			}
		}
		bool get_state() { return ok; }
		// \r буду ставить как конец строки для getline - надо строку получать целиком
		string get_content() {
			if (cl_type == out || !ok) return "";
			string content;
			getline(in_file, content, '\r');
			in_file.close();
			return content;
		}
		bool set_content(string content) {
			if (cl_type == in || !ok) return false;
			out_file << content << '\r';
			out_file.close();
			return true;
		}
};

vector<string> split_string(string str, char delimiter) {
	vector<string> tmp;
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
	auto splitted_csv = split_string(str, '\n');
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
	if (data.empty()) return "";
	string to_return = patient::form_csv_header();
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
	print_message(format("{}", patient::form_csv_string({ 12,"й","ц","у","к","н"})));
	return EXIT_SUCCESS;
}