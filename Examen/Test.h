#pragma once
#include <iostream> 
#include"Menu.h"
#include<list>
#include"BTree.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <regex>

using namespace std;

string encryptDecrypt(string toEncrypt) 
{
	char key[3] = { 'K', 'C', 'Q' };
	string output = toEncrypt;
	for (int i = 0; i < toEncrypt.size(); i++)
	{	output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];	}
	return output;
}

void encryptPass(string& pass)
{
	int ch;
	ch = _getch();
	while (ch != 13) 
	{
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
}

struct exam_file 
{
	bool exam_base	  (string base, string str)		const;
	bool exam_category(string category, string str) const;
	bool exam_admin	  ()							const;
	bool exam_user    (string name)					const;
};

bool exam_file::exam_base(string base, string str) const
{
	ifstream f(base);
	string buff_str;
	if (f.is_open())
	{
		while (getline(f, buff_str))
		{
			if (buff_str == str)
			{	f.close();	return true;	}
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
	else				 { return false; }
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

bool exam_file::exam_user(string name) const
{
	string str;
	ifstream f("base_users.txt");
	if (f.is_open())
	{
		while (getline(f, str))
		{
			if (name == str) { return true; }
		}
	}
	return false;
}


class test 
{
	exam_file exam;
public:
	void   add			      (string name_test, string name_file_answer);
	void   go_test		      (string name_test, string my_answer)						const;
	void   result			  (string name, string name_faile_answer, string my_answer) const;
	string get_name_answer	  (string name_test)										const;
	void   files			  (string name_file)										const;
	void   file_category_tests(string categort)											const;
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
				if (exam.exam_base("base_tests.txt", name_test) == false)
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
	{	cout << "Оштбка при открытии файлов для записа\n";	system("pause");	}
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
		f.close(); out.close(); return; 
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
		double answer = 12 / (p + n);
		answer = answer * p;
		cout << p << " - правильных\n";
		cout << n << " - неправильных\n";
		cout << answer << " - балов из 12 \n";
		system("pause");
		out << "По этому тесту у вас " << answer << " из 12 \n";
		f1.close(); out.close(); f2.close();
		return;
	}
	else 
	{ 
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
	string getName    () const;
	string getPassword() const;
	void   setName	  (string name);
	void   setPassword(string pass);
};	

User::User(): name("no name"), password("no pass") {};
User::User(string name, string pass) : name(name) { setPassword(pass); };
User::~User(){}
void   User::setName(string name)		{	this->name = name;	}
string User::getName()     const		{	return name;		}
void   User::setPassword(string pass)	
{
	password = encryptDecrypt(pass);
}
string User::getPassword() const		{ return encryptDecrypt(password); }


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
	void   setNumber			 (string number);
	void   setAddress			 (string address);
	void   setFIO				 (string fio);
	string getNumber			 () const;
	string getAddress			 () const;
	string get_FIO				 () const;
	void   add					 (string category, string test);
	void   info		             ();
	void   profil				 ();
	void   viewing_previons_tests() const;
	void   take_a_test			 ();
};

Student::Student() : User(), number("no number"), address("no address"), FIO("no FIO") {};

Student::Student(string name, string pass) : User(name, pass) { info(); }

Student::Student(string name, string pass, string number, string address, string FIO)
	: User(name, pass), number(number), address(address), FIO(FIO) 
{
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
		setAddress(st);
		getline(f, st);
		setNumber(st);
	}
}

void Student::profil()
{
	cout << "Name - "		<< this->getName();
	cout << "\nFIO - "		<< this->get_FIO();
	cout << "\nNumber - "	<< this->getNumber();
	cout << "\nAddress - "	<< this->getAddress();
	cout << "\nPassword - " << this->getPassword();
	cout << "\n";
	system("pause");
}

Student::~Student() {}

void	Student::setNumber (string number)	{ this->number = number; }
void	Student::setAddress(string address) { this->address = address; }
void	Student::setFIO	   (string fio)		{ FIO = fio; }
string  Student::getNumber () const			{ return number; }
string  Student::getAddress() const		    { return address; }
string  Student::get_FIO   () const			{ return FIO; }

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
	{	out << "Категория : " << category << " тест - " << test << "\n";	}
}

class Admin : public User
{
	BTree<string, list<User*>> user;
	string FIO;
	exam_file exam;
	test* tests = nullptr;
public:
	Admin();
	Admin(string name, string pass);
	Admin(string name, string pass, string FIO);
	virtual void menu() override;
	string get_FIO();
	void   setFIO(string name);

	void menegment_user	  ();
	void add_user		  ();
	void delete_user      ();
	void user_modification();

	void statistic			   ()				 const;//статистика
	void statistic_categories  (string category) const;//по ктегории
	void statistic_test		   (string name_test)const;// по тесту
	void statistic_user		   (string user)	 const;//по пользователю
	void statistic_output_fille(string name_file)const;//загрузить статистику в файл

	void menegment_tests ();
	void add			 ();
	void del			 ();
	void add_test        ();
	void delete_test     ();
	void add_category    ();
	void delete_category ();
	void add_questions   ();
	void delete_questions();
	void import_txt		 (string name_file)const;
	void export_txt		 (string name_file_test, string name_file_user)const; 
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
	string name_test, name_category, name_file, name_file_test;
	do {
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tПрофiль адміна : " << get_FIO();
		int choice = Menu::select_vertical(
			{ "Управлiння користувачами",
			  "Перегляд статистики",
			  "Управління тестуваннями",
			  "Загрузить тест в файл",
			  "Вийти"					},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: menegment_user();		break;
		case 1: statistic();			break;
		case 2: menegment_tests();		break;
		case 3: 	
			tests->files(base_category);
			cout << "Названиие категории :\n";
			getline(cin, name_category);
			if (exam.exam_base(base_category, name_category)) {
				tests->file_category_tests(name_category);
				cout << "Названиие теста :\n";
				getline(cin, name_test);
				if (exam.exam_base(base_tests, name_category + "_" + name_test)) {
					system("cls");
					cout << "Название файла \n";
					getline(cin, name_file);
					ofstream out(name_file + ".txt");
					if (out.is_open())
					{
						out << "Категорія - " << name_category << "\n";
						out << "Назва тесту - " << name_test << "\n";
					}
					out.close();
					name_file_test = name_category + "_" + name_test;
					export_txt(name_file_test, name_file);
				}
			}			break;
		case 4: return;
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
		case 1: delete_user();			break;
		case 2: user_modification();	break;
		case 4:							return;
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
			cout << "Password :"; 
			getline(cin, new_pass);
			new_pass = encryptDecrypt(new_pass);
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
	else { cout << "Ошибка открытия файла для записи"; system("pause");  }
}

void Admin::delete_user()
{
	string name_user;
	ifstream f_user(base_users);
	ofstream out_t(temp);
	if (f_user.is_open() && out_t.is_open())
	{
		ifstream f(base_users);
		string st, buff;
		if (f.is_open())
		{
			getline(f, st);
			getline(f, st);
			while (getline(f, st))
			{
				cout << " - " << st << "\n";
				getline(f, st);
			}
			ifstream f_1(base_users);
			cout << "Введите логин человека\n";
			getline(cin, name_user);
			if (exam.exam_user(name_user) == true)
			{
				while (getline(f_1, buff))
				{
					if (name_user == buff)
					{
						name_user += "_inform_on_user.txt";
						remove(name_user.c_str());
						getline(f_1, buff);
					}
					else
					{	out_t << buff << "\n";	}
				}
				f_user.close(); out_t.close();
				ofstream out_user(base_users);
				ifstream f_t(temp);
				if (out_user.is_open() && f_t.is_open())
				{
					while (getline(f_t, buff))
					{	out_user << buff << "\n";	}
				}
				out_user.close(); f_t.close();
			}
			else { cout << "Человека с таким логином нет \n"; system("pause"); }
		}
		else { cout << "Ошибка открытия файла для чтения\n"; system("pause"); }
		f.close();
	}
	else { cout << "Ошибка открытия файла для чтения\n"; system("pause"); }
}

void Admin::user_modification() 
{
	ofstream out; ifstream f;
	f.open(base_users);
	if (f.is_open())
	{
		string name_student, buff, new_inform;
		cout << "Введіть логін студента\n";
		getline(cin, name_student);
		while (getline(f, buff))
		{
			if (name_student == buff) {
				cout << "Для проверки введите пароль \n";
				string pass_student;
				getline(cin, pass_student);
				pass_student = encryptDecrypt(pass_student);
				getline(f, buff);
				if (pass_student == buff)
				{
					f.close();
					system("cls");
					cout << "\n\n\n\n\n\n\t\t\t\tВиберіть що хочете змінити";
					int choice = Menu::select_vertical(
						{ "Login",
						  "Пароль",
						  "ПІП",
						  "Номер телефону",
						  "Адреса",
						  "Вихід"			},
						HorizontalAlignment::Center);
					switch (choice)
					{
					case 0:
						f.open(base_users); out.open(temp);
						cout << "Введите новый логин\n";
						getline(cin, new_inform);
						if (f.is_open() && out.is_open())
						{
							while (getline(f, buff))
							{
								if (buff != name_student) 
								{	out << buff << "\n";	}
								else
								{	out << new_inform << "\n";	}
							}
							f.close(); out.close();
							f.open(temp); out.open(base_users);
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
							f.close(); out.close();
							f.open(name_student + "_inform_on_user.txt"); out.open(temp);
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{
									if (buff != name_student)
									{	out << buff << "\n";	}
									else
									{	out << new_inform << "\n";	}
								}
								f.close(); out.close();
								name_student += "_inform_on_user.txt";
								remove(name_student.c_str());
								f.open(temp); out.open(new_inform + "_inform_on_user.txt");
								if (f.is_open() && out.is_open())
								{
									while (getline(f, buff))
									{	out << buff << "\n";}
								}
							}
							f.close(); out.close();
						}
						break;
					case 1:
						f.open(base_users); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							cout << "Введите новый пароль\n";
							getline(cin, new_inform);
							while (getline(f, buff))
							{
								if (buff == name_student)
								{
									out << name_student << "\n";
									out << encryptDecrypt(new_inform) << "\n";
									getline(f, buff);
								}
								else 
								{ out << buff << "\n"; }
							}
							f.close(); out.close();
							f.open(temp); out.open(base_users);
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
						}
						break;
					case 2:
						f.open(name_student + "_inform_on_user.txt"); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							getline(f, buff);
							out << buff << "\n";
							cout << "Введите имя\n";
							getline(cin, buff);
							out << buff << "\n";
							getline(f, buff);
							getline(f, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							f.close(); out.close();
							f.open(temp); out.open(name_student + "_inform_on_user.txt");
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
						}
						break;
					case 3:
						f.open(name_student + "_inform_on_user.txt"); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							getline(f, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							cout << "Введите номер\n";
							getline(cin, buff);
							out << buff << "\n";
							f.close(); out.close();
							f.open(temp); out.open(name_student + "_inform_on_user.txt");
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
						}
						break;
					case 4:
						f.open(name_student + "_inform_on_user.txt"); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							getline(f, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							cout << "Введите адресс\n";
							getline(cin, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							f.close(); out.close();
							f.open(temp); out.open(name_student + "_inform_on_user.txt");
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
						}
						break;
					case 5: break;
					}
				}
				else { cout << "Не верній пароль\n"; system("pause"); }
			}
			else { cout << "Такого имени нет\n"; system("pause"); }
		}	
	}
	else { cout << "База недоступна\n"; system("pause"); }
}


void Admin::statistic() const
{
	do {
		string buff;
		system("cls");
		cout << "\n\n\n\n\n\n\t\t\t\tСтатистика ";
		int choice = Menu::select_vertical(
			{ "За категорією",
			  "За тестом",
			  "За студентом",
			  "Вийти"			},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0:
			tests->files(base_category);
			cout << "Введіть категорію\n";
			getline(cin, buff);
			if (exam.exam_base(base_category, buff))
			{	statistic_categories(buff);	}	
			break;
		case 1: /*statistic_test;*/			break;
		case 2: /*statistic_user();*/		break;
		case 3: return;
		}
	} while (true);
}

void Admin::statistic_categories(string category) const
{
	cout << category << "\n";
	string user, inf, buff;
	float summ = 0.0f;
	int count = 0;
	ifstream base_user(base_users);
	while (getline(base_user, user))
	{
		
		ifstream user_res(user + "_result.txt");
		if (user_res.is_open())
		{
			cout << user << "\n";
			while (getline(user_res, inf))
			{
				inf.erase(inf.begin(), inf.begin() + 12);
				buff = inf;
				size_t size = category.size();
				buff.resize(size);
				cout << buff << "\n";
				if (category == buff)
				{
					inf.erase(inf.begin(), inf.begin() + size + 8);
					cout << inf << "\n";
					getline(user_res, inf);
					cout << inf << "\n";
					inf.erase(inf.begin(), inf.begin() + 21);
					cout << inf << "\n";
					inf.resize(2);
					summ += stoi(inf);
					cout << summ << "\n";
				}
			}
		}
	}
	system("pause");
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
		case 2: delete_questions();		break;
		case 3: return;
		}
	} while (true);
}

