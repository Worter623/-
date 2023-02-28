#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int PriorityQueue[10000];
//�Ѷ�Ԫ����С
//�ϸ�ǰsize�Ѿ�+1
void PercolateUp(int PriorityQueue[], int size,int insert_element)
{
	int i;
	for (i = size; PriorityQueue[i / 2] > insert_element; i /= 2)
		PriorityQueue[i] = PriorityQueue[i / 2];
	PriorityQueue[i] = insert_element;
}

void PercolateDown(int PriorityQueue[], int begin, int size)
{
	int temp = PriorityQueue[begin], child;
	for (child = 2*begin; child <= size;child*=2)
	{
		if (child < size && PriorityQueue[child + 1] < PriorityQueue[child])
			child++;//�ҳ����Һ����и�С���Ǹ�
		if (temp <= PriorityQueue[child])
			break;//����ø��ױ����Һ��Ӷ�С�����Ѿ�ȷ�����˸ø���Ҫ���˵�λ��
		PriorityQueue[begin] = PriorityQueue[child];//�Ѻ��ӷŵ����׵�λ��
		begin = child;
	}
	PriorityQueue[begin] = temp;//���׷ŵ����˵�λ��
}
