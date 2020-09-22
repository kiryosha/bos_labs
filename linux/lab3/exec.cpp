#include <stdio.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Example: ./exec program_name argument1 argument2 argument[n] \n";
		return 0;
	}
	if (argc == 2 && argv[1] == string("/?"))
	{
		cout << "Сreator: Ikonnikov Kirill Mikhailovich\nGroup student 'BI-31'\nAvailable options: /? [./exec program_name argument1 argument2 argument[n]]\n";
		return 0;
	}
	execv(argv[1], argv);
	return 0;
}
