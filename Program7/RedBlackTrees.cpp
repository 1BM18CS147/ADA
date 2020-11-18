
#include <iostream>
using namespace std;

struct RBNode {
  int data;
  RBNode *parent;
  RBNode *left;
  RBNode *right;
  int color;
};


class RBTree {
   private:
  RBNode* root;
  RBNode* Tnull;

  void initNode(RBNode* node, RBNode* parent) {
    node->data = 0;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->color = 0;
  }

 
  void rbTransplant(RBNode* x, RBNode* y) {
    if (x->parent == NULL) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->parent = y->parent;
  }


  void balance(RBNode* n) {
    RBNode* m;
    while (n->parent->color == 1) {
      if (n->parent == n->parent->parent->right) {
        m = n->parent->parent->left;
        if (m->color == 1) {
          m->color = 0;
          n->parent->color = 0;
          n->parent->parent->color = 1;
          n = n->parent->parent;
        } else {
          if (n == n->parent->left) {
            n = n->parent;
            rightRotate(n);
          }
          n->parent->color = 0;
          n->parent->parent->color = 1;
          leftRotate(n->parent->parent);
        }
      } else {
        m = n->parent->parent->right;

        if (m->color == 1) {
          m->color = 0;
          n->parent->color = 0;
          n->parent->parent->color = 1;
          n = n->parent->parent;
        } else {
          if (n == n->parent->right) {
            n = n->parent;
            leftRotate(n);
          }
          n->parent->color = 0;
          n->parent->parent->color = 1;
          rightRotate(n->parent->parent);
        }
      }
      if (n == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printN(RBNode* root, string s, bool last) {
    if (root != Tnull) {
      cout << s;
      if (last) {
        cout << "Right----";
        s += "   ";
      } else {
        cout << "Left ----";
        s += "|  ";
      }

      string NodeColor = root->color ? "Red" : "Black";
      cout << root->data << "(" << NodeColor << ")" << endl;
      printN(root->left, s, false);
      printN(root->right, s, true);
    }
  }

   public:
  RBTree() {
    Tnull = new RBNode;
    Tnull->color = 0;
    Tnull->left = NULL;
    Tnull->right = NULL;
    root = Tnull;
  }



  void leftRotate(RBNode* n) {
    RBNode* y = n->right;
    n->right = y->left;
    if (y->left != Tnull) {
      y->left->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL) {
      this->root = y;
    } else if (n == n->parent->left) {
      n->parent->left = y;
    } else {
      n->parent->right = y;
    }
    y->left = n;
    n->parent = y;
  }

  void rightRotate(RBNode* n) {
    RBNode* y = n->left;
    n->left = y->right;
    if (y->right != Tnull) {
      y->right->parent = n;
    }
    y->parent = n->parent;
    if (n->parent == NULL) {
      this->root = y;
    } else if (n == n->parent->right) {
      n->parent->right = y;
    } else {
      n->parent->left = y;
    }
    y->right = n;
    n->parent = y;
  }

  // Inserting a node
  void insert(int value) {
    RBNode* node = new RBNode;
    node->parent = NULL;
    node->data = value;
    node->left = Tnull;
    node->right = Tnull;
    node->color = 1;

    RBNode* y = NULL;
    RBNode* n = this->root;

    while (n != Tnull) {
      y = n;
      if (node->data < n->data) {
        n = n->left;
      } else {
        n = n->right;
      }
    }

    node->parent = y;
    if (y == NULL) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == NULL) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == NULL) {
      return;
    }

    balance(node);
  }

  RBNode* getRoot() {
    return this->root;
  }

  void printTree() {
    if (root) {
      printN(this->root, "", true);
    }
  }
};



int main() {
  RBTree tree;
  int n,val;
  cout<<"Enter number of nodes\n";
  cin>>n;
  while(n){
  cout<<"Enter value\n";
  cin>>val;
  tree.insert(val);
  n--;
  }

  

  tree.printTree();
}


