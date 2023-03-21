#pragma once
#include <iostream> 
#include"Menu.h"
#include<list>
#include"BTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <regex>

using namespace std;

class exam_file 
{
public:
	bool exam_base(string base, string str) const;
	bool exam_category(string category, string str) const;
	bool exam_admin() const;
};

string encryptDecrypt(string toEncrypt) {
	char key[3] = { 'K', 'C', 'Q' };
	string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}

void encryptPass(string& pass)
{
	int ch;
	ch = _getch();

	while (ch != 13) {
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
}

bool exam_file::exam_base(string base, string str) const
{
	ifstream f(base);
	string buff_str;
	if (f.is_open())
	{
		while (getline(f, buff_str))
		{
			if (buff_str == str)
			{
				f.close();
				return true;
			}
		}
	}
	f.close();
	return false;
}

bool exam_file::exam_category(string category, string str) const
{
	size_t s = category.size();
	str.resize(s);
	if (category == str) { return true; }
	else { return false; }
}

bool exam_file::exam_admin() const
{
	string str;
	ifstream f("base_users.txt");
	if (f.is_open())
	{
		while (getline(f, str))
		{
			str.resize(6);
			if ("Admin_" == str)	{	return true;	}
		}
	}
	return false;
}

class test 
{
	exam_file exam;
public:

	void add(string name_test, string name_file_answer);
	void go_test(string name_test, string my_answer) const;
	void result(string name, string name_faile_answer, string my_answer) const;
	string get_name_answer(string name_test) const;
	void files(string name_file) const;
	void file_category_tests(string categort) const;
	
};

void test::add(string name_test, string name_file_answer)
{
	system("cls");
	ofstream out_test(name_test + ".txt", ios::app);
	ofstream out_answer(name_file_answer + ".txt", ios::app);
	ofstream out_base("base_tests.txt", ios::app);
	if (out_test.is_open() && out_answer.is_open() && out_base.is_open())
	{
		char a;
		do {
			string st;
			cout << "Задание\n"; getline(cin, st); out_test << st << "\n";
			cout << "Варианты ответов \n"; getline(cin, st); out_test << st << "\n";
			cout << "Правильный ответ \n"; getline(cin, st); out_answer << st << "\n";
			cout << "дабвить еще?(0 - нет, 1 - да)\n"; cin >> a; cin.ignore();
			if (a == '0')
			{
				if (exam.exam_base("base_test.txt", name_test) == false)
				{ 
					out_base << name_test << "\n"; 
					cout << "Тест успешно добавлен\n";
					system("pause");
				}
				out_test.close(); out_answer.close(); out_base.close();
				return;
			}
			else if (a != '1')
			{
				out_test.close(); out_answer.close(); out_base.close();
				cout << "Был выбран некоректный вариент,файл закрыт на последнем вопроссе\n";
				system("pause");
				a = false;
				return;
			}
			system("cls");
		} while (true);
	}
	else
	{
		cout << "Оштбка при открытии файлов для записа\n";
		system("pause");
	}
	
}


void test::go_test(string name_test, string my_answer) const
{
	ifstream f(name_test);
	ofstream out(my_answer);
	string str, otv;
	int count = 1;
	if (f.is_open() && out.is_open())
	{
		while (getline(f, str))
		{
			system("cls");
			cout << "Тест\n";
			cout << "Задание номер " << count << "\n";
			cout << str << "\nВарианты ответов";
			getline(f, str);
			cout << str << "\n";
			cout << "Ответ - "; cin >> otv;
			count++;
			out << otv << "\n";
		}
		f.close(); out.close();
	}
	else 
	{ 
		cout << "Ошибка открытия файла(\n"; system("pause"); 
		f.close(); out.close();
		return; 
	}
}

void test::result(string name, string name_file_answer, string my_answer) const
{
	int p = 0, n = 0;
	string str, otv;
	ifstream f1(name_file_answer);
	ifstream f2(my_answer);
	ofstream out(name + "_result.txt", ios::app);
	if (f1.is_open() && f2.is_open() && out.is_open())
	{
		while (getline(f1, str) && getline(f2, otv))
		{
			if (str == otv) { p++; }
			else { n++; }
		}
		f1.close(); f2.close();
		cout << p << " - правильных\n";
		cout << n << " - неправильных\n";
		system("pause");
		out << "По этому тесту у вас " << p << " из " << p + n << "\n";
		f1.close(); out.close(); f2.close();
		return;
	}
	else { 
		cout << "Ошибка открытия файла("; 
		system("pause"); 
		f1.close(); out.close(); f2.close();
		return; 
	}
}

string test::get_name_answer(string name_test) const
{	return name_test + "_answer";	}

void test::files(string file_name) const
{
	ifstream f(file_name);
	string st;
	if (f.is_open())
	{
		while (getline(f, st)) 
		{	cout << " - " << st << "\n"; }
	}
	f.close();
}

void test::file_category_tests(string category) const
{
	string buff_str;
	ifstream f("base_tests.txt");
	if (f.is_open()) {
		while (getline(f, buff_str))
		{
			if (exam.exam_category(category, buff_str) == true)
			{
				buff_str = regex_replace(buff_str, regex(category + "_"), "");
				cout << " - " << buff_str << "\n";
			}
		}
	}
}

class User
{
	string name;
	string password;

protected:
	string base_tests = "base_tests.txt";
	string base_users = "base_users.txt";
	string base_category = "base_category.txt";
	string temp = "temp.txt";
public:
	User();
	User(string name, string pass);
	virtual void menu() = 0;
	virtual ~User();
	string getName() const;
	string getPassword() const;
	void setName(string name);
	void setPassword(string pass);
};	

User::User(): name("no name"), password("no pass") {};
User::User(string name, string pass) : name(name) { setPassword(pass); };
User::~User(){}
void   User::setName(string name)		{	this->name = name;	}
string User::getName() const			{	return name;		}
void   User::setPassword(string pass)	{	password = pass;	}
string User::getPassword() const		{	return password;	}


class Student : public User
{
	exam_file* exam = nullptr;
	test* test = nullptr;
	string number;
	string address;
	string FIO;
public:
	Student();
	Student(string name, string pass);
	Student(string name, string pass, string number, string address, string FIO);
	virtual ~Student();
	virtual void menu() override;
	void setNumber(string number);
	void setAddress(string address);
	void setFIO(string fio);
	string getNumber() const;
	string getAddress()  const;
	string get_FIO() const;
	void add(string category, string test);
	void info();
	void profil();
	void viewing_previons_tests() const;//посмотреть предыдущие тесты и их результаты
	void take_a_test();//пройти тест
	void contine_test() const;//продолжить тест
};

Student::Student() : User(), number("no number"), address("no address"), FIO("no FIO") {};

Student::Student(string name, string pass) : User(name, pass) { info(); }

Student::Student(string name, string pass, string number, string address, string FIO)
	: User(name, pass), number(number), address(address), FIO(FIO) 
{
	//сохранение информации о пользователе в файл с его логином
	ofstream out(name + "_inform_on_user.txt");
	if (out.is_open())
	{
		out << name << "\n";
		out << FIO << "\n";
		out << number << "\n";
		out << address << "\n";
	}
};

void Student::info()
{
	string st;
	ifstream f(this->getName() + "_inform_on_user.txt");
	if (f.is_open())
	{
		getline(f, st);
		setName(st);
		getline(f, st);
		setFIO(st);
		getline(f, st);
		setNumber(st);
		getline(f, st);
		setAddress(st);
	}
}

void Student::profil()
{
	cout << "Name - " << this->getName();
	cout << "\nFIO - " << this->get_FIO();
	cout << "\nNumber - " << this->getNumber();
	cout << "\nAddress - " << this->getAddress();
	cout << "\nPassword - " << this->getPassword();
	cout << "\n";
	system("pause");
}

Student::~Student() {}

void	Student::setNumber(string number)	{ this->number = number; }
void	Student::setAddress(string address) { this->address = address; }
void	Student::setFIO(string fio)			{ FIO = fio; }
string  Student::getNumber() const			{ return number; }
string  Student::getAddress()  const		{ return address; }
string  Student::get_FIO() const			{ return FIO; }

void Student::menu()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tПрофiль студента : " << get_FIO();
		int choice = Menu::select_vertical(
			{ "Перегляд попереднiх результатiв",
			  "Пройти тест",
			  "Продовжити тест",
			  "Переглянути профіль",
			  "Вийти"							},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: viewing_previons_tests();			break;
		case 1: take_a_test();					    break;
		case 2: /*contine_test();*/					break;
		case 3: profil();							break;
		case 4: return;
		}
	} while (true);
}

