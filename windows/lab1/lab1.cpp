#define _CRT_SECURE_NO_DEPRECATE // отключение предупреждений
#include <iostream> //  
#include <windows.h> // подключение библиотек
#include <conio.h> // и заголовочных файлов
#include <string>  // 
#include <vector> //

using namespace std; // объявление пространства имен

void main(int argc, char *argv[]) // объявление функции (для работы в командной строке) 
{
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 (кириллица) в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(LC_CTYPE, "Russian"); //// вызов функции настройки локали

	int count_rl = 1, count_all = 0; //
	char ch_vvod; // объявление переменных
	string str_vvod; //

	if (argc >= 2) 
	{
		if (argv[1] == string("/?"))
		{
			cout << "Создатель: Мокеев Игнат Анатольевич\nСтудент группы 'БИ-31'\nДоступные сведения: /?\n";// сведения о создателе
			return;
		}
		else if(argc > 2 || argv[1] != string("/?"))
		{
			cout << "Введен неправильный параметр!\n";
			return;
		}
	}
	if(argc == 1)
	{
		while (true)
		{
			cout << "Введите текст: " << endl;
			ch_vvod = _getche(); // считание символов с консоли и вывод на экран
			while (ch_vvod != 26) // до тех пор, пока не введется ctrl+z
			{
				if (ch_vvod != 8) str_vvod.push_back(ch_vvod); //добавление элементов в конец вектора
				else str_vvod.pop_back();
				if (ch_vvod == 13) count_rl++; // переход на новую строку, возврат каретки
				ch_vvod = _getche();
				if (ch_vvod == 13) cout << endl;
			}

			count_all = str_vvod.length(); // подсчет длины строки

			if (count_all >= 1)
			{
				if (str_vvod.back() == '\r') // перемещение курсора в начало строки
					count_rl--;
			}

			int count_slova = 0;
			char* s = new char[str_vvod.size() + 1]; //  строка, ранее созданная  посредством ввода символов с клавиатуры 
			strcpy(s, str_vvod.c_str());             // копируется в новые символьные переменные, которые входят в массив, 
			char* mass_s = strtok(s, " ,.-:;!\r/");  // где строки разбиваются на лексемы - слова
			while (mass_s != NULL)                   //
			{
				mass_s = strtok(NULL, " ,.-:;!\r/"); // определение количества слов
				count_slova++;
			}

			if (str_vvod.size() <= 1) // определение количества строк 
			{
				count_rl = 0;
			}

			cout << endl;
			cout << "Всего символов: " << count_all << endl << "Количество строк: " << count_rl << endl << "Количество слов: " << count_slova << endl;
			// вывод результатов 
			cout << "Для обновления нажмите Enter" << endl;
			cout << "Для выхода нажмите ESC" << endl;

			char ch;
			ch = _getch();
			if (ch == 27) break; // выход из программы
			else system("cls");
		}
	}
}