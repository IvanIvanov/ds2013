#ifndef MAP_NODE_H_
#define MAP_NODE_H_

#include <cstdlib>

// A generic implementation of a (key, value) binary search tree node.
template <typename K, typename V>
struct Node {
  K key;
  V value;
  Node<K, V>* left;
  Node<K, V>* right;

  Node(K key, V value, Node<K, V>* left, Node<K, V>* right) {
    this->key = key;
    this->value = value;
    this->left = left;
    this->right = right;
  }
};

// Returns the node of the binary search tree rooted at root which contains
// the given key or NULL if such a key does not exist in the tree.
template <typename K, typename V>
Node<K, V>* Search(Node<K, V>* root, K key) {
  if (root == NULL) {
    return NULL;
  }
  if (key == root->key) {
    return root;
  }
  if (key < root->key) {
    return Search(root->left, key);
  } else {
    return Search(root->right, key);
  }
} 

// Inserts a new Node with the given key and value into the binary search tree
// while maintaining the binary search tree property. A pointer to the root
// node of the new tree is returned as the result. This pointer points to the
// old root node if it is not NULL or to a newly created node otherwise.
template <typename K, typename V>
Node<K, V>* Insert(Node<K, V>* root, K key, V value) {
  if (root == NULL) {
    return new Node<K, V>(key, value, NULL, NULL);
  }
  if (key < root->key) {
    root->left = Insert(root->left, key, value);
  } else {
    root->right = Insert(root->right, key, value);
  }
  return root;
}

// Delete a node with the given key from a binary search tree while
// maintaining the binary search tree property. A pointer to the root
// node of the new tree is returned as the result. If the tree does not
// contain a node with the given key than no node is deleted.
template <typename K, typename V>
Node<K, V>* DeleteKey(Node<K, V>* root, K key) {
  Node<K, V>* node = Search(root, key);
  if (node == NULL) {
    return root;
  }
  return DeleteNode(root, node);
}

// Delete a particular node from the binary search tree while maintaining
// the binary search tree property. A pointer to the root node of the new tree
// is returned as a result. It is assumed that the node to be deleted is not
// NULL and is present in the binary search tree rooted at root.
template <typename K, typename V>
Node<K, V>* DeleteNode(Node<K, V>* root, Node<K, V>* node) {
  if (node == root) {
    return DeleteRoot(root);
  }
  DeleteInnerNode(root, node);
  return root;
}

// Delete the root node from a binary search tree while maintaining the
// binary search tree property. A pointer to the root node of the new tree
// is returned as a result. It is assumed that the root node is not NULL.
template <typename K, typename V>
Node<K, V>* DeleteRoot(Node<K, V>* root) {
  if (root->left == NULL && root->right == NULL) {
    delete root;
    return NULL;
  }
  if (root->left != NULL && root->right == NULL) {
    Node<K, V>* left = root->left;
    delete root;
    return left;
  }
  if (root->left == NULL && root->right != NULL) {
    Node<K, V>* right = root->right;
    delete root;
    return right;
  }
  Node<K, V>* successor = Successor(root);
  root->key = root->key;
  root->value = successor->value;
  return DeleteNode(root, successor);
}

// Delete an inner node (a node that is not the root of the tree) from a
// binary search tree while maintaining the binary search tree property.
template <typename K, typename V>
void DeleteInnerNode(Node<K, V>* root, Node<K, V>* node) {
  Node<K, V>* parent = Parent(root, node);
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
    Node<K, V>* successor = Successor(node);
    node->key = successor->key;
    node->value = successor->value;
    DeleteNode(root, successor);
  }
}

// Find the node in the binary search tree that contains the next greatest
// key than the key at the given node. It is assumed that the given node
// always has two non-NULL children. This successor node is found be finding
// the leftmost grandchild of the current nodes right sub-tree.
template <typename K, typename V>
Node<K, V>* Successor(Node<K, V>* node) {
  Node<K, V>* current = node->right;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

// Find the parent node of a given node in a binary search tree. It is assumed
// that the given node is always present in the tree rooted at root and is
// guaranteed not to be the root node.
template <typename K, typename V>
Node<K, V>* Parent(Node<K, V>* root, Node<K, V>* node) {
  if (root == NULL) {
    return NULL;
  }
  if (root->left == node) {
    return root;
  }
  if (root->right == node) {
    return root;
  }
  if (node->key < root->key) {
    return Parent(root->left, node);
  } else {
    return Parent(root->right, node);
  }
}

// Deletes all the nodes in a binary search tree.
template <typename K, typename V>
void DeleteTree(Node<K, V>* root) {
  if (root == NULL) {
    return;
  }
  DeleteTree(root->left);
  DeleteTree(root->right);
  delete root;
}

#endif

