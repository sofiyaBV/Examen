#include "Test.h"
#include <Windows.h> 
#include<locale>
using namespace std;

void main()
{
	setlocale(LC_CTYPE, "ukr");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Testing_system a;
	a.menu();
		system("pause");		
}
