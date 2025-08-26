#include <iostream>
int main () {
    int n; std::string s;
    std::cin >> n >> s;
    int left = 0; int right = n - 1;
    int counter_of_errors = 0;
    while (left < right) {
        if (s[left] == s[right]) {
            left ++; right--;
            continue;
        }
        else if (s[left] != s[right]) {
            counter_of_errors ++;
            // if ((s[left] == s[right + 1]) & (right != n - 1)) {
            //     left ++; right --;
            // }
            if (s[left] == s[right - 1]) {
                right --;
            }
            // else if ((s[left - 1] == s[right]) & (left != 0)) {
            //     left --; right--;
            // }
            else if (s[left + 1] == s[right]) {
                left ++;
            }
        }
        if (counter_of_errors > 1) {
            break;
        }
    }
    if (counter_of_errors <= 1) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}