void Admin::add_test()
{
	cout << "~ Существующие категории\n";
	tests->files(base_category);
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
		{	tests->add(name_test, tests->get_name_answer(name_test));	}
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
		{	add_category();	}
		else return;
	}
}

void Admin::delete_test()
{
	cout << "~ Существующие категории\n";
	tests->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == 1)
	{
		cout << "~ Существующие тесты \n";
		tests->file_category_tests(name_category);
		cout << "Введите название теста\n";
		getline(cin, name_test);
		if (exam.exam_base(base_tests, name_category + "_" + name_test) == 1)
		{
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
			{	cout << "eror file\n";	system("pause");	}
		}
	}
}

void Admin::add_category()
{
	cout << "~ Уже имеющиеся категории ~\n";
	tests->files(base_category);
	cout << "Введите название категории что ходите добавить\n";
	string name_category, buff_str;
	getline(cin, name_category);
	ifstream f(base_category);
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
		{	out << name_category << "\n";	}
		else
		{
			cout << "Ошибка открытия файла для чтения\n";
			system("pause");
		}
		out.close();
	}
	else
	{	cout << "Ошибка открытия файла для записи\n";system("pause");	}
}

void Admin::delete_category()
{
	cout << "~ Существующие категории\n";
	tests->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_category;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == true)
	{
		string buff;
		ifstream f_test(base_tests);
		ofstream out_temp_test(temp);
		if (f_test.is_open() && out_temp_test.is_open()) {
			while (getline(f_test, buff))
			{
				if (exam.exam_category(name_category, buff) == false)
				{	out_temp_test<< buff << "\n";	}
				else
				{
					buff += ".txt";
					remove(buff.c_str());
					buff = regex_replace(buff, regex(".txt"), "");
					buff += "_answer.txt";
					remove(buff.c_str());
				}
			}
		}
		f_test.close(); out_temp_test.close();
		ifstream f_temp(temp);
		ofstream out_tests(base_tests);
		if (f_temp.is_open() && out_tests.is_open())
		{
			while (getline(f_temp, buff))
			{	out_tests << buff << "\n";	}
		}
		f_temp.close(); out_tests.close();
		remove(temp.c_str());
		ifstream f_category(base_category);
		ofstream out_temp_category(temp);
		if (f_category.is_open() && out_temp_category.is_open()) 
		{
			while (getline(f_category, buff))
			{
				if (name_category != buff)
				{	out_temp_category << buff << "\n";	}
			}
		}
		f_category.close(); out_temp_category.close();
		ifstream f_temp_category(temp);
		ofstream out_category(base_category);
		if (f_temp_category.is_open() && out_category.is_open())
		{
			while (getline(f_temp_category, buff))
			{	
				out_category << buff << "\n";	
				cout << "Все тесты с этой категории были удалены\n";
				system("pause");
			}
		}
		f_temp_category.close(); out_category.close();
		remove(temp.c_str());
	}
	else
	{	cout << "eror file\n";	system("pause");	}
}

