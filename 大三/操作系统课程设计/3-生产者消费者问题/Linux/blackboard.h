#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
// 4��������
const int buffer_size = 4;
// �ź���id
const int empty_id = 0;
const int full_id = 1;
const int mutex_id = 2;
// �������ռ���нṹ�壺������ݵ������ͷβָ�롢�Ƿ�Ϊ��
struct shared_memory_buffer_data {
	int head;
	int tail;
	bool isEmpty;
	char buffer[buffer_size];
};
// �Զ���һ�����ڳ�ʼ���ź�����union semun
union semun {
	int val;
	struct semid_ds* buf;
	unsigned short* array;
};