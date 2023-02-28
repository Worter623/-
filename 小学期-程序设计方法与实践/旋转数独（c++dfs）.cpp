#include <cstdio>
#include <cstring>
using namespace std;

int T,ans[5][5],temp[5][5],map[18][18],nmap[18][18],min;

void input()//���뺯������ÿ���������map 
{
	int a,i,j;
	char c;
	for(i=0;i<16;i++)
	{//ע��ÿ����һ�����Ҫ�����س�
		for(j=0;j<16;j++)
		{
			c=getchar();
			if(c>='0'&&c<='9')	a=c-'0';
			if(c>='A'&&c<='F')	a=c-'A'+10;	
			map[i][j]=a;
		}
		c=getchar();
	}
}

void rotate(int k,int x,int y)
{//�ԣ�x��y������תk�Σ���¼��ת���������nmap�� 
	int i,j,temp=k;
	switch(temp)
	{
		case 0:
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					nmap[4*x+i][4*y+j]=map[4*x+i][4*y+j];
			break;
		case 1:
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					nmap[4*x+i][4*y+j]=map[4*x+j][4*y+3-i];
			break;			
		case 2:
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					nmap[4*x+i][4*y+j]=map[4*x+3-i][4*y+3-j];
			break;	
		case 3:
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					nmap[4*x+i][4*y+j]=map[4*x+3-j][4*y+i];
			break;			
		default:
			break;
	}
} 

int check1(int x,int y)
{//�����һ������ǰ�������Ŀ���û���ظ�����/������ 
	if(y<=0)	return 1;
	int i,j,vis[18];
	for(i=4*x;i<4*x+4;i++)
	{//��4�� 
		memset(vis,0,sizeof(vis));
		for(j=0;j<4*y+4;j++)//���� 
		{
			if(vis[nmap[i][j]])	return 0;
			vis[nmap[i][j]]=1;
		}	
	}
	return 1;
}

int check2(int y,int x)
{
	if(x<=0)	return 1;
	int i,j,vis[18];
	for(i=4*y;i<4*y+4;i++)
	{//��4�� 
		memset(vis,0,sizeof(vis));
		for(j=0;j<4*x+4;j++)//���� 
		{
			if(vis[nmap[j][i]])	return 0;
			vis[nmap[j][i]]=1;			
		}	
	}
	return 1;
} 

int check(int x,int y)
{
	return check1(x,y)&&check2(y,x);
}

void dfs(int now,int sum)
{//�Ե�ǰ״̬ 
	int i,j,x=now/4,y=now%4; 
	if(now==16)
	{//if�ѵ���� 
		if(sum<min)//�ҽ������������������ 
		{//���´𰸣��𰸰��������Ͳ������� 
			min=sum;
			for(i=0;i<4;i++)
				for(j=0;j<4;j++)
					ans[i][j]=temp[i][j];
		}
		return;
	}
	for(i=0;i<4;i++)
	{//�Ե�ǰ״̬��ÿһ��������  ����ת����
		rotate(i,x,y);//������һ��״̬������ 
		if(check(x,y))
		{//�����һ��״̬�Ϸ� 
			temp[x][y]=i;//��¼ĳ��������˼��Σ������� 
			dfs(now+1,sum+i);//dfs��һ��״̬ 
		} 
	}	
}

int main()
{
	scanf("%d\n",&T);
	for (int p=0;p<T;p++)
	{//��ÿһ������ �ȳ�ʼ�� 
		min=9999999;
		input();
		dfs(0,0);//�����Ϸ���ʼdfs
		printf("%d\n",min);//һ���н⣬��ӡ���ս�ͺ��� 
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)//ans��¼���ǵ�i��j����ת�˼��� 
				for(int k=0;k<ans[i][j];k++)
					printf("%d %d\n",i+1,j+1);
	}
}
