#include <iostream>

void swap(int *pointer_one, int *pointer_two) {
    int temp;
    temp = *pointer_one;
    *pointer_one = *pointer_two;
    *pointer_two = temp;
}

int main () {
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                a[j] --;
                a[j + 1] ++;
                swap(&a[j], &a[j + 1]);
                flag = true;
            }
            if (a[j + 1] < a[j]) {
                std::cout << ":(";
                return 0;
            }
        }
        if (!flag) {
                for (int w = 0; w < n; w++) {
                    std::cout << a[w] << " ";
                }
                return 0;
            }
    }
        
    for (int w = 0; w < n; w++) {
        std::cout << a[w] << " ";
    }
}