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

