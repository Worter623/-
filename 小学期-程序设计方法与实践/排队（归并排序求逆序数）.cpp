#include <stdio.h>
long long int a[300002],sum=0;//ȫ�ֱ����������� 
void merge(long long int a[],long long int first,long long int middle,long long int last,long long int temp[])
{
	long long int i=first,j=middle+1,m=middle,n=last,k=0;
	while (i<=m&&j<=n) //a[i] ǰ�����  a[j] �������
	{
		if(a[i]<=a[j])
			temp[k++]=a[i++];
		else
		{//a[j]��ǰ��ÿһ�������������������
			temp[k++]=a[j++];
			sum+=m-i+1;
		}
	}
	while (i<=m)
		temp[k++]=a[i++];
	while (j<=n)
		temp[k++]=a[j++];
	for (i=0;i<k;i++)
		a[first+i]=temp[i];
}

void mergesort(long long int a[],long long int first,long long int last,long long int temp[])
{	if (first<last)
	{
		long long int middle = (first+last)/2;
		mergesort(a,first,middle,temp);    //�������
		mergesort(a,middle+1,last,temp); //�ұ�����
		merge(a,first,middle,last,temp); //�������кϲ�
	}}

void Mergesort(long long int a[],long long int n)
{
	long long int *p=new long long int[n];
	mergesort(a,0,n-1,p);
}

int main()
{
	long long int n;
	scanf("%lld\n",&n);
	for(int i=0;i<n;i++)
		scanf("%lld",&a[i]);
	Mergesort(a,n);//������Ժ��� 
	printf("%lld\n",sum);
}
