#include<stdio.h>
#include<string.h>
int main()
{
	unsigned char ch1,ch2,ch3;
	int temp1,temp2,temp3,flag=0,m1,m2,m3;
	long i,n,u[65536]={0};
	while(scanf("%c",&ch1)!=EOF)
	{//������ʱscanf("%c", ch1)���õ���������һ���ֽڡ�
		temp1=ch1;
		if(temp1<128)continue;//���ڷ�Χ�ڡ�0-127�����ַ����ԣ�����������������,�����ں��ֶ��ԣ�����1/3��1/2
		else if (temp1<224&&temp1>191)//���ڡ�110xxxxx��������ȶ�����ֽڶ��ԣ��䷶Χ�ǡ�11000000����192�� ~��11011111����223��
		{//�����ֽڱ�ʾ 
			ch2=getchar();
			temp2=ch2;
			n=(temp1-192)*64+temp2-128;
			u[n]++;
		}
		else
		{//�����ֽڱ�ʾ
			ch2=getchar();	temp2=ch2;
			ch3=getchar();	temp3=ch3;
			n=(temp1-224)*4096+(temp2-128)*64+temp3-128;
			u[n]++;
		}
	}
	for(i=0;i<65536;i++)
		if(u[i]>1)
			{flag=1;	break;}
	if(flag==1)
	{	for(i=128;i<65536;i++)
		{
			if(i>127&&i<2048)
			{	if(u[i]>1)
				{
					m2=i%64+128;
					m1=i/64+192;
					printf("%c%c",m1,m2);
					printf(" 0x%04x",i);
					printf(" %ld\n",u[i]);
				}
				else continue;}
			else
			{	if(u[i]>1)
				{
					m3=i%64+128;
					m2=(i/64)%64+128;
					m1=i/4096+224;
					printf("%c%c%c",m1,m2,m3);
					printf(" 0x%04x",i);
					printf(" %ld\n",u[i]);
				}
				else continue;}
		}}
	else
		printf("No repeat!\n");
} 