void Student::viewing_previons_tests() const
{
	ifstream f(this->getName() + "_result.txt");
	string st;
	if (f.is_open())
	{
		while (getline(f, st)){	cout << st << "\n";	}
	}
	else{	cout << "По вашим прохождениям нет данных\n";	}
	f.close();
	system("pause");
}

void Student::take_a_test()
{
	cout << "~ Существующие категории\n";
	test->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	if (exam->exam_base(base_category, name_category) == true)
	{
		system("cls");
		cout << "~ Существующие тесты \n";
		ifstream f(base_tests);
		if (f.is_open()) {
			while (getline(f, buff_str))
			{
				if (exam->exam_category(name_category, buff_str) == true)
				{
					buff_str = regex_replace(buff_str, regex(name_category + "_"), "");
					cout << " - " << buff_str << "\n";
				}
			}
		}
		cout << "Введите название теста\n";
		getline(cin, name_test);
		name_test = name_category + "_" + name_test;
		if (exam->exam_base(base_tests, name_test) == true)
		{
			string answer = this->getName() + "_" + test->get_name_answer(name_test) + ".txt";
			add(name_category, regex_replace(name_test, regex(name_category + "_"), ""));
			test->go_test(name_test + ".txt", answer);
			test->result(this->getName(),test->get_name_answer(name_test ) + ".txt", answer);
			
		}
	}
}

