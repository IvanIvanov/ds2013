#include <iostream>

using namespace std;

// A function that partitions a sub-interval of an array treating the last
// element as the pivot.
int Partition(int* a, int left, int right) {
  int pivot = a[right];
  int i = left - 1;
  for (int j = left; j <= right; j++) {
    if (a[j] <= pivot) {
      swap(a[++i], a[j]);
    }
  }
  return i;
}

// Quick sort - Partition the interval to be sorted into two parts. The left
// part will contain all elements smaller than or equal to the pivot (some
// arbitrary element from the interval to be sorted) and the right part will
// contain all elements greater than the pivot. The two parts can now be sorted
// independently with quick sort which will produce a sorted order for the
// whole interval. Expected time complexity - O(n log(n)).
void QuickSort(int* a, int left, int right) {
  if (left >= right) {
    return;
  }

  int i = Partition(a, left, right);
  QuickSort(a, left, i - 1);
  QuickSort(a, i + 1, right);
}

int main(void) {
  int n = 10;
  int a[] = { 0, 9, 8, 1, 3, 2, 7, 4, 6, 5 };
  cout << "Sequence before sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;

  QuickSort(a, 0, n - 1);

  cout << "Sequence after  sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;
  return 0;
}

