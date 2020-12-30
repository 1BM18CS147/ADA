#include<bits/stdc++.h>

using namespace std;

int c;
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

Node* insert(Node* node, int key)  
{  

    if (node == NULL)  
        return(NewNode(key));  

    if (key < node->key)  
        node->left = insert(node->left, key);  
    else if (key > node->key)  
        node->right = insert(node->right, key);  
    else   
        return node;  

    node->height = 1 + max(height(node->left),  
                        height(node->right));  

    int BF =Balance(node);  


    if (BF > 1 && key < node->left->key)  
        return RightRotation(node);  


    if (BF < -1 && key > node->right->key)  
        return LeftRotation(node);  

    if (BF > 1 && key > node->left->key)  
    {  
        node->left = LeftRotation(node->left);  
        return RightRotation(node);  
    }  

    if (BF < -1 && key < node->right->key)  
    {  
        node->right = RightRotation(node->right);  
        return LeftRotation(node);  
    }  


    return node;  
}

void print(Node* root) 
{ 
     if(root!=NULL) 
     { 
        print(root->left);
        if(c>=0){
        cout << root->key <<" ";
        c=c-1;
        } 
        print(root->right);   
     } 
} 


int main()  
{  


    int n,t,val;
    cin>>t;

    while(t--)
    {
     Node *node = NULL; 
     cin>>n;
     c=n-3;
     //cout<<"c "<<c<<"\n";
     while(n--)
     {
      cin>>val;
      node = insert(node, val);  
      }    
      print(node);
      cout<<endl;
    } 

    return 0;  
}  