void Student::add(string category, string test)
{
	ofstream out(this->getName() + "_result.txt", ios::app);
	if (out.is_open())
	{
		out << "Категория : " << category << " тест - " << test << "\n";
	}
}

class Admin : public User
{
	BTree<string, list<User*>> user;
	string FIO;
	exam_file exam;
	test* test = nullptr;
public:
	Admin();
	Admin(string name, string pass);
	Admin(string name, string pass, string FIO);

	virtual void menu() override;

	string get_FIO();
	void setFIO(string name);

	void menegment_user();// управління користувачами
	void add_user();//додати користувача
	void delete_user();// відалити користувача
	void user_modification();// изменить параметрі пользователя

	void statistic() const;//статистика
	void statistic_categories()const;//по ктегории
	void statistic_test()const;// по тесту
	void statistic_user()const;//по пользователю
	void statistic_output_fille()const;//загрузить статистику в файл

	void menegment_tests();// управление тестами
	void add();
	void del();
	void add_test();// добавить тест
	void delete_test();
	void add_category();//  категорию
	void delete_category();
	void add_questions();//добавить вопросс
	void delete_questions();
	void inport_txt()const;// импортировать из файла
	void export_txt()const;// експортировать в файл
};

Admin::Admin() :User() {};

Admin::Admin(string name, string pass) : User(name, pass) 
{
	string st;
	ifstream f(this->getName() + "_inform_on_admin.txt");
	if (f.is_open())
	{
		getline(f, st);
		setName(st);
		getline(f, st);
		setFIO(st);
	}
};

Admin::Admin(string name, string pass, string FIO)
{
	ofstream out(name + "_inform_on_admin.txt");
	if (out.is_open())
	{
		out << name << "\n";
		out << FIO << "\n";
		out << pass << "\n";
	}
}

