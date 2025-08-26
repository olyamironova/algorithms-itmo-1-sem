#include <iostream>

void LSD(std::string *Words, int n, int Iteration, int Length) {
    int Basis = 'z' / 1;
    std::string *SortedMassive = new std::string[n];
    int Count[Basis + 1];
    int k = Length - 1;
    while (k > Length - Iteration - 1) {
        for (int i = 0; i < Basis + 1; i++) {
            Count[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            Count[Words[i][k] + 1]++;
        }
        for (int i = 0; i < Basis; i++) {
            Count[i + 1] += Count[i];
        }
        for (int i = 0; i < n; i++) {
            SortedMassive[Count[Words[i][k]]++] = Words[i];
        }
        for (int i = 0; i < n; i++) {
            Words[i] = SortedMassive[i];
        }
        k--;
    }
}

int main() {
    std::string* Words;
    int CountOfWords, Length, CountIteration;
    std::cin >> CountOfWords >> Length >> CountIteration;
    Words = new std::string[CountOfWords];
    std::string Temporarly;
    for (int i = 0; i < CountOfWords; i++) {
        std::cin >> Temporarly;
        const char* Word = Temporarly.c_str();
        Words[i] = Word;
    }
    LSD(Words, CountOfWords, CountIteration, Length);
    for (int i = 0; i < CountOfWords; i++) {
        std::cout << Words[i] << std::endl;
    }
}