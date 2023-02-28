#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

queue <int> q;
vector <int> clue[300003];
int n,m,flag=0,temp1,temp2,ans=-1;

int bfs(int s,int t)
{
	int currentnode;
	q.push(s);
	while(!q.empty())
	{
		currentnode=q.front();
		q.pop();
		for(int i=0;i<clue[currentnode].size();i++)
		{
			if(clue[currentnode][i]==t)	return 1;
			q.push(clue[currentnode][i]);
		}	
	}
	return -1;//û�ҵ� 
}

int main()
{
	scanf("%d%d\n",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&temp1,&temp2);
		if(temp1==temp2)//a=b:found
			{ans=i+1;break;}
		if(!flag)//flag==0
		{//��ÿһ������bfs 
			clue[temp1].push_back(temp2);//�����ڽӱ� 
			if(bfs(temp2,temp1)!=-1)//�ջ��Ļ���¼ans������ֻ����
				{ans=i+1;flag=1;} 
		}
	}
	printf("%d\n",ans);
}
