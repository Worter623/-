#include <windows.h>
#include <iostream>
#include <time.h>
#include "blackboard.h"
using namespace std;

// ��ʽ����ӡʱ��
void printTime(SYSTEMTIME time)
{
	cout << time.wYear << "��" << time.wMonth << "��" << time.wDay << "��" << time.wHour << "ʱ" << time.wMinute << "��" << time.wSecond << "��" << time.wMilliseconds << "����" << endl;
}
//�������ʱ��
int setDelay()
{
	srand(time(NULL) + GetCurrentProcessId());
	return rand() % 3 + 1;
}
//�����������ĸ
char setCharacter()
{
	srand(time(NULL) + GetCurrentProcessId());
	char t[] = { 'G','X','Y' };
	return t[rand() % 3];
}
int main()
{
	char producer_character;
	SYSTEMTIME current_time;
	HANDLE producer_shared_file_handle;
	LPVOID producer_map_view_of_file;
	//��ȡ����ӳ���ļ�
	producer_shared_file_handle = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, file_name);
	if (producer_shared_file_handle == NULL)
	{
		cout << "OpenFileMapping����  " << GetLastError() << endl;
		return 0;
	}
	producer_map_view_of_file = MapViewOfFile(producer_shared_file_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (producer_map_view_of_file == NULL)
	{
		cout << "MapViewOfFile����  " << GetLastError() << endl;
		CloseHandle(producer_shared_file_handle);
		return 0;
	}
	//��ȡ����������Ϣ
	shared_memory* producer_shared_memory = (struct shared_memory*)producer_map_view_of_file;
	HANDLE producer_empty = OpenSemaphore(SEMAPHORE_ALL_ACCESS,FALSE, sem_empty);
	HANDLE producer_full = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, sem_full);
	HANDLE producer_mutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, sem_mutex);
	//����4��
	for (int i = 0; i < 4; i++)
	{
		int delay=setDelay() * 1000;
		Sleep(delay);
		//P(empty),P(mutex)
		WaitForSingleObject(producer_empty, INFINITE);
		WaitForSingleObject(producer_mutex, INFINITE);
		//write
		producer_character = setCharacter();
		int current_tail = producer_shared_memory->space.tail;
		producer_shared_memory->space.buffer[current_tail] = producer_character;
		producer_shared_memory->space.tail = (current_tail + 1) % buffer_size;
		producer_shared_memory->space.isEmpty = false;
		GetSystemTime(&current_time);
		cout << "������" << GetCurrentProcessId() << "������������д����ĸ" << producer_character << "��";
		printTime(current_time);
		cout << "������������Ϊ";
		current_tail = producer_shared_memory->space.tail;
		if (producer_shared_memory->space.isEmpty == true)
			cout << "��" << endl;
		else{
			int j = (current_tail - 1 >= producer_shared_memory->space.head) ? (current_tail - 1):(current_tail - 1 + buffer_size);
			for (j; j >= producer_shared_memory->space.head; j--)
			{
				cout << producer_shared_memory->space.buffer[j % buffer_size];
			}
			cout << endl;
		}
		//V(mutex),V(full)
		ReleaseSemaphore(producer_mutex,1,NULL);
		ReleaseSemaphore(producer_full, 1,NULL);
	}
	//�ر��ļ�ӳ����ͼ�͹���������
	UnmapViewOfFile(producer_map_view_of_file);
	producer_shared_memory = NULL;
	CloseHandle(producer_shared_file_handle);
	return 0;
}
