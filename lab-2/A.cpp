#include <iostream>

int main () {
	int n;
	std::cin >> n;
	int a[n];
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	int key;
	for (int i = 1; i < n; i++) {
		key = a[i];
		int j = i - 1;
		while ((j >= 0) && (key < a[j])) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
	for (int i = 0; i < n; i++) {
		std::cout << a[i] << " ";
	}
}