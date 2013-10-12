Примери
===========

### Пример - Реализация на стек с масив ###
Следва реализация на абстрактния тип данни за стек, базиран на масив с фиксирана дължина. Реализацията е генерична и позволява създаването на стекове от различни типове данни.

```c++
// A simple generic stack implementation based on an array.
template <typename T>
class Stack {
private:
  T* data;  // The array that stores the elements in the stack.
  int size; // The number of elements in data.
  int top;  // the index of data into which the next value is pushed.

public:
  Stack(int size);
  ~Stack();
  bool Push(const T& value);
  bool Pop(T& value);
  bool Top(T& value);
  bool IsEmpty();
};

template <typename T>
Stack<T>::Stack(int size) {
  this->size = size;
  this->top = 0;
  this->data = new T[size];
}

template <typename T>
Stack<T>::~Stack() {
  delete [] data;
}

template <typename T>
bool Stack<T>::Push(const T& value) {
  if (top == size) {
    return false;
  }
  data[top++] = value;
  return true;
}

template <typename T>
bool Stack<T>::Pop(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[--top];
  return true;
}

template <typename T>
bool Stack<T>::Top(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[top - 1];
  return true;
}

template <typename T>
bool Stack<T>::IsEmpty() {
  return top == 0;
}

```

### Пример - Реализация на стек с динамичен масив ###
Следва реализация на абстрактния тип данни за стек, базиран на масив, който се увеличава и свива според броя елементи, които съдържа. Реализацията е генерична и позволява създаването на стекове от различни типове данни.

```c++
// An implementation of a generic dynamic stack that can expand and shrink
// based on the number of elements it contains.
template <typename T>
class DynamicStack {
private:
  T* data;      // The array that stores the elements in the stack.
  int top;      // the index of data into which the next value is pushed.
  int capacity; // The current size of the data array.
  void Resize(int new_capacity);

public:
  DynamicStack();
  ~DynamicStack();
  void Push(const T& value);
  bool Pop(T& result);
  bool Top(T& result);
  bool IsEmpty();
};

template <typename T>
DynamicStack<T>::DynamicStack() {
  this->capacity = 2;
  this->top = 0;
  this->data = new T[capacity];
}

template <typename T>
DynamicStack<T>::~DynamicStack() {
  delete [] data;
}

template <typename T>
void DynamicStack<T>::Push(const T& value) {
  if (top >= capacity) {
    Resize(2 * capacity);
  }
  data[top++] = value;
}

template <typename T>
bool DynamicStack<T>::Pop(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[--top];
  if (capacity > 16 && 4 * top < capacity) {
    Resize(capacity / 2);
  }
  return true;
}

template <typename T>
bool DynamicStack<T>::Top(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[top - 1];
  return true;
}

template <typename T>
bool DynamicStack<T>::IsEmpty() {
  return top == 0;
}

template <typename T>
void DynamicStack<T>::Resize(int new_capacity) {
  T* new_data = new T[new_capacity];
  for (int i = 0; i < top; i++) {
    new_data[i] = data[i];
  }
  delete [] data;
  data = new_data;
  capacity = new_capacity;
}
```

### Пример - Реализация на опашка с масив ###
Следва реализация на абстрактния тип данни за опашка, базирана на масив с фиксирана дължина използваща техниката "wrap around". Реализацията е генерична и позволява създаването на опашки от различни типове данни.


```c++
// An implementation of a generic queue based on a fixed sized array with wrap around. 
template <typename T>
class Queue {
private:
  T* data;      // The array that stores the elements of the queue.
  int size;     // The size of the data array.
  int front;    // The index that points to the element at the head of the queue.
  int back;     // The index where the next elemene of the queue will be pushed.
  int elements; // The total number of elements in the queue.

public:
  Queue(int size);
  ~Queue();
  bool Push(const T& value);
  bool Pop(T& result);
  bool Front(T& result);
  bool IsEmpty();
};

template <typename T>
Queue<T>::Queue(int size) {
  this->size = size;
  this->front = 0;
  this->back = 0;
  this->elements = 0;
  this->data = new T[size];
}

template <typename T>
Queue<T>::~Queue() {
  delete [] data;
}

template <typename T>
bool Queue<T>::Push(const T& value) {
  if (elements == size) {
    return false;
  }
  data[back] = value;
  back = (back + 1) % size;
  elements++;
  return true;
}

template <typename T>
bool Queue<T>::Pop(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[front];
  front = (front + 1) % size;
  elements--;
  return true;
}

template <typename T>
bool Queue<T>::Front(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[front];
  return true;
}

template <typename T>
bool Queue<T>::IsEmpty() {
  return elements == 0;
}
```


