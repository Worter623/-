#include <stdio.h>
#include <string.h>
long long int n,hand[200003],pile[200003];//ȫ�ֱ����������� 
int main()
{
	long long int shift=0,n,i,p1=0,flag1=2,flag2=0,flag3=0,flag4=0,max=0,temp;
	scanf("%lld\n",&n);
	for(i=0;i<n;i++)
		scanf("%lld",&hand[i]);
	for(i=0;i<n;i++)
	{	scanf("%lld",&pile[i]);//������� 
		if(pile[i]==1)	{flag3=1;p1=i;}}//1��pile  ��p1 
	if(flag3==0)	shift=1;//1�����ƶ��������2 
	if(shift==0) //��˳�򣬳����������2 
		for(i=p1+1;i<n;i++)
		{
			if(flag1==pile[i])flag1++;
			else	shift=1;
		} 
	flag1--;//��¼˳������һλ����Ϊflag1 
	if(flag1==n&&p1==0)flag4=1;//ȫ��˳�� 
	if(flag4==0)
{	if(shift==0)//��n���Ƶ���һ�����ڲ������� �� flag2=1
		for(i=0;i<n;i++)
			if(hand[i]==pile[n-1]+1)	flag2=1;
	if(flag2==0)shift=1;//���� shift=1
	if(shift==0)
		for(i=0;i<p1;i++)
			if(pile[i]!=0&&i>(pile[i]-pile[n-1]))	shift=1;}
	if(shift==0)	printf("%lld\n",n-flag1);//���1����1234
	else//�������
	{
		for(i=0;i<n;i++)
		{
			if(pile[i]!=0)
				{temp=i-pile[i]+2;
				max=(max>temp)?max:temp;}
		}
		printf("%lld\n",n+max);
	}
	
}
