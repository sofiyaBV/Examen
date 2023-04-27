#pragma once
#include <iostream> 
#include"Menu.h"
#include<list>
#include<map>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <regex>

using namespace std;

string encryptDecrypt(string toEncrypt) 
{
	char key[3] = { 'A', 'r', 'N' };
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
	bool exam_str	  (string str)					const;
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

bool exam_file::exam_str(string str) const
{
	if (str.empty() == true || str == " ") { return true; }
	else								   { return false; }
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
	size_t count = 1;
	if (out_test.is_open() && out_answer.is_open() && out_base.is_open())
	{
		size_t a;
		do {
			string st;
			cout << "Завдання № " << count << "\n";getline(cin, st);
			while (exam.exam_str(st))
			{	cout << "Завдання не може бути пустим, введіть повторно :\n"; getline(cin, st);	}
			out_test << st << "\n";
			cout << "Варінти відповідей \n";  getline(cin, st); out_test   << st << "\n";
			cout << "Правильна відповідь \n"; getline(cin, st); out_answer << st << "\n";
			cout << "Додадти ще запитання?(0 - ні, будь яке додатнэ число - так)\n";
			cin >> a; 
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
				cout << "Додадти ще запитання?(0 - ні, будь яке додатнэ число - так)\n";
				cin >> a;
			}
			cin.ignore();
			count++;
			if (a == 0)
			{
				if (exam.exam_base("base_tests.txt", name_test) == false)
				{ 
					out_base << name_test << "\n"; 
					cout << "Тест завантажено у базу\n";
					system("pause");
				}
				out_test.close(); out_answer.close(); out_base.close();	return;
			}system("cls");
		} while (true);
	}
	else
	{	cout << "Файл для запису не був відкритий\n";	system("pause");	}
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
			cout << "Тест - \n";
			cout << "Завдання №" << count << "\n";
			cout << str << "\nВаріанти відповідей "; getline(f, str);
			cout << str << "\n";
			cout << "Ваша відповідь - "; cin >> otv;
			count++;
			out << otv << "\n";
		}f.close(); out.close();
	}
	else 
	{ 
		cout << "Файл не був відкритий\n"; system("pause"); 
		f.close(); out.close(); return; 
	}
}

void test::result(string name, string name_file_answer, string my_answer) const
{
	system("cls");
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
			else			{ n++; }
		}
		f1.close(); f2.close();
		double answer = 12 / (p + n);
		answer = answer * p;
		cout << p << " - правельних відповідей\n";
		cout << n << " - неправильних відповідей\n";
		if (p == p + n)
		{
			cout << "12 - балів з 12 \n";
			out << "З цього тесту у вас 12 з 12 \n";
		}
		else
		{
			cout << answer << " - балов из 12 \n";
			out << "З цього тесту у вас " << answer << " з 12 \n";
		}
		system("pause");
		f1.close(); out.close(); f2.close();
		remove(my_answer.c_str());
		return;
	}
	else 
	{ 
		cout << "Файл не був відкритий"; 
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
	}f.close();
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
	string base_tests	 = "base_tests.txt";
	string base_users	 = "base_users.txt";
	string base_category = "base_category.txt";
	string temp          = "temp.txt";
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

User::User(): name("no name"), password("no pass"){};
User::User(string name, string pass) : name(name) { setPassword(pass); };
User::~User(){}
void   User::setName	(string name)	{	this->name = name;					}
string User::getName	() const		{	return name;						}
void   User::setPassword(string pass)	{	password = encryptDecrypt(pass);	}
string User::getPassword() const		{   return encryptDecrypt(password);	}


class Student : public User
{
	exam_file* exam = nullptr;
	test* test		= nullptr;
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
	cout << "Логін - "			 << this->getName();
	cout << "\nПІБ - "			 << this->get_FIO();
	cout << "\nНомер телефону - "<< this->getNumber();
	cout << "\nАдресса - "		 << this->getAddress();
	cout << "\nПароль - "		 << this->getPassword();
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
			  "Переглянути профіль",
			  "Вийти"							},
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: viewing_previons_tests();			break;
		case 1: take_a_test();					    break;
		case 2: profil();							break;
		case 3: return;
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
	else{	cout << "По вашим проходженням немає данних\n";	}
	f.close();
	system("pause");
}