### Пример - Задача ###
Да се напише програма, която чете n цели числа от стандартния вход, сумира ги и изпечатва сумата на стандартния изход.

**Формат на входа:**

На първия ред на стандартния вход се съдържа единствено цяло число n (0 <= n <= 1000), което указва броя на числата, които да бъдат събрани. Следват n цели числа ai, където -1000 <= ai <= 1000.

**Формат на изхода:**

Да се изпечата единствено число на стандартния изход, което да е сумата от числата, които трябва да бъдат събрани. Забележка: числото трябва да бъде следвано от символ за нов ред.

**Примерен вход:**
```
3
1 2 3
```

**Примерен изход:**
```
6
```

**Примерно решение:**
```c++
#include <iostream>

using namespace std;

// This simple example demonstrates how to read and write integers
// from the standard input and output.
int main(void) {
  int n;
  int sum = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int value;
    cin >> value;
    sum += value;
  }
  cout << sum << endl;
  return 0;
}

```

### Пример - Задача ###
Да се напише програма, която упражнява реализация на стек. Програмата трябва да симулира двете стандартни операции върху стек:

* Push value - която добавя цялото число value на върха на стека.
* Pop        - която премахва числото на върха на стека.

като чете операциите от стандартния вход и пише резултатите от тях на стандартния изход.

**Формат на входа:**

На първия ред на стандартния вход се съдържа единствено цяло число n (0 <= n <= 1000), което указва броя на операциите, които да се симулират. Следват n операции, за Push и Pop, като вида на операцията се определя от едно число което е или 0 (за операцията Push) или 1 (за операцията Pop). Ako операцията е Push (т.е. е зададена с код 0), то кода е последван от още едно цяло число x, където -1000 <= x <= 1000 е числото което трябва да бъде добавено към върха на стека.

**Формат на изхода:**

За всяка операция от тип Pop (т.е. операция зададена с кода 1), да се изпечата на отделен ред числото, което е било премахнато в резултат на операцията. Забележка - може да се предполага, че никога няма да бъде дадена операция Pop за празен стек.

**Примерен вход:**
```
10
0 1
0 2
0 3
0 4
1
1
0 5
1
1
1
```

**Примерен изход:**
```
4
3
5
2
1
```

**Примерно решение:**

```c++
#include <iostream>

using namespace std;

// A simple generic stack implementation based on an array.
template <typename T>
class Stack {
private:
  T* data;  // The array that stores the elements in the stack.
  int size; // The number of elements in data.
  int top;  // the index of data into which the next value is pushed.

public:
  Stack(int size);
  ~Stack();
  bool Push(const T& value);
  bool Pop(T& value);
  bool Top(T& value);
  bool IsEmpty();
};

template <typename T>
Stack<T>::Stack(int size) {
  this->size = size;
  this->top = 0;
  this->data = new T[size];
}

template <typename T>
Stack<T>::~Stack() {
  delete [] data;
}

template <typename T>
bool Stack<T>::Push(const T& value) {
  if (top == size) {
    return false;
  }
  data[top++] = value;
  return true;
}

template <typename T>
bool Stack<T>::Pop(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[--top];
  return true;
}

template <typename T>
bool Stack<T>::Top(T& result) {
  if (IsEmpty()) {
    return false;
  }
  result = data[top - 1];
  return true;
}

template <typename T>
bool Stack<T>::IsEmpty() {
  return top == 0;
}

#define PUSH_COMMAND 0
#define POP_COMMAND  1

// Takes the stack out for a test drive.
int main(void) {
  int n;
  Stack<int> stack(1024);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int command;
    int value;
    cin >> command;
    if (command == PUSH_COMMAND) {
      cin >> value;
      stack.Push(value);
    } else if (command == POP_COMMAND) {
      stack.Pop(value);
      cout << value << endl;
    }
  }
  return 0;
}
```

