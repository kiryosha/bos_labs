#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

using namespace std;

void searchFunction()
{
	int ch = -1;
	int contWords = 0;
	int countLine = 1;
	int countSymbols = 0;
	int lenthWord = 0;
	string temp = " ,.-:;!\n/";

	while (true)
	{
		ch = getchar();
		if (ch == EOF)
		{
			if (lenthWord > 1) contWords++;
			break;
		}
		if (ch == '\n') countLine++;
		else
		{
			countSymbols++;
			if (temp.find(ch) == -1 && !isdigit(ch)) lenthWord++;
		}
		if (lenthWord >= 1 && temp.find(ch) != -1)
		{
			if (lenthWord > 1) contWords++;
			lenthWord = 0;
		}
	}
	cout << endl << "Number of characters: " << countSymbols << "\nWord Count: " << contWords << "\nNumber of lines: " << countLine << endl;
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
	searchFunction();
	return 0;
}