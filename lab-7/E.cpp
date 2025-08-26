#include <iostream>
#include <string>
#include <map>

class ArithmeticEncoder {
private:
    std::map<char, double> charProbabilities;

public:
    void calculateProbabilities(const std::string& input) {
        charProbabilities.clear();
        int totalChars = input.length();

        for (char ch : input) {
            charProbabilities[ch]++;
        }

        for (auto& pair : charProbabilities) {
            pair.second /= totalChars;
        }
    }

    double encode(const std::string& message) {
        double lowerBound = 0.0;
        double upperBound = 1.0;

        for (char ch : message) {
            double rangeSize = upperBound - lowerBound;
            upperBound = lowerBound + rangeSize * (charProbabilities[ch] + accumulateProbabilities(ch));
            lowerBound = lowerBound + rangeSize * accumulateProbabilities(ch);
        }

        return lowerBound;
    }

private:
    double accumulateProbabilities(char ch) {
        double accumulatedProb = 0.0;

        for (const auto& pair : charProbabilities) {
            if (pair.first < ch) {
                accumulatedProb += pair.second;
            }
        }

        return accumulatedProb;
    }
};

int main() {
    ArithmeticEncoder encoder;

    std::string inputString;
    std::cin >> inputString;

    encoder.calculateProbabilities(inputString);
    double encodedValue = encoder.encode(inputString);

    std::cout.precision(6);
    std::cout << std::fixed << encodedValue << std::endl;

    return 0;
}
