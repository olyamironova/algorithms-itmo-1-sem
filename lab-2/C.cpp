#include <iostream>

void merge(long long *a, long long left, long long mid, long long right) {
	long long iterator_1 = 0, iterator_2 = 0;
	long long result[right - left];
	while ((left + iterator_1 < mid) && (mid + iterator_2 < right)) {
		if (a[left + iterator_1] < a[mid + iterator_2]) {
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
	for (int i = 0; i < (iterator_1 + iterator_2); i++) {
		a[left + i] = result[i];
	}
}

void mergeSortRecursive(long long* a, long long left, long long right) {
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
	long long x = 0; long long y = 0; long long s = 0; long long i = n - 1;
	while (i > 0) {
		if ((a[i] - a[i - 1] == 1) || (a[i] == a[i - 1])) {
			if (x == 0) {
				x = a[i - 1];
			}
			else {
				y = a[i - 1];
			}
			i--;
			i--;
		}
		else {
			i--;
		}
		if ((x != 0) && (y != 0)) {
			s += x * y;
			x = 0; y = 0;
		}
	}
	std::cout << s;
}