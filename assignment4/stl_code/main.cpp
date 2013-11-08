#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;
 
// Demonstrate the vector container built-in the standard STL library.
// For more information on vectors see:
//     http://www.cplusplus.com/reference/vector/vector/
void VectorExample(void) {
  cout << "Demonstrating the vector container." << endl;

  cout << "Creating an empty vector." << endl;
  vector <int> v1;

  cout << "Adding the values from 1 to 10 to the back of the vector." << endl;
  for (int i = 1; i <= 10; i++) {
    v1.push_back(i); // O(1)
  }

  cout << "Size: " << v1.size() << endl; // O(1)

  cout << "Removing the last element from the vector." << endl;
  v1.pop_back(); // O(1)

  cout << "Removing the second (index 1) from the vector." << endl;
  v1.erase(v1.begin() + 1); // O(n)

  cout << "Printing the vector." << endl;
  for (int i = 0; i < v1.size(); i++) {
    cout << v1[i] << " "; // O(1)
  }
  cout << endl;
}

// Demonstrate the set container built-in the standard STL library.
// For more information on sets see:
//     http://www.cplusplus.com/reference/set/set/
void SetExample(void) {
  cout << "Demonstrating the set container." << endl;

  cout << "Creating an empty set." << endl;
  set <int> s;
  
  cout << "Adding the values from 1 to 10 to the set." << endl;
  for (int i = 1; i <= 10; i++) {
    s.insert(i); // O(log n)
  }

  cout << "Size: " << s.size() << endl; // O(1)

  cout << "Removing the element with value 3 from the set." << endl;
  s.erase(3); // O(log n)

  cout << "Is 3 contained in the set: " << s.count(3) << endl; // O(log n)
  cout << "Is 5 contained in the set: " << s.count(5) << endl; // O(log n)
  cout << "Size: " << s.size() << endl; // O(1)
}

// Demonstrate the map container built-in the standard STL library.
// For more information on maps see:
//     http://www.cplusplus.com/reference/map/map/
void MapExample(void) {
  cout << "Demonstrating the map container." << endl;

  cout << "Creating an empty map." << endl;
  map <string, int> m;

  cout << "Adding the entries: ('foo', 1), ('bar', 2), ('baz', 3)." << endl;
  m["foo"] = 1; // O(log n)
  m["bar"] = 2; // O(log n)
  m["baz"] = 3; // O(log n)
  cout << "Size: " << m.size() << endl; // O(1)
  cout << "Setting 'bar' to the value 42." << endl;
  m["bar"] = 42; // O(log n)
  cout << "The value that corresponds to 'bar' is: " << m["bar"] << endl; // O(log n)
  cout << "Is 'foo' contained in the map: " << m.count("foo") << endl; // O(log n)
  cout << "Is 'blah' contained in the map: " << m.count("blah") << endl; // O(log n)

  cout << "Deleting the 'foo' key from the map." << endl;
  m.erase("foo"); // O(log n)
  cout << "Size: " << m.size() << endl; // O(log n)
}

// Demonstrate the queue container built-in the standard STL library.
// For more information on queues see:
//     http://www.cplusplus.com/reference/queue/queue/
void QueueExample(void) {
  cout << "Demonstrating the queue container." << endl;

  cout << "Creating an empty queue." << endl;
  queue<double> q;

  cout << "Adding the numbers from 1 to 10 to the back of the queue." << endl;
  for (int i = 1; i <= 10; i++) {
    q.push(i); // O(1)
  }
  cout << "Empty: " << q.empty() << endl; // O(1)
  cout << "The front of the queue is: " << q.front() << endl; // O(1)
  cout << "Remove the top of the queue." << endl;
  q.pop(); // O(1)
  cout << "The front of the queue is: " << q.front() << endl; // O(1)
}

int main(void) {
  VectorExample();
  cout << endl;
  SetExample();
  cout << endl;
  MapExample();
  cout << endl;
  QueueExample();
  return 0;
}

