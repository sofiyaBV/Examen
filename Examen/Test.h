#pragma once
#include <iostream> 
#include"Menu.h"
using namespace std;

class User{
	string name;
	string password;
public:
	User();
	User(string name, string pass);
	virtual ~User();
	virtual void menu() const = 0;
protected:
	void setName();
	void setPassword();
	void getName() const;
	void getPassword() const;
};

User::User() : name("no name"), password("no pass") {};

User::User(string name, string pass) : name(name), password(pass) {};

User::~User(){}

class Student : public User
{
	string number;
	string address;
	string FIO;
protected:
	Student();
	Student(string name, string pass, string number, string address, string FIO);
	virtual ~Student();
	virtual void menu() const override;

	void setNumber();
	void setAddress();
	void setFIO();
	void getNumber() const;
	void getAddress() const;
	void get_FIO() const;

	void viewing_previons_tests();//посмотреть предыдущие тесты и их результаты
	void take_a_test();//пройти тест
	void contine_test();//продолжить тест
};

Student::Student() : User(), number("no number"), address("no address"), FIO("no FIO") {};

Student::Student(string name, string pass, string number, string address, string FIO)
	: User(name, pass), number(number), address(address), FIO(FIO) {};

Student::~Student() {}

void Student::menu() const
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
		case 0: /*viewing_previons_tests();;*/		break;
		case 1: /*take_a_test();*/					break;
		case 2: /*contine_test();*/					break;
		case 3: return;
		}
	} while (true);
}

class Admin : public User
{
protected:
	Admin();
	Admin(string name, string pass);
	virtual void menu() const override;

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

void Admin::menu() const
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

class Testing_system
{
	User* users;
	void login();
	void Registration();
public:
	Testing_system();
	~Testing_system();
	virtual void menu() const ;
};

Testing_system::Testing_system() : users(nullptr) {}
Testing_system::~Testing_system() { /*delete[] users;*/ }

void Testing_system::menu() const
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
		case 0: /*login();*/		break;
		case 1: /*Registration();*/ break;
		case 2: return;
		}
	} while (true);
}