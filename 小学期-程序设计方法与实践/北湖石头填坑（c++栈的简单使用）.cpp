#include<cstring>
#include<cstdio>
#include<stack>
#include<cstdlib>
using namespace std;
stack <long long int> row;
long long int t,i,n,parity[200003];
int main()
{//ֻҪ����ʯ��ĸ߶Ȳ���2�ı����Ϳ�������
	while(scanf("%lld",&n)!=EOF)
	{  
		memset(parity,0,sizeof(parity));
		while(!row.empty())	row.pop();//��ʼ�� 
		for(i=0;i<n;i++)
		{
			scanf("%lld",&t);
			parity[i]=t%2;		
		}//���룬parity 0ż1�� 
		for(i=0;i<n;i++)
		{//ջΪ�վ���ջ 
			if(row.empty())	row.push(parity[i]);
			else
			{//ջ��Ϊ���ҿ��Ժϲ��͵�����ǰջ��Ԫ�أ�������ջ 
				if((parity[i]-row.top())%2==0)	row.pop();
				else	row.push(parity[i]);
			}
		}
		if(row.size()==0||row.size()==1)	printf("YES\n");
		else	printf("NO\n");
	}
} 
