#include <iostream>

void swap(int* poiner_one, int* pointer_two) {
	int temp;
	temp = *poiner_one;
	*poiner_one = *pointer_two;
	*pointer_two = temp;
}

int main () {
	int n;
	std::cin >> n;
	int a[n];
	for (int i = 0; i < n; i++) {
		a[i] = i + 1;
	}
	for (int i = 2; i < n; i++) {
		swap(&a[i], &a[i / 2]);
	}
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
}