void Student::take_a_test()
{
	cout << "~ Існуючі категорії \n";
	test->files(base_category);
	cout << "Введіть назву потрібної категорії : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{ cout << "Ви нічого не написали\n";	getline(cin, name_category);}
	system("cls");
	if (exam->exam_base(base_category, name_category) == true)
	{
		system("cls");
		cout << "~ Існуючі тести тесты \n";
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
		cout << "Введіть назву теста :\n";
		getline(cin, name_test);
		while (exam->exam_str(name_test))
		{ cout << "Ви нічого не написали\n";	getline(cin, name_test);}
		name_test = name_category + "_" + name_test;
		if (exam->exam_base(base_tests, name_test) == true)
		{
			string answer = this->getName() + "_" + test->get_name_answer(name_test) + ".txt";
			add(name_category, regex_replace(name_test, regex(name_category + "_"), ""));
			test->go_test(name_test + ".txt", answer);
			test->result(this->getName(), test->get_name_answer(name_test) + ".txt", answer);
		}
	}
}


void Student::add(string category, string test)
{
	ofstream out(this->getName() + "_result.txt", ios::app);
	if (out.is_open())
	{	out << "Категорія : " << category << " тест - " << test << "\n";	}
}

class Admin : public User
{
	string FIO;
	exam_file* exam = nullptr;
	test* tests		= nullptr;
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

	void statistic			  ()									  const;
	void statistic_categories (string category)					      const;
	void statistic_test		  (string name_category ,string name_test)const;
	void statistic_user		  (string user)							  const;

	void menegment_tests ();
	void add			 ();
	void del			 ();
	void add_test        ();
	void delete_test     ();
	void add_category    ();
	void delete_category ();
	void add_questions   ();
	void delete_questions();
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
string Admin::get_FIO()			{ return FIO; }

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
			cout << "Назва потрібної категорії :\n";
			getline(cin, name_category);
			if (exam->exam_base(base_category, name_category)) {
				tests->file_category_tests(name_category);
				cout << "Назва потрібного тесту :\n";
				getline(cin, name_test);
				while (exam->exam_str(name_test))
				{	cout << "Ви нічого не написали\n";	getline(cin, name_test);	}
				if (exam->exam_base(base_tests, name_category + "_" + name_test)) {
					system("cls");
					cout << "Назва вашого файлу - \n";
					getline(cin, name_file);
					while (exam->exam_str(name_file))
					{	cout << "Ви нічого не написали\n";	getline(cin, name_category);	}
					ofstream out(name_file + ".txt");
					if (out.is_open())
					{
						out << "Категорія - "	<< name_category << "\n";
						out << "Назва тесту - " << name_test	 << "\n";
					}
					out.close();
					name_file_test = name_category + "_" + name_test;
					export_txt(name_file_test, name_file);
				}
			}break;
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
		case 3:							return;
		}
	} while (true);
}

void Admin::add_user()
{
	string new_name, new_pass;
	ofstream out(base_users, ios::app);
	if (out.is_open())
	{
		cout << "Логін :"; 
		getline(cin, new_name);
		while (exam->exam_str(new_name))
		{	cout << "Ви нічого не написали\n";	getline(cin, new_name);	}
		if (exam->exam_base(base_users, new_name) == false)
		{
			cout << "Пароль :"; 
			getline(cin, new_pass);
			while (exam->exam_str(new_pass))
			{	cout << "Ви нічого не написали\n";	getline(cin, new_pass);	}
			new_pass = encryptDecrypt(new_pass);
			if (exam->exam_admin() == true)
			{
				out << new_name << "\n";
				out << new_pass << "\n";
				string new_FIO, new_number, new_address;
				cout << "ПІБ :"; getline(cin, new_FIO);
				cout << "Номер телефону :"; getline(cin, new_number);
				cout << "Адреса :"; getline(cin, new_address);
				User* student = new Student(new_name, new_pass, new_address, new_number, new_FIO);
			}
		}
		else
		{
			cout << "Таке ім'я вже зайняте";
			system("pause");	return;
		}
	}
	else { cout << "Файл не відкрився"; system("pause");  }
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
			{	cout << " - " << st << "\n";	getline(f, st);	}
			ifstream f_1(base_users);
			cout << "Введіть логін :";
			getline(cin, name_user);
			while (exam->exam_str(name_user))
			{	cout << "Ви нічого не написали\n";	getline(cin, name_user);	}
			if (exam->exam_user(name_user) == true)
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
			else { cout << "Людини з таким логіном немає \n"; system("pause"); }
		}
		else { cout << "Файл не був відкритий\n"; system("pause"); }
		f.close();
	}
	else { cout << "Файл не був відкритий\n"; system("pause"); }
}

