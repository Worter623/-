#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <Psapi.h>
#include <conio.h>
#include <TlHelp32.h> //ʹ��PROCESSENTRY32�ṹ��
#include <tchar.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
using namespace std;

void ShowHelp() {
	system("cls");
	cout << "����һ���ڴ���ӳ���" << endl;
	cout << "���롮space_plot����ȡϵͳ��ַ�ռ䲼��" << endl;
	cout << "���롮memory_used����ȡ�����ڴ�ʹ�����" << endl;
	cout << "���롮process_state�����ҵ�ʵ�����ִ���ļ����鿴����ʵʱ�����ַ�ռ䲼�ֺ͹�������Ϣ" << endl;
	//������ �������������ִ���ļ� �˴�Ϊ�����ҵҪ����ʹ��CreateProcess���ӽ�����
	cout << "���롮ctrl+C�����ߡ�quit������ֹ�ó���" << endl;
	cout << "��������Է������˵�" << endl;
	while (!_kbhit());
	return;
}
void ShowSpacePlot() {
	while (!_kbhit())
	{
		system("cls");
		SYSTEM_INFO system_info;
		PERFORMACE_INFORMATION performance_information;
		performance_information.cb = sizeof(performance_information);
		GetPerformanceInfo(&performance_information, performance_information.cb);
		GetSystemInfo(&system_info);
		cout << "----------��ַ�ռ䲼��----------" << endl;
		cout << "�ڴ�����Ϊ" << performance_information.KernelTotal << endl;
		cout << "�ڴ�ҳ�Ĵ�СΪ��" << performance_information.PageSize / 1024 << "KB" << endl;
		cout << "��ҳ�ص�ǰ��СΪ��" << performance_information.KernelPaged << endl;
		cout << "�Ƿ�ҳ�ص�ǰ��СΪ��" << performance_information.KernelNonpaged << endl;
		cout << "ÿ�����̿��õ�ַ�ռ����С�ڴ��ַΪ��   0x" << system_info.lpMinimumApplicationAddress << endl;
		cout << "ÿ�����̿��õ�ַ�ռ������ڴ��ַΪ��   0x" << system_info.lpMaximumApplicationAddress << endl;
		cout << "ϵͳ�䱸��CPU������Ϊ��" << system_info.dwNumberOfProcessors << endl;
		cout << "�ܹ�������ַ�ռ��������С��λΪ��" << system_info.dwAllocationGranularity / 1024 << "KB" << endl;
		cout << "----------��������Է������˵�----------" << endl;
		Sleep(1000);
	}
}
void ShowMemoryUsed() {
	while (!_kbhit())
	{
		system("cls");
		MEMORYSTATUSEX memory_status;
		PERFORMACE_INFORMATION performance_information;
		memory_status.dwLength = sizeof(memory_status);
		performance_information.cb = sizeof(performance_information);
		GetPerformanceInfo(&performance_information, performance_information.cb);
		GlobalMemoryStatusEx(&memory_status);
		cout << "----------�����ڴ�ʹ�����----------" << endl;
		cout << "�ڴ��������Ϊ��" << (float)memory_status.ullTotalPhys / 1024 / 1024 / 1024 << "GB" << endl;
		cout << "��ǰ���õ������ڴ�Ϊ��" << performance_information.PhysicalAvailable << endl;
		cout << "�ڴ��ʹ����Ϊ��" << memory_status.dwMemoryLoad << "%" << endl;
		cout << "ϵͳ���������Ϊ��" << performance_information.SystemCache << endl;
		cout << "ҳ�ļ���������Ϊ��" << (float)memory_status.ullTotalPageFile / 1024 / 1024 / 1024 << "GB" << endl;
		cout << "ϵͳ��ǰ�ύҳ������Ϊ��" << performance_information.CommitTotal << endl;
		cout << "���õ�ҳ�ļ�Ϊ��" << (float)memory_status.ullAvailPageFile / 1024 / 1024 / 1024 << "GB" << endl;
		cout << "�����ڴ��������Ϊ��" << (float)memory_status.ullTotalVirtual / 1024 / 1024 / 1024 << "GB" << endl;
		cout << "���õ������ڴ�Ϊ��" << (float)memory_status.ullAvailVirtual / 1024 / 1024 / 1024 << "GB" << endl;
		cout << "���õ���չ�����ڴ�Ϊ��" << (float)memory_status.ullAvailExtendedVirtual / 1024 << "KB" << endl;
		cout << "��ǰ�򿪵ľ������Ϊ��" << performance_information.HandleCount << endl;
		cout << "��ǰ���̸���Ϊ��" << performance_information.ProcessCount << endl;
		cout << "��ǰ�̸߳���Ϊ��" << performance_information.ThreadCount << endl;
		cout << "----------��������Է������˵�----------" << endl;
		Sleep(1000);
	}
}
HANDLE FilenameToHandle(WCHAR filename[]){
	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(process_entry);
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	bool ok = Process32First(hProcess, &process_entry);
	bool flag = false;
	if (!ok) {
		cout << "process32first failed" << endl;
		return NULL;
	}
	while (ok)
	{
		if (wcscmp(process_entry.szExeFile, filename) == 0) {
			flag = true;
			break;
		}
		ok = Process32Next(hProcess, &process_entry);
	}//�õ���filename�Ľ��̾��
	CloseHandle(hProcess);
	if (flag)
		return (OpenProcess(PROCESS_ALL_ACCESS, false, process_entry.th32ProcessID));
	else
		return NULL;
}
void ShowProcessState() {
	while (!_kbhit())
	{
		system("cls");
		cout << "----------�鿴ParentProcess������ռ䲼�ֺ͹�������Ϣ----------" << endl;
		WCHAR filename[20] = { '\0' };
		wcscpy_s(filename, L"ParentProcess.exe");
		HANDLE hProcess = FilenameToHandle(filename);
		if (hProcess == NULL) {
			cout << "�����ѽ���" << endl;
			continue;
		}
		MEMORY_BASIC_INFORMATION memory_basic_information;
		memset(&memory_basic_information, 0, sizeof(MEMORY_BASIC_INFORMATION));
		PROCESS_MEMORY_COUNTERS process_memory_counters;
		SYSTEM_INFO system_info;
		GetSystemInfo(&system_info);
		GetProcessMemoryInfo(hProcess, &process_memory_counters, sizeof(process_memory_counters));
		LPCVOID block_counter = system_info.lpMinimumApplicationAddress;
		cout << "��������Ϣ��" << (float)process_memory_counters.WorkingSetSize / 1024 << "KB" << endl;
		for (; block_counter < system_info.lpMaximumApplicationAddress;)
		{
			if (VirtualQueryEx(hProcess, block_counter, &memory_basic_information, sizeof(memory_basic_information)) == sizeof(memory_basic_information)) 
			{//���ȵ�ȷ��
				 //confirmed,��ѯ��ַ�ռ����ڴ��ַ����Ϣ  //�����Ľ�β���䳤��
				LPCVOID page_end = (PBYTE)block_counter + memory_basic_information.RegionSize;//ҳ����ַ+�������С
				TCHAR size[MAX_PATH];
				StrFormatByteSize(memory_basic_information.RegionSize, size, MAX_PATH);//��ʽ���ļ��Ĵ�С
				cout << "���ַ��   " << (DWORD)block_counter << "--" << (DWORD)page_end << "(" << size << ")     ";
				if(memory_basic_information.State==MEM_COMMIT)
					cout << "���ύ";
				else if (memory_basic_information.State == MEM_FREE)
					cout << "���е�";
				else if (memory_basic_information.State == MEM_RESERVE)
					cout << "������";
				if (memory_basic_information.Type == MEM_IMAGE)
					cout << ",Image";
				else if (memory_basic_information.Type == MEM_PRIVATE)
					cout << ",Private";
				else if (memory_basic_information.Type == MEM_MAPPED)
					cout << ",Mapped";
				cout << endl;
				block_counter = page_end; //�ƶ�ָ���Ի����һ����
			}
		}
		Sleep(3000);
	}
}
int main()
{
	while (1)
	{
		system("cls");
		cout << "-----�ڴ���ӳ���-----" << endl;
		cout << "���롮help���ɻ�ȡ����" << endl;
		string input;
		cin >> input;
		if (input == "help")
			ShowHelp();
		else if (input == "space_plot")
			ShowSpacePlot();
		else if (input == "memory_used")
			ShowMemoryUsed();
		else if (input == "process_state")
			ShowProcessState();
		else if (input == "quit")
			break;
	}
	return 0;
}