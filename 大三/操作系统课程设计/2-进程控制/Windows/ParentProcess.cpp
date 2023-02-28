#include <windows.h>
#include <iostream>
using namespace std;

void printTime(SYSTEMTIME time)
{
    cout << time.wYear << "��" << time.wMonth << "��" << time.wDay << "��" << time.wHour << "ʱ" << time.wMinute << "��" << time.wSecond << "��" << time.wMilliseconds <<"����"<< endl;
}
void TimeCost(SYSTEMTIME Tbegin, SYSTEMTIME Tend)
{
    int day = Tend.wDay - Tbegin.wDay;
    int hour = Tend.wHour - Tbegin.wHour;
    int minute = Tend.wMinute - Tbegin.wMinute;
    int seconds = Tend.wSecond - Tbegin.wSecond;
    int milliseconds = Tend.wMilliseconds - Tbegin.wMilliseconds;
    if (milliseconds < 0) { seconds--; milliseconds += 1000; }
    if (seconds < 0) { minute--; seconds += 60; }
    if (minute < 0) { hour--; minute += 60; }
    if (hour < 0) { day--; hour += 24; }
    cout << "�ӽ��̺�ʱ" << day << "��" << hour << "ʱ" << minute << "��" << seconds << "��" << milliseconds << "����" << endl;
}
int main(int argc, char* argv[])
{
    STARTUPINFO si;   //�洢�½���������Ϣ��ָ��
    PROCESS_INFORMATION pi;  //�洢�½�����Ϣ�������
    SYSTEMTIME childpStart, childpEnd;
    memset(&si, 0, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    memset(&pi, 0, sizeof(PROCESS_INFORMATION));

    //��������
    if (CreateProcess(NULL, argv[1], NULL, NULL, false, false, NULL, NULL, &si, &pi)){
        GetSystemTime(&childpStart);
        cout << "Successfully created child process in ";
        printTime(childpStart);
    }
    else {
        cout << "Failed to create child process" << endl;
        exit(1);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    GetSystemTime(&childpEnd);
    cout << "Successfully closed child process in ";
    printTime(childpEnd);
    TimeCost(childpStart, childpEnd);
    return 0;
}
