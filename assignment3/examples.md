Примери
=======

### Пример - реализация на основни функции за манипулиране на възлите на дървета за двоично търсене. ###

```C++
#include <iostream>

using namespace std;

// This file contains a simple implementation of binary search tree nodes and
// some basic functions to manipulate them. Included are functions for
// searching, inserting and traversing binary search trees as well as functions
// for printing their contents in various ways.
//
// A binary search tree known as a BST is a rooted binary tree defined as
// follows:
//
//   * An empty rooted binary tree is a binary search tree.
//   * A non-empty rooted binary tree is a binary search tree if and only
//     if its left subtree is a binary search tree, it's right subtree is
//     a binary search tree and the value of its root element is greater than
//     all the values in the left subtree and smaller than all the values
//     in the right subtree.
//
// The Node data type and the functions that manipulate it are
// intentionally not implemented using templates in order to make
// the underlying algorithms easier to understand.


// Can be implemented using templates for the values stored inside the nodes.
struct Node {
  int value;
  Node* left;
  Node* right;

  Node(int value, Node* left, Node* right) {
    this->value = value;
    this->left = left;
    this->right = right;
  }
};

// Returns the node of the binary search tree rooted at root which contains
// the given value or NULL if such a value does not exist in the tree.
Node* Search(Node* root, int value) {
  if (root == NULL) {
    return NULL;
  }
  if (value == root->value) {
    return root;
  }
  if (value < root->value) {
    return Search(root->left, value);
  } else {
    return Search(root->right, value);
  }
}

// Inserts a new Node with the given value into the binary search tree while
// maintaining the binary search tree property. A pointer to the root Node
// of the new tree is returned as a result. This pointer points to the old
// root Node if it is not NULL or to a newly created Node otherwise.
Node* Insert(Node* root, int value) {
  if (root == NULL) {
    return new Node(value, NULL, NULL);
  }
  if (value < root->value) {
    root->left = Insert(root->left, value);
  } else {
    root->right = Insert(root->right, value);
  }
  return root;
}

// Computes the height of the tree rooted at root. The height of a tree is the
// number of nodes along the longest path from the root of the tree to a leaf
// of the tree.
int Height(Node* root) {
  if (root == NULL) {
    return 0;
  }
  return 1 + max(Height(root->left), Height(root->right));
}

// A function that does an in-order traversal of the nodes of a binary search
// tree and for each node calls the function f. An in-order traversal of the
// nodes in a rooted binary tree is done by first recursively doing an in-order
// traversal of the nodes in the left subtree followed by visiting the root
// followed by recursively doing an in-order traversal of the nodes in the
// right subtree.
void TraverseInOrder(Node* root, void (*f) (Node*)) {
  if (root == NULL) {
    return;
  }

  TraverseInOrder(root->left, f);
  f(root);
  TraverseInOrder(root->right, f);
}

// A function that does a pre-order traversal of the nodes of a binary search
// tree and for each node calls the function f. An pre-order traversal of the
// nodes in a rooted binary tree is done by first visiting the root node of
// the binary tree followed by recursively doing a pre-order traversal of the
// nodes in the left subtree followed by recursively doing a pre-order
// traversal of the nodes in the right subtree.
void TraversePreOrder(Node* root, void (*f) (Node*)) {
  if (root == NULL) {
    return;
  }

  f(root);
  TraversePreOrder(root->left, f);
  TraversePreOrder(root->right, f);
}

// A function that does a post-order traversal of the nodes of a binary search
// tree and for each node calls the function f. An post-order traversal of the
// nodes in a rooted binary tree is done by recursively doing a post-order
// traversal of the nodes in the left subtree followed by recursively doing a
// post-order traversal of the nodes in the right subtree followed by visiting
// the root node of the binary tree.
void TraversePostOrder(Node* root, void (*f)(Node*)) {
  if (root == NULL) {
    return;
  }

  TraversePostOrder(root->left, f);
  TraversePostOrder(root->right, f);
  f(root);
}

// Print the nodes of a binary search tree rooted at root in a human
// readable directory like structure by using new lines and indentation
// determined by the depth of the current node.
void PrintIndented(Node* root, int depth) {
  for (int i = 0; i < depth; i++) {
    cout << "  ";
  }

  if (root == NULL) {
    cout << "NULL" << endl;
  } else {
    cout << root->value << endl;
    PrintIndented(root->left, depth + 1);
    PrintIndented(root->right, depth + 1);
  }
}

// Deallocates the memory for a single tree node.
void DeleteNode(Node* node) {
  delete node;
}

// Deallocates the memory for the whole binary search tree rooted at root.
void DeleteTree(Node* root) {
  if (root == NULL) {
    return;
  }
  DeleteTree(root->left);
  DeleteTree(root->right);
  DeleteNode(root);
}

// Deallocates the memory for the whole binary search tree rooted at root by
// delegating to the generic TraversePostOrder algorithm with the appropriate
// function as an argument.
void DeleteTree2(Node* root) {
  TraversePostOrder(root, DeleteNode);
}

// Prints the value of a single node.
void PrintNode(Node* node) {
  cout << node->value << endl;
}

// A simple driver program that exercises binary search trees.
int main(void) {
  // Creating a binary search tree by manually creating all nodes.
  Node* root1 =
      new Node(
          10,
          new Node(
              5,
              new Node(1, NULL, NULL),
              new Node(9, NULL, NULL)),
          new Node(
              15,
              new Node(12, NULL, NULL),
              new Node(20, NULL, NULL)));

  cout << "Hierarchical representation of the first tree:" << endl;
  PrintIndented(root1, 0);
  cout << "In-order traversal:" << endl;
  TraverseInOrder(root1, PrintNode);
  cout << "Pre-order traversal:" << endl;
  TraversePreOrder(root1, PrintNode);
  cout << "Post-order traversal:" << endl;
  TraversePostOrder(root1, PrintNode);
  cout << "Height of the tree: " << Height(root1) << " " << endl;

  cout << "Searching for the node with a value of 12: ";
  if (Search(root1, 12)->value == 12) {
    cout << "Found!" << endl;
  }

  DeleteTree(root1);

  cout << endl << endl;

  // Creating the same binary search tree but with the insert operation.
  Node* root2 = NULL;
  root2 = Insert(root2, 10);
  root2 = Insert(root2, 5);
  root2 = Insert(root2, 1);
  root2 = Insert(root2, 9);
  root2 = Insert(root2, 15);
  root2 = Insert(root2, 12);
  root2 = Insert(root2, 20);

  cout << "Hierarchical representation of second tree:" << endl;
  PrintIndented(root2, 0);
  cout << "In-order traversal:" << endl;
  TraverseInOrder(root2, PrintNode);
  cout << "Pre-order traversal:" << endl;
  TraversePreOrder(root2, PrintNode);
  cout << "Post-order traversal:" << endl;
  TraversePostOrder(root2, PrintNode);
  cout << "Height of the tree: " << Height(root2) << " " << endl;

  cout << "Searching for the node with a value of 9: ";
  if (Search(root2, 9)->value == 9) {
    cout << "Found!" << endl;
  }

  DeleteTree2(root2);

  return 0;
}
```

