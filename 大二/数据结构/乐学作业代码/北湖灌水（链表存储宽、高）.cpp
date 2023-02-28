#include <stdio.h>  
#include <stdlib.h>
#include <string.h>  

typedef long long int element_type;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node 
{  element_type element,width,height;  
   Position next,previous;  
}; 
Position setlist(List head,element_type n)  
{     //����ƽ������ 
    Position p,tem_p=head,min=head; 
    element_type w,h;
    for(element_type i=0;i<n;i++)
    {
	   	scanf("%lld%lld",&w,&h);	   	
		p=(Position)malloc(sizeof(struct Node));  
        p->element=i;
        p->width=w;
        p->height=h;
        p->previous=tem_p;
        p->next=NULL; 
        tem_p->next=p;
        tem_p=p;
        if(min->height > h)	min=p;
    }
    Position right=(List)malloc(sizeof(struct Node));
	right->width=0;	right->height=100010;//�ұ߸�ǽ 
	p->next=right;
	right->next=NULL;
    return min;
}  
void Delete(Position p)
{
	p->previous->next=p->next;
	p->next->previous=p->previous;
}
int main()  
{
	element_type i,n,time=0,ans[100005];
	scanf("%lld",&n); 
	List left;//��߸�ǽ 
	left=(List)malloc(sizeof(struct Node));
	left->width=0;	left->height=100010;
	left->previous=NULL;	left->next=NULL;
	Position min=setlist(left,n);
	while(min->previous->height!=min->next->height)
	{//����ƽ�������ֻʣ���һ������� 
		ans[min->element]=time+min->width;
		if(min->previous->height > min->next->height)
		{//���ұ���ƽ���� 
			time+=(min->next->height - min->height)*min->width;
			min->next->width+=min->width;
			Delete(min);
			min=min->next;
		}
		else
		{
			time+=(min->previous->height - min->height)*min->width;
			min->previous->width+=min->width;
			Delete(min);
			min=min->previous;
		}
		if(min->height < min->previous->height && min->height < min->next->height)
			continue;
		else
		{//����һ����ֱ���ҵ����ݿ� 
			if(min->previous->height > min->next->height)
				while(min->height > min->next->height)
					min=min->next;
			else
				while(min->height > min->previous->height)
					min=min->previous;
		}
	}//���һ��ƽ����ƽ 
	ans[min->element]=time+min->width;
	for(i=0;i<n;i++)
		printf("%lld\n",ans[i]);
}
