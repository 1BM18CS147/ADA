
#include<iostream> 
using namespace std; 

// A twoThreeTree node 

class TwoThreeTreeNode
{
	int *keys;
	TwoThreeTreeNode **child;
	int n;
	bool leaf;
	public:
		TwoThreeTreeNode(bool leaf);
		void traverse();
		int findKey(int k);
		void insertNonFull(int k);
		void splitChild(int i, TwoThreeTreeNode *y);
		void remove(int k);
		void removeFromLeaf(int ind);
		void removeFromNonLeaf(int ind);
		int getPred(int ind);
		int getSucc(int ind);
		void fill(int ind);
		void borrowFromNext(int ind);
		void borrowFromPrev(int ind);
		void merge(int ind);
		friend class TwoThreeTree;
};

class TwoThreeTree
{
	TwoThreeTreeNode *root = NULL;
	public:
		
		void traverse()
		{
			if(root != NULL)
				root->traverse();
		}
		void insert(int k);
		void remove(int k);
};

TwoThreeTreeNode::TwoThreeTreeNode(bool leaf1)
{
	leaf = leaf1;
	keys = new int[3];
	child = new TwoThreeTreeNode *[4];
	n = 0;
}

int TwoThreeTreeNode::findKey(int k)
{
	int ind = 0;
	while(ind<n && keys[ind]<k)
		++ind;
	return ind;
}

void TwoThreeTree::insert(int k)
{
	if(root == NULL)
	{
		root = new TwoThreeTreeNode(true);
		root->keys[0] = k;
		root->n = 1;
	}
	else{
		if(root->n == 3)
		{
			TwoThreeTreeNode *s = new TwoThreeTreeNode(false);
			s->child[0] = root;
			s->splitChild(0, root);
			int i = 0;
			if(s->keys[0]<k)
				i++;
			s->child[i]->insertNonFull(k);
			root = s;
		}
		else
			root->insertNonFull(k);
	}
}

void TwoThreeTreeNode::insertNonFull(int k)
{
	int i = n-1;
	if(leaf == true)
	{
		while(i>=0 && keys[i] > k)
		{
			keys[i+1] = keys[i];
			i--;
		}
		keys[i+1] = k;
		n = n + 1;
	}
	else{
		while(i>=0 && keys[i]>k)
			i--;
		if(child[i+1]->n == 3)
		{
			splitChild(i+1, child[i+1]);
			if(keys[i+1]<k)
				i++;
		}
		child[i+1]->insertNonFull(k);
	}
}

void TwoThreeTreeNode::splitChild(int i, TwoThreeTreeNode *y)
{
	TwoThreeTreeNode *z = new TwoThreeTreeNode(y->leaf);
	z->n = 1;
	z->keys[0] = y->keys[2];
	if(y->leaf == false)
	{
		for(int j=0; j<2; j++)
			z->child[j] = y->child[j+2];
	}
	y->n = 1;
	for(int j=n; j>=i+1; j--)
		child[j+1] = child[j];
	child[i+1] = z;
	for (int j = n-1; j >= i; j--) 
        	keys[j+1] = keys[j]; 
  
    	keys[i] = y->keys[1]; 
 
    	n = n + 1; 
}

void TwoThreeTreeNode::traverse()
{
	cout<<endl;
	int i;
	for(i=0; i<n; i++)
	{
		if(leaf == false)
			child[i]->traverse();
		cout<<" "<<keys[i];
	}
	if(leaf == false)
		child[i]->traverse();

	cout<<endl;
}

void TwoThreeTreeNode::remove(int k)
{
	int ind = findKey(k);
	if(ind<n && keys[ind] == k)
	{
		if(leaf)
			removeFromLeaf(ind);
		else
			removeFromNonLeaf(ind);
	}
	else
	{
		if(leaf)
		{
			cout<<"The key doesn't exist"<<endl;
			return;
		}
		bool flag = ((ind==n)?true : false);
		if(child[ind]->n < 2)
			fill(ind);
		if(flag && ind>n)
			child[ind-1]->remove(k);
		else
			child[ind]->remove(k);
	}
	return;
}

void TwoThreeTreeNode::removeFromLeaf(int ind)
{
	for(int i=ind+1; i<n; ++i)
		keys[i-1] = keys[i];
	n--;
	return;
}

void TwoThreeTreeNode::removeFromNonLeaf(int ind)
{
	int k = keys[ind];
	if(child[ind]->n >=2)
	{
		int pred = getPred(ind);
		keys[ind] = pred;
		child[ind]->remove(pred);
	}
	else if(child[ind+1]->n >= 2)
	{
		int succ = getSucc(ind);
		keys[ind] = succ;
		child[ind+1]->remove(succ);
	}
	else{
		merge(ind);
		child[ind]->remove(k);
	}
	return;
}

