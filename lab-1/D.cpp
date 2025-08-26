#include <iostream>
int main() {
    int seasons, episods_in_seasons, all_episods;
    std::cin >> seasons >> episods_in_seasons >> all_episods;
    int missing = 0;
    int** series = new int*[(seasons + 1)];
    for (int i = 0; i < (seasons + 1); i++) {
        series[i] = new int[(episods_in_seasons + 1)];
    }
    for (int i = 0; i < all_episods; i++) {
        int number_of_episod, number_of_season;
        std::cin >> number_of_episod >> number_of_season;
        series[number_of_season][number_of_episod] = 1;
    }

    for (int i = 1; i < (seasons + 1); i ++) {
        for (int j = 1; j < (episods_in_seasons + 1); j ++) {
            if (series[i][j] != 1) {
                missing = missing + 1;
            }
        }
    }
    std::cout << missing << "\n";
    for (int i = 1; i < (seasons + 1); i ++) {
        for (int j = 1; j < (episods_in_seasons + 1); j ++) {
            if (series[i][j] != 1) {
                std::cout << j << " " << i << "\n";
            }
        }
    }
}