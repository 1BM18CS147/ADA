#include<bits/stdc++.h>
using namespace std; 

struct node
{
	int data;
	struct node *next;
};
typedef struct node * NODE;

NODE getnode()
{
	NODE p;
	p=(NODE)malloc(sizeof(struct node));
	if(p!=NULL)
		return p;
	else
	{
		printf("memory could not be allocated\n");
		exit(0);
	}
}

NODE insert(NODE head,int item)
{
	NODE p,q;
	q=getnode();
	q->data=item;
	q->next=NULL;
	if(head==NULL)
		return q;
	p=head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	p->next=q;
	return head;
	
}

NODE reverse (NODE head, int k)  
{  
    NODE curr = head;  
    NODE next = NULL;  
    NODE prev = NULL;  
    int c = 0;  
      
    while (curr != NULL && c < k)  
    {  
        next = curr->next;  
        curr->next = prev;  
        prev = curr;  
        curr = next;  
        c++;  
    }  
      
    
    if (next != NULL)  
    head->next = reverse(next, k);  
  
    return prev;  
}  

void display(NODE head)
{
	NODE p;
	if(head==NULL)
	{
		cout<<"List is empty";
		exit(0);
	}
	p=head;
	while(p!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
}


int main()
{
	NODE head=NULL;
	int item;
	int n,k;
	cin>>n;
	for(int i=0;i<n;i++)
	{
	cin>>item;
	head=insert(head,item);
	}
	cin>>k;
	
	head=reverse(head,k);
	display(head);
	return 0;
}

/*
i/p->
5
1 2 3 4 5
3

o/p->
3 2 1 5 4 


i/p->
8 
1 2 2 4 5 6 7 8
4

o/p->
4 2 2 1 8 7 6 5 
*/
