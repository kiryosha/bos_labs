#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

void full_info(wstring name_s)
{
    SERVICE_STATUS_PROCESS stat;
    LPQUERY_SERVICE_CONFIG lpqscBuf;
    DWORD dwBytesNeeded, buf_size = 0;
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    SC_HANDLE schService = OpenService(hSCM, name_s.c_str(), SERVICE_QUERY_CONFIG);
    SC_HANDLE svc = OpenService(hSCM, name_s.c_str(), SC_MANAGER_ALL_ACCESS);
    lpqscBuf = (LPQUERY_SERVICE_CONFIG)LocalAlloc(LPTR, 4096);
    QueryServiceConfig(schService, lpqscBuf, 4096, &dwBytesNeeded);
    QueryServiceStatusEx(svc, SC_STATUS_PROCESS_INFO, (BYTE*)&stat, sizeof stat, &buf_size);

    if(lpqscBuf->lpDisplayName != NULL)
    {
        wcout << "Short name: " << name_s << "\nLong name: " << lpqscBuf->lpDisplayName << endl;

        if (lpqscBuf->dwServiceType == 0x1)
            cout << "Type of service: Kernel Driver.\n";
        if (lpqscBuf->dwServiceType == 0x2)
            cout << "Type of service: Driver service.\n";
        if (lpqscBuf->dwServiceType == 0x8)
            cout << "Type of service: Recognizer Driver.\n";
        if (lpqscBuf->dwServiceType == 0x10)
            cout << "Type of service: Win32 Own Process.\n";
        if (lpqscBuf->dwServiceType == 0x20)
            cout << "Type of service: Win32 Share Process.\n";
        if (lpqscBuf->dwServiceType == 0x110)
            cout << "Type of service: Interactive Own Process\n";
        if (lpqscBuf->dwServiceType == 0x120)
            cout << "Type of service: Interactive Share Process\n";
        if (lpqscBuf->dwServiceType == 0x30)
            cout << "Type of service: WIN32\n";
        if (lpqscBuf->dwServiceType == 0x210)
            cout << "Type of service: Win32 packaged process\n";
        if (lpqscBuf->dwServiceType == 0xf0)
            cout << "Type of service: ERROR\n";
        if (lpqscBuf->dwServiceType == 0xe0)
            cout << "Type of service: User_share_process instance\n";

        if (lpqscBuf->dwStartType == 0x00)
            cout << "Start typee: Boot\n";
        if (lpqscBuf->dwStartType == 0x01)
            cout << "Start typee: System\n";
        if (lpqscBuf->dwStartType == 0x02)
            cout << "Start typee: Autoload\n";
        if (lpqscBuf->dwStartType == 0x03)
            cout << "Start typee: Manual\n";
        if (lpqscBuf->dwStartType == 0x04)
            cout << "Start typee: Disabled\n";


        if (stat.dwCurrentState == SERVICE_STOPPED)
            cout << "Status: has stopped.\n";
        if (stat.dwCurrentState == SERVICE_RUNNING)
            cout << "Status: is running.\n";
        if (stat.dwCurrentState == SERVICE_STOP_PENDING)
            cout << "Status: is stopping.\n";
        if (stat.dwCurrentState == SERVICE_STOP_PENDING)
            cout << "Status: is starting.\n";
        if (stat.dwCurrentState == SERVICE_PAUSED)
            cout << "Status: is paused.\n";
        if (stat.dwCurrentState == SERVICE_PAUSE_PENDING)
            cout << "Status: is pausing.\n";
        if (stat.dwCurrentState == SERVICE_CONTINUE_PENDING)
            cout << "Status: is about to continue.\n";
        cout << "PID: " << stat.dwProcessId << endl;
        LocalFree(lpqscBuf);
    }
    else
    {
        cout << "There is no such service!" << endl;
    }
}


void sd(DWORD dwServiceType, string sd)
{
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE);
    DWORD bufferSize = 0;
    DWORD requiredBufferSize = 0;
    DWORD totalServicesCount = 0;
    SERVICE_STATUS_PROCESS ssStatus;

    EnumServicesStatusEx(
        hSCM,
        SC_ENUM_PROCESS_INFO,
        dwServiceType,
        SERVICE_STATE_ALL,
        NULL,
        bufferSize,
        &requiredBufferSize,
        &totalServicesCount,
        NULL,
        NULL);

    vector<BYTE> buffer(requiredBufferSize);
    EnumServicesStatusEx(hSCM,
        SC_ENUM_PROCESS_INFO,
        dwServiceType,
        SERVICE_STATE_ALL,
        buffer.data(),
        buffer.size(),
        &requiredBufferSize,
        &totalServicesCount,
        NULL,
        NULL);

    LPENUM_SERVICE_STATUS_PROCESS services = reinterpret_cast<LPENUM_SERVICE_STATUS_PROCESS>(buffer.data());
    for (unsigned int i = 0; i < totalServicesCount; ++i)
    {
        SERVICE_STATUS_PROCESS ssStatus;
        ENUM_SERVICE_STATUS_PROCESS service = services[i];
        ssStatus = service.ServiceStatusProcess;

        cout << endl;
        wcout << "Short name: " << service.lpServiceName << "\nLong name: " << service.lpDisplayName;
        if (ssStatus.dwCurrentState == SERVICE_STOPPED)
            cout << "\nStatus: " << sd << " has stopped.\n";
        if (ssStatus.dwCurrentState == SERVICE_RUNNING)
            cout << "\nStatus: " << sd << " is running.\n";
        if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
            cout << "\nStatus: " << sd << " is stopping.\n";
        if (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
            cout << "\nStatus: " << sd << " is starting.\n";
        if (ssStatus.dwCurrentState == SERVICE_PAUSED)
            cout << "\nStatus: " << sd << " is paused.\n";
        if (ssStatus.dwCurrentState == SERVICE_PAUSE_PENDING)
            cout << "\nStatus: " << sd << " is pausing.\n";
        if (ssStatus.dwCurrentState == SERVICE_CONTINUE_PENDING)
            cout << "\nStatus: " << sd << " is about to continue.\n";
    }

    (void)CloseServiceHandle(hSCM);
}

wstring s2ws(const string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
  
    if (argc >= 2)
    {
        if (argv[1] == string("/?"))
        {
            cout << "Creator: ?????\nStudent of the group 'BI-31'\nAvailable options: /? /d /i <name_service>\n";
            return 0;
        }
        if(argv[1] == string("/d"))
        {
            system("cls");
            sd(SERVICE_DRIVER, "Driver");
            system("pause");
            return 0;
        }
    }
    if(argc == 3)
    {
        if(argv[1] == string("/i"))
        {
            system("cls");
            wstring name_sw = s2ws(argv[2]);
            full_info(name_sw);
            system("pause");
            return 0;
        }
    }
    if(argc == 1)
    {
        system("cls");
        sd(SERVICE_WIN32, "Service");
        system("pause");
        return 0;
    }
    if(argc > 3)
        cout << "Available options: /? /d /i" << endl;
    system("pause");
	return 0;
}