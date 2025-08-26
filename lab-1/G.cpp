#include <iostream>
int main () {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;
        int left = 15; 
        int right = 30;
        for (int j = 0; j < n; j++) { 
            int score;
            std::string sign;
            std::cin >> sign >> score;
                if ((sign == ">=") && (score >= 15) && (left <= score)) {
                        left = score;
                    }
                if ((sign == "<=") && (right <= 30) && (right >= score)) {
                        right = score;
                    }
                if (left <= right) {
                    std::cout << left << "\n";
                }
                    else {
                    std::cout << -1 << "\n";
                    }
                }
            }
        }
