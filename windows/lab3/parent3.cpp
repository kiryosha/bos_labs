#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	STARTUPINFO sti = { 0 };
	PROCESS_INFORMATION pi = { 0 };
	setlocale(LC_ALL, "Russian");
  	if (argc >= 2)
  	{
    	if (argv[1] == string("/?"))
    	{
      		cout << "Creator: ????\nStudent of the group 'BI-31'\nAvailable option: /?\n";
      		return 0;
    	}	
    	else if (argc > 2 || argv[1] != string("/?"))
    	{
      		cout << "You entered the wrong parameter!\n";
      		return 0;
    	}
  	}
  	if(argc == 1)
  	{
		cout << "The parent program is running!";
		CreateProcess(NULL, "child.exe I am child", NULL, NULL, FALSE, 0, NULL, NULL, &sti, &pi);
		return 0;
	}
}