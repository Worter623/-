#include<cstring>
#include<cstdio>
#include<stack>
#include<cstdlib>
using namespace std;
struct houses
{  
    long long int color,height; 
}house[1000003]; 
stack <struct houses> row;
long long int i,j,test_case,n,temp,result,colors[1000003];
int main()
{
	scanf("%lld\n",&test_case);
	for(i=0;i<test_case;i++)
	{//��ÿ������  
		memset(colors,0,sizeof(colors));
		result=0;
		while(!row.empty())	row.pop();//��ʼ��
		scanf("%lld\n",&n);
		for(j=0;j<n;j++)
			scanf("%lld",&house[j].color);
		for(j=0;j<n;j++)
			scanf("%lld",&house[j].height);		//���� (debug finished)
		colors[house[0].color]++;
		result++;
		row.push(house[0]);//ջ�к�colors��¼���һ���������� 
		for(j=0;j<n;j++)
		{//���ջ�����Ӹ��� or ջΪ�� �� ѹ�������� 
			if(house[j].height<row.top().height||row.empty())
			{
				temp=house[j].color;
				if(colors[temp]==0)result++;
				colors[temp]++;
				row.push(house[j]);
			}
			if(house[j].height>=row.top().height) //���������ߣ�����ջ����  Ȼ��ѹ�������� 
			{	
				while(house[j].height>=row.top().height)
				{
					temp=row.top().color;
					colors[temp]--;
					if(colors[temp]==0)result--;
					row.pop();
					if(row.empty())break;
				}
				temp=house[j].color;
				if(colors[temp]==0)result++;
				colors[temp]++;
				row.push(house[j]);
			}		
			if(j!=n-1)	printf("%lld ",result);//���
			if(j==n-1) 	printf("%lld\n",result);
		}
	}
} 	
