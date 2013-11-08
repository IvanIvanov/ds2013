#ifndef SET_NODE_H_
#define SET_NODE_H_

#include <cstdlib>

// A generic implementation of a binary search tree node.
template <typename T>
struct Node {
  T value;
  Node<T>* left;
  Node<T>* right;

  Node(T value, Node<T>* left, Node<T>* right) {
    this->value = value;
    this->left = left;
    this->right = right;
  }
};

// Returns the node of the binary search tree rooted at root which contains
// the given value or NULL if such a value does not exist in the tree.
template <typename T>
Node<T>* Search(Node<T>* root, T value) {
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
// of the new tree is returned as the result. This pointer points to the old
// root Node if it is not NULL or to a newly created Node otherwise.
template <typename T>
Node<T>* Insert(Node<T>* root, T value) {
  if (root == NULL) {
    return new Node<T>(value, NULL, NULL);
  }
  if (value < root->value) {
    root->left = Insert(root->left, value);
  } else {
    root->right = Insert(root->right, value);
  }
  return root;
}

// Delete a node with the given value from a binary search tree while
// maintaining the binary search tree property. A pointer to the root
// node of the new tree is returned as the result. If the tree does not
// contain a node with the given value than no node is deleted.
template <typename T>
Node<T>* DeleteValue(Node<T>* root, T value) {
  Node<T>* node = Search(root, value);
  if (node == NULL) {
    return root;
  }
  return DeleteNode(root, node);
}

// Delete a particular node from the binary search tree while maintaining
// the binary search tree property. A pointer to the root node of the new tree
// is returned as a result. It is assumed that the node to be deleted is not
// NULL and is present in the binary search tree rooted at root.
template <typename T>
Node<T>* DeleteNode(Node<T>* root, Node<T>* node) {
  if (node == root) {
    return DeleteRoot(root);
  }
  DeleteInnerNode(root, node);
  return root;
}

// Delete the root node from a binary search tree while maintaining the
// binary search tree property. A pointer to the root node of the new tree
// is returned as a result. It is assumed that the root node is not NULL.
template <typename T>
Node<T>* DeleteRoot(Node<T>* root) {
  if (root->left == NULL && root->right == NULL) {
    delete root;
    return NULL;
  }
  if (root->left != NULL && root->right == NULL) {
    Node<T>* left = root->left;
    delete root;
    return left;
  }
  if (root->left == NULL && root->right != NULL) {
    Node<T>* right = root->right;
    delete root;
    return right;
  }
  Node<T>* successor = Successor(root);
  root->value = successor->value;
  return DeleteNode(root, successor);
}

// Delete an inner node (a node that is not the root of the tree) from a
// binary search tree while maintaining the binary search tree property.
template <typename T>
void DeleteInnerNode(Node<T>* root, Node<T>* node) {
  Node<T>* parent = Parent(root, node);
  if (node->left == NULL && node->right == NULL) {
    if (parent->left == node) {
      parent->left = NULL;
    } else {
      parent->right = NULL;
    }
    delete node;
  } else if (node->left != NULL && node->right == NULL) {
    if (parent->left == node) {
      parent->left = node->left;
    } else {
      parent->right = node->left;
    }
    delete node;
  } else if (node->left == NULL && node->right != NULL) {
    if (parent->left == node) {
      parent->left = node->right;
    } else {
      parent->right = node->right;
    }
    delete node;
  } else {
    Node<T>* successor = Successor(node);
    node->value = successor->value;
    DeleteNode(root, successor);
  }
}

// Find the node in the binary search tree that contains the next greatest
// value than the value at the given node. It is assumed that the given node
// always has two non-NULL children. This successor node is found be finding
// the leftmost grandchild of the current nodes right sub-tree.
template <typename T>
Node<T>* Successor(Node<T>* node) {
  Node<T>* current = node->right;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

// Find the parent node of a given node in a binary search tree. It is assumed
// that the given node is always present in the tree rooted at root and is
// guaranteed not to be the root node.
template <typename T>
Node<T>* Parent(Node<T>* root, Node<T>* node) {
  if (root == NULL) {
    return NULL;
  }
  if (root->left == node) {
    return root;
  }
  if (root->right == node) {
    return root;
  }
  if (node->value < root->value) {
    return Parent(root->left, node);
  } else {
    return Parent(root->right, node);
  }
}

// Deletes all the nodes in a binary search tree.
template <typename T>
void DeleteTree(Node<T>* root) {
  if (root == NULL) {
    return;
  }
  DeleteTree(root->left);
  DeleteTree(root->right);
  delete root;
}

#endif

