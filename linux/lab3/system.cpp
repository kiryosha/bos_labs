#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Example: ./system program_name argument1 argument2 argument[n] \n";
		return 0;
	}
	if (argc == 2 && argv[1] == string("/?"))
	{
		cout << "Сreator: Ikonnikov Kirill Mikhailovich\nGroup student 'BI-31'\nAvailable options: /? [./exec program_name argument1 argument2 argument[n]]\n";
		return 0;
	}
	char command[128];
	strcpy(command, "./");
	for (int i = 1; i < argc; i++)
	{
		strcat(command, argv[i]);
		strcat(command, " ");
	}
	system(command);
	return 0;
}
