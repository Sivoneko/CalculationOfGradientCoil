// Расчет котушек.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include "Header.h"
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

string File(CheckClass &first)
{
	char text[200];
	GetCurrentDirectoryA(sizeof(text), text); // записываем текущую директорию
	string NewDirectory;
	//создаем название папки
	if (first.getAnswerOut() == 'y')
		NewDirectory = "Отсортировано";
	else
		NewDirectory = "Витков " + to_string(first.GetKolVitkov()) + " Ширина " + to_string(first.GetShirKat());

	string End = text + (string)"\\" + NewDirectory; // создаем путь новой папки
	string FileInNewDirection; //для создания файла в указанной папке
	string NewFileName; //для генерации названия файла
	string Mask = ".txt"; //формат файла

						  //Если указанной папки нет
	if ((CreateDirectoryA(End.c_str(), NULL)))
	{
		//создаем папку для отсортированных данных
		if (first.getAnswerOut() == 'y')
		{
			End += (string)"\\" + "Витков " + to_string(first.GetKolVitkov()) + " Ширина " + to_string(first.GetShirKat());
			CreateDirectoryA(End.c_str(), NULL);
		}
		//создаем окончательный путь папки и файла в ней
		NewFileName = "Sech " + to_string(first.GetSech()[0]) + " - " + to_string(first.GetSech()[first.GetNumberDiam() - 1]) + Mask;
		FileInNewDirection = End + "\\" + NewFileName;

	}
	//если указанная папка уже существует
	else
	{
		int count = 0;
		while (1)
		{
			//создаем имя файла
			//в случае если файла с таким именем не существует
			if (count == 0)
			{
				NewFileName = "Sech " + to_string(first.GetSech()[0]) + " - " + to_string(first.GetSech()[first.GetNumberDiam() - 1]);
			}
			//в случае если файл с таким именем существует
			else
			{
				NewFileName = "Sech " + to_string(first.GetSech()[0]) + " - " + to_string(first.GetSech()[first.GetNumberDiam() - 1]) + "(" + to_string(count) + ")";
			}

			//создаем папку для отсортированных данных
			if ((first.getAnswerOut() == 'y') && (count == 0))
			{
				End += (string)"\\" + "Витков " + to_string(first.GetKolVitkov()) + " Ширина " + to_string(first.GetShirKat());
				CreateDirectoryA(End.c_str(), NULL);
			}

			//создаем окончательный путь создания папки и файла
			NewFileName += Mask;
			FileInNewDirection = End + "\\" + NewFileName;

			//создаем файл в созданной нами папке
			ifstream FileOpenCheck(FileInNewDirection.c_str());

			//проверяем, создалась ли папка и файл
			if (!FileOpenCheck.is_open())
			{
				FileOpenCheck.close();
				break;
			}

			count++;
		}
	}

	return FileInNewDirection;

}

void Menu()
{
	cout << "1 - Расчитать для 1-й ширины котушки \n";
	cout << "2 - Расчтитать для нескольких вариантов ширины котушки \n";
	cout << "o - Выход\n";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	char ViborVMenu;

	do
	{
		system("cls");
		Menu();
		cout << "Выберите пункт: ";
		cin >> ViborVMenu;

		switch (ViborVMenu)
		{
		case '1': //для 1-го варианта ширины котушки
		{
			CheckClass *first = new CheckClass[1];

			first->SetKolShir(1);

			cin >> first;

			string FileInNewDirection;
			//выводим в файл
			for (int i(0); i < 2; i++)
			{
				FileInNewDirection = File(first[0]);
				ofstream FileVivod(FileInNewDirection.c_str(), ios::out);


				FileVivod << first[0];

				FileVivod.close();

				first[0].SetAnswerOut('y');
			}
			break;
		}
		case '2': // для нескольких вариантов ширины котушки
		{
			cout << "Введите количетсво вариантов ширины котушки: ";
			int Shirina;
			cin >> Shirina;

			CheckClass *first = new CheckClass[Shirina];
			//устанавливаем количество вариантов ширины котушки
			first->SetKolShir(Shirina);

			cin >> first;

			string FileInNewDirection;
			//выводим в файл
			for (int i(0); i < Shirina; i++)
			{
				for (int j(0); j < 2; j++)
				{
					FileInNewDirection = File(first[i]);

					ofstream FileVivod(FileInNewDirection.c_str(), ios::out);

					FileVivod << first[i];

					FileVivod.close();
					//для того, чтобы вывести отсортированные
					first[i].SetAnswerOut('y');

				}
			}
			break;
		}
		default:
			break;
		}
	} while (ViborVMenu != 'o');

	_getch();
	return 0;
}

