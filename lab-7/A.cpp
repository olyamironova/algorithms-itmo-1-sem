#include <iostream>
#include <vector>

void GrayCode(long long n) {
    if (n <= 0) {
        return;
    }

    std::vector<std::string> arr = {"0", "1"};

    for (long long i = 2; i < (1 << n); i <<= 1) {
        for (long long j = i - 1; j >= 0; --j) {
            arr.push_back(arr[j]);
        }

        for (long long j = 0; j < i; ++j) {
            arr[j] = "0" + arr[j];
        }

        for (long long j = i; j < 2 * i; ++j) {
            arr[j] = "1" + arr[j];
        }
    }

    for (const auto &code : arr) {
        std::cout << code << '\n';
    }
}

int main() {
    long long n;
    std::cin >> n;
    GrayCode(n);
    std::cout << "\n";
    return 0;
}