#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

// Generate random array
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

// -------- Parallel Bubble Sort --------
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

// -------- MAIN --------
int main() {
    int n = 5000;
    vector<int> arr1(n), arr2(n);

    srand(time(0));
    generateArray(arr1, n);
    arr2 = arr1;

    double start, end;

    // Sequential
    start = clock();
    bubbleSort(arr1);
    end = clock();

    cout << "Sequential Bubble Sort Time: "
         << end - start << " sec\n";

    // Parallel
    start = clock();
    parallelBubbleSort(arr2);
    end = clock();

    cout << "Parallel Bubble Sort Time: "
         << end - start << " sec\n";

    return 0;
}