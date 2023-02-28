#include<stdio.h>
#include<string.h>
long long int start[300002]={0},end[300002]={0};
void qsort(long long int *a,long long int l,long long int r,long long int *b)
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
            i++;j--;
        }
    }
    if (l<j) qsort(a,l,j,b);
    if (i<r) qsort(a,i,r,b);
}

int main()
{
	long long int i,n,temp,things=1,k=0;
	scanf("%lld",&n);
	for(i=0;i<n;i++)
		scanf("%lld %lld",&start[i],&end[i]);
	qsort(end,0,n-1,start);//����end����˳����start 
	for(i=0;i<n-1;i++)
	{
		if(end[i-k]<=start[i+1])
			{k=0;things++;}
		else k++;
	}
	printf("%lld\n",things);
} 
