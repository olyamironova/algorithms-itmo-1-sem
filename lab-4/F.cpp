#include <iostream>
#include <vector>
#include <algorithm>

struct Multiplier {
    long long current_value;
    long long number_of_add_values;
    long long original_value;

    Multiplier(long long CurrentValue, long long NumberOfAddValues, long long OriginalValue) {
        current_value = CurrentValue;
        number_of_add_values = NumberOfAddValues;
        original_value = OriginalValue;
    }
};

std::vector<long long> Primes(long long n) {
    std::vector<long long> PrimeDivisors;
    std::vector<char> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (long long i = 2; i <= n; ++i) {
        if (prime[i])  {
            if (i * 1 * i <= n) {
                for (long long j = i * i; j <= n; j += i) {
                    prime[j] = false;
                }
            }
        }
    }
    for (long long i = 0; i < n; ++i) {
        if (prime[i] == true) {
            PrimeDivisors.push_back(i);
        }
    }
    return PrimeDivisors;
}

void swap(Multiplier* pointer_one, Multiplier* pointer_two) {
    Multiplier temp = *pointer_one;
    *pointer_one = *pointer_two;
    *pointer_two = temp;
}


void siftDown(std::vector<Multiplier> &Numbers, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (Numbers[right].current_value < Numbers[left].current_value)) {
            j = right;
        }
        if (Numbers[i].current_value <= Numbers[j].current_value) {
            break;
        }
        swap(&Numbers[i], &Numbers[j]);
            i = j;
    }
}

void heapify(std::vector<Multiplier> &Numbers) {
    long long n = Numbers.size();
    for (long long i = n - 1; i >= 0; --i) {
        siftDown(Numbers, i, n);
    }
}

void siftUp(std::vector<Multiplier> &Numbers, long long i) {
    while (Numbers[i].current_value < Numbers[(i - 1) / 2].current_value) {
        swap(&Numbers[i], &Numbers[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Multiplier extract_min(std::vector<Multiplier> &Numbers) {
    Multiplier tmp = Numbers[0];
    swap(&Numbers[0], &Numbers.back());
    Numbers.pop_back();
    siftDown(Numbers, 0, Numbers.size());
    return tmp;
}

int main() {
    long long n;
    std::cin >> n;
    std::vector<Multiplier> Numbers;
    std::vector<long long> FirstPrimeDivisors;
    FirstPrimeDivisors.reserve(5000000);
    FirstPrimeDivisors = Primes(5000000);
    for (long long i = 0; i < n; ++i) {
        struct Multiplier multiplier = {FirstPrimeDivisors[i], 0, FirstPrimeDivisors[i]};
        Numbers.push_back(multiplier);
    }
    heapify(Numbers);

    std::vector<long long> answer;

    for (long long i = 0; i < Numbers.size(); ++i) {
        Multiplier temporary = extract_min(Numbers);
        for (long long i = 0; i < temporary.number_of_add_values * 2 + 1 - temporary.number_of_add_values; ++i) {
            answer.push_back(temporary.original_value);
        }
        temporary.number_of_add_values = temporary.number_of_add_values * 2 + 1;
        temporary.current_value = temporary.current_value * temporary.current_value;
        Numbers.push_back(temporary);
        siftUp(Numbers, Numbers.size() - 1);
    }

    std::sort(answer.begin(), answer.end());
    std::cout << answer.size() << '\n';
    for (long long i = 0; i < answer.size(); ++i) {
        std::cout << answer[i] << " ";
    }
}