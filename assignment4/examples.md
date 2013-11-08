Примери
=======

### Пример - Реализация на тип данни Set (множество) онсована на дърво за двоично търсене. ###

Хедърен файл - [bst-set.h](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/set_code/bst-set.h) с реализацията на Set.
```C++
#ifndef BST_SET_H_
#define BST_SET_H_

#include <cstdlib>
#include "set-node.h"

// A generic implementation of the set abstract data type that is based binary
// search trees.
template <typename T>
class Set {
 private:
  int size;
  Node<T>* root;

 public:
  Set();
  ~Set();
  bool Insert(const T& value);
  bool Contains(const T& value);
  bool Remove(const T& value);
  int  Size();
};

template <typename T>
Set<T>::Set() {
  size = 0;
  root = NULL;
}

template <typename T>
Set<T>::~Set() {
  DeleteTree(root);
}

template <typename T>
bool Set<T>::Insert(const T& value) {
  if (Contains(value)) {
    return false;
  }
  root = ::Insert(root, value);
  size++;
  return true;
}

template <typename T>
bool Set<T>::Contains(const T& value) {
  return Search(root, value) != NULL;
}

template <typename T>
bool Set<T>::Remove(const T& value) {
  if (!Contains(value)) {
    return false;
  }
  root = DeleteValue(root, value);
  size--;
  return true;
}

template <typename T>
int Set<T>::Size() {
  return size;
}

#endif

```

Хедърен файл - [set-node.h](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/set_code/set-node.h) с реализацията на възлите на дърветата за двоично търсене използвани при реализацията на Set.
```C++
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

```

Сорс файл - [main.cpp](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/set_code/main.cpp), който демонстрира операциите върху класа Set.
```C++
#include <iostream>
#include <string>
#include "bst-set.h"

using namespace std;

// An example that demonstrates the use of a set of integers.
void SetExample1(void) {
  int n = 1000;
  Set<int> s;

  cout << "Demonstrating a set of integers." << endl;

  cout << "Inserting the elements from 1 to n (1000) in an empty set." << endl;
  for (int i = 1; i <= n; i++) {
    s.Insert(i);
  }

  // The set should contain exactly n (1000) elements.
  cout << "Size: " << s.Size() << endl;

  cout << "Inserting the elements from 1 to n (1000) into the set again."
       << endl;
  // Inserting elements already contained in the set.
  for (int i = 1; i <= n; i++) {
    s.Insert(i);
  }

  // The number of elements of the set should remain the same.
  cout << "Size: " << s.Size() << endl;

  // The set should contain all the elements from 1 to n (1000).
  for (int i = 1; i <= n; i++) {
    if (!s.Contains(i)) {
      cout << "Error the element "
           << i
           << " should be contained in the set."
           << endl;
    }
  }

  cout << "Removing all odd elements from the set." << endl;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      s.Remove(i);
    }
  }

  // The set should contain exactly n / 2 (500) elements.
  cout << "Size: " << s.Size() << endl;

  cout << "Removing all even elements from the set." << endl;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 0) {
      s.Remove(i);
    }
  }

  // The set should contain exactly 0 elements.
  cout << "Size: " << s.Size() << endl;
}

// An example that demonstrates the use of a set of strings.
void SetExample2(void) {
  Set<string> s;

  cout << "Demonstrating a set of strings." << endl;

  cout << "Inserting the strings 'foo', 'bar' and 'baz' into a set." << endl;
  s.Insert("foo");
  s.Insert("bar");
  s.Insert("baz");
  cout << "Size: " << s.Size() << endl;
  cout << "Inserting the string 'foo' again." << endl;
  s.Insert("foo");
  cout << "Size: " << s.Size() << endl;
  cout << "Removing the string 'foo'." << endl;
  s.Remove("foo");
  cout << "Size: " << s.Size() << endl;
  cout << "Removing the strings 'bar' and 'baz'." << endl;
  s.Remove("bar");
  s.Remove("baz");
  cout << "Size: " << s.Size() << endl;
}

// Taking the Set implementation out for a test drive.
int main(void) {
  SetExample1();
  cout << endl;
  SetExample2();
  return 0;
}


```

