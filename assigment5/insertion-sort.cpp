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