void Admin::add_questions()
{
	cout << "~ Существующие категории\n";
	tests->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_test, name_category, str;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == 1)
	{
		cout << "~ Существующие тесты \n";
		tests->file_category_tests(name_category);
		cout << "Введите название теста\n";
		getline(cin, name_test);
		if (exam.exam_base(base_tests, name_category + "_" + name_test) == 1)
		{
			ifstream f(name_category + "_" + name_test + ".txt");
			if (f.is_open())
			{	tests->add(name_category + "_" + name_test, tests->get_name_answer(name_category + "_" + name_test));		}
			f.close();
		}
	}
}

void Admin::delete_questions() 
{
	cout << "~ Существующие категории\n";
	tests->files(base_category);
	cout << "Введите название нужной категории : \n";
	string name_test,name_category, str;
	int num;
	getline(cin, name_category);
	if (exam.exam_base(base_category, name_category) == 1)
	{
		cout << "~ Существующие тесты \n";
		tests->file_category_tests(name_category);
		cout << "Введите название теста\n";
		getline(cin, name_test);
		if (exam.exam_base(base_tests, name_category + "_" + name_test) == 1)
		{
			int count = 1;
			ifstream f_tests(name_category + "_" + name_test + ".txt");
			if (f_tests.is_open())
			{
				cout << "Номер\tзадание" << "\n";
				while (getline(f_tests, str))
				{
					cout << count << "\t" << str << "\n";
					getline(f_tests, str);
					count++;
				}
				system("pause");
			}
			f_tests.close();
			ifstream f_tests2(name_category + "_" + name_test + ".txt");
			cout << "Введите номер задания\n";
			cin >> num; cin.ignore();
			ofstream out_temp(temp);
			if (out_temp.is_open() && f_tests2.is_open())
			{
				for (size_t i = 1; i < num; i++)
				{
					getline(f_tests2, str);
					out_temp << str << "\n";
					getline(f_tests2, str);
					out_temp << str << "\n";
				}
				getline(f_tests2, str);
				getline(f_tests2, str);
				for (size_t i = num + 1; i < count; i++)
				{
					getline(f_tests2, str);
					out_temp << str << "\n";
					getline(f_tests2, str);
					out_temp << str << "\n";
				}
			}
			out_temp.close(); f_tests2.close();
			ifstream f_temp_(temp);
			ofstream out_test(name_category + "_" + name_test + ".txt");
			if (f_temp_.is_open() && out_test.is_open())
			{
				while (getline(f_temp_, str))
				{	out_test << str << "\n";	}
			}
			out_test.close(); f_temp_.close();
			remove(temp.c_str());
			ifstream f_answer(name_category + "_" + name_test + "_answer.txt");
			ofstream out_temp_answer(temp);
			if (f_answer.is_open() && out_temp_answer.is_open())
			{
				for (size_t i = 1; i < num; i++)
				{
					getline(f_answer, str);
					out_temp_answer << str << "\n";
				}
				getline(f_answer, str);
				for (size_t i = num + 1; i < count; i++)
				{
					getline(f_answer, str);
					out_temp_answer << str << "\n";
				}
			}
			out_temp_answer.close(); f_answer.close();
			ifstream f_temp_answer(temp);
			ofstream out_answer(name_category + "_" + name_test + "_answer.txt");
			if (f_temp_answer.is_open() && out_answer.is_open())
			{
				while (getline(f_temp_answer, str))
				{	out_answer << str << "\n";	}
			}
			out_answer.close(); f_temp_answer.close();
		}
	}
}

void Admin::export_txt(string name_file_test, string name_file_user) const
{
	ifstream f_test(name_file_test + ".txt");
	ifstream f_test_answer(name_file_test + "_answer.txt");
	ofstream out_test(name_file_user + ".txt", ios::app);
	string buff;
	if (f_test.is_open() && f_test_answer.is_open() && out_test.is_open())
	{
		for (size_t i = 1; getline(f_test, buff); i++)
		{
			out_test << i << ". " << buff << "\n";
			getline(f_test, buff);
			out_test << " ~ " << buff << "\n";
		}
		for (size_t i = 1; getline(f_test_answer, buff); i++)
		{	out_test << i << ". " << buff << "\n";	}
	}
	f_test.close(); f_test_answer.close(); out_test.close();
}

void Admin::import_txt(string name_file) const
{
	//тест с файла
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

Testing_system::Testing_system () {}
Testing_system::~Testing_system() {}

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
				cout << "\nFIO :"; getline(cin, new_FIO);
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