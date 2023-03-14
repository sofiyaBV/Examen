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

class test 
{
public:

	void add(string name_test, string name_file_answer);
	void go_test(string name_test, string my_answer);
	void result(string name_user, string name_faile_answer, string my_answer);
	string get_name_answer(string name_test);
	void files(string name_file);
	void file_category_tests(string categort);
	bool exam_base(string base, string str);
	bool exam_category(string category, string str);
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
				if (exam_base("base_test.txt", name_test) == false)
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

bool test::exam_base(string base, string str)
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

bool test::exam_category(string category, string str)
{
	size_t s = category.size();
	str.resize(s);
	if (category == str) { return true; }
	else { return false; }
}

void test::go_test(string name_test, string my_answer)
{
	ifstream f(name_test);
	ofstream out(my_answer);
	string str, otv;
	int count = 1;
	/*if (f.is_open() && out.is_open())
	{
		while (getline(f, str))
		{
			system("cls");
			cout << "Тест\n";
			cout << "Задание номер " << count << "\n";
			cout << str << "\n";
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
	}*/
}

void test::result(string name_user, string name_file_answer, string my_answer)
{
	int p = 0, n = 0;
	string str, otv;
	ifstream f1(name_file_answer);
	ifstream f2(my_answer);
	ofstream out(name_user + "col_otv_" + my_answer ,ios::app);
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

string test::get_name_answer(string name_test)
{	return name_test + "_answer";	}

void test::files(string file_name)
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

void test::file_category_tests(string category)
{
	string buff_str;
	ifstream f("base_tests.txt");
	if (f.is_open()) {
		while (getline(f, buff_str))
		{
			if (exam_category(category, buff_str) == true)
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

public:
	User();
	User(string name, string pass);
	virtual void menu() = 0;
	virtual ~User();
	string getName() const;
	string getPassword() const;
	void setName(string name);
	void setPassword(string pass);

	void go(User* u);

	friend ostream& operator<<(ostream& out, const User* p);
	friend istream& operator>>(istream& in, User* p);
	
};	

User::User(): name("no name"), password("no pass") {};
User::User(string name, string pass) : name(name) { setPassword(pass); };
User::~User(){}
void   User::setName(string name)		{	this->name = name;	}
string User::getName() const			{	return name;		}
void   User::setPassword(string pass)	{	password = pass;	}
string User::getPassword() const		{	return password;	}
void User::go(User* u) { u->menu(); }

class Student : public User
{
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
	void setNumber(string number)	{ this->number = number;	}
	void setAddress(string address) { this->address = address;  }
	void setFIO(string fio)			{ FIO = fio;				}
	string getNumber() const		{ return number;			}
	string getAddress()  const		{ return address;			}
	string get_FIO() const			{ return FIO;				}
	void viewing_previons_tests();//посмотреть предыдущие тесты и их результаты
	void take_a_test();//пройти тест
	void contine_test();//продолжить тест
	void profil();
};

Student::Student() : User(), number("no number"), address("no address"), FIO("no FIO") {};

Student::Student(string name, string pass) : User(name, pass) {}

Student::Student(string name, string pass, string number, string address, string FIO)
	: User(name, pass), number(number), address(address), FIO(FIO) {};

Student::~Student() {}

void Student::menu()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tПрофiль студента : " << User::getName();
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

void Student::viewing_previons_tests()
{
	this->test->files("name_test");
	cout << "Введите название теста\n";
	string name_test, st;
	getline(cin, name_test);
	ifstream f(this->getName() + "col_otv_my_" + test->get_name_answer(name_test));
	if (f.is_open())
	{
		cout << " ~ " << name_test << "\n";
		getline(f, st);
		cout << st; 
		system("pause");
	}
	else
	{
		cout << "Вы не проходили этот тест\n";
		system("pause");
		return;
	}
	f.close();
}

void Student::take_a_test()
{
	cout << "~ Существующие категории\n";
	test->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	if (test->exam_base(base_category, name_category) == 1)
	{
		system("cls");
		cout << "~ Существующие тесты \n";
		ifstream f(base_tests);
		if (f.is_open()) {
			while (getline(f, buff_str))
			{
				if (test->exam_category(name_category, buff_str) == true)
				{
					buff_str = regex_replace(buff_str, regex(name_category + "_"), "");
					cout << " - " << buff_str << "\n";
				}
			}
		}
		cout << "Введите название теста\n";
		getline(cin, name_test);
		name_test = name_category + "_" + name_test;
	}
	
	/*this->test->files("name_test");
	cout << "Введите название теста\n";
	string name_test;
	getline(cin, name_test);
	this->test->go_test(name_test + ".txt", "my_" + test->get_name_answer(name_test));
	this->test->result(this->getName(), test->get_name_answer(name_test), "my_" + test->get_name_answer(name_test));*/
}

class Admin : public User
{
	test* test = nullptr;
public:
	Admin();
	Admin(string name, string pass);
	virtual void menu() override;

	void menegment_user();// управління користувачами
	void add_user();//додати користувача
	void delete_user();// відалити користувача
	void user_modification();// изменить параметрі пользователя

	void statistic();//статистика
	void statistic_categories();//по ктегории
	void statistic_test();// по тесту
	void statistic_user();//по пользователю
	void statistic_output_fille();//загрузить статистику в файл

	void menegment_tests();// управление тестами
	void add();
	void del();
	void add_test();// добавить тест
	void delete_test();
	void add_category();//  категорию
	void delete_category();
	void add_questions();//добавить вопросс
	void delete_questions();
	void inport_txt();// импортировать из файла
	void export_txt();// експортировать в файл
};

Admin::Admin() :User() {};

Admin::Admin(string name, string pass) : User(name, pass) {};

void Admin::menu()
{
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tПрофiль адміна : " << User::getName();
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
		case 0: //add_user();				break;
		case 1: /*delete_user();*/			break;
		case 2: /*user_modification();*/	break;
		case 3: return;
		}
	} while (true);
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
		case 0: /*delete_category();*/		break;
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
	if (test->exam_base(base_category, name_category) == 1)
	{
		system("cls");
		cout << "~ Существующие тесты \n";
		ifstream f(base_tests);
		if (f.is_open()) {
			while (getline(f, buff_str))
			{
				if (test->exam_category(name_category, buff_str) == true)
				{
					buff_str = regex_replace(buff_str, regex(name_category + "_"), "");
					cout << " - " << buff_str << "\n";
				}
			}
		}
		cout << "Введите название теста\n";
		getline(cin, name_test);
		name_test = name_category + "_" + name_test;
		if (test->exam_base(base_tests, name_test) == 0)
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
	string temp = "temp.txt";
	getline(cin, name_category);
	if (test->exam_base(base_category, name_category) == 1)
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
		if (test->exam_base(base_category, name_category) == 1)
		{
			cout << "Такая категория уже существует\n";
			system("pause");
			return;
		}
		f.close();
		ofstream out(base_category, ios::app);
		if (out.is_open())
		{	out << name_category << "\n";	}//записываем если нет совпадений
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
	BTree<string, list<User*>> user;
	string file_user = "base_users.txt";
	void login();
	void Registration();
	bool exam_admin();
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
		cout << "Name :"; getline(cin, new_name);
		list<User*>* new_list = user.getValue(new_name);
		if (!new_list) {
			cout << "Password :"; getline(cin, new_pass);
			if (exam_admin() == true) 
			{
				string new_FIO, new_number, new_address;
				out << new_name << "\n";
				out << new_pass << "\n";
				cout << "FIO :"; getline(cin, new_FIO);
				cout << "Mobile number :"; getline(cin, new_number);
				cout << "Home address :"; getline(cin, new_address);
				User* student = new Student(new_name, new_pass, new_FIO, new_number, new_address);
				list<User*> newList;
				newList.push_back(student);
				user.push_r(student->getName(), newList);
				student->menu();
			}
			else 
			{
				out << "Admin_" + new_name << "\n";
				out << new_pass << "\n";
				User* admin = new Admin(new_name, new_pass);
				list<User*> newList;
				newList.push_back(admin);
				user.push_r(admin->getName(), newList);
				admin->menu();
			}
		}
		else { cout << "Це ім'я зайняте "; system("pause"); }
	}
	else { cout << "eror"; system("pause"); return; }
}

bool Testing_system::exam_admin()
{
	string str;
	ifstream f(file_user);
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

void Testing_system::login()
{
	string this_name, file_name, pass, file_pass;
	ifstream f(file_user);
	cout << "Name - ";
	getline(cin, this_name);
	if (f.is_open()) 
	{
		while (getline(f, file_name))
		{
			if ("Admin_" + this_name == file_name)
			{
				cout << "Password - ";
				getline(cin, pass);
				getline(f, file_pass);
				if (pass == file_pass)
				{
					User* user = new Admin(this_name, pass);
					user->menu();
					return;
					system("pause");
				}
			}
			else if (this_name == file_name)
			{
				cout << "Password - ";
				getline(cin, pass);
				getline(f, file_pass);
				if (pass == file_pass)
				{
					User* user = new Student(this_name, pass);
					user->menu();
					return;
					system("pause");
				}
			}
		}		
	}
}