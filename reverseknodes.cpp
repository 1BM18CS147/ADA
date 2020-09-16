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

NODE reverse(NODE head,int k)
{
    
    NODE prev=NULL;
    NODE curr=head;
    NODE p=curr;
    NODE next=NULL;
    
    while(curr!=NULL && k>0)
    {
        next=curr->next;
        curr->next=prev;
        prev = curr; 
        curr = next; 
        k--;
    }
    p->next=curr;
    head = prev; 
    return head;
    
    
    
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