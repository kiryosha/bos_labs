#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void menu();

void vivod_diskov() 
{
	while (true)
	{
		int bit;
		char ch;
		string name_disk;
		DWORD bit_m = GetLogicalDrives();

		for (int i = 0; i < 26; i++)
		{
			bit = ((bit_m >> i) & 0x00000001);
			if (bit == 1)
			{
				name_disk = char(65 + i);

				name_disk += ":\\";
				cout << "Доступные устройства: " << name_disk << endl;
			}
		}
		cout << endl;
		cout << "Для обновления нажмите Enter" << endl;
		cout << "Для выхода нажмите ESC" << endl;
		ch = _getch();
		if (ch == 27)
		{
			system("cls");
			menu();
			break;
		}
		else 
		{
			Sleep(1000);
			system("cls");
		}
	}
}

void vivod_info()
{
	int d;
	char ch;
	string name_disk;
	cout << "Введите букву устройства (Например, С): ";
	cin >> name_disk;
	name_disk += ":\\";
	d = GetDriveType(name_disk.c_str());
	cout << "Буква диска: " << name_disk << endl;
	cout << "Тип устройства: ";
	if (d == DRIVE_UNKNOWN) cout << "не известный тип" << endl;
	if (d == DRIVE_NO_ROOT_DIR) cout << "не правильный путь" << endl;
	if (d == DRIVE_REMOVABLE) cout << "съёмный диск" << endl;
	if (d == DRIVE_FIXED) cout << "фиксированный диск" << endl;
	if (d == DRIVE_REMOTE) cout << "удалённый или network диск" << endl;
	if (d == DRIVE_CDROM) cout << "CD-ROM" << endl;
	if (d == DRIVE_RAMDISK) cout << "RAM-DISK" << endl;

	char FileSystemNameBuffer[100];
	char VolumeNameBuffer[100];
	unsigned long VolumeSerialNumber;
	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		name_disk.c_str(),
		VolumeNameBuffer,
		100,
		&VolumeSerialNumber,
		NULL,
		NULL, 
		FileSystemNameBuffer,
		100
	);

	if (GetVolumeInformationFlag != 0)
	{
		cout << "Имя тома: " << VolumeNameBuffer << endl;
		cout << " Серийный номер: " << VolumeSerialNumber << endl;
		cout << "Файловая система: " << FileSystemNameBuffer << endl;
	}

	__int64 FreeBytesAvailable, TotalNumberOfBytes, TotalNumberOfFreeBytes;

	if (GetDiskFreeSpaceEx(name_disk.c_str(), (PULARGE_INTEGER)&FreeBytesAvailable, (PULARGE_INTEGER)&TotalNumberOfBytes, (PULARGE_INTEGER)&TotalNumberOfFreeBytes))
	{
		cout << "Свободно: " << (long long(TotalNumberOfFreeBytes)) << " Байт | " << (long long(TotalNumberOfFreeBytes)) / 1048576 << " Мб | " << (long double(TotalNumberOfFreeBytes)) / 1048576 / 1024 << " Гб | " << endl;
		cout << "Занято: " << (long long(TotalNumberOfBytes - TotalNumberOfFreeBytes)) << " Байт | " << (long long(TotalNumberOfBytes - TotalNumberOfFreeBytes)) / 1048576 << " Мб | " << (long double(TotalNumberOfBytes - TotalNumberOfFreeBytes)) / 1048576 / 1024 << " Гб | " << endl;
		cout << "Емкость: " << (long long(TotalNumberOfBytes)) << " Байт | " << (long long(TotalNumberOfBytes)) / 1048576 << " Мб | " << (long double(TotalNumberOfBytes)) / 1048576 / 1024 << " Гб | " << endl;
	}
	cout << endl;
	cout << "Для выхода нажмите ESC" << endl;
	while (true)
	{
		ch = _getch();
		if (ch == 27)
		{
			system("cls");
			menu();
			break;
		}
	}
}

void ejectDrive(string name_disk)
{
	string temp = "\\\\.\\";
	temp.push_back(name_disk[0]);
	temp.push_back(name_disk[1]);
	DWORD dwRet = 0;
	HANDLE hVol = CreateFile(temp.c_str(), GENERIC_READ, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hVol == INVALID_HANDLE_VALUE)
		return;

	if (!DeviceIoControl(hVol, FSCTL_LOCK_VOLUME, 0, 0, 0, 0, &dwRet, 0))
		return;

	if (!DeviceIoControl(hVol, FSCTL_DISMOUNT_VOLUME, 0, 0, 0, 0, &dwRet, 0))
		return;

	DeviceIoControl(hVol, IOCTL_STORAGE_EJECT_MEDIA, 0, 0, 0, 0, &dwRet, 0);

	CloseHandle(hVol);
}

void del_disk() 
{
	int d;
	char ch;
	string name_disk;
	cout << "Введите букву устройства (Например, С): ";
	cin >> name_disk;
	name_disk += ":\\";
	d = GetDriveType(name_disk.c_str());
	if (d == DRIVE_REMOVABLE || d == DRIVE_CDROM)
	{
		ejectDrive(name_disk);
		cout << "Устройство " << name_disk << " извлечено!";
	}
	else
	{
		cout << "Устройство " << name_disk << " не может быть извлечено!";
	}
	cout << endl;
	cout << "Для выхода нажмите ESC" << endl;
	while (true)
	{
		ch = _getch();
		if (ch == 27)
		{
			system("cls");
			menu();
			break;
		}
	}
}

void menu()
{
	int choise;
	cout << "1. Вывод списка доступных устройств-накопителей в системе." << endl;
	cout << "2. Вывод доступной информации о отдельном устройстве." << endl;
	cout << "3. Удаление устройства." << endl;
	cout << "4. Выход." << endl;
	cout << "Ваш выбор: ";
	cin >> choise;
	switch (choise)
	{
	case 1:
		system("cls");
		vivod_diskov();
		break;
	case 2:
		system("cls");
		vivod_info();
		break;
	case 3:
		system("cls");
		del_disk();
		break;
	case 4:
		exit(0);
	}
}

void main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	if (argc >= 2)
	{
		if (argv[1] == string("/?"))
		{
			cout << "Создатель: ?????\nСтудент группы 'БИ-31'\nДоступные параметры: /?\n";
			return;
		}
		else if (argc > 2 || argv[1] != string("/?"))
		{
			cout << "Введен неправильный параметр!\n";
			return;
		}
	}
	if(argc == 1)
	{
		menu();
	}
}