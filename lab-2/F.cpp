#include <iostream>

void merge(std::pair <long long, long long> *a, int left, int mid, int right) {
	int iterator_1 = 0, iterator_2 = 0;
	std::pair <long long, long long> result[right - left];
	while ((left + iterator_1 < mid) && (mid + iterator_2 < right)) {
		if (a[left + iterator_1].first > a[mid + iterator_2].first) {
			result[iterator_1 + iterator_2].first = a[left + iterator_1].first;
			result[iterator_1 + iterator_2].second = a[left + iterator_1].second;
			iterator_1 ++;
		}
		else if (a[left + iterator_1].first == a[mid + iterator_2].first) {
			if (a[left + iterator_1].second < a[mid + iterator_2].second) {
				result[iterator_1 + iterator_2].first = a[left + iterator_1].first;
				result[iterator_1 + iterator_2].second = a[left + iterator_1].second;
				iterator_1 ++;
				}
			else {
				result[iterator_1 + iterator_2].first = a[mid + iterator_2].first;
				result[iterator_1 + iterator_2].second = a[mid + iterator_2].second;
				iterator_2 ++;
				}
			}
			else {
				result[iterator_1 + iterator_2].first = a[mid + iterator_2].first;
				result[iterator_1 + iterator_2].second = a[mid + iterator_2].second;
				iterator_2 ++;
				}
	}
	while (left + iterator_1 < mid) {
		result[iterator_1 + iterator_2].first = a[left + iterator_1].first;
		result[iterator_1 + iterator_2].second = a[left + iterator_1].second;
		iterator_1 ++;
	}
	while (mid + iterator_2 < right) {
		result[iterator_1 + iterator_2].first = a[mid + iterator_2].first;
		result[iterator_1 + iterator_2].second = a[mid + iterator_2].second;
		iterator_2 ++;
	}
	for (int i = 0; i < (iterator_1 + iterator_2); i++) {
		a[left + i] = result[i];
	}
}

void mergeSortRecursive(std::pair <long long, long long> *a, int left, int right) {
	if (left + 1 >= right) {
		return;
	}
	int mid = (left + right) / 2;
	mergeSortRecursive(a, left, mid);
	mergeSortRecursive(a, mid, right);
	merge(a, left, mid, right);
}

int main () {
	const long long mod = 1e9 + 7;
	int n, k, m;
	std::cin >> n >> m >> k;
	long long coefficient[n];
	for (int i = 0; i < n; i++) {
		std::cin >> coefficient[i];
	}
	std::pair <long long, long long> raiting[m];
	
	for (int i = 0; i < m; i++) {
		long long grades[n];
		long long key;
		for (int j = 0; j < n; j++) {
			std::cin >> key;
			grades[j] = key % mod;
		}
		for (int j = 0; j < n; j++) {
			raiting[i].first = (raiting[i].first + (grades[j] * coefficient[j])) % mod;
			raiting[i].second = i;
		}
	}

	mergeSortRecursive(raiting, 0, m);
	
	for (int i = 0; i < k; i++) {
		std::cout << raiting[i].second + 1 << " ";
	}
}