void Admin::user_modification() 
{
	ofstream out; ifstream f;
	f.open(base_users);
	if (f.is_open())
	{
		string name_student, buff, new_inform;
		cout << "Введіть логін користувача\n";
		getline(cin, name_student);
		while (exam->exam_str(name_student))
		{	cout << "Ви нічого не написали\n";	getline(cin, name_student);	}
		while (getline(f, buff))
		{
			if (name_student == buff) {
				cout << "Для перевірки введіть пароль користувача \n";
				string pass_student;
				getline(cin, pass_student);
				while (exam->exam_str(pass_student))
				{	cout << "Ви нічого не написали\n";	getline(cin, pass_student);	}
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
						  "ПІБ",
						  "Номер телефону",
						  "Адреса",
						  "Вихід"			},
						HorizontalAlignment::Center);
					switch (choice)
					{
					case 0:
						f.open(base_users); out.open(temp);
						cout << "Введіть новий логін\n";
						getline(cin, new_inform);
						while (exam->exam_str(new_inform))
						{	cout << "Ви нічого не написали\n";	getline(cin, new_inform);	}
						if (exam->exam_user(new_inform) == false) 
						{
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
										{	out << buff << "\n";	}
									}
								}
								f.close(); out.close();
							}
						}
						else { cout << "Такий логін вже використовується\n"; system("pause"); }
						return;
					case 1:
						f.open(base_users); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							cout << "Введіть новий пароль\n";
							getline(cin, new_inform);
							while (exam->exam_str(new_inform))
							{	cout << "Ви нічого не написали\n";	getline(cin, new_inform);	}
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
						}break;
					case 2:
						f.open(name_student + "_inform_on_user.txt"); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							getline(f, buff);
							out << buff << "\n";
							cout << "Введіть нове ім'я\n";
							getline(cin, buff);
							while (exam->exam_str(buff))
							{	cout << "Ви нічого не написали\n";	getline(cin, buff);	}
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
						}break;
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
							cout << "Введіть новий номер\n";
							getline(cin, buff);
							while (exam->exam_str(buff))
							{	cout << "Ви нічого не написали\n";	getline(cin, buff);	}
							out << buff << "\n";
							f.close(); out.close();
							f.open(temp); out.open(name_student + "_inform_on_user.txt");
							if (f.is_open() && out.is_open())
							{
								while (getline(f, buff))
								{	out << buff << "\n";	}
							}
						}break;
					case 4:
						f.open(name_student + "_inform_on_user.txt"); out.open(temp);
						if (f.is_open() && out.is_open())
						{
							getline(f, buff);
							out << buff << "\n";
							getline(f, buff);
							out << buff << "\n";
							cout << "Введіть ному адресу\n";
							getline(cin, buff);
							while (exam->exam_str(buff))
							{	cout << "Ви нічого не написали\n";	getline(cin, buff);	}
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
						}	break;
					case 5: break;
					}
				}
				else { cout << "Не верній пароль\n"; system("pause"); }
			}
		}	
	}
	else { cout << "Файл не був відкритий\n"; system("pause"); }
}


void Admin::statistic() const
{
	do {
		string category, test, user, buff;
		ifstream base;
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
			cout << "~ Існуючі категорії \n";
			tests->files(base_category);
			cout << "Введіть категорію\n";
			getline(cin, category);
			while (exam->exam_str(category))
			{	cout << "Ви нічого не написали\n";	getline(cin, category);	}
			if (exam->exam_base(base_category, category))
			{
				system("cls");
				statistic_categories(category);	
				base.open(base_tests);
				if (base.is_open())
				{
					while (getline(base, buff))
					{
						if (exam->exam_category(category, buff))
						{
							buff.erase(buff.begin(), buff.begin() + category.size() + 1);
							statistic_test(category, buff);
						}
					}
				}
				base.close();
			}	
			system("pause");
			break;
		case 1: 
			cout << "~ Існуючі категорії \n";
			tests->files(base_category);
			cout << "Введіть категорію\n";
			getline(cin, category);
			while (exam->exam_str(category))
			{	cout << "Ви нічого не написали\n";	getline(cin, category);	}
			if (exam->exam_base(base_category, category))
			{
				system("cls");
				cout << "~ Існуючі тести \n";
				tests->file_category_tests(category);
				cout << "Введіть назву теста\n";
				getline(cin, test);
				while (exam->exam_str(test))
				{	cout << "Ви нічого не написали\n";	getline(cin, test);	}
				buff = category + "_" + test;
				if (exam->exam_base(base_tests, buff))
				{
					system("cls");
					statistic_test(category, test);
				}
			}
			system("pause");
			break;
		case 2: 
			cout << "~ Існуючі юзери\n";
			base.open(base_users);
			if (base.is_open())
			{
				while (getline(base, buff))
				{
					if (buff.find("Admin_") == string::npos) 
					{ cout << buff << "\n"; }
					getline(base, buff);
				}
				getline(cin, user);
				while (exam->exam_str(user))
				{	cout << "Ви нічого не написали\n";	getline(cin, user);	}
				if (exam->exam_user(user))
				{	statistic_user(user); }
			}
			system("pause");
			break;
		case 3: return;
		}
	} while (true);
}

