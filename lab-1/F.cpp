#include <iostream>
int main () {
    int countDay;
    std::cin >> countDay;
    int day[countDay];
    int globalSumm = 0, leftSumm[countDay], rightSumm[countDay];
    int temporary = 0;
    for (int i = 0; i < countDay; i++) {
        std::cin >> day[i];
    }
    for (int i = 0; i < countDay; i++) {
        globalSumm += day[i];
    }
    leftSumm[0] = 0;
    for (int i = 1; i < countDay; i++) {
        leftSumm[i] = leftSumm[i - 1] + day[i - 1];
    }
    int ans = -1;
    for (int i = 0; i < countDay; i++) {
        if (leftSumm[i] == globalSumm - leftSumm[i + 1]) {
            ans = i;
            break;
        }
    }
    std::cout << ans;
    return 0;
}