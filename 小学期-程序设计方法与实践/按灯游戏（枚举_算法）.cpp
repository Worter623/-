#include<stdio.h>  
#include<string.h>  
char cinput[20][20];  
int input[20][20],map[20][20],press[20][20];  
  
long long int line(int n,int m);/*ö�ٵ�һ�е�2^m�ֿ���*/  
long long int test(int n,int m);/*������һ�еĵ��ǲ��Ƕ�����*/  
void switches(int i,int j); /*����i�е�j�к���Χ����յ�Ƶı仯���*/  
  
long long int line(int n,int m)  
{/*����2^m*/  
    long long int possibilities=1<<17,result=999999999,minstep[1<<17];  
    for(int i=0;i<possibilities;i++)  
    {/*��ģ���һ�У���¼�ı�򲻸ı�*/   
        int temp=i;  
        for(int j=1;j<m-1;j++)  
        {  
            press[1][j]=temp%2;  
            temp/=2;  
        }  
    /*ÿһ�γ���֮ǰ��ʼ��*/  
        for(int j=1;j<n;j++)  
            for(int k=1;k<m-1;k++)  
                map[j][k]=input[j][k];  
    /*����test��������ɲ�����   ÿ����һ�κ�������ı亯��ֵ */  
        int k=test(n,m);/*��������ֵ������  ����step=0���������*/  
        if(k>=0)  
            minstep[i] = k;  
        else  
            minstep[i] = 9999999999;  
    }  
/*ѡ����С����*/  
    for(int i=0;i<possibilities;i++)  
    {  
        result = (minstep[i]<result)?minstep[i]:result;  
    }  
    return result;  
}  
  
long long int test(int n,int m)  
{/*������*/  
    long long int step=0;  
    for(int i=1;i<n;i++)  
    {/*����i�еĿ���*/  
        for(int j=1;j<m-1;j++)  
            if(press[i][j]==1)  
                {step++;switches(i,j);}  
        for(int j=1;j<m-1;j++)  
        {/*���ݵ�i�еƵĿ������������i+1�а��򲻰�*/  
            if(map[i][j]==1)  
                press[i+1][j]=1;  
            else  
                press[i+1][j]=0;        
        }     
    }  
    /*�������һ�еĵ��ǲ��ǹ��ţ��Ǿͷ��ز���*/      
    int sum=0;  
    for(int i=1;i<m-1;i++)  
        sum+=map[n-1][i];  
    if(sum==0)  return step;  
    if(sum>0)    return -1;  
}  
  
void switches(int i,int j)  
{  
    map[i][j]=(map[i][j]+1)%2;  
    map[i+1][j]=(map[i+1][j]+1)%2;    
    map[i-1][j]=(map[i-1][j]+1)%2;    
    map[i][j+1]=(map[i][j+1]+1)%2;    
    map[i][j-1]=(map[i][j-1]+1)%2;  
}  
  
int main()  
{  
    int n,m;  
    scanf("%d %d\n",&n,&m);  
    m+=2;n++;  
    for(int i=1;i<n;i++)  
        for(int j=1;j<m;j++)  
        {
			scanf("%c",&cinput[i][j]); 
			input[i][j]=cinput[i][j]-'0';	   	
		} 
    printf("%lld\n",line(n,m));  
}  
