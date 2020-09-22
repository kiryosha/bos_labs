#include <iostream>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <string>

using namespace std;

HANDLE hEvent1;
CRITICAL_SECTION cs;

DWORD WINAPI fun_thread(LPVOID n)
{

	int b = (int)n;
	EnterCriticalSection(&cs);
	srand(time(0));
	while (true)
	{
		if (WaitForSingleObject(hEvent1, 0) == WAIT_OBJECT_0)
		{
			cout << "\nПоток " << b << " завершил работу!";
			ExitThread(0);
		}
		cout << "Поток " << b << endl;
		Sleep((rand() % 20) * 150);
		LeaveCriticalSection(&cs);
	}
	return 0;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL,"Rus");
	InitializeCriticalSection(&cs);
    if (argc >= 2)
    {
        if (argv[1] == string("/?"))
        {
            cout << "Создатель: ?????\nСтудент группы 'БИ-31'\nДоступные параметры: /? <кол-во потоков>\n";
            return 0;
        }
    }

	HANDLE const hMutex = CreateMutexW(NULL, FALSE, L"lab5");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		cout << "Программа уже запущена!" << endl;
		system("pause");
		return -1;
	}

	hEvent1 = CreateEventA(NULL, TRUE, FALSE, NULL);

	int count_t;

	if(argc >= 2)
	{
		if(argv[1] != string("/?"))
			count_t = atoi(argv[1]);
		for (int i = 1; i <= count_t; i++)
		{
			HANDLE thread1 = CreateThread(NULL, 0, fun_thread, LPVOID(i), 0, NULL);
		}
	}

	if(argc == 1)
	{
		cout << "Введите доступные параметры!";
		return -1;
	}

	while (true)
	{
		if (_getch() == 27)
		{
			SetEvent(hEvent1);
			Sleep(2000);
			break;
		}
	}
	return 0;
}