void Admin::setFIO(string name) { FIO = name; }
string Admin::get_FIO() { return FIO; }

void Admin::menu()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tПрофiль адміна : " << get_FIO();
		int choice = Menu::select_vertical(
			{ "Управлiння користувачами",
			  "Перегляд статистики",
			  "Управління тестуваннями",
			  "Вийти"					},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: menegment_user();		break;
		case 1: //statistic();			break;
		case 2: menegment_tests();		break;
		case 3: return;
		}
	} while (true);
}

void Admin::menegment_user()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tУправління користувачами ";
		int choice = Menu::select_vertical(
			{ "Додати користувача",
			  "Видалити користувача",
			  "Змінити інформацію користувача",
			  "Вийти"							},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: add_user();				break;
		case 1: /*delete_user();*/			break;
		case 2: /*user_modification();*/	break;
		case 3: return;
		}
	} while (true);
}

void Admin::add_user()
{
	string new_name, new_pass;
	ofstream out(base_users, ios::app);
	if (out.is_open())
	{
		cout << "Name :"; getline(cin, new_name);
		list<User*> new_list;
		if (exam.exam_base(base_users, new_name) == false)
		{
			cout << "Password :"; getline(cin, new_pass);
			if (exam.exam_admin() == true)
			{
				out << new_name << "\n";
				out << new_pass << "\n";
				string new_FIO, new_number, new_address;
				cout << "FIO :"; getline(cin, new_FIO);
				cout << "Mobile number :"; getline(cin, new_number);
				cout << "Home address :"; getline(cin, new_address);
				User* student = new Student(new_name, new_pass, new_address, new_number, new_FIO);
				new_list.push_back(student);
				user.push_r(student->getName(), new_list);
			}
		}
		else
		{
			cout << "такое имя уже есть";
			system("pause");
			return;
		}
	}
	else { cout << "eror"; system("pause"); return; }
}

void statistic() {
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tСтатистика ";
		int choice = Menu::select_vertical(
			{ "За категоріями",
			  "За тестом",
			  "За студентом",
			  "Вийти"			},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: /*statistic_categories();*/		break;
		case 1: /*statistic_test;*/			break;
		case 2: /*statistic_user();*/		break;
		case 3: return;
		}
	} while (true);
}

void Admin::menegment_tests()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tУпрпвління тестами ";
		int choice = Menu::select_vertical(
			{ "Додати",
			 "Видалити",
			  "Вийти"				},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: add(); break;
		case 1: del(); break;
		case 2: return;
		}
	} while (true);
}

void Admin::add()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tДодавання ";
		int choice = Menu::select_vertical(
			{ "Додати категорію ",
			"Додати тест ",  
			 "Додати запитання ",
			  "Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: add_category();		break;
		case 1: add_test();			break;
		case 2: add_questions();	break;
		case 3: return;
		}
	} while (true);
}

void Admin::del()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tВидалення ";
		int choice = Menu::select_vertical(
			{ "Видалити категорію",
			  "Видалити тест ",
			 "Видалити запитання",
			  "Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: delete_category();		break;
		case 1: delete_test();				break;
		case 2: //delete_questions();		break;
		case 3: return;
		}
	} while (true);
}

void Admin::add_test()
{
	cout << "~ Существующие категории\n";
	test->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == 1)
	{
		system("cls");
		cout << "~ Существующие тесты \n";
		ifstream f(base_tests);
		if (f.is_open()) {
			while (getline(f, buff_str))
			{
				if (exam.exam_category(name_category, buff_str) == true)
				{
					buff_str = regex_replace(buff_str, regex(name_category + "_"), "");
					cout << " - " << buff_str << "\n";
				}
			}
		}
		cout << "Введите название теста\n";
		getline(cin, name_test);
		name_test = name_category + "_" + name_test;
		if (exam.exam_base(base_tests, name_test) == 0)
		{	test->add(name_test, test->get_name_answer(name_test));	}
		else
		{
			cout << "Тест с таким именем уже существует. Хотите добавить вопрос?1 - да , 0 - нет\n";
			bool a; cin >> a; cin.ignore();
			if (a == true)
			{	add_questions();	}
			else return;
		}
	}
	else
	{
		cout << "Твкой категории нет. Создать новую? ?1 - да , 0 - нет\n";
		bool a; cin >> a; cin.ignore();
		if (a == true)
		{	add_category();}
		else return;
	}
}

