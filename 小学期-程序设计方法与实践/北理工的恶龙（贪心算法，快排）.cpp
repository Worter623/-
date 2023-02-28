#include<stdio.h>
#include<string.h>
void qsort(long long int *a,long long int l,long long int r,long long int *b,long long int *c)
{//�������� 
    long long int i=l,j=r,mid=a[(l+r)/2],temp;
    while (i<j)
    {
        while (a[i]<mid) i++;//��mid������� 
        while (a[j]>mid) j--;//��mid�ұ���С�� 
        if (i<=j)
        {//������С 
            temp=a[i];a[i]=a[j];a[j]=temp;
			temp=b[i];b[i]=b[j];b[j]=temp;
			temp=c[i];c[i]=c[j];c[j]=temp;            
            i++;j--;
        }
    }
    if (l<j) qsort(a,l,j,b,c);
    if (i<r) qsort(a,i,r,b,c);
}
long long int negative[200002],positive[200002],x[200002],y[200002];
int main()
{
	long long int i,n,t,temp=0,exp=0,money=0;
	scanf("%lld\n",&n);
	for(i=0;i<n;i++)
		scanf("%lld %lld",&x[i],&y[i]);
	for(i=0;i<n;i++)//����y[i] �����Ǹ�������ǰ�棬����temp��ʼ 
		if(y[i]<0)	
			{t=y[i];y[i]=y[temp];y[temp]=t;
			t=x[i];x[i]=x[temp];x[temp]=t;
			temp++;}
	for(i=0;i<temp;i++)//��y�������Ѷ�+�������СΪ�ţ��������� 
		negative[i]=x[i]+y[i];
	qsort(negative,0,temp-1,x,y);
	for(i=temp;i<n;i++)//��y�������Ѷ�СΪ�ţ��������� 
		positive[i]=x[i];
	qsort(positive,temp,n-1,x,y);
	for(i=temp;i<n;i++)
	{//��ʼ���ȴ�����temp��ʼ�� 
		if(exp<x[i])	
			{money+=x[i]-exp;	exp=x[i];}
		exp+=y[i];
	} 
	for(i=temp-1;i>-1;i--)
	{//�� ���Ӵ��С 
		if(exp<x[i])	
			{money+=x[i]-exp;	exp=x[i];}
		exp+=y[i];	
	}
	printf("%lld\n",money);
} 
