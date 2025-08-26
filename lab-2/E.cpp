#include <iostream>

long long counter = 0;

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
			counter += (mid - left) - iterator_1;
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

int main () {
	long long n;
	std::cin >> n;
	long long a[n];
	for (long long i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	mergeSortRecursive(a, 0, n);
	std::cout << counter;
}