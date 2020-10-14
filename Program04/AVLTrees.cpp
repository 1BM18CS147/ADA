#include<bits/stdc++.h>

using namespace std;


class Node  
{  
    public: 
    int key;  
    Node *left;  
    Node *right;  
    int height;  
};  

int height(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}  

Node* NewNode(int key)  
{  
    Node* node = new Node(); 
    node->key = key;  
    node->left = NULL;  
    node->right = NULL;  
    node->height = 1; 
    return(node);  
}  


//Balance factor Calculations

int Balance(Node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  


int max(int x, int y)  
{  
    return (x > y)? x : y;  
}  
  


//Right and left rotation
Node *RightRotation(Node *y)  
{  
    Node *x = y->left;  
    Node *T2 = x->right;
    x->right = y;  
    y->left = T2;   
    y->height = max(height(y->left), 
                    height(y->right)) + 1;  
    x->height = max(height(x->left), 
                    height(x->right)) + 1;   
    return x;  
}  


Node *LeftRotation(Node *x)  
{  
    Node *y = x->right;  
    Node *T2 = y->left; 
    y->left = x;  
    x->right = T2; 
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;
    return y;  
}  


//insertion function
Node* insert(Node* node, int key)  
{  
    //Normal BST Insertion
    if (node == NULL)  
        return(NewNode(key));  
  
    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else   
        return node;  
  
    //Updating heights of parent nodes
    node->height = 1 + max(height(node->left),  
                        height(node->right));  
  
    //Get Balancing Factor
    int BF =Balance(node);  
  
 
    // Left Rotation 
    if (BF > 1 && key < node->left->key)  
        return RightRotation(node);  
  
    // Right Rotation  
    if (BF < -1 && key > node->right->key)  
        return LeftRotation(node);  
  
    // LR Rotation
    if (BF > 1 && key > node->left->key)  
    {  
        node->left = LeftRotation(node->left);  
        return RightRotation(node);  
    }  
  
    // RL Rotation
    if (BF < -1 && key < node->right->key)  
    {  
        node->right = RightRotation(node->right);  
        return LeftRotation(node);  
    }  
  
    
    return node;  
}




Node * minNode(Node* node)  
{  
    Node* curr = node;  

    while (curr->left != NULL)  
        curr = curr->left;  
  
    return curr;  
}  
  

//Deletion function
Node* Delete(Node* node, int key)  
{  
    //BST deletion
    if (node == NULL)  
        return node;  
  

    if ( key < node->key )  
        node->left = Delete(node->left, key);  
 
    else if( key > node->key )  
        node->right = Delete(node->right, key);  

    else
    {  
    
        if( (node->left == NULL) ||(node->right == NULL) )  
        {  
            Node *temp = node->left ? node->left :node->right;  
  
            if (temp == NULL)  
            {  
                temp = node;  
                node = NULL;  
            }  
            else  
            *node = *temp; 
            free(temp);  
        }  
        else
        {  

            Node* temp = minNode(node->right);
            node->key = temp->key;  
            node->right = Delete(node->right,temp->key);  
        }  
    }  

    if (node == NULL)  
    return node;  
  
    //Balancing the tree
    node->height = 1 + max(height(node->left),height(node->right));  
    
    //Right rotation
    int BF = Balance(node);
    if (BF > 1 && Balance(node->left) >= 0)  
        return RightRotation(node);  
    
    //LR Rotation
    if (BF > 1 &&Balance(node->left) < 0)  
    {  
        node->left = LeftRotation(node->left);  
        return RightRotation(node);  
    }  
  
    //Left Rotation
    if (BF < -1 && Balance(node->right) <= 0)  
        return LeftRotation(node);  
   
    //RL Rotation
    if (BF < -1 && Balance(node->right) > 0)  
    {  
        node->right = RightRotation(node->right);  
        return LeftRotation(node);  
    }  
  
    return node;  
}  


//Level Wise printing functions
void printNodes(Node* node, int level) 
{ 
    if (node == NULL) 
        return; 
    if (level == 1) 
        cout<<node->key<<"  "; 
    else if (level > 1) 
    { 
        printNodes(node->left, level-1); 
        printNodes(node->right, level-1); 
    } 
} 


void print(Node* node) 
{ 
    int h = height(node); 
    int i; 
    for (i=1; i<=h; i++) 
    { 
        printNodes(node, i); 
        cout<<"\n"; 
    } 
} 



//Main Function
int main()  
{  
    Node *node = NULL;  
    int n,Value,ch=3;
    while(ch)
    {
    cout<<"Enter \n1 to insert\n2 to delete\n0 to exit\n";
    cin>>ch;
    switch(ch)
    {
     case 1: cout<<"Enter number of values\n";
             cin>>n;
             while(n--)
             {
             cout<<"Enter value\n";
             cin>>Value;
             node = insert(node, Value);  
             }
             cout << "The  AVL tree after insertion is \n";  
             print(node);  
             cout<<"\nThe height of tree is\n";
             cout<<height(node)<<"\n";
             break;
     case 2: cout<<"Enter value to be deleted\n";
             cin>>n;
             node=Delete(node,n);
             cout<<"The AVL tree after deletion is \n";
             print(node);
             cout<<"\nThe height of tree is\n";
             cout<<height(node)<<"\n";
             break;

    } 
    } 
    return 0;  
}  
  
