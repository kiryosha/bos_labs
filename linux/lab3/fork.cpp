#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "Example: ./fork program_name argument1 argument2 argument[n] \n";
		return 0;
	}
	if (argc == 2 && argv[1] == string("/?"))
	{
		cout << "Сreator: Ikonnikov Kirill Mikhailovich\nGroup student 'BI-31'\nAvailable options: /? [./exec program_name argument1 argument2 argument[n]]\n";
		return 0;
	}
	pid_t pid;
	int status;

	switch(pid = fork())
	{
		case -1:
		{
			perror("fork");
			exit(1);
		}
		case 0:
		{
			cout << "This is child!\nMy PID: " << getpid() << "\nParent PID " << getppid() << endl << endl;
			execv(argv[1], argv);
			exit(0);
		}
		default:
		{
			cout << "This is parent!\nMy PID: " << getpid() << "\nChild PID " << pid << endl << endl;
			wait(&status);
			exit(0);
		}
	}
	return 0;
}
