#include <iostream>
#include <vector>

void PrintTree(const std::vector<long long>& values, long long left_index, long long right_index) {
    if (left_index > right_index) {
        return;
    }
    long long middle_index = left_index + ((right_index - left_index) / 2);
    std::cout << values[middle_index] << " ";
    PrintTree(values, left_index, middle_index - 1);
    PrintTree(values, middle_index + 1, right_index);
}

int main() {
    long long n;
    std::cin >> n;
    long long value;
    std::vector<long long> values;
    for (long long i = 0; i < n; ++i) {
        std::cin >> value;
        values.push_back(value);
    }
    PrintTree(values, 0, n - 1);
}