void Admin::statistic_categories(string category) const
{
	string user, inf, buff;
	double summ = 0.0;
	int count = 0;
	size_t size = category.size();
	ifstream base;
	base.open(base_users);
	if (base.is_open()) {
		while (getline(base, user))
		{
			ifstream user_res(user + "_result.txt");
			if (user_res.is_open())
			{
				while (getline(user_res, inf))
				{
					inf.erase(inf.begin(), inf.begin() + 12);
					buff = inf;
					buff.resize(size);
					if (category == buff)
					{
						inf.erase(inf.begin(), inf.begin() + size + 8);
						getline(user_res, inf);
						inf.erase(inf.begin(), inf.begin() + 20);
						inf.resize(2);
						try {summ += stoi(inf);}
						catch (exception& e) { summ += 0; }
						count++;
					}
				}
			}
			getline(base, user);
		}
	}
	base.close();
	if(count != 0) cout << "~Середня оцінка з категорії " << category << " - " << (summ / count) << " балів\n";
	else cout << "~Середня оцінка з категорії " << category << " - " << 0 << " балів\n";
	cout << "Кількість проходжень - " << count << "\n";
	cout << "~Середнi оцінки тестів : \n";
}

void Admin::statistic_test(string name_category, string name_test) const
{
	map<string, double> user_m;
	map<string, double> count_user;
	string buff, user_buff, us;
	double summ = 0.0;
	double summ_m = 0.0;
	int count = 0;
	ifstream base(base_users);
	if (base.is_open())
	{
		while (getline(base, buff))
		{
			ifstream user(buff + "_result.txt");
			if (user.is_open())
			{
				while (getline(user, user_buff))
				{
					us = buff;
					user_m[us];
					user_buff.erase(user_buff.begin(), user_buff.begin() + name_category.size() + 20);
					if (user_buff == name_test)
					{
						getline(user, user_buff);
						user_buff.erase(user_buff.begin(), user_buff.begin() + 20);
						user_buff.resize(2);
						try
						{
							summ  += stoi(user_buff);
							summ_m = stoi(user_buff);
						}
						catch (exception& e) { summ += 0; }
						user_m[us] += summ_m;
						count_user[us] += 1;
						count++;
					}
					else{	getline(user, user_buff);	}
				}
			}	getline(base, buff);
		}
	}base.close();
	if (count != 0) cout << "~Середня оцінка з тесту " << name_test << " - " << (summ / count) << " балів\n";
	else cout << "~Середня оцінка з тесту " << name_test << " - " << 0 << " балів\n";
	cout << "Кількість проходжень - " << count << "\n";
	for (const auto& n : user_m)
	{
		for (const auto& a : count_user)
		{
			if (n.first == a.first)
			{	cout << n.first << " - " << n.second / a.second << " балів \n";	}
		}
	}
}

