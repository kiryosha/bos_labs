#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main(int argc, char *argv[])
{

  setlocale(LC_ALL, "Russian");
  cout << "The parent program is running!";
  if (argc >= 2)
  {
    if (argv[1] == string("SW_SHOWMAXIMIZED"))
    {
        ShellExecute(NULL, "open", "child.exe", "I am child", NULL, SW_SHOWMAXIMIZED);
        return 0;
    }
    if (argv[1] == string("SW_SHOWMINIMIZED"))
    {
        ShellExecute(NULL, "open", "child.exe", "I am child", NULL, SW_SHOWMINIMIZED);
        return 0;
    }
    if (argv[1] == string("/?"))
    {
      cout << "Creator: ?????\nStudent of the group 'BI-31'\nAvailable option: /?, SW_SHOWMAXIMIZED, SW_SHOWMINIMIZED\n";
      return 0;
    }
    else if (argc > 2 || argv[1] != string("/?") || argv[1] != string("SW_SHOWMAXIMIZED") || argv[1] != string("SW_SHOWMINIMIZED"))
    {
      cout << "You entered the wrong parameter!\n";
      return 0;
    }
  }
  if(argc == 1)
  {
    ShellExecute (NULL, "open", "child.exe", "I am child", NULL, SW_SHOWNORMAL);
    return 0;
  }
}