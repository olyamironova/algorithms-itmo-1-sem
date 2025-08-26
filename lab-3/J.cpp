#include <iostream>

int main() {
    long long n;
    std::cin >> n;
    std::pair <long long, std::string> data[n + 1];
    long long max = -1000000;
    for (long long j = 1; j < n + 1; j++) {
        std::cin >> data[j].first;
        if (data[j].first > max) {
            max = data[j].first;
        }
    }
    for (long long j = 1; j < n + 1; j++) {
        std::cin >> data[j].second;
    }

    long long k = max;
    long long count[k + 1];
    long long q;
    std::cin >> q;
    long long PrefSumm[k + 1];
    PrefSumm[0] = 0;
    long long PrefCount[k + 1];
    PrefCount[0] = 0;
    long long PrefXOR[k + 1];
    PrefXOR[0] = 0;
    for (long long j = 0; j < k + 1; j++) {
        count[j] = 0;
    }

    for(long long j = 0; j < n + 1; j++) {
        count[data[j].first]++;
    }

    for (long long j = 0; j < k + 1; j++) {
        PrefSumm[j] = 0;
    }
    for (long long j = 1; j < k + 1; j++) {
        PrefSumm[j] = j * count[j] + PrefSumm[j - 1];
    }

    for (long long j = 0; j < k + 1; j++) {
        PrefXOR[j] = 0;
    }

    for (long long j = 1; j < k + 1; j++) {
        if (count[j] % 2 == 0) {
            PrefXOR[j] = PrefXOR[j - 1] ^ 0;
        } else {
            PrefXOR[j] = PrefXOR[j - 1] ^ j;
        }
    }
    
    for(long long j = 1; j < k + 1; j++) {
        count[j] = count[j - 1] + count[j];
    }

    std::pair <long long, std::string> sorted[n + 1];
    for (long long j = n + 1 - 1; j > 0; j--) {
        sorted[count[data[j].first] - 1].first = data[j].first;
        sorted[count[data[j].first] - 1].second = data[j].second;
        count[data[j].first]--;
    }
    for (long long j = 1; j < n; j++) {
        std::cout << sorted[j].first << " ";
    }
    std::cout << sorted[n].first << '\n';

    for (long long j = 1; j < n; j++) {
        std::cout << sorted[j].second << " ";
    }
    std::cout << sorted[n].second << '\n';

    for (long long j = 0; j < k + 1; j++) {
        PrefCount[j] = 0;
    }
    for (long long j = 1; j < n + 1; j++) {
        PrefCount[sorted[j].first]++;
    }
    for (long long j = 1; j < k + 1; j++) {
        PrefCount[j] += PrefCount[j - 1];
    }

    std::string command; long long l, r;
    long long j = 0;
    while (j < q) {
        std::cin >> command >> l >> r;
        if (command == "Count") {
            if (r <= max) {
                std::cout << (PrefCount[r] - PrefCount[l - 1]) << std::endl;
            } else {
                std::cout << (PrefCount[max] - PrefCount[l - 1]) << std::endl;
            }
        } else if (command == "Sum") {
            if (r <= max) {
                std::cout << (PrefSumm[r] - PrefSumm[l - 1]) << std::endl;
            } else {
                std::cout << (PrefSumm[max] - PrefSumm[l - 1]) << std::endl;
            }
        } else if (command == "Xor") {
            if (r <= max) {
                std::cout << (PrefXOR[r] ^ PrefXOR[l - 1]) << std::endl;
            } else {
                std::cout << (PrefXOR[max] ^ PrefXOR[l - 1]) << std::endl;
            }
        }
        j++;
    }
    return 0;
}