void Admin::delete_test()
{
	cout << "~ Существующие категории\n";
	test->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == 1)
	{
		cout << "~ Существующие тесты \n";
		test->file_category_tests(name_category);
		cout << "Введите название теста\n";
		getline(cin, name_test);
		name_test = name_category + "_" + name_test;
		ifstream f(base_tests);
		ofstream out(temp);
		if (f.is_open() && out.is_open())
		{
			while (getline(f, buff_str))
			{
				if (name_test != buff_str)
				{	out << buff_str << "\n";	}
				else
				{
					name_test += ".txt";
					remove(name_test.c_str());
					name_test = regex_replace(name_test, regex(".txt"), "");
					name_test += "_answer.txt";
					remove(name_test.c_str());
					cout << "Тест был удалён\n";
					system("pause");
				}
			}
			f.close(); out.close();
			ifstream ft(temp);
			ofstream out2(base_tests);
			if (ft.is_open() && out2.is_open())
			{
				while (getline(ft, buff_str))
				{	out2 << buff_str << "\n";	}
			}
			remove(temp.c_str());

			ft.close(); out2.close();
		}
		else 
		{ 
			cout << "eror file\n"; 
			system("pause"); 
		}
		
	}
}

void Admin::add_category()
{
	cout << "~ Уже имеющиеся категории ~\n";
	test->files(base_category);//тут выводим все имеющиеся категории
	cout << "Введите название категории что ходите добавить\n";
	string name_category, buff_str;
	getline(cin, name_category);
	ifstream f(base_category);//открываем поток для проверки
	if (f.is_open())
	{	
		if (exam.exam_base(base_category, name_category) == 1)
		{
			f.close();
			cout << "Такая категория уже существует\n";
			system("pause");
			return;
		}
		f.close();
		ofstream out(base_category, ios::app);
		if (out.is_open())
		{
			out << name_category << "\n";
		}//записываем если нет совпадений
		else
		{
			cout << "Ошибка открытия файла для чтения\n";
			system("pause");
		}
		out.close();
	}
	else
	{
		cout << "Ошибка открытия файла для записи\n";
		system("pause");
	}
}

void Admin::delete_category()
{
	cout << "~ Существующие категории\n";
	test->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == true)
	{
		ifstream f_test(base_tests);
		string st;
		ofstream out_temp_test(temp);
		while (getline(f_test, st))
		{
			if (exam.exam_category(name_category, st) == true)
			{
				//нашли тест
				st += ".txt";
				remove(st.c_str());
				st = regex_replace(st, regex(".txt"), "_answer.txt");
				remove(st.c_str());
				cout << st << "  - удалён" << "\n";
				system("pause");
			}
			else
			{
				cout << " записали в файд" << "\n";
				system("pause");
				out_temp_test << st << "\n";
			}
		}
		f_test.close(); out_temp_test.close();
		ifstream f_temp(temp);
		ofstream out_tests(base_tests);
		if (f_temp.is_open() && out_tests.is_open())
		{
			while (getline(f_temp, st))
			{
				cout << " загрузили новый список" << "\n";
				system("pause");
				out_tests << st << "\n";
			}
		}
		f_temp.close(); out_tests.close();
		ifstream f_category(base_category);
		ofstream out_temp_category(temp);
		while (getline(f_category, st))
		{
			if (name_category != st)
			{
				cout << " категории не совпадают записываем" << "\n";
				system("pause");
				out_temp_category << st << "\n";
			}
		}
		f_category.close(); out_temp_category.close();
		ifstream f_temp_category(temp);
		ofstream out_category(base_category);
		if (f_temp_category.is_open() && out_category.is_open())
		{
			while (getline(f_temp_category, st))
			{
				cout << " выгружаем в фвйл" << "\n";
				system("pause");
				out_category << st << "\n";
			}
		}
		f_temp_category.close(); out_category.close();
	}
}

