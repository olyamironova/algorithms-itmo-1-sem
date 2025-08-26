#include <iostream>

void swap(long long* pointer_one, long long* pointer_two) {
    long long temp = *pointer_one;
    *pointer_one = *pointer_two;
    *pointer_two = temp;
}

void siftDown(long long *a, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (a[right] > a[left])) {
            j = right;
        }
        if (a[i] >= a[j]) {
            break;
        }
        swap(&a[i], &a[j]);
        i = j;
    }
}

int main() {
    long long n;
    std::cin >> n;
    long long a[n];
    for (long long i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (long long i = n - 1; i >= 0; --i) {
        siftDown(a, i, n);
    }
    long long max_board = n;
    for (long long i = 0; i < n; ++i) {
        swap(&a[0], &a[--max_board]);
        siftDown(a, 0, max_board);
    }
    for (long long i = 0; i < n; ++i) {
        std::cout << a[i] << " ";
    }
}
