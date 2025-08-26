#include <iostream>
int main () {
    int x; int y;
    std::cin >> x >> y;
    while (true) {
        if ((x == 0) || (y == 0)) {
            if (x > y) {
                std::cout << x;
                break;
            }
            else {
                std::cout << x;
                break;
            }
        }
        if (x > y) {
            x = x - y;
        }
        else {
            y = y - x;
        }
    }
}