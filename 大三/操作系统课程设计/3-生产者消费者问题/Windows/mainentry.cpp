#include <windows.h>
#include <iostream>
#include "blackboard.h"
using namespace std;

// ��ʽ����ӡʱ��
void printTime(SYSTEMTIME time)
{
	cout << time.wYear << "��" << time.wMonth << "��" << time.wDay << "��" << time.wHour << "ʱ" << time.wMinute << "��" << time.wSecond << "��" << time.wMilliseconds << "����" << endl;
}
// ��������
bool CreateProcess(int process_id)
{
	bool create_process_ok;
	SYSTEMTIME c_time;
	STARTUPINFO si;   //�洢�½���������Ϣ��ָ��
	PROCESS_INFORMATION pi;  //�洢�½�����Ϣ�������
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));

	if (process_id >= producer_process_headid && process_id <= producer_process_tailid)
	{//����������
		create_process_ok = CreateProcess(producer_exe_name, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (!create_process_ok)
		{
			cout << "������" << process_id << "��������  " << GetLastError() << endl;
			return false;
		}
		GetSystemTime(&c_time);
		cout << "������" << process_id << "��PIDΪ"<<GetProcessId(pi.hProcess)<<"�����ɹ���";
		printTime(c_time);
	}
	else {//����������
		create_process_ok = CreateProcess(consumer_exe_name, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		if (!create_process_ok)
		{
			cout << "������" << process_id << "��������  " << GetLastError() << endl;
			return false;
		}
		GetSystemTime(&c_time);
		cout << "������" << process_id << "��PIDΪ"<<GetProcessId(pi.hProcess)<<"�����ɹ���";
		printTime(c_time);
	}
	created_process_handles[process_id] = pi.hProcess;
	created_thread_handles[process_id] = pi.hThread;
	return true;
}

int main()
{
	int i = 1;
	SYSTEMTIME current_time;
	HANDLE shared_file_handle;
	LPVOID map_view_of_file;

	//����ʼ ��ӡ
	GetSystemTime(&current_time);
	cout << "������ʼ�� : ";
	printTime(current_time);

	//�ڽ����д���һ���ļ�ӳ�����ģ�⹲���ڴ���
	shared_file_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, shared_memory_size, file_name);
	if (shared_file_handle == NULL)
	{
		cout << "CreateFileMapping����  " << GetLastError() << endl;
		return 0;
	}
	//���ļ�ӳ���ϴ�������ӳ�䣬ӳ�䵽�������������ַ�ռ䣬����ӳ����ͼ�ļ��Ŀ�ʼ��ֵַ
	map_view_of_file = MapViewOfFile(shared_file_handle, FILE_MAP_ALL_ACCESS, 0, 0, shared_memory_size);
	if (map_view_of_file == NULL)
	{
		cout << "MapViewOfFile����  " << GetLastError() << endl;
		CloseHandle(shared_file_handle);
		return 0;
	}
	//ӳ����ͼ�ļ��Ŀ�ʼ��ֵַ����Ϊ���������Ŀ�ʼ��ַ ��ʼ����������
	shared_memory* p_shared_memory = (struct shared_memory*)map_view_of_file;
	p_shared_memory->space.head = 0;
	p_shared_memory->space.tail = 0;
	p_shared_memory->space.isEmpty = true;
	HANDLE semaphore_empty = CreateSemaphore(NULL, buffer_size, buffer_size, sem_empty);
	HANDLE semaphore_full = CreateSemaphore(NULL, 0, buffer_size, sem_full);
	HANDLE semaphore_mutex = CreateSemaphore(NULL, 1, 1, sem_mutex);
	//��������
	while (i < process_total + 1) {
		bool ok = CreateProcess(i++);
		if (!ok)
		{
			CloseHandle(shared_file_handle);
			return 0;
		}
	}
	//�ȴ��ӽ��̷���
	for (int j = 1; j < process_total + 1; j++) {
		WaitForSingleObject(created_process_handles[j], INFINITE);
		CloseHandle(created_process_handles[j]);
		CloseHandle(created_thread_handles[j]);
	}
	//�ر��ļ�ӳ���ϵ���ͼ��ռ��
	UnmapViewOfFile(map_view_of_file);
	p_shared_memory = NULL;
	CloseHandle(shared_file_handle);
	GetSystemTime(&current_time);
	cout << "����������� : ";
	printTime(current_time);
	return 0;
}
