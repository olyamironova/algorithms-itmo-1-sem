#include <iostream>
#include <vector>

void swap(int* pointer_one, int* pointer_two) {
    int temp = *pointer_one;
    *pointer_one = *pointer_two;
    *pointer_two = temp;
}

void create(std::vector<std::vector<int>>& heapes) {
    std::vector<int> new_heap;
    heapes.push_back(new_heap);
}

void siftUp(std::vector<int> &heap, int index_of_element) {
    while  (heap[index_of_element] < heap[(index_of_element - 1) / 2]) {
        swap(&heap[index_of_element], &heap[(index_of_element - 1) / 2]);
        index_of_element = (index_of_element - 1) / 2;
    }
}

void insert(std::vector<int> &heap, int x) {
    heap.push_back(x);
    siftUp(heap, heap.size() - 1);
}

void siftDown(std::vector<int> &heap, int i, int heapsize) {
    while ((2 * i + 1) < heapsize) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if ((right < heapsize) && (heap[right] < heap[left])) {
            j = right;
        }
        if (heap[i] <= heap[j]) {
            break;
        }
        swap(&heap[i], &heap[j]);
        i = j;
    }
}

void extract_min(std::vector<int> &heap) {
    if (heap.empty()) {
        std::cout << "*" << '\n';
    } else {
        int x = heap.front();
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(heap, 0, heap.size());
        std::cout << x << '\n';
    }
}


void heapify(std::vector<int> &heap) {
    int n = heap.size();
    for (int i = n - 1; i >= 0; --i) {
        siftDown(heap, i, n);
    }
}

void merge(std::vector<std::vector<int>> &heapes, int k, int m) {
    std::vector<int> new_heap;
    for (int i = 0; i < heapes[k].size(); ++i) {
        new_heap.push_back(heapes[k][i]);
    }
    for (int i = 0; i < heapes[m].size(); ++i) {
        new_heap.push_back(heapes[m][i]);
    }
    heapify(new_heap);
    heapes.push_back(new_heap);

}

void decrease_key(std::vector<int> &heap, int x, int y) {
    for (int i = 0; i < heap.size(); ++i) {
        if (heap[i] == x) {
            heap[i] = y;
            siftUp(heap, i);
            break;
        }
    }
}

int main() {
    std::cin.tie(0);
    std::vector<std::vector<int>> heapes;
    heapes.reserve(1e6);
    std::string command;
    int k, x, y, m;
    while (std::cin >> command) {
        if (command == "create") {
            create(heapes);
        } else if (command == "insert") {
            std::cin >> k >> x;
            insert(heapes[k], x);
        } else if (command == "extract-min") {
            std::cin >> k;
            extract_min(heapes[k]);
        } else if (command == "merge") {
            std::cin >> k >> m;
            merge(heapes, k, m);
        } else if (command == "decrease-key") {
            std::cin >> k >> x >> y;
            decrease_key(heapes[k], x, y);
        }
    }
}