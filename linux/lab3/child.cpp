#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	int i;
	if(string(argv[0]) == "./exec" || string(argv[0]) == "./fork" ) i = 1;
	if(string(argv[0]) == "./child") i = 0;
	cout << "Child program is running..." << endl;
	cout << "The " << argv[0]<< " program is running and received arguments: " << endl;
	while(argv[i++] != NULL)
		cout << argv[i] << endl;
	return 0;
}
