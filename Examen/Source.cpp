#include <iostream>
#include <string>
#include "Test.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//setlocale(LC_CTYPE, "ukr");
	Testing_system a;
	a.menu();
		system("pause");
		return 0;
		
}
