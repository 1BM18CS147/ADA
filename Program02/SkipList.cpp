#include <bits/stdc++.h> 
using namespace std; 

class Node 
{ 
public: 
	int key; 
	Node **forward; 
	Node(int, int); 
}; 



Node::Node(int key, int level) 
{ 
	this->key = key; 

	forward = new Node*[level+1]; 

	memset(forward, 0, sizeof(Node*)*(level+1)); 
}; 


class SkipList 
{ 
	
	int MaxLevel; 	
	float P; 
	int level; 
	Node *head; 
public: 
	SkipList(int, float); 
	int randLevel(); 
	Node* createNode(int, int); 
	void insertElement(int); 
        void deleteElement(int); 
        void searchElement(int); 
	void PrintList(); 
}; 

SkipList::SkipList(int MaxLevel, float P) 
{ 
	this->MaxLevel = MaxLevel; 
	this->P = P; 
	level = 0; 

	head = new Node(-1, MaxLevel); 
}; 


int SkipList::randLevel() 
{ 
	float r = (float)rand()/RAND_MAX; 
	int lvl = 0; 
	while (r < P && lvl < MaxLevel) 
	{ 
		lvl++; 
		r = (float)rand()/RAND_MAX; 
	} 
	return lvl; 
}; 


Node* SkipList::createNode(int key, int level) 
{ 
	Node *n = new Node(key, level); 
	return n; 
}; 



//insertion in skip List
void SkipList::insertElement(int key) 
{ 
	Node *curr = head; 

	
	Node *update[MaxLevel+1]; 
	memset(update, 0, sizeof(Node*)*(MaxLevel+1)); 

	for (int i = level; i >= 0; i--) 
	{ 
		while (curr->forward[i] != NULL && 
			curr->forward[i]->key < key) 
			curr = curr->forward[i]; 
		update[i] = curr; 
	} 

	curr = curr->forward[0]; 

	if (curr == NULL || curr->key != key) 
	{ 

		int r_lev = randLevel(); 

		{ 
			for (int i=level+1;i<r_lev+1;i++) 
				update[i] = head; 

			level = r_lev; 
		} 


		Node* newNode = createNode(key, r_lev); 

		for (int i=0;i<=r_lev;i++) 
		{ 
			newNode->forward[i] = update[i]->forward[i]; 
			update[i]->forward[i] = newNode; 
		} 
		cout << "Inserted key " << key << "\n"; 
	} 
}; 


//Print List function
void SkipList::PrintList() 
{ 
	cout<<"\n*****Skip List*****"<<"\n"; 
	for (int i=0;i<=level;i++) 
	{ 
		Node *node = head->forward[i]; 
		cout << "Level " << i << ": "; 
		while (node != NULL) 
		{ 
			cout << node->key<<" "; 
			node = node->forward[i]; 
		} 
		cout << "\n"; 
	} 
}; 


//Deletion function
void SkipList::deleteElement(int key) 
{ 
    Node *curr = head; 

    Node *update[MaxLevel+1]; 
    memset(update, 0, sizeof(Node*)*(MaxLevel+1)); 
  
    for(int i = level; i >= 0; i--) 
    { 
        while(curr->forward[i] != NULL  && 
              curr->forward[i]->key < key) 
            curr = curr->forward[i]; 
        update[i] = curr; 
    } 
 
    curr = curr->forward[0]; 
  
  
    if(curr != NULL and curr->key == key) 
    { 
     
        for(int i=0;i<=level;i++) 
        { 
      
            if(update[i]->forward[i] != curr) 
                break; 
  
            update[i]->forward[i] = curr->forward[i]; 
        } 
  
        while(level>0 && 
              head->forward[level] == 0) 
            level--; 
         cout<<"deleted key "<<key<<"\n"; 
    } 
}; 

void SkipList::searchElement(int key) 
{ 
    Node *curr = head; 
  
    for(int i = level; i >= 0; i--) 
    { 
        while(curr->forward[i] && 
               curr->forward[i]->key < key) 
            curr = curr->forward[i]; 
  
    } 
 
    curr = curr->forward[0]; 

    if(curr and curr->key == key)  
        cout<<"Key found"<<key<<"\n"; 
}; 

int main() 
{ 
	
	srand((unsigned)time(0)); 

	
	SkipList lst(3, 0.5); 

	lst.insertElement(1); 
	lst.insertElement(3); 
	lst.insertElement(5); 
	lst.insertElement(2); 
	lst.insertElement(22); 
	lst.insertElement(39); 
	lst.insertElement(67); 
	lst.insertElement(76); 
	 
        cout<<"List after insertion"<<"\n";
	lst.PrintList(); 

        lst.deleteElement(22); 
        cout<<"List after deletion"<<"\n";
        lst.PrintList(); 
        lst.searchElement(19); 
  

       
} 

