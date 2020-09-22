#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	for(int i = 0; i < argc; i++)
		cout << argv[i] << " ";
	cout << endl;
	system("pause");
}