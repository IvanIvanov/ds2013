Примери
===========

### Пример - Функции, които манипулират възли на свързан списък ###
Следва генерична реализация на основната градивна частица на свързаните списъци - възела (Node). Показани са и редица функции за манипулирането на възли.

```C++
#include <iostream>

using namespace std;

template <typename T>
struct Node {
  T value;
  Node<T>* next;

  Node(T value, Node<T>* next) {
    this->value = value;
    this->next = next;
  }
};

template <typename T>
Node<T>* FindElement(Node<T>* head, T elem) {
  while (head != NULL) {
    if (elem == head->value) {
      return head;
    }
    head = head->next;
  }
  return NULL;
}

template <typename T>
Node<T>* FindNthElement(Node<T>* head, int n) {
  while (head != NULL) {
    if (n == 1) {
      return head;
    }
    n--;
    head = head->next;
  }
  return NULL;
}

template <typename T>
int Length(Node<T>* head) {
  int length = 0;
  while (head != NULL) {
    length++;
    head = head->next;
  }
  return length;
}

template <typename T>
void PrintList(Node<T>* head) {
  while (head != NULL) {
    cout << head->value << endl;
    head = head->next;
  }
}

template <typename T>
void DeleteList(Node<T>* head) {
  while (head != NULL) {
    Node<T>* next = head->next;
    delete head;
    head = next;
  }
}

template <typename T>
Node<T>* InsertBefore(Node<T>* node, int value) {
  return new Node<T>(value, node);
}

template <typename T>
Node<T>* InsertAfter(Node<T>* node, int value) {
  if (node == NULL) {
    return NULL;
  }
  Node<T>* new_node = new Node<T>(value, node->next);
  node->next = new_node;
  return new_node;
}

template <typename T>
bool DeleteAfter(Node<T>* node) {
  if (node == NULL) {
    return false;
  }
  if (node->next == NULL) {
    return false;
  }
  Node<T>* tmp = node->next->next;
  delete node->next;
  node->next = tmp;
  return true;
}

template <typename T>
Node<T>* Reverse(Node<T>* head) {
  Node<T>* prev = NULL;
  Node<T>* cur = head;
  while (cur != NULL) {
    Node<T>* tmp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = tmp;
  }
  return prev;
}

// A basic driver program that does simple tests on the list
// node manipulation functions.
int main(void) {
  cout << "Creating the list list1." << endl;
  Node<int>* list1 = new Node<int>(1, new Node<int>(2, NULL));
  PrintList(list1);
  cout << "The second element of list1 has a value of: "
       << FindNthElement(list1, 2)->value << endl;
  cout << "The length of list1 is: " << Length(list1) << endl;
  
  cout << "Inserting the value 7 after the first element of the list." << endl;
  InsertAfter(list1->next, 7);
  PrintList(list1);
  
  cout << "Deleting the element after the second element of the list." << endl;
  DeleteAfter(list1->next);
  PrintList(list1);

  cout << "Deleting list1" << endl;
  DeleteList(list1);

  cout << "Creating the list list2." << endl;
  Node<int>* list2 = NULL;
  for (int i = 10; i >= 0; i--) {
    list2 = InsertBefore(list2, i);
  }
  PrintList(list2);
  cout << "Reversing list2." << endl;
  list2 = Reverse(list2);
  PrintList(list2);

  cout << "Deleting list2." << endl;
  DeleteList(list2);

  return 0;
}

```

### Пример - Реализация на едносвързан списък ###
Следва генерична реализация на едносвързан списък изграден от възли.

```C++
#include <iostream>

using namespace std;

template <typename T>
class SinglyLinkedList {
 private:
  struct Node {
    T value;
    Node* next;
    Node(T value, Node* next);
  };
  Node* head; // The first node of the linked list.
  int size;   // The number of elements in the linked list.

 public:
  SinglyLinkedList();
  ~SinglyLinkedList();
  void InsertFront(const T& value);
  bool RemoveFront(T& result);
  bool Front(T& result);
  bool NthElement(int n, T& result);
  int Size();
};

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
  head = NULL;
  size = 0;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  while (head != NULL) {
    Node* next = head->next;
    delete head;
    head = next;
  }
}

template <typename T>
void SinglyLinkedList<T>::InsertFront(const T& value) {
  head = new Node(value, head);
  size++;
}

template <typename T>
bool SinglyLinkedList<T>::RemoveFront(T& result) {
  if (size == 0) {
    return false;
  }
  result = head->value;
  Node* next = head->next;
  delete head;
  head = next;
  size--;
  return true;
}

template <typename T>
bool SinglyLinkedList<T>::Front(T& result) {
  if (size == 0) {
    return false;
  }
  result = head->value;
  return true;
}

// Stores the value of the nth element in the result output variable.
// The first element of the list is accessed with n = 1 (not n = 0).
template <typename T>
bool SinglyLinkedList<T>::NthElement(int n, T& result) {
  Node* current = head;
  while (current != NULL) {
    if (n == 1) {
      result = current->value;
      return true;
    }
    n--;
    current = current->next;
  }
  return false;
}

template <typename T>
int SinglyLinkedList<T>::Size() {
  return size;
}

template <typename T>
SinglyLinkedList<T>::Node::Node(T value, Node* next) {
  this->value = value;
  this->next = next;
}

// A simple main function to take the SinglyLinkedList out for a test drive.
int main(void) {
  SinglyLinkedList<int> list;
  for (int i = 1; i <= 10; i++) {
    list.InsertFront(i);
  }
  cout << "Created a list of size: " << list.Size() << endl;
  for (int i = 1; i <= 10; i++) {
    int value;
    list.NthElement(i, value);
    cout << "The Nth element of the list is: " << value << endl;
  }

  for (int i = 1; i <= 10; i++) {
    cout << "Removing the first element from the list." << endl;
    int value;
    list.RemoveFront(value);
    cout << "The new list size is: " << list.Size() << endl;
  }

  return 0;
}

```

