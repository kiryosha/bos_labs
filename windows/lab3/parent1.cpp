#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>

using namespace std;

int main(int argc, char *argv[])
{

  setlocale(LC_ALL, "Russian");
  if (argc >= 2)
  {
    if (argv[1] == string("/?"))
    {
      cout << "Creator: ?????\nStudent of the group 'BI-31'\nAvailable option: /?\n";
      return 0;
    }
    else if (argc > 2 || argv[1] != string("/?"))
    {
      cout << "Incorrect parameter entered!\n";
      return 0;
    }
  }
  cout << "The parent program is running!";
  _execl("child.exe", "I", "am", "child!", NULL);
}