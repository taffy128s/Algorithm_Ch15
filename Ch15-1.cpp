#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <list>
#define SIZE 20

int arr[SIZE];

std::list<int> LIS(int *A, int n) {
    int mem_pos[SIZE] = {0}, temp[SIZE] = {0}, temp_idx = 0;
    temp[0] = A[0];
    mem_pos[0] = 0;
    for (int i = 1; i < n; i++) {
        if (A[i] >= temp[temp_idx]) {
            temp[++temp_idx] = A[i];
            mem_pos[i] = temp_idx;
        } else {
            // O(n)
            /*int j;
            for (j = temp_idx; j >= 0; j--) if (A[i] >= temp[j]) break;
            temp[j + 1] = A[i];
            mem_pos[i] = j + 1;*/
            // O(lgn)
            int l = 0, r = temp_idx;
            while (l < r) {
                int mid = (l + r) / 2;
                if (A[i] >= temp[mid]) l = mid + 1;
                else r = mid;
            }
            temp[l] = A[i];
            mem_pos[i] = l;
        }
    }
    std::list<int> l;
    for (int i = n - 1; temp_idx >= 0; i--) {
        if (mem_pos[i] == temp_idx) {
            l.push_front(A[i]);
            temp_idx--;
        }
    }
    return l;
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++)
        arr[i] = rand() % (SIZE * 2);
    std::sort(arr, arr + SIZE);
    for (int i = 0; i < SIZE; i++)
        printf("%2d ", arr[i]);
    puts("");
    std::list<int> l = LIS(arr, SIZE);
    for (auto i : l)
        printf("%2d ", i);
    puts("");
    return 0;
}