void Admin::statistic_user(string user) const
{
	map<string, double> m;
	map<string, double> c;
	ifstream user_(user + "_result.txt");
	string buff, test, category;
	size_t n;
	double summ = 0.0;
	if (user_.is_open())
	{
		while (getline(user_, buff))
		{
			buff.erase(buff.begin(), buff.begin() + 12);
			n = buff.find("тест");
			category = buff;
			category.erase(category.begin() + n, category.end());
			test = buff;
			test.erase(test.begin(), test.begin() + n + 7);
			getline(user_, buff);
			buff.erase(buff.begin(), buff.begin() + 20);
			buff.resize(2);
			try { summ = stoi(buff); }
			catch (exception& e) { summ += 0; }
			m["Категорія - " + category + ", тест " + test] += summ;
			c["Категорія - " + category + ", тест " + test] += 1;
		}
		for (const auto& n : m)
		{
			for (const auto& a : c) 
			{
				if (n.first == a.first)
				{	cout << n.first << " - " << n.second / a.second << " балів \n";	}
			}
		}
	}user_.close();
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
	cout << "~ Існуючі категорії\n";
	tests->files(base_category);
	cout << "Введіть назву потрібної категорії: \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category); }
	if (exam->exam_base(base_category, name_category) == 1)
	{
		system("cls");
		cout << "~ Існуючі тести \n";
		tests->file_category_tests(name_category);
		cout << "Введіть назву потрібного тесту\n";
		getline(cin, name_test);
		while (exam->exam_str(name_test))
		{	cout << "Ви нічого не написали\n";	getline(cin, name_test);	}
		name_test = name_category + "_" + name_test;
		if (exam->exam_base(base_tests, name_test) == 0)
		{	tests->add(name_test, tests->get_name_answer(name_test));	}
		else
		{
			cout << "Тест з такою назвою вже є.Хочете додади запитання?1 - так , 0 - ні\n";
			bool a; cin >> a; cin.ignore();
			if (a == true)
			{	add_questions();	}
			else return;
		}
	}
	else
	{
		cout << "Такої категорії немає. Додати нову? ?1 - так , 0 - ні\n";
		bool a; cin >> a; cin.ignore();
		if (a == true)
		{	add_category();	}
		else return;
	}
}

void Admin::delete_test()
{
	cout << "~ Існуючі категорії\n";
	tests->files(base_category);
	cout << "Введіть назву потрібної категорії : \n";
	string name_category, name_test, buff_str;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category);	}
	if (exam->exam_base(base_category, name_category) == 1)
	{
		cout << "~ Існуючі тести \n";
		tests->file_category_tests(name_category);
		cout << "Введіть назву потрібного тесту : \n";
		getline(cin, name_test);
		while (exam->exam_str(name_test))
		{	cout << "Ви нічого не написали\n";	getline(cin, name_test);	}
		if (exam->exam_base(base_tests, name_category + "_" + name_test) == 1)
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
						cout << "Тест було видалено\n";
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
			{	cout << "Файл не відкрився\n";	system("pause");	}
		}
	}
}

void Admin::add_category()
{
	cout << "~ Існуючі категорії \n";
	tests->files(base_category);
	cout << "Введіть назву нової категорії\n";
	string name_category, buff_str;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category); }
	ifstream f(base_category);
	if (f.is_open())
	{	
		if (exam->exam_base(base_category, name_category) == 1)
		{
			f.close();
			cout << "Така категорія вже існує\n";
			system("pause");	return;
		}
		f.close();
		ofstream out(base_category, ios::app);
		if (out.is_open())
		{	out << name_category << "\n";	}
		else
		{
			cout << "Файл не відкрився\n";
			system("pause");
		}
		out.close();
	}
	else
	{	cout << "Файл не відкрився";system("pause");	}
}

void Admin::delete_category()
{
	cout << "~ Існуючі категорії\n";
	tests->files(base_category);
	cout << "Введіть назву потрібної категорії : \n";
	string name_category;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category);	}
	if (exam->exam_base(base_category, name_category) == true)
	{
		string buff;
		ifstream f_test(base_tests);
		ofstream out_temp_test(temp);
		if (f_test.is_open() && out_temp_test.is_open()) {
			while (getline(f_test, buff))
			{
				if (exam->exam_category(name_category, buff) == false)
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
				cout << "Всі тести з цієї категорії було видалено\n";
				system("pause");
			}
		}
		f_temp_category.close(); out_category.close();
		remove(temp.c_str());
	}
	else
	{	cout << "Файл не відкрився\n";	system("pause");	}
}

