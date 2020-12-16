
#include <bits/stdc++.h> 
using namespace std; 

#define mini -9999

struct Node 
{ 
    int value, degree; 
    Node *parent, *child, *sibling; 
}; 

Node *root = NULL; 
int binomialLink(Node *h1, Node *h2) 
{ 
    h1->parent = h2; 
    h1->sibling = h2->child; 
    h2->child = h1; 
    h2->degree = h2->degree + 1; 
} 
  

Node *createNode(int n) 
{ 
    Node *newN = new Node; 
    newN->value = n; 
    newN->parent = NULL; 
    newN->sibling = NULL; 
    newN->child = NULL; 
    newN->degree = 0; 
    return newN; 
} 

Node *Merge(Node *h1, Node *h2) 
{ 
    if (h1 == NULL) 
        return h2; 
    if (h2 == NULL) 
        return h1; 
  
    Node *res = NULL;  
    if (h1->degree <= h2->degree) 
        res = h1; 
  
    else if (h1->degree > h2->degree) 
        res = h2; 

    while (h1 != NULL && h2 != NULL) 
    { 
 
        if (h1->degree < h2->degree) 
            h1 = h1->sibling; 
        else if (h1->degree == h2->degree) 
        { 
            Node *sib2 = h1->sibling; 
            h1->sibling = h2; 
            h1 = sib2; 
        } 
        else
        { 
            Node *sib2 = h2->sibling; 
            h2->sibling = h1; 
            h2 = sib2; 
        } 
    } 
    return res; 
} 
  

Node *Union(Node *h1, Node *h2) 
{ 
    if (h1 == NULL && h2 == NULL) 
       return NULL; 
  
    Node *res = Merge(h1, h2); 
 
    Node *prev = NULL, *curr = res, 
         *next = curr->sibling; 
    while (next != NULL) 
    { 
        if ((curr->degree != next->degree) || 
                ((next->sibling != NULL) && 
                 (next->sibling)->degree == 
                 curr->degree)) 
        { 
            prev = curr; 
            curr = next; 
        } 
  
        else
        { 
            if (curr->value <= next->value) 
            { 
                curr->sibling = next->sibling; 
                binomialLink(next, curr); 
            } 
            else
            { 
                if (prev == NULL) 
                    res = next; 
                else
                    prev->sibling = next; 
                binomialLink(curr, next); 
                curr = next; 
            } 
        } 
        next = curr->sibling; 
    } 
    return res; 
} 
  
void Insert(int x) 
{ 

    root = Union(root, createNode(x)); 
} 

void display(Node *h) 
{ 

    while (h) 
    { 
        cout << h->value << " "; 
        display(h->child); 
        h = h->sibling; 
    } 
} 
 
int revertList(Node *h) 
{ 
    if (h->sibling != NULL) 
    { 
        revertList(h->sibling); 
        (h->sibling)->sibling = h; 
    } 
    else
        root = h; 
} 

Node* getmin(Node *h)
{
    if (h == NULL) 
       return NULL; 
  
    Node *min_node_prev = NULL; 
    Node *min_node = h; 
  
    int min = h->value; 
    Node *curr = h; 
    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->value < min) 
        { 
            min = (curr->sibling)->value; 
            min_node_prev = curr; 
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 
   return curr;

}
Node *extractMin(Node *h) 
{ 
    if (h == NULL) 
       return NULL; 
  
    Node *min_node_prev = NULL; 
    Node *min_node = h; 
  
    int min = h->value; 
    Node *curr = h; 
    while (curr->sibling != NULL) 
    { 
        if ((curr->sibling)->value < min) 
        { 
            min = (curr->sibling)->value; 
            min_node_prev = curr; 
            min_node = curr->sibling; 
        } 
        curr = curr->sibling; 
    } 

    if (min_node_prev == NULL && 
        min_node->sibling == NULL) 
        h = NULL; 
  
    else if (min_node_prev == NULL) 
        h = min_node->sibling; 
 
    else
        min_node_prev->sibling = min_node->sibling; 

    if (min_node->child != NULL) 
    { 
        revertList(min_node->child); 
        (min_node->child)->sibling = NULL; 
    } 
 
    return Union(h, root); 
} 
  
 
Node *findNode(Node *h, int value) 
{ 
    if (h == NULL) 
      return NULL; 
    if (h->value == value) 
        return h; 
    Node *res = findNode(h->child, value); 
    if (res != NULL) 
       return res; 
  
    return findNode(h->sibling, value); 
} 

void decreaseKey(Node *H, int val,int nval) 
{ 

    Node *node = findNode(H,val); 
   
    if (node == NULL)
        return; 
    node->value = nval; 
    Node *parent = node->parent; 
    while (parent != NULL && node->value < parent->value) 
    { 
        swap(node->value, parent->value); 
        node = parent; 
        parent = parent->parent; 
    } 
} 
  

Node *Delete(Node *h, int value) 
{ 
    if (h == NULL) 
        return NULL; 
    decreaseKey(h, value, mini); 
    return extractMin(h); 
} 

int main() 
{ 

    int  ch=-1,n,num;
    while(ch!=0)
    {
      cout<<"\nEnter\n1.To Insert\n2.To delete\n3.To extractmin\n4.To getmin\n0. To exit\n";
      cin>>ch;
      switch(ch)
      {
        case(1):cout<<"Enter number of elements\n";
                cin>>n;
                cout<<"Enter values\n";
                while(n)
                {
                    cin>>num;
                    Insert(num);
                    n--;
                }
                cout<<"The heap  is\n";
                display(root); 
                break;

        case(2):cout<<"Enter number to be deleted\n";
                cin>>num;
                root=Delete(root,num);
                cout<<"After deleting node with value "<<num<<",\n";
                cout<<"The heap  is\n";
                display(root); 
                break;

        case(3):
                cout<<"After deleting node with value "<<getmin(root)->value<<",\n";
                root=extractMin(root);
                cout<<"The heap  is\n";
                display(root); 
                break;

        case(4):cout<<"Minimum value in heap is"<<getmin(root)->value;
                break;
        case(0):break;
        default:cout<<"Wrong choice try again!\n";
       }

      }

  
    return 0; 
} 
