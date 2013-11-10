Примери
=======

### Пример - сортиране чрез метода на селекцията (selection sort) ###

Сорс файл - [selection-sort.cpp](), който предоствая примерна реализация на сортиране чрез метода на селекцията:

```C++
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

```


### Пример - сортиране чрез метода на вмъкването (insertion sort) ###

Сорс файл - [insertion-sort.cpp](), който предоствая примерна реализация на сортиране чрез метода на вмъкването:

```C++
#include <iostream>

using namespace std;

// Insertion sort works the way many people sort a hand of playing cards.
// We start with an empty left hand and the cards face down on the table.
// We then remove one card at a time from the table and insert it into the
// correct position in the left hand. To find the correct position for a card,
// we compare it with each of the cards already in the hand, from right to
// left. At all times, the cards held in the left hand are sorted, and these
// cards were originally the top cards of the pile on the table. Time
// complexity - O(n^2).
void InsertionSort(int* a, int n) {
  for (int i = 1; i < n; i++) {
    int value = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > value) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = value;
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

  InsertionSort(a, n);

  cout << "Sequence after  sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;
  return 0;
}
```

### Пример - сортиране чрез метода на сливането (merge sort) ###

Сорс файл - [merge-sort.cpp](), който предоствая примерна реализация на сортиране чрез метода на сливането:

```C++
#include <iostream>

using namespace std;

#define INF 2147483647

// Merge two sorted sequences a[left..mid] and a[mid + 1..right] into a single
// sorted sequence a[left..right].
void Merge(int* a, int left, int mid, int right) {
  int n = mid - left + 1;
  int m = right - mid;
  int* a1 = new int[n + 1];
  int* a2 = new int[m + 1];
  for (int i = left; i <= mid; i++) a1[i - left] = a[i];
  for (int i = mid + 1; i <= right; i++) a2[i - mid - 1] = a[i];
  a1[n] = INF;
  a2[m] = INF;
  int i = 0;
  int j = 0;
  int k = 0;
  while (k < n + m) {
    if (a1[i] < a2[j]) {
      a[left + k] = a1[i++];
    } else {
      a[left + k] = a2[j++];
    }
    k++;
  }
  delete [] a1;
  delete [] a2;
}

// Merge sort - to sort an array split it into two halves. Recursively sort
// each of the halves using merge sort and then combine the two sorted halves
// together by merging them into a single sorted sequence. Time complexity -
// O(n log(n)).
void MergeSort(int* a, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = (left + right) / 2;
  MergeSort(a, left, mid);
  MergeSort(a, mid + 1, right);
  Merge(a, left, mid, right);
}

int main(void) {
  int n = 10;
  int a[] = { 0, 9, 8, 1, 3, 2, 7, 4, 6, 5 };
  cout << "Sequence before sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;

  MergeSort(a, 0, n - 1);

  cout << "Sequence after  sorting:";
  for (int i = 0; i < n; i++) {
    cout << " " << a[i];
  }
  cout << endl;
  return 0;
}
```

### Пример - сортиране чрез метода на бързата сортировка (quick sort) ###

Сорс файл - [quick-sort.cpp](), който предоствая примерна реализация на сортиране чрез метода на бързата сортировка:

```C++
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
```