void Admin::add_questions()
{
	cout << "~ Існуюючі категорії\n";
	tests->files(base_category);
	cout << "Введіть назву потрібної категорії : \n";
	string name_test, name_category, str;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category);	}
	if (exam->exam_base(base_category, name_category) == 1)
	{
		cout << "~ Існуючі тести \n";
		tests->file_category_tests(name_category);
		cout << "Введіть назву потрібного тесту :\n";
		getline(cin, name_test);
		while (exam->exam_str(name_test))
		{	cout << "Ви нічого не написали\n";	getline(cin, name_test);	}
		if (exam->exam_base(base_tests, name_category + "_" + name_test) == 1)
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
	cout << "~ Існуючі каткгорії\n";
	tests->files(base_category);
	cout << "Введіть назву потрібної категорії : \n";
	string name_test,name_category, str;
	int num;
	getline(cin, name_category);
	while (exam->exam_str(name_category))
	{	cout << "Ви нічого не написали\n";	getline(cin, name_category);	}
	if (exam->exam_base(base_category, name_category) == 1)
	{
		cout << "~ Існуючі тести \n";
		tests->file_category_tests(name_category);
		cout << "Введіть назву потрібного тесту : \n";
		getline(cin, name_test);
		while (exam->exam_str(name_test))
		{	cout << "Ви нічого не написали\n";	getline(cin, name_test);	}
		if (exam->exam_base(base_tests, name_category + "_" + name_test) == 1)
		{
			int count = 1;
			ifstream f_tests(name_category + "_" + name_test + ".txt");
			if (f_tests.is_open())
			{
				cout << "Номер\tзавдання" << "\n";
				while (getline(f_tests, str))
				{
					cout << count << "\t" << str << "\n";
					getline(f_tests, str);
					count++;
				}	system("pause");
			}
			f_tests.close();
			ifstream f_tests2(name_category + "_" + name_test + ".txt");
			cout << "Введіть номер завдання\n";
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
		out_test << "Відповіді : \n";
		for (size_t i = 1; getline(f_test_answer, buff); i++)
		{	out_test << i << ". " << buff << "\n";	}
	}	f_test.close(); f_test_answer.close(); out_test.close();
}

class Testing_system
{
	exam_file exam;
	string file_user = "base_users.txt";
	void login();
	void Registration();
public:
	Testing_system();
	~Testing_system();
	virtual void menu();
};

Testing_system::Testing_system() 
{ 
	ofstream(file_user, ios::app); 
	ofstream("base_category.txt", ios::app);
	ofstream("base_tests.txt", ios::app);
}
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
		cout << "Логін : "; getline(cin, new_name);
		while (exam.exam_str(new_name))
		{	cout << "Ви нічого не написали\n";	getline(cin, new_name);	}
		if (exam.exam_base(file_user, new_name) == false)
		{
			cout << "Пароль : "; encryptPass(new_pass);
			while (exam.exam_str(new_pass))
			{	cout << "\nПароль не може бути пустим або приймати пробіл 1 символом\n";	encryptPass(new_pass);	}
			new_pass = encryptDecrypt(new_pass);
			if (exam.exam_admin() == true)
			{
				out << new_name << "\n";
				out << new_pass << "\n";
				string new_FIO, new_number, new_address;
				cout << "\nПІБ :";			getline(cin, new_FIO);
				cout << "Номер телефону :"; getline(cin, new_number);
				cout << "Адреса :";			getline(cin, new_address);
				User* student = new Student(new_name, new_pass, new_address, new_number, new_FIO);
				student->menu();
			}
			else
			{
				out << "Admin_" + new_name << "\n";
				out << new_pass << "\n";
				string new_FIO;
				cout << "\nПІБ :"; getline(cin, new_FIO);
				while (exam.exam_str(new_FIO))
				{	cout << "Ви нічого не написали\n";	getline(cin, new_FIO);	}
				User* admin = new Admin(new_name, new_pass, new_FIO);
				admin->menu();
			}
		}
		else
		{
			cout << "Такий логін вже зайнятий";
			system("pause");
			return;
		}
	}
	else { cout << "Файл не відкрився"; system("pause"); return; }
}



void Testing_system::login()
{
	string this_name, file_name, pass, file_pass;
	ifstream f(file_user);
	cout << "Логін - ";
	getline(cin, this_name);
	while (exam.exam_str(this_name))
	{	cout << "Ви нічого не написали\n";	getline(cin, this_name); }
	if (f.is_open()) 
	{
		while (getline(f, file_name))
		{
			if ("Admin_" + this_name == file_name)
			{
				cout << "Пароль - ";	encryptPass(pass);
				while (exam.exam_str(pass))
				{	cout << "\nПароль не може бути пустим або приймати пробіл 1 символом\n";	encryptPass(pass);	}
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
					cout << "Неправельний пароль";
					system("pause");
					return;
				}
			}
			else if (this_name == file_name)
			{
				cout << "Пароль - ";	encryptPass(pass);
				while (exam.exam_str(pass))
				{	cout << "\nПароль не може бути пустим або приймати пробіл 1 символом\n";	encryptPass(pass);	}
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
					cout << "Неправельний пароль";
					system("pause");
					return;
				}
			}
		}	
		cout << "Неправельний логін ";
		system("pause");
	}
}