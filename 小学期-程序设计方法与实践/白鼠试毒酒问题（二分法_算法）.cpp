#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{	/*��ȡ������Ŀ��ÿ������������*/
	long long int test_case;
	scanf("%lld",&test_case);
	long long int sample[10000],result[10000];
	for(int i=0;i<test_case;i++)
		scanf("%lld",&sample[i]);
	/*���ÿ����������������������¼���*/
	for(int i=0;i<test_case;i++)
	{
		double m=log(sample[i])/log(2);
		if(m != (int)m ) m++ ;
		result[i]=(int)m;
	}
	/*��ӡ�������*/
	for(int i=0;i<test_case;i++)
		printf("%d\n",result[i]);
} 
