#include <iostream>
#include <vector>

void swap(std::pair<long long, long long>* pointer_one, std::pair<long long, long long>* pointer_two) {
        std::pair<long long, long long> temp = *pointer_one;
        *pointer_one = *pointer_two;
        *pointer_two = temp;
}

//(номер города, рейтинг) (номер города, гонорар)
// если города имеют одинаковый рейтинг
// то обращаемся к городу с бОльшим номером города

void siftDown_Raiting(std::vector<std::pair<long long, long long>> &heap, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (heap[right].second > heap[left].second)) {
            j = right;
        }
        else if ((right < heapsize) && (heap[right].second == heap[left].second))
            if (heap[right].first > heap[left].first) {
                j = right;
            }
        if (heap[i].second >= heap[j].second) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i = j;
    }
}

void heapify_Raiting(std::vector<std::pair<long long, long long>> &heap) {
    long long n = heap.size();
    for (long long i = n - 1; i >= 0; --i) {
        siftDown_Raiting(heap, i, n);
    }
}

void siftDown_Gonorar(std::vector<std::pair<long long, long long>> &heap, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (heap[right].second > heap[left].second)) {
            j = right;
        }
        else if ((right < heapsize) && (heap[right].second == heap[left].second))
            if (heap[right].first > heap[left].first) {
                j = right;
            }
        if (heap[i].second >= heap[j].second) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i = j;
    }
}

void heapify_Gonorar(std::vector<std::pair<long long, long long>> &heap) {
    long long n = heap.size();
    for (long long i = n - 1; i >= 0; --i) {
        siftDown_Gonorar(heap, i, n);
    }
}


long long num_of_max_gonorar(std::vector<std::pair<long long, long long>> &heap) {
    return heap[0].first;
}

long long num_of_max_raiting(std::vector<std::pair<long long, long long>> &heap) {
    return heap[0].first;
}

void extract_max_raiting(std::vector<std::pair<long long, long long>> &Raiting) {
    swap(Raiting[0], Raiting.back());
    Raiting.pop_back();
    siftDown_Raiting(Raiting, 0, Raiting.size());
}

void extract_max_gonorar(std::vector<std::pair<long long, long long>> &Gonorar) {
    swap(Gonorar[0], Gonorar.back());
    Gonorar.pop_back();
    siftDown_Raiting(Gonorar, 0, Gonorar.size());
}

int main() {
    long long n;
    std::cin >> n;
    std::vector<std::pair<long long, long long>> Raiting;
    std::vector<std::pair<long long, long long>> Gonorar;
    long long nums, raiting, gonorar;
    for (long long i = 0; i < n; ++i) {
        std::cin >> nums >> raiting >> gonorar;
        Raiting.push_back(std::make_pair(nums, raiting));
        Gonorar.push_back(std::make_pair(nums, gonorar));
    }
    heapify_Raiting(Raiting);
    heapify_Gonorar(Gonorar);
    std::vector<long long> Call;
    std::vector<long long> Tour;
    long long m;
    std::string answer;
    std::cin >> m;
    while (m > 0) {
        while ((!(Raiting.empty())) && (m > 0)) {
            if (num_of_max_raiting(Raiting) == num_of_max_gonorar(Gonorar)) {
                Tour.push_back(Raiting[0].first);
                extract_max_raiting(Raiting);
                extract_max_gonorar(Gonorar);
            } else if (num_of_max_raiting(Raiting) != num_of_max_gonorar(Gonorar)) {
                Call.push_back(Raiting[0].first);
                std::cin >> answer;
                if (answer == "YES") {
                    Tour.push_back(Raiting[0].first);
                    extract_max_raiting(Raiting);
                } else if (answer == "NO") {
                    extract_max_raiting(Raiting);
                }
                --m;
            }
        }
    }
    
    while (!(Raiting.empty())) {
        if (num_of_max_raiting(Raiting) == num_of_max_gonorar(Gonorar)) {
            Tour.push_back(Raiting[0].first);
            extract_max_raiting(Raiting);
            extract_max_gonorar(Gonorar);
        } else if (num_of_max_raiting(Raiting) != num_of_max_gonorar(Gonorar)) {
            extract_max_raiting(Raiting);
        }
    }
    for (long long i = 0; i < Call.size(); ++i) {
        std::cout << Call[i] << " ";
    }
    std::cout << '\n';
    for (long long i = 0; i < Tour.size(); ++i) {
        std::cout << Tour[i] << " ";
    }
}