#include <iostream>
#include <vector>
using namespace std;

int H, W, M, N,centerx,centery;
vector<vector<int>> src;
vector<vector<int>> dst;
vector<vector<int>> result;

bool CorrodeJudge(int x, int y) {
	bool flag = false;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (x - centerx + i >= 0 && y - centery + j >= 0 && x - centerx + i < H && y - centery + j < W)
				if (src[x - centerx + i][y - centery + j] == 0)
				{//�����һ����Ϊ0 ����ʴ
					flag = true;
					break;
				}
		}
		if (flag)
			break;
	}
	return flag;
}

bool SwellJudge(int x, int y) {
	bool flag = false;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (x - centerx + i >= 0 && y - centery + j >= 0 && x - centerx + i < H && y - centery + j < W)
				if (dst[x - centerx + i][y - centery + j] == 255)
				{//�����һ����Ϊ255 ������
					flag = true;
					break;
				}
		}
		if (flag)
			break;
	}
	return flag;
}

int main()
{
	cin >> N >> M >> H >> W;
	centerx = N / 2 + 1;
	centery = M / 2 + 1;
	vector<int> temp;
	int dot;
	//����src
	for (int i = 0; i < H; i++){
		for (int j = 0; j < W; j++){
			cin >> dot;
			temp.push_back(dot);
		}
		src.push_back(temp);
		vector<int>().swap(temp);
	} 
	//��ʴ ��dst��
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (src[i][j]) {//�Ҷ�ֵΪ1����Ϊ0��
				if (CorrodeJudge(i, j))//�õ����ʴ
					temp.push_back(0);
				else
					temp.push_back(src[i][j]);
			}
			else
				temp.push_back(src[i][j]);
		}
		dst.push_back(temp);
		vector<int>().swap(temp);
	}
	//���� ��result��
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (!dst[i][j]) {//�Ҷ�ֵΪ0
				if (SwellJudge(i, j))//�õ������
					temp.push_back(255);
				else
					temp.push_back(dst[i][j]);
			}
			else
				temp.push_back(dst[i][j]);
		}
		result.push_back(temp);
		vector<int>().swap(temp);
	}
	//���result
	for (int i = 0; i < result.size(); i++) {
		int count = result[i].size();
		for (int j = 0; j < count; j++) {
			cout << result[i][j];
			if (j < count - 1)
				cout << " ";
		}
		cout << endl;
	}
}