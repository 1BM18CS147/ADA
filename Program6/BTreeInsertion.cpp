#include<iostream> 
using namespace std; 

 
class BTreeN 
{ 
	int *values; 
	int t;	  
	BTreeN **C; 
	int n;	 
	bool leaf; 
public: 
	BTreeN(int _t, bool _leaf);  
 
	void insertNonFull(int k);
        void splitChild(int i, BTreeN *y); 
	void traverse();
	BTreeN *search(int k); 
friend class BTree; 
}; 


class BTree 
{ 
	BTreeN *root;
	int t;
public: 
	BTree(int _t) 
	{ root = NULL; t = _t; } 
	void traverse() 
	{ if (root != NULL) root->traverse(); }
	BTreeN* search(int k) 
	{ return (root == NULL)? NULL : root->search(k); }
	void insert(int k); 
}; 

BTreeN::BTreeN(int t1, bool leaf1) 
{ 
	t = t1; 
	leaf = leaf1;
        n = 0; 
	values = new int[2*t-1]; 
	C = new BTreeN *[2*t]; 
	
} 

void BTreeN::traverse() 
{ 
        int i;
	for (i = 0; i < n; i++) 
	{ 
		if (leaf == false) 
			C[i]->traverse(); 
		cout << " " << values[i]; 
	}
	if (leaf == false) 
		C[i]->traverse(); 
} 
BTreeN *BTreeN::search(int k) 
{ 

	int i = 0; 
	while (i < n && k > values[i]) i++; 
		

	if (values[i] == k) 
		return this; 

	if (leaf == true) 
		return NULL; 

	return C[i]->search(k); 
} 

void BTree::insert(int k) 
{ 

	if (root == NULL) 
	{ 
		root = new BTreeN(t, true); 
		root->values[0] = k;
		root->n = 1; 
	} 
	else 
	{  
		if (root->n == 2*t-1) 
		{ 
			BTreeN *s = new BTreeN(t, false); 
			s->C[0] = root; 
			s->splitChild(0, root);
			int i = 0; 
			if (s->values[0] < k) 
				i++; 
			s->C[i]->insertNonFull(k); 
 
			root = s; 
		} 
		else 
			root->insertNonFull(k); 
	} 
} 

void BTreeN::insertNonFull(int k) 
{ 
	int i = n-1;
	if (leaf == true) 
	{ 
		while (i >= 0 && values[i] > k) 
		{ 
			values[i+1] = values[i]; 
			i--; 
		} 
		values[i+1] = k; 
		n = n+1; 
	} 
	else 
	{ 
		while (i >= 0 && values[i] > k) i--; 
			
		if (C[i+1]->n == 2*t-1) 
		{ 
			splitChild(i+1, C[i+1]); 
			if (values[i+1] < k) 
				i++; 
		} 
		C[i+1]->insertNonFull(k); 
	} 
} 

void BTreeN::splitChild(int i, BTreeN *y) 
{ 
	BTreeN *z = new BTreeN(y->t, y->leaf); 
	z->n = t - 1; 
	for (int j = 0; j < t-1; j++) 
		z->values[j] = y->values[j+t];
	if (y->leaf == false) 
	{ 
		for (int j = 0; j < t; j++) 
			z->C[j] = y->C[j+t]; 
	}  
	y->n = t - 1; 
	for (int j = n; j >= i+1; j--) 
		C[j+1] = C[j]; 
	C[i+1] = z;  
	for (int j = n-1; j >= i; j--) 
		values[j+1] = values[j]; 
	values[i] = y->values[t-1]; 
	n = n + 1; 
} 

int main() 
{ 
        int n,k,num;
        cout<<"Enter degree of tree\n";
        cin>>num;
        BTree t(num);
	cout<<"Enter the no. of values"<<endl;
	cin>>n;
	cout<<"Enter the values"<<endl;
	for(int i=0; i<n; i++)
	{
		cin>>k;
		t.insert(k);
	}
	cout << "BTree after insertion is\n"; 
    	t.traverse();
        cout<<"\n";
        
	return 0;
 
	
} 