### Пример - Реализация на двусвързан списък ###
Следва генерична реализация на двусвързан списък.

```C++
#include <iostream>

using namespace std;

// This class implements a circular doubly linked list by using a special
// sentinel node. The next pointer of the sentinel node points to the head
// node of the list and the prev pointer of the sentinel points to the last
// node of the list. The list is circularly linked because the next pointer
// of the last node points to the sentinel and the prev pointer of the head
// node points to the sentinel - thus creating a loop which passes through the
// sentinel. The benefit of using a sentinel node is that it significantly
// simplifies the logic for inserting and removing elements from the list
// because it eliminates the handling of cases in which certain pointers are
// NULL.
template <typename T>
class DoublyLinkedList {
 private:
  struct Node {
    T value;
    Node* prev;
    Node* next;
    Node();
    Node(T value, Node* prev, Node* next);
  };

  Node* sentinel; // A special dummy node.
  int size;       // The number of elements in the list.

  void InsertAfter(Node* node, const T& value);
  void RemoveNode(Node* node, T& result);

 public:
  DoublyLinkedList();
  ~DoublyLinkedList();
  void InsertFront(const T& value);
  void InsertBack(const T& value);
  bool RemoveFront(T& result);
  bool RemoveBack(T& result);
  bool Front(T& result);
  bool Back(T& result);
  int Size();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  sentinel = new Node();
  sentinel->next = sentinel;
  sentinel->prev = sentinel;
  size = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node* current = sentinel->next;
  while (current != sentinel) {
    Node* next = current->next;
    delete current;
    current = next;
  }
  delete sentinel;
}

template <typename T>
void DoublyLinkedList<T>::InsertFront(const T& value) {
  InsertAfter(sentinel, value);
  size++;
}

template <typename T>
void DoublyLinkedList<T>::InsertBack(const T& value) {
  InsertAfter(sentinel->prev, value);
  size++;
}

template <typename T>
bool DoublyLinkedList<T>::RemoveFront(T& result) {
  if (size == 0) {
    return false;
  }
  RemoveNode(sentinel->next, result);
  size--;
  return true;
}

template <typename T>
bool DoublyLinkedList<T>::RemoveBack(T& result) {
  if (size == 0) {
    return false;
  }
  RemoveNode(sentinel->prev, result);
  size--;
  return true;
}

template <typename T>
bool DoublyLinkedList<T>::Front(T& result) {
  if (size == 0) {
    return false;
  }
  result = sentinel->next->value;
  return true;
}

template <typename T>
bool DoublyLinkedList<T>::Back(T& result) {
  if (size == 0) {
    return false;
  }
  result = sentinel->prev->value;
  return true;
}

template <typename T>
int DoublyLinkedList<T>::Size() {
  return size;
}

template <typename T>
void DoublyLinkedList<T>::InsertAfter(Node* node, const T& value) {
  Node* new_node = new Node(value, node, node->next);
  new_node->next->prev = new_node;
  new_node->prev->next = new_node;
}

template <typename T>
void DoublyLinkedList<T>::RemoveNode(Node* node, T& result) {
  node->prev->next = node->next;
  node->next->prev = node->prev;
  result = node->value;
  delete node;
}

template <typename T>
DoublyLinkedList<T>::Node::Node() {
  this->prev = NULL;
  this->next = NULL;
}

template <typename T>
DoublyLinkedList<T>::Node::Node(T value, Node* prev, Node* next) {
  this->value = value;
  this->prev = prev;
  this->next = next;
}

// Simple test driver.
int main(void) {
  DoublyLinkedList<int> list;
  for (int i = 1; i <= 5; i++) {
    list.InsertBack(i);
  }
  for (int i = 6; i <= 10; i++) {
    list.InsertFront(i);
  }
  cout << "List size: " << list.Size() << endl;
  for (int i = 1; i <= 10; i++) {
    int value;
    list.RemoveFront(value);
    cout << "Removing the element at the front: " << value << endl;
  }
  cout << "List size: " << list.Size() << endl;

  return 0;
}

```

