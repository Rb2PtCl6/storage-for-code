#include <iostream>
#include <format>
#include <string>
#include <optional>
#include <regex>
#include <fstream>
#include <filesystem>

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
	string name = "��� ������";
	string surname1 = "��� ������";
	string surname2 = "��� ������";
	string address = "��� ������";
	int id = 0;
	string diagnosis = "��� ������";
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
		print_message(format("���: {}\n������� : {}\n��������: {}\n������: {}\n����� �������� : {}\n������� ��������: {}\n",
			name, surname1, surname2, address, id, diagnosis));
	}
	bool is_valid_name(string str) { 
		regex comparison("[�-��-�]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_surname1(string str) {
		regex comparison("[�-��-�]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_surname2(string str) {
		regex comparison("[�-��-�]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_address(string str) {
		regex comparison("[�-��-�0-9,-/. ]{1,}");
		return regex_match(str, comparison);
	}
	bool is_valid_diagnosis(string str) {
		regex comparison("[�-��-�0-9]{1,}");
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
		// \r ���� ������� ��� ����� ������ ��� getline - ���� ������ �������� �������
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

int main() {
	system("chcp 1251>nul");
	print_message(format("{}\n", "������ ������, 4303, 1 �����������, 8 ������� �����������, ��� �������"));
	
	//bool leave_menu = false;
	//do {
		// �������� ������ ����� ������
		// ���������� - 1
		// ���� - 2
		// 
		// ������ ���� � ����������
		// ������� ���������� �����
		// 
		// ������� ���� ��� ����� ����� ������ ( ���������� ����� csv )
		// ������� ���� ��� ������ ������
		// 
		// ������ ������������ ����?
		// �� - 1
		// ��� - 2
		// 
		// ������ ���� �� �������� ��� ������
		// 
		// �������� ������ ������ ������
		// ������� - 1
		// ���� - 2
		// ��������������� - 3
		//
		// �������� ���������� ��������
		// ���� ������ - 1
		// ����� ������ - 2
		//
		/*print_message(format("\n{}\n{}\n{}\n{}\n", "������ �������� ���� ������������� � ������� �������?", "�� - 1", "��� - 2", "��� �����:"));
		switch (getter::getInt().num)
		{
		case yes:
			print_message(format("\n{}\n", "������ ����� �� ����"));
			leave_menu = true;
			break;
		case no:
			print_message(format("\n{}\n", "������� �������� � ����"));
			break;
		default:
			print_message(format("\n{}\n", "������� ����������� ��������! �� �������� � ����!"));
			break;
		}
	} while (!leave_menu);*/

	/*auto f1 = file_worker(out, "f1.csv");
	auto a1 = f1.set_content("id,str,num\n1,w,9.0\n2,u,5.0");

	print_message(format("{}\n", a1));*/

	auto b1 = filesystem::exists("f1.csv"); // con - ���������� ���������� - ���� ������ ������
	auto b2 = filesystem::exists("f2.csv");
	auto f1 = file_worker(in, "f1.csv");
	auto a1 = f1.get_content();
	auto f2 = file_worker(in, "f2.csv");
	auto a2 = f2.get_content();

	auto f3 = file_worker(out, "com");
	auto a3 = f3.get_content();

	print_message(format("{} - {}\n{} - {}\n{}\n", b1, a1, b2, a2, a3));
	print_message(format("{} {}", filesystem::exists("con10"), filesystem::exists("com")));

	return EXIT_SUCCESS;
}