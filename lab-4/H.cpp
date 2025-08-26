#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

void sum(std::vector<int> &lhs, std::string &rhs) {
    bool overflow = false;
    long long max_length = std::max(lhs.size(), rhs.size());
    for (long long k = 0; k < max_length; ++k) {
        if (k == lhs.size()) {
            lhs.push_back(0);
        }
        int8_t temporary;
        if (k >= rhs.size()) {
            temporary = lhs[k] + overflow;
        } else {
            temporary = (int)(rhs[k] - '0' + overflow + lhs[k]);
        }
        lhs[k] = temporary % 10;
        if (temporary >= 10) {
            overflow = true;
        } else {
            overflow = false;
        }
        if ((!overflow) && (k >= rhs.size())) {
            break;
        }
    }
    if (overflow) {
        lhs.push_back(overflow);
    }
}

int main() {
    long long n;
    std::cin >> n;
    std::vector<int> lhs;
    for (long long i = 0; i < n; ++i) {
        std::string rhs;
        std::cin >> rhs;
        std::reverse(rhs.begin(), rhs.end());
        sum(lhs, rhs);
    }
    for (long long i = lhs.size() - 1; i >= 0; --i) {
        std::cout << lhs[i];
    }
}