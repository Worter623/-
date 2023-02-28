#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
/* father[x]��ʾx�ĸ��ڵ� */
int father[100];
typedef struct
{
	int x, y;
	int w;
}edge;
edge e[100];

/* �ȽϺ�������Ȩֵ(��ͬ��x����)�������� */
int cmp(const void* a, const void* b) {
	if ((*(edge*)a).w == (*(edge*)b).w)
		return (*(edge*)a).x - (*(edge*)b).x;
	return (*(edge*)a).w - (*(edge*)b).w;
}
int find(int x) {
	if (x != father[x])
		father[x] = find(father[x]);
	return father[x];
}
/* �жϼ����Ƿ���ͬ */
int Is_same(int i, int j) {
	//�ҵ�i�ĸ��ڵ�
	int fx = find(i), fy = find(j);
	if (fx != fy) {
		father[fx] = fy;
		return 1;
	}
	return 0;
}

//��ʼ�� father���� 
void Initialize(int n) {
	for (int i = 1; i < n + 1; i++)
		father[i] = i;
}

int main()
{
	int i = 0, m, n, count = 0, sum = 0;
	int record[100];
	edge temp;
	cin >> n >> m;
	for (i = 0; i < m; i++) {
		cin >> temp.x >> temp.y >> temp.w;
		e[i] = temp;
	}
	qsort(e, m, sizeof(edge), cmp);
	Initialize(n);
	for (i = 0; i < m; i++) {
		if (Is_same(e[i].x, e[i].y)) {
			if (count == n)
				break;
			sum += e[i].w;
			record[count++] = i;
		}
	}
	if (count < n - 1)
		cout << "-1" << endl;
	else{
		for(i=0;i<count;i++)
			cout << e[record[i]].x << " " << e[record[i]].y << endl;
		cout << sum << endl;
	}
	return 0;
}
