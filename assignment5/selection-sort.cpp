#include <iostream>

using namespace std;

// Selection sort - Repeatedly choose the smallest element, then the second
// smallest and so on until all the element are sorted. Time complexity -
// O(n^2).
void SelectionSort(int* a, int n) {
  for (int i = 0; i < n; i++) {
    int min_i = i;
    for (int j = i; j < n; j++) {
      if (a[min_i] > a[j]) min_i = j;
    }
    swap(a[i], a[min_i]);
  }
}

int main(void) {
  int n = 10;
  int a[] = { 0, 9, 8, 1, 3, 2, 7, 4, 6, 5 };
  cout << "Sequence before sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;

  SelectionSort(a, n);

  cout << "Sequence after  sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;
  return 0;
}


