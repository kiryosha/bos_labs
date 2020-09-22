#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void outputInfoService(string nameService)
{
	string line;
	string command = "systemctl status ";
	command += nameService;
	command += " > tempService.txt";
	system(command.c_str());
	ifstream in("tempService.txt");
	cout << "Name: " << nameService << endl;
	if (in.is_open())
    {
        while (getline(in, line))
        {
        	int indexFullName = line.find("- ");
        	if(indexFullName != -1)
        		cout << "Full name: " << line.substr(indexFullName + 2) << endl;
        	string act = "Active: ";
        	int indexStatus = line.find(act);
        	if(indexStatus != -1)
        		cout << "Status: " << line.substr(indexStatus + act.length()) << endl;
        }
    }
    in.close();
    remove("tempService.txt");
    cout << endl;
}

vector<string> readFileService()
{
	string line;
	vector<string> nameService;
	system("systemctl list-unit-files --type=service --all > service.txt");
	ifstream in("service.txt");
    if (in.is_open())
    {
        while (in >> line)
        {
        	int index = line.find(".");
        	if(index != -1 && line.find("@") == -1)
        	{
        		string temp;
        		for (int i = 0; i < index; i++)
        			temp += line[i];
        		nameService.push_back(temp);
        	}
        }
    }
    in.close();
    remove("service.txt");
    return nameService;
}

bool isUint(const string& s){
    return s.find_first_not_of("0123456789") == string::npos;
}

void outputInfoModules(string nameModule)
{
	string line;
	string command = "modinfo ";
	command += nameModule;
	command += " > tempModule.txt";
	system(command.c_str());
	ifstream in("tempModule.txt");
	cout << "Name: " << nameModule << endl;
	if (in.is_open())
    {
        while (getline(in, line))
        {
        	string act = "description:    ";
        	int indexStatus = line.find(act);
        	if(indexStatus != -1)
        		cout << "Full name: " << line.substr(indexStatus + act.length()) << endl;
        }
    }
    in.close();
    remove("tempModule.txt");
    cout << endl;
}

vector<string> readFileModule()
{
	int i = 0;
	string line;
	vector<string> nameModule;
	system("lsmod > modules.txt");
	ifstream in("modules.txt");
    if (in.is_open())
    {
        while (in >> line)
        {
        	if(!isUint(line) && i >= 4)
        		nameModule.push_back(line);
        	i++;
        }
    }
    in.close();
    remove("modules.txt");
    return nameModule;
}

int main(int argc, char* argv[])
{
	if (argc >= 2)
    {
        if (argv[1] == string("/?"))
        {
            cout << "Creator: Ikonnikov K. M.\nStudent of the group 'BI-31'\nAvailable options: /? /d /i <name_service>\n";
            return 0;
        }
        if(argv[1] == string("/d"))
        {
            vector<string> nameModule = readFileModule();
            for (int i = 0; i < nameModule.size(); ++i)
				outputInfoModules(nameModule[i]);
            return 0;
        }
    }
    if(argc == 3)
    {
        if(argv[1] == string("/i"))
        {
        	string command = "modinfo ";
        	command += string(argv[2]);
        	system(command.c_str());
        	command = "systemctl status ";
        	command += string(argv[2]);
        	command += " --no-pager";
        	system(command.c_str());
            return 0;
        }
    }
    if(argc == 1)
    {
        vector<string> nameService = readFileService();
        for (int i = 0; i < nameService.size(); ++i)
			outputInfoService(nameService[i]);
        return 0;
    }
	return 0;
}
