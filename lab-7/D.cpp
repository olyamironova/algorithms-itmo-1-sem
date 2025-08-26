#include <iostream>
#include <string>
#include <map>
#include <cmath>

#define LL long long

using namespace std;

string Decode(string encode_str) {
    LL ctr_bits = 0;
    LL w_bits = 0;

    LL size = encode_str.length();

    string decode;

    for (LL i = 0; i < size; ++i) {
        if (!((i + 1) & i)) {
            ctr_bits++;
        }
    }

    for (LL i = 0; i < ctr_bits; ++i) {
        LL sum = 0;

        for (LL j = 1LL << i; j < size; ++j) {
            if ((j + 1) & (1LL << i)) {
                sum += static_cast<LL>(encode_str[j] - '0');
            }
        }

        sum %= 2;

        if (sum != static_cast<LL>(encode_str[(1LL << i) - 1] - '0')) {
            w_bits += 1LL << i;
        }
    }

    if (w_bits) {
        encode_str[w_bits - 1] = (encode_str[w_bits - 1] == '0') ? '1' : '0';
    }

    for (auto i = 0; i < size; ++i) {
        if (i & (i + 1)) {
            decode += encode_str[i];
        }
    }

    return decode;
}

int main() {
    int n;
    cin >> n;

    string str;
    for (auto i = 0; i < n; ++i) {
        cin >> str;
        cout << Decode(str) << '\n';
    }
}