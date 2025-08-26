#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    long long a[n];
    for (long long i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    bool flag = true;
    for (long long i = n / 2 - 1; i >= 0; --i) {
        if ((2 * i + 1 < n) && (2 * i + 2 < n)) {
            if ((a[i] > a[2 * i + 1]) || (a[i] > a[2 * i + 2])) {
                flag = false;
                break;
            } else {
                continue;
            }
        }
    }
    if (flag) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}