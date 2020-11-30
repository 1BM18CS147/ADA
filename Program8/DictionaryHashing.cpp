#include<bits/stdc++.h>

using namespace std;
# define max 10 //predefining size of hash table as 10

typedef struct item
{
    int data;
    struct item *next;
} node;

node *ptr[max],*root[max],*temp[max];

class Dictionary
{
public:
    int ind;
    void insert(int);
    void search(int);
    void Delete(int);
    Dictionary();
};

Dictionary::Dictionary()
{
    ind=-1;
    for(int i=0; i<max; i++)
    {
        root[i]=NULL;
        ptr[i]=NULL;
        temp[i]=NULL;
    }
}
void Dictionary::insert(int k)
{
    ind=int(k%max);
    ptr[ind]=(node*)malloc(sizeof(node));
    ptr[ind]->data=k;
    if(root[ind]==NULL)
    {
        root[ind]=ptr[ind];
        root[ind]->next=NULL;
        temp[ind]=ptr[ind];
    }
    else
    {
        temp[ind]=root[ind];
        while(temp[ind]->next!=NULL)
            temp[ind]=temp[ind]->next;
        temp[ind]->next=ptr[ind];
    }
}
void Dictionary::search(int k)
{
    int f=0;
    ind=int(k%max);
    temp[ind]=root[ind];
    while(temp[ind]!=NULL)
    {
        if(temp[ind]->data==k)
        {
            cout<<"key found at index "<<ind<<"!!\n";
            f=1;
            break;
        }
        else temp[ind]=temp[ind]->next;
    }
    if (f==0)
        cout<<"key not found!!\n";
}
void Dictionary::Delete(int k)
{
 
    ind=int(k%max);
    temp[ind]=root[ind];
    while(temp[ind]->data!=k && temp[ind]!=NULL)
    {
        ptr[ind]=temp[ind];
        temp[ind]=temp[ind]->next;
    }
   
    ptr[ind]->next=temp[ind]->next;
    cout<<k<<" is deleted.\n";
    temp[ind]->data=-1;
    temp[ind]=NULL;
    free(temp[ind]);
}



int main()
{
    int val,ch=0,n,num;
    
    Dictionary dict;
    do
    {
        
        cout<<"Enter\n1.Insert\n2.Search\n3.Delete\n4.Exit\n";
        cin>>ch;
        switch(ch)
        {
        case 1:
            cout<<"\nEnter the number of elements to be inserted:";
            cin>>n;
            cout<<"\nEnter the elements to be inserted:";
            for(int i=0; i<n; i++)
            {
                cin>>num;
                dict.insert(num);
            }
            break;
        case 2:
            cout<<"\nEnter the element to be searched:";
            cin>>n;
            dict.search(n);
            break;
        case 3:
            cout<<"\nEnter the element to be deleted:";
            cin>>n;
            dict.Delete(n);
            break;
        case 4:
            break;
        default:
            cout<<"\nInvalid Choice.";
        }
        
    }
    while(ch!=4);

return 0;
}