void Admin::add_questions()
{
	test->files("name_questions");
	cout << "Введите название теста\n";
	string name_test, str;
	getline(cin, name_test);
	ifstream f("name_tests.txt");
	if (f.is_open())
	{
		while (getline(f, str))
		{
			if (name_test == str)
			{
				f.close();
				test->add(name_test, test->get_name_answer(name_test));
			}
		}
	}
	f.close();	
}


class Testing_system
{
	exam_file exam;
	BTree<string, list<User*>> user;
	string file_user = "base_users.txt";
	void login();
	void Registration();
public:
	Testing_system();
	~Testing_system();
	virtual void menu();
};

Testing_system::Testing_system() {}
Testing_system::~Testing_system() { }

void Testing_system::menu()
{
	do {
		system("cls");
		int choice = Menu::select_vertical(
			{ "Увiйти",
			"Зареєструватися",
			"Настройки",
			"Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: login();		break;
		case 1: Registration(); break;
		case 2: settingConsole(); break;
		case 3: return;
		}
	} while (true);
}

void Testing_system::Registration()
{
	string new_name, new_pass;
	ofstream out(file_user, ios::app);
	if (out.is_open())
	{
		cout << "Login :"; getline(cin, new_name);
		list<User*> new_list;
		if (exam.exam_base(file_user, new_name) == false)
		{
			cout << "Password :"; encryptPass(new_pass);
			new_pass = encryptDecrypt(new_pass);
			if (exam.exam_admin() == true)
			{
				out << new_name << "\n";
				out << new_pass << "\n";
				string new_FIO, new_number, new_address;
				cout << "\nFIO :"; getline(cin, new_FIO);
				cout << "Mobile number :"; getline(cin, new_number);
				cout << "Home address :"; getline(cin, new_address);
				User* student = new Student(new_name, new_pass, new_address, new_number, new_FIO);
				new_list.push_back(student);
				user.push_r(student->getName(), new_list);
				student->menu();
			}
			else
			{
				out << "Admin_" + new_name << "\n";
				out << new_pass << "\n";
				string new_FIO;
				cout << "FIO :"; getline(cin, new_FIO);
				User* admin = new Admin(new_name, new_pass, new_FIO);
				new_list.push_back(admin);
				user.push_r(admin->getName(), new_list);
				admin->menu();
			}
		}
		else
		{
			cout << "такое имя уже есть";
			system("pause");
			return;
		}
	}
	else { cout << "eror"; system("pause"); return; }
}



void Testing_system::login()
{
	string this_name, file_name, pass, file_pass;
	ifstream f(file_user);
	cout << "Login - ";
	getline(cin, this_name);
	if (f.is_open()) 
	{
		while (getline(f, file_name))
		{
			if ("Admin_" + this_name == file_name)
			{
				cout << "Password - ";
				encryptPass(pass);
				pass = encryptDecrypt(pass);
				getline(f, file_pass);
				if (pass == file_pass)
				{
					User* user = new Admin(this_name, pass);
					user->menu();
					return;
					system("pause");
				}
				else 
				{
					cout << "Неверный пароль";
					system("pause");
					return;
				}
			}
			else if (this_name == file_name)
			{
				cout << "Password - ";
				encryptPass(pass);
				pass = encryptDecrypt(pass);
				getline(f, file_pass);
				if (pass == file_pass)
				{
					User* user = new Student(this_name, pass);
					user->menu();
					return;
					system("pause");
				}
				else
				{
					cout << "Неверный пароль";
					system("pause");
					return;
				}
			}
		}	
		cout << "Неверное имя пользователя";
		system("pause");
	}
}