int TwoThreeTreeNode::getPred(int ind)
{
	TwoThreeTreeNode *curr = child[ind];
	while(!curr->leaf)
		curr = curr->child[curr->n];
	return curr->keys[curr->n-1];
}

int TwoThreeTreeNode::getSucc(int ind) 
{ 
	TwoThreeTreeNode *curr = child[ind+1]; 
    	while (!curr->leaf) 
    		curr = curr->child[0]; 
    	return curr->keys[0]; 
} 
  
void TwoThreeTreeNode::fill(int ind) 
{ 
	if(ind!=0 && child[ind-1]->n>=2) 
        	borrowFromPrev(ind); 

    	else if (ind!=n && child[ind+1]->n>=2) 
        	borrowFromNext(ind); 
    	else
    	{ 
        	if (ind != n) 
            		merge(ind); 
        	else
            		merge(ind-1); 
    	} 
    	return; 
} 

void TwoThreeTreeNode::borrowFromPrev(int ind) 
{ 
  
    	TwoThreeTreeNode *c=child[ind]; 
    	TwoThreeTreeNode *sibling=child[ind-1]; 

    	for (int i=c->n-1; i>=0; --i) 
        	c->keys[i+1] = c->keys[i]; 
  
    	if (!c->leaf) 
    	{ 
        	for(int i=c->n; i>=0; --i) 
        	    c->child[i+1] = c->child[i]; 
    	} 
    	c->keys[0] = keys[ind-1]; 

    	if(!c->leaf) 
        	c->child[0] = sibling->child[sibling->n]; 

    	keys[ind-1] = sibling->keys[sibling->n-1]; 
  
    	c->n += 1; 
    	sibling->n -= 1; 
  
 	return; 
} 

void TwoThreeTreeNode::borrowFromNext(int ind) 
{ 
  
    	TwoThreeTreeNode *c=child[ind]; 
    	TwoThreeTreeNode *sibling=child[ind+1]; 
  
    	c->keys[(c->n)] = keys[ind]; 

    	if (!(c->leaf)) 
        	c->child[(c->n)+1] = sibling->child[0]; 
  
    	keys[ind] = sibling->keys[0]; 
 
    	for (int i=1; i<sibling->n; ++i) 
        	sibling->keys[i-1] = sibling->keys[i]; 

    	if (!sibling->leaf) 
    	{ 
        	for(int i=1; i<=sibling->n; ++i) 
            		sibling->child[i-1] = sibling->child[i]; 
    	} 

    	c->n += 1; 
    	sibling->n -= 1; 
  
    	return; 
} 

void TwoThreeTreeNode::merge(int ind) 
{ 
    	TwoThreeTreeNode *c = child[ind]; 
    	TwoThreeTreeNode *sibling = child[ind+1]; 

    	c->keys[1] = keys[ind]; 
 
    	for (int i=0; i<sibling->n; ++i) 
        	c->keys[i+2] = sibling->keys[i]; 
  
    	if (!c->leaf) 
    	{ 
        	for(int i=0; i<=sibling->n; ++i) 
            		c->child[i+2] = sibling->child[i]; 
    	} 
  
    	for (int i=ind+1; i<n; ++i) 
        	keys[i-1] = keys[i]; 
 
    	for (int i=ind+2; i<=n; ++i) 
        	child[i-1] = child[i]; 

    	c->n += sibling->n+1; 
    	n--; 

    	delete(sibling); 
    	return; 
} 

void TwoThreeTree::remove(int k) 
{ 
    	if (!root) 
    	{ 
        	cout << "The tree is empty\n"; 
        	return; 
    	} 
 
    	root->remove(k); 

    	if (root->n==0) 
    	{ 
        	TwoThreeTreeNode *tmp = root; 
        	if (root->leaf) 
            		root = NULL; 
        	else
            		root = root->child[0]; 
 
        	delete tmp; 
    	} 
    	return; 
} 
		

		

int main() 
{ 
    TwoThreeTree tree; 
	int n,k,ch;
        ch=3;
        while(true)
        {
        cout<<"Enter\n1 to insert \n 2 to delete \n0 to exit\n";
        cin>>ch;
        if(ch==1)
        {
	cout<<"Enter the no. of values"<<endl;
	cin>>n;
	cout<<"Enter the values"<<endl;
	for(int i=0; i<n; i++)
	{
		cin>>k;
		tree.insert(k);
	}
	cout << "TwoThreeTree after insertion is\n"; 
    	tree.traverse();
        }
        else if(ch==2)
        {
	cout<<"Enter the key to be deleted \n";
	cin>>k;
	tree.remove(k);
	cout<<"TwoThreeTree after deletion is \n";
	tree.traverse();
        }
        else if(ch==0) exit(0);
        else cout<<"Wrong choice.Try again\n";
        }
	return 0;
 
} 
