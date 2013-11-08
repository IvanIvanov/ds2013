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

