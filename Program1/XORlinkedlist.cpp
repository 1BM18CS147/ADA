#include <bits/stdc++.h> 
#include <inttypes.h>  
using namespace std; 

class Node  
{  
    public: 
    int data;  
    Node* nextprev; 
};  

Node* XOR (Node *x, Node *y)  
{  
    return (Node*) ((uintptr_t) (x) ^ (uintptr_t) (y));  
}  

void insert_front(Node **head, int data)  
{  
    Node *newNode = new Node();  
    newNode->data = data;  
  

    newNode->nextprev = *head;  
  

    if (*head != NULL)  
    {  
 
        (*head)->nextprev = XOR(newNode, (*head)->nextprev);  
    }  
  
 
    *head = newNode;  
}  

void insert_end(Node** head,int data)
{
    Node* newNode=new Node();
    newNode->data=data;
    
    if(*head==NULL){
        newNode->nextprev=*head;
    }
    
    else
    {
        Node* curr=*head;
        Node* prev=NULL;
        Node* next;
        
        while(curr!=NULL)
        {
            next=XOR(prev,curr->nextprev);
            prev=curr;
            curr=next;
        }
        
        newNode->nextprev=curr;
        curr->nextprev=XOR(prev,newNode);
    }
}

void printList (Node *head)  
{  
    
    Node *curr = head;  
    Node *prev = NULL;  
    Node *next;  
  
    cout << "Nodes of XOR linked list are: \n";  
  
    while (curr != NULL)  
    {  

        cout<<curr->data<<" ";  
  
        next = XOR (prev, curr->nextprev);  
  
 
        prev = curr;  
        curr = next;  
    }  
}  
  

int main () {  
    Node *head = NULL; 
    int front_n, end_n;
    cout << "Enter number of nodes to enter in the front \n"; 
    cin >> front_n;
    cout<<"Enter values \n";
    int value;
    
    while (front_n) {
      cin >> value;
      insert_front(&head, value); 
      front_n--;
    }

    cout << "Enter number of nodes to enter in the end \n"; 
    cin >> end_n;
    cout<<"Enter values\n";
    
    while (end_n) {
      cin >> value;
      //insert_end(&head, value);  
    }
  
    printList(head);  
  
    return 0;  
}  