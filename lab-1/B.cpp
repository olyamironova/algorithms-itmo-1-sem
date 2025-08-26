#include <iostream>
int main () {
    long long n, k;
    std::cin >> n >> k;
    long long a[n];
    for (long long i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (long long i = 0; i < n; i++) {
        std::cout << a[(n - (k % n) + i) % n] << " ";
    }
}