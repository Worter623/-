#include<stdio.h>  
#include<string.h>   
int main()  
{//��ȡ���룬�õ�a��λ��   
    long long int l,la;  
    char a[100002];  
    scanf("%lld\n",&l);  
    gets(a);  
    la=strlen(a);  
    long long int temp=la,flag=0,equal=0,t;  
    for(int k=la-1;k>=0;k--)//�ж�a�Ƿ�ȫΪ9����temp=l����temp=��������Ϊ9��һλ   
    {   if(a[k]!='9')  
        {   temp=k; break;}     }  
    if(la%l==0)   
    {  
        if(la==l)  
        {  
            if(temp==la)  
            {//a��λ������l��lѭ���ڶ���9  
                for(int j=0;j<2;j++)  
                {  
                    printf("1");  
                    for(int i=1;i<l;i++)  
                        printf("0");  
                }  
            }  
            else//a��λ������l��lѭ���ڲ�����9   
            {  
                a[temp]+=1 ;  
                for(int i=temp+1;i<l;i++)  
                    a[i]='0';  
                for(int i=0;i<l;i++)  
                    printf("%c",a[i]);  
            }  
        }  
        else  
        {//la>l  
            for(int j=1;j<la/l;j++)
			for(int i=0;i<l;i++)  
            {  
                if(a[i]>a[i+l*j]&&equal==i+l*(j-1))  
                {   flag=1;break;}  
                if(a[i]==a[i+l*j])equal++;  
                if(a[i]<a[i+l*j]&&equal==i+l*(j-1))  
                {   flag=2;break;}  
            }  
            if(flag==0&&temp!=la)flag=2;
            if(flag==1)//l>l+1
                for(int i=0;i<la/l;i++)  
                    for(int j=0;j<l;j++)  
                        printf("%c",a[j]);  
            if(flag==0&&temp==la)//l=l+1,a==9  
            {  
                for(int j=0;j<la/l+1;j++)  
                {  
                    printf("1");  
                    for(int i=1;i<l;i++)  
                        printf("0");  
                }  
            }  
            if(flag==2)  
            {  //l<l+1 plus l=l+1,a!=9   
                for(int k=l-1;k>=0;k--)  
                {   if(a[k]!='9')  
                    {   t=k;    break;}     }  
                a[t]+=1 ;  
                for(int i=t+1;i<l;i++)   a[i]='0';  
                for(int i=0;i<la/l;i++)    
                    for(int j=0;j<l;j++)  
                        printf("%c",a[j]);  
            }  
        }  
    }  
    else//la&l!=0  
        for(int i=0;i<la/l+1;i++)  
        {  
            printf("1");  
            for(int j=1;j<l;j++)  
                printf("0");  
        }  
    printf("\n");  
}  
