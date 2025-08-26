#include <iostream>
#include <random>

void swap(long long* poiner_one, long long* pointer_two) {
	long long temp;
	temp = *poiner_one;
	*poiner_one = *pointer_two;
	*pointer_two = temp;
}

void quicksort(long long *a, int left, int right) {
	int i = left;
	int j = right;
	int ind_pivot = rand() % (right - left + 1) + left;
	long long pivot = a[ind_pivot];
	while (i < j) {
		while (a[i] < pivot) {
			i++;
		}
		while (a[j] > pivot) {
			j--;
		}
		if (i <= j) {
			swap(&a[i], &a[j]);
			i++;
			j--;
		}
	}
	if (left < j) {
		quicksort(a, left, j);
	}
	if (right > i) {
		quicksort(a, i, right);
	}
}

int main () {
	int n;
	std::cin >> n;
	long long a[n];
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	quicksort(a, 0, n - 1);
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
}