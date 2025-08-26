#include <iostream>

bool Checking(long long distance, long long* places, long long n, long long Necessary) {
    long long LastBoyar = *places;
    long long Boyars = 1;
    for (long long j = 1; j < n; j++) {
        long long NewBoyar = places[j];
        if ((NewBoyar - LastBoyar) >= distance) {
            Boyars ++;
            LastBoyar = NewBoyar;
        }
    }
    return Boyars >= Necessary;
}

int main() {
    long long AmountPlaces, boyars;
    std::cin >> AmountPlaces >> boyars;
    long long places[AmountPlaces];
    for (long long j = 0; j < AmountPlaces; j++) {
        std::cin >> places[j];
    }
    long long left = 0;
    long long right = places[AmountPlaces - 1] - places[0] + 1;
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        if (Checking(mid, places, AmountPlaces, boyars)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    std::cout << left;
}