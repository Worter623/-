#include<stdio.h>  
#include<string.h>  

int main()  
{/*��ȡÿ����ȣ���Ҫ��ȥ�Ĳ��ֵ���ȡ�������ã�Ϊʵ�����һ��ȫ�������ҷ�ֹre����n+1�������Ϊ0*/ 
    long long int n,h,column_height[100003],reverse_depth[100003],interval=0;  
    scanf("%lld %lld\n",&n,&h);  
    for(long long int i=0;i<n;i++)   
		scanf("%lld",&column_height[i]); 
	for(long long int i=0;i<n;i++)
		reverse_depth[i] = h-column_height[n-1-i];
	reverse_depth[n]=0;
 	/*���һ�������ұ߸ߣ����+=���Ҹ߶Ȳ�*/
	for(long long int i=0;i<n;i++)
		if(reverse_depth[i]>reverse_depth[i+1])
			interval+=reverse_depth[i]-reverse_depth[i+1];
	printf("%lld\n",interval);
}