### Пример - Реализация на тип данни Map (речник, който на ключове съпоставя стойности) основана на дърво за двоично търсене. ###

Хедърен файл - [bst-map.h](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/set_code/main.cpp) с реализацията на Map.
```C++
#ifndef BST_MAP_H_
#define BST_MAP_H_

#include <cstdlib>
#include "map-node.h"

// A generic implementation of the map abstract data type that is based binary
// search trees.
template <typename K, typename V>
class Map {
 private:
  int size;
  Node<K, V>* root;

 public:
  Map();
  ~Map();
  void Insert(const K& key, const V& value);
  bool GetValue(const K& key, V& value);
  bool ContainsKey(const K& key);
  bool RemoveKey(const K& key);
  int  Size();
};

template <typename K, typename V>
Map<K, V>::Map() {
  size = 0;
  root = NULL;
}

template <typename K, typename V>
Map<K, V>::~Map() {
  DeleteTree(root);
}

template <typename K, typename V>
void Map<K, V>::Insert(const K& key, const V& value) {
  if (ContainsKey(key)) {
    RemoveKey(key);
  }
  root = ::Insert(root, key, value);
  size++;
}

template <typename K, typename V>
bool Map<K, V>::GetValue(const K& key, V& value) {
  Node<K, V>* node = Search(root, key);
  if (node == NULL) {
    return false;
  }
  value = node->value;
  return true;
}

template <typename K, typename V>
bool Map<K, V>::ContainsKey(const K& key) {
  return Search(root, key) != NULL;
}

template <typename K, typename V>
bool Map<K, V>::RemoveKey(const K& key) {
  if (!ContainsKey(key)) {
    return false;
  }
  root = DeleteKey(root, key);
  size--;
  return true;
}

template <typename K, typename V>
int Map<K, V>::Size() {
  return size;
}

#endif

```

Хедърен файл - [map-node.h](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/map_code/map-node.h) с реализацията на възлите на дърветата за двоично търсене използвани при реализацията на Map.
```C++
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

```

Сорс файл - [main.cpp](https://github.com/IvanIvanov/ds2013/blob/master/assignment4/map_code/main.cpp), който демонстрира операциите върху класа Map.
```C++
#include <iostream>
#include <string>
#include "bst-map.h"

using namespace std;

// A demonstration of a map from strings to integers.
void MapExample1(void) {
  Map<string, int> m;

  cout << "Demonstrating a map from strings to integers." << endl;
  cout << "Inserting the key value pairs: ('foo', 1), ('bar', 2), ('baz', 3)."
       << endl;
  m.Insert("foo", 1);
  m.Insert("bar", 2);
  m.Insert("baz", 3);
  cout << "Size: " << m.Size() << endl;
  cout << "Inserting the key: 'bar' with a different value: 42." << endl;
  m.Insert("bar", 42);
  cout << "Size: " << m.Size() << endl;
  cout << "Removing key: 'foo'." << endl;
  m.RemoveKey("foo");
  cout << "Size: " << m.Size() << endl;
  cout << "ContainsKey('foo') = " << m.ContainsKey("foo") << endl;
  cout << "ContainsKey('bar') = " << m.ContainsKey("bar") << endl;
  cout << "ContainsKey('baz') = " << m.ContainsKey("baz") << endl;
  
  int value;
  m.GetValue("bar", value);
  cout << "GetValue('bar') = " << value << endl;
  m.GetValue("baz", value);
  cout << "GetValue('baz') = " << value << endl;
}

// Taking the Map implementation out for a test drive.
int main(void) {
  MapExample1();
  return 0;
}

```

