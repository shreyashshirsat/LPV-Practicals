#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// -------- Generate Random Array --------
void generateArray(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000;
}

// -------- Sequential Bubble Sort --------
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// -------- Parallel Bubble Sort (Odd-Even) --------
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// -------- Merge Function --------
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp(r - l + 1);
    int i = l, j = m + 1, k = 0;

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    for (int i = l; i <= r; i++)
        arr[i] = temp[i - l];
}

// -------- Sequential Merge Sort --------
void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// -------- Parallel Merge Sort --------
void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return;

    // Limit threads for small parts
    if (r - l < 1000) {
        mergeSort(arr, l, r);
        return;
    }

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        parallelMergeSort(arr, l, m);

        #pragma omp section
        parallelMergeSort(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

// -------- MAIN --------
int main() {
    int n = 50000;  // change size if needed

    vector<int> arr1(n), arr2(n), arr3(n), arr4(n);

    srand(time(0));
    generateArray(arr1, n);

    // Copy arrays
    arr2 = arr1;
    arr3 = arr1;
    arr4 = arr1;

    // -------- Sequential Bubble --------
    auto start = high_resolution_clock::now();
    bubbleSort(arr1);
    auto end = high_resolution_clock::now();

    cout << "Sequential Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    // -------- Parallel Bubble --------
    start = high_resolution_clock::now();
    parallelBubbleSort(arr2);
    end = high_resolution_clock::now();

    cout << "Parallel Bubble Sort Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    // -------- Sequential Merge --------
    start = high_resolution_clock::now();
    mergeSort(arr3, 0, n - 1);
    end = high_resolution_clock::now();

    cout << "Sequential Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    // -------- Parallel Merge --------
    start = high_resolution_clock::now();
    parallelMergeSort(arr4, 0, n - 1);
    end = high_resolution_clock::now();

    cout << "Parallel Merge Sort Time: "
         << duration_cast<milliseconds>(end - start).count()
         << " ms\n";

    return 0;
}