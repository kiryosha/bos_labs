#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>

using namespace std;

void menu();

vector<string> strtokResult(char buf[128])
{
	vector<string> result;
	char* temp;
	temp = strtok(buf, " ");
	while (temp)
	{
		result.push_back(temp);
		temp = strtok(NULL, " ");
	}
	return result;
};

bool checkDevices(string name)
{
	char buf[128];
	bool check = false;
	string commandDisk = "lsblk -lo NAME,TYPE | grep .*disk";
	size_t indexDot = commandDisk.find_first_of('.');
	commandDisk.insert(indexDot, name);
	FILE* fs = popen(commandDisk.c_str(), "r");
	if(fgets(buf, sizeof(buf) - 1, fs) != NULL)
		if(strlen(buf) != 0) check = true;
	fclose (fs);
	if(!check)
	{
		string commandRom = "lsblk -lo NAME,TYPE | grep .*rom";
		commandRom.insert(indexDot, name);
		FILE* fsTwo = popen(commandRom.c_str(), "r");
		if(fgets(buf, sizeof(buf) - 1, fsTwo) != NULL)
			if(strlen(buf) != 0) check = true;
		fclose(fsTwo);
	}
	return check;
}

void outputListStorageDevices()
{
	char buf[128];
	vector<string> diskInfo;
	FILE* fs = popen("lsblk -lo NAME,TYPE,MODEL", "r");
	cout << "Available devices:" << endl;
	cout << "name\t" << "model" << endl;
	while (fgets(buf, sizeof(buf) - 1, fs))
	{
		if (strstr(buf, "rom") || strstr(buf, "disk"))
		{
			vector<string> diskInfo = strtokResult(buf);
			cout << diskInfo[0] << "\t" << diskInfo[2];
		}
	}
}

void outputOneStorageDevice(string name)
{
	char bufSize[128];
	char bufInfo[128];
	char bufFS[128];
	bool check = checkDevices(name);
	if(check)
	{
		string commandDf = "df -h | grep";
		size_t indexLastDF = commandDf.find_first_of(commandDf[commandDf.length() - 1]);
		commandDf.insert(indexLastDF + 1, " ");
		commandDf.insert(indexLastDF + 2, name);
		FILE* fs = popen(commandDf.c_str(), "r");
		fgets(bufSize, sizeof(bufSize) - 1, fs);
		fclose(fs);
		if(strlen(bufSize) == 0)
		{
			cout << "Disk drive is empty!" << endl;
			return;
		}
		string commandLSBLK = "lsblk -lo NAME,MODEL,SERIAL,STATE | grep";
		size_t indexLastLS = commandLSBLK.find_first_of(commandLSBLK[commandLSBLK.length() - 1]);
		commandLSBLK.insert(indexLastLS + 1, " ");
		commandLSBLK.insert(indexLastLS + 2, name);
		FILE* fsTwo = popen(commandLSBLK.c_str(), "r");
		fgets(bufInfo, sizeof(bufInfo) - 1, fsTwo);
		fclose(fsTwo);
		vector<string> df = strtokResult(bufSize);
		vector<string> lsDiskInfo = strtokResult(bufInfo);
		int indexName = df[0].find(name);
		string stringPasth = df[0].substr(indexName, df[0].length() - indexName);
		string commandFsType = "lsblk -lo NAME,FSTYPE | grep";
		size_t indexLastFsType = commandFsType.find_first_of(commandFsType[commandFsType .length() - 1]);
		commandFsType.insert(indexLastFsType + 1, " ");
		commandFsType.insert(indexLastFsType + 2, stringPasth);
		FILE* fsT = popen(commandFsType.c_str(), "r");
		fgets(bufFS, sizeof(bufFS) - 1, fsT);
		fclose(fsT);
		vector<string> fsTyphe = strtokResult(bufFS);
		cout << "Name: " << lsDiskInfo[0] << "\t" << df[0] << endl;
		cout << "Model: " << lsDiskInfo[1] << endl;
		cout << "FsType: " << fsTyphe[1];
		cout << "Serial: " << lsDiskInfo[2] << endl;
		cout << "Stat: " << lsDiskInfo[3];
		cout << "Size: " << df[1] << endl;
		cout << "Used: " << df[2] << endl;
		cout << "Available: " << df[3] << endl;
	}
	else cout << "Not found!" << endl;
}

void extraction(string name)
{
	string commandE = "echo XXXX | sudo eject -s /dev/";
	size_t indexLastE = commandE.find("/", commandE.find("/") + 1);
	commandE.insert(indexLastE + 1, name);
	system(commandE.c_str());
}

void menu()
{
	int choise;
	string name;
	string nameE;
	cout << "1. Lists the available storage devices in the system.." << endl;
	cout << "2. Displaying available information about an individual device." << endl;
	cout << "3. Remove device." << endl;
	cout << "4. Output." << endl;
	cout << "Your choice: ";
	cin >> choise;
	switch (choise)
	{
	case 1:
		system("clear");
		outputListStorageDevices();
		break;
	case 2:
		system("clear");
		cout << "Enter disk name(Example sda): ";
		cin >> name;
		outputOneStorageDevice(name);
		break;
	case 3:
		system("clear");
		cout << "Enter disk name(Example sda): ";
		cin >> nameE;
		extraction(nameE);
		break;
	case 4:
		exit(0);
	}
}

int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		if (argv[1] == string("/?"))
		{
			cout << "Сreator: Ikonnikov Kirill Mikhailovich\nGroup student 'BI-31'\nAvailable options: /? \n";
			return 0;
		}
		else
		{
			cout << "Invalid parameter entered!\n";
			return 0;
		}
	}
	menu();
	return 0;
}
