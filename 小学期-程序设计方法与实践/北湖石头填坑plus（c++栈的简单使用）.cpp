#include<cstring>
#include<cstdio>
#include<stack>
#include<cstdlib>
using namespace std;
stack <long long int> row;
long long int i,n,maxi,flag,height[200003];
int main()
{//����ʯ��ȸ߲ſ��Ժϲ� 
	while(scanf("%lld",&n)!=EOF)
	{  
		flag=0;maxi=0;
		memset(height,0,sizeof(height));
		while(!row.empty())	row.pop();//��ʼ�� 
		for(i=0;i<n;i++)
		{
			scanf("%lld",&height[i]);
			if(maxi<height[i])	maxi=height[i];
		}//����  �������ֵ 	
		for(i=0;i<n;i++)
		{//ջΪ�վ���ջ 
			if(row.empty())	row.push(height[i]);
			else
			{
				if(height[i]>row.top())	
					{flag=1;break;}//�����ǰ�߶ȴ���ջ��Ԫ��һ��������ƽ 
				else 
				{//ջ��Ϊ���ҿ��Ժϲ��͵�����ǰջ��Ԫ�أ�������ջ 
					if(height[i]==row.top())	row.pop();
					else row.push(height[i]);
				}
			}
		}
		if(row.size()>1)	flag=1;//ջ��Ԫ�ش���1һ��������ƽ 
		if(row.size()==1&&row.top()!=maxi)	flag=1;

		if(flag==1)	printf("NO\n");//���
		else	printf("YES\n"); 
	}
} 
