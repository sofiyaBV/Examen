#pragma once
#include <iostream> 
#include"Menu.h"
#include<list>
using namespace std;

class User{
	string name;
	string password;
protected:
	User();
	User(string name, string pass);
	
	void setName();
	void setPassword();
	
public:
	virtual void menu() = 0;
	virtual ~User();
	string getName() const;
	string getPassword() const;
};

User::User() : name("no name"), password("no pass") {};

User::User(string name, string pass) : name(name), password(pass) {};

User::~User(){}

string User::getName() const{	return name;	}

class Student : public User
{
	string number;
	string address;
	string FIO;
public:
	Student();
	Student(string name, string pass, string number, string address, string FIO);
	virtual ~Student();
	virtual void menu() override;

	void setNumber(string number) { this->number = number; }
	void setAddress(string address) { this->address = address; }
	void setFIO(string fio) { FIO = fio; }
	string getNumber() const { return number; }
	string getAddress()  const { return address; }
	string get_FIO() const { return FIO; }

	void viewing_previons_tests();//посмотреть предыдущие тесты и их результаты
	void take_a_test();//пройти тест
	void contine_test();//продолжить тест
};

Student::Student() : User(), number("no number"), address("no address"), FIO("no FIO") {};

Student::Student(string name, string pass, string number, string address, string FIO)
	: User(name, pass), number(number), address(address), FIO(FIO) {};

Student::~Student() {}

void Student::menu()
{
	do {
		system("cls");
		int choice = Menu::select_vertical(
			{ "Перегляд попереднiх результатiв",
			"Пройти тест",
			"Продовжити тест",
			"Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: /*viewing_previons_tests();*/		break;
		case 1: /*take_a_test();*/					break;
		case 2: /*contine_test();*/					break;
		case 3: return;
		}
	} while (true);
}

void Student::viewing_previons_tests()
{

}

void Student::take_a_test()
{

}

void Student::contine_test()
{

}

class Admin : public User
{
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
	void add_test();// добавить тест
	void add_category();// удалить категорию
	void add_questions();//добавить вопросс
	void inport_txt();// импортировать из файла
	void export_txt();// експортировать в файл
};

Admin::Admin() :User() {};

Admin::Admin(string name, string pass) : User(name, pass) {};

void Admin::menu()
{
	do {
		system("cls");
		int choice = Menu::select_vertical(
			{ "Управлiння користувачами",
			"Перегляд статистики",
			"Управління тестуваннями",
			"Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: /*menegment_user();*/		break;
		case 1: /*statistic();*/			break;
		case 2: /*menegment_tests();*/		break;
		case 3: return;
		}
	} while (true);
}

void statistic() {
	cout << "Statistic" << endl;
	
}

class Testing_system
{
	list<User*> user;
	size_t size;
	void login();
	void Registration();
public:
	Testing_system();
	~Testing_system();
	virtual void menu();
};

Testing_system::Testing_system() {}
Testing_system::~Testing_system() { user.clear(); }



void Testing_system::menu()
{
	do {
		system("cls");
		int choice = Menu::select_vertical(
			{ "Увiйти",
			"Зареєструватися",
			"Вийти" },
			HorizontalAlignment::Center);
		switch (choice)
		{
		case 0: login();		break;
		case 1: Registration(); break;
		case 2: return;
		}
	} while (true);
}

void Testing_system::Registration()
{
	string new_name, new_pass;
	cout << "Name :"; cin >> new_name;
	cout << "Password :"; cin >> new_pass;
	if (user.empty() == 1) {
		User* admin = new Admin(new_name, new_pass);
		user.push_back(admin);
		admin->menu();
	}
	else {
		string new_FIO, new_number, new_address;
		cout << "FIO :"; cin >> new_FIO;
		cout << "Mobile number :"; cin >> new_number;
		cout << "Home address :"; cin >> new_address;
		User* student = new Student(new_name, new_pass, new_FIO, new_number, new_address);
		user.push_back(student);
		student->menu();
	}
}

void Testing_system::login()
{
	string new_name, new_pass;
	cout << "Name :"; cin >> new_name;
	for(User* u : user)
	{
		if (user == new_name)
		{

		}
	}
	/*for (size_t i = 0; i < user.size(); i++)
	{
		if (new_name == user.rend()) {}
	}*/
}