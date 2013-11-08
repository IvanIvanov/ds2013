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

