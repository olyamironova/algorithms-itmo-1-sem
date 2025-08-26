#include <iostream>

long long binary_search_index(long long c, long long *b, long long n, long long Necessary) {
    long long left = 0, right = n;
    while (left < right) {
        long long middle = (right + left) / 2;
        if (c + b[middle] <= Necessary) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

long long obj_fun(long long *a, long long *b, long long Necessary, long long n) {
    long long count = 0;
    for (long long i = 0; i < n; i++) {
        long long x = binary_search_index(a[i], b, n, Necessary);
        count += x;
    }
    return count;
}

long long Binary_search(long long *a, long long *b, long long n, long long k) {
    long long min = a[0] + b[0];
    long long max = a[n - 1] + b[n - 1];
    while (max > min) {
        long long mid = (min + max) / 2;
        long long x = obj_fun(a, b, mid, n);
        if (x < k) {
            min = mid + 1;
        } else {
            max = mid;
        }
    }
    return min;
}

void merge(long long *a, long long left, long long mid, long long right) {
    long long iterator_1 = 0, iterator_2 = 0;
    long long result[right - left];
    while ((left + iterator_1 < mid) && (mid + iterator_2 < right)) {
        if (a[left + iterator_1] <= a[mid + iterator_2]) {
            result[iterator_1 + iterator_2] = a[left + iterator_1];
            iterator_1 ++;
        }
        else {
            result[iterator_1 + iterator_2] = a[mid + iterator_2];
            iterator_2 ++;

        }
    }
    while (left + iterator_1 < mid) {
        result[iterator_1 + iterator_2] = a[left + iterator_1];
        iterator_1 ++;
    }
    while (mid + iterator_2 < right) {
        result[iterator_1 + iterator_2] = a[mid + iterator_2];
        iterator_2 ++;
    }
    for (long long i = 0; i < (iterator_1 + iterator_2); i++) {
        a[left + i] = result[i];
    }
}

void mergeSortRecursive(long long *a, long long left, long long right) {
    if (left + 1 >= right) {
        return;
    }
    long long mid = (left + right) / 2;
    mergeSortRecursive(a, left, mid);
    mergeSortRecursive(a, mid, right);
    merge(a, left, mid, right);
}

int main() {
    long long n, k;
    std::cin >> n >> k;
    long long a[n], b[n];
    for (long long j = 0; j < n; j++) {
        std::cin >> a[j];
    }
    for (long long j = 0; j < n; j++) {
        std::cin >> b[j];
    }
    mergeSortRecursive(a, 0, n);
    mergeSortRecursive(b, 0, n);
    std::cout << Binary_search(a, b, n, k);
}