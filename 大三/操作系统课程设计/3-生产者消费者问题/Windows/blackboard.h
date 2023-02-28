#include <windows.h>
#include <tchar.h>

// �����ڴ��С 2048 �ֽ�
const int shared_memory_size = 2048;
// �������ļ���
TCHAR file_name[] = TEXT("Buffer");
// 4��������
const int buffer_size = 4;
// 3��������
const int producer_process_headid = 1;
const int producer_process_tailid = 3;
// 4��������
const int consumer_process_headid = 4;
const int consumer_process_tailid = 7;
// ������һ����7
const int process_total = 7;
// �ź�����
TCHAR sem_empty[] = TEXT("Empty");
TCHAR sem_full[] = TEXT("Full");
TCHAR sem_mutex[] = TEXT("Mutex");
// �����ߣ������ߵĳ�����
TCHAR producer_exe_name[] = TEXT("producer.exe");
TCHAR consumer_exe_name[] = TEXT("consumer.exe");
// �������������ӽ��̡��̵߳ľ������
HANDLE created_process_handles[process_total + 1];
HANDLE created_thread_handles[process_total + 1];
// �������ռ���нṹ�壺������ݵ������ͷβָ�롢�Ƿ�Ϊ��
struct shared_memory_buffer_data{
	int head;
	int tail;
	bool isEmpty;
	char buffer[buffer_size];
};
// �����������ṹ��
struct shared_memory{
	shared_memory_buffer_data space;
	HANDLE semaphore_full;
	HANDLE semaphore_empty;
	HANDLE semaphore_mutex;
};
