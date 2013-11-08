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

