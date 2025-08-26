#include <iostream>
#include <vector>

//(зп, время освобождения)
//занятые (время освобождения, зп) и свободные (зп, время освобождения)
void swap(std::pair <long long, long long>* pointer_one, std::pair <long long, long long>* pointer_two) {
    std::pair <long long, long long> temp = *pointer_one;
    *pointer_one = *pointer_two;
    *pointer_two = temp;
}

void siftDown_free(std::vector<std::pair<long long, long long>> &heap, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (heap[right].first < heap[left].first)) {
            j = right;
        }
        if ((right < heapsize) && (heap[right].first == heap[left].first)) {
            if (heap[right].second < heap[left].second) {
                j = right;
            }
        }
        if (heap[i].first <= heap[j].first) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i = j;
    }
}

//(зп, время освобождения)
//занятые (время освобождения, зп) и свободные (зп, время освобождения)
void siftDown_busy(std::vector<std::pair<long long, long long>> &heap, long long i, long long heapsize) {
    while ((2 * i + 1) < heapsize) {
        long long left = 2 * i + 1;
        long long right = 2 * i + 2;
        long long j = left;
        if ((right < heapsize) && (heap[right].second < heap[left].second)) {
            j = right;
        }
        if ((right < heapsize) && (heap[right].second == heap[left].second)) {
            if (heap[right].first < heap[left].first) {
                j = right;
            }
        }
        if (heap[i].second <= heap[j].second) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i = j;
    }
}
//
//void heapify_free(std::vector<std::pair<long long, long long>> &heap) {
//    long long n = heap.size();
//    for (long long i = n - 1; i >= 0; --i) {
//        siftDown_free(heap, i, n);
//    }
//}
//
//void heapify_busy(std::vector<std::pair<long long, long long>> &heap) {
//    long long n = heap.size();
//    for (long long i = n - 1; i >= 0; --i) {
//        siftDown_busy(heap, i, n);
//    }
//}
//(зп, время освобождения)
//занятые (время освобождения, зп) и свободные (зп, время освобождения)
void siftUp_free(std::vector<std::pair<long long, long long>> &heap, long long i) {
    while (i != 0) {
        if (heap[i].first < heap[(i - 1) / 2].first) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else if ((heap[i].first == heap[(i - 1) / 2].first) && (heap[i].second < heap[(i - 1) / 2].second)) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}

void siftUp_busy(std::vector<std::pair<long long, long long>> &heap, long long i) {
    while (i != 0) {
        if (heap[i].second < heap[(i - 1) / 2].second) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else if ((heap[i].second == heap[(i - 1) / 2].second) && (heap[i].first < heap[(i - 1) / 2].first)) {
            swap(&heap[i], &heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}

int main() {
    std::cin.tie(0);
    long long n, m;
    std::cin >> n >> m;
    std::vector<std::pair<long long, long long>> free;
    std::vector<std::pair<long long, long long>> busy;
    free.reserve(10000000);
    busy.reserve(10000000);
    long long salary;
    for (long long i = 0; i < n; ++i) {
        std::cin >> salary;
        std::pair<long long, long long> shawerma_chef = std::make_pair(salary, 0);
        free.push_back(shawerma_chef);
    }
    for (long long i = n - 1; i >= 0; --i) {
        siftDown_free(free, i, n);
    }
    long long global_salary = 0;
    for (long long i = 0; i < m; ++i) {
        long long time_of_begin, time_of_process;
        std::cin >> time_of_begin >> time_of_process;
        if (!(busy.empty())) {
            while ((!(busy.empty())) && (busy[0].second <= time_of_begin)) {
                free.push_back(busy[0]);
                swap(busy[0], busy.back());
                busy.pop_back();
                siftDown_busy(busy, 0, busy.size());
                siftUp_free(free, free.size() - 1);
            }
        }
        if (!(free.empty())) {
            free[0].second = time_of_begin + time_of_process;
            global_salary += free[0].first * time_of_process;
            busy.push_back(free[0]);
            swap(free[0], free.back());
            free.pop_back();
            siftUp_busy(busy, busy.size() - 1);
            siftDown_free(free, 0, free.size());
        }
    }
    std::cout << global_salary;
}
