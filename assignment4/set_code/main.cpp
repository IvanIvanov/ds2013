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

