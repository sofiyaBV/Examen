#pragma once
#include <windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>

#include "Function.h"

class Menu
{
public:
	static int select_vertical(vector <string> menu, HorizontalAlignment ha, int y = 12)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO start_attribute;
		GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
		int backColor = start_attribute.wAttributes & 15;
		int textColor = (start_attribute.wAttributes >>= 4) & 15;
		int maxLen = 0;
		for (size_t i = 0; i < menu.size(); i++)
		{
			menu[i] = " " + menu[i] + " ";
			if (menu[i].length() > maxLen)
				maxLen = menu[i].length();
		}
		int x = 0;
		switch (ha)
		{
		case Center: x = 40 - maxLen / 2; break;
		case Left:   x = 0;	              break;
		case Right:  x = 80 - maxLen;     break;
		}
		char c;
		int pos = 0;
		do
		{
			for (int i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(textColor, backColor);
					gotoxy(x, y + i);
					std::cout << setw(maxLen) << left;
					gotoxy(x, y + i);
					std::cout << menu[i] << endl;
					SetColor(backColor, textColor);
				}
				else
				{
					SetColor(backColor, textColor);
					gotoxy(x, y + i);
					std::cout << setw(maxLen) << left;
					gotoxy(x, y + i);
					std::cout << menu[i] << endl;
					SetColor(textColor, backColor);
				}
			}
			c = _getch();
			switch (c)
			{
			case 72: if (pos > 0)               pos--; break; // up
			case 80: if (pos < menu.size() - 1) pos++; break; // down
			case 13: break;
			}
		} while (c != 13);

		for (size_t i = 0; i < 2; i++)
		{
			SetColor(backColor, textColor);
			gotoxy(x, y + pos);
			std::cout << setw(maxLen) << left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << endl;
			Sleep(200);
			SetColor(textColor, backColor);
			gotoxy(x, y + pos);
			std::cout << setw(maxLen) << left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << endl;
			SetColor(backColor, textColor);
			Sleep(200);
		}
		SetColor(backColor, textColor);
		std::system("cls");
		return pos;
	}

};


void settingConsole() {

	std::system("cls");
	int choice = Menu::select_vertical(
		{ "Чёрный",
		"Синий",
		"Зелёный",
		"Голубой",
		"Красный",
		"Лиловый",
		"Жёлтый",
		"Серыё" },
		HorizontalAlignment::Center);
	switch (choice)
	{
	case 0: std::system("color 07"); break;
	case 1: std::system("color 17"); break;
	case 2: std::system("color 27"); break;
	case 3: std::system("color 37"); break;
	case 4: std::system("color 47"); break;
	case 5: std::system("color 57"); break;
	case 6: std::system("color 67"); break;
	case 7: std::system("color 70"); break;
	case 8: std::system("color 87"); break;
	default:
		break;
	}
}