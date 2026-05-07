#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
using namespace std;

int main() {
    int n = 10000;
    int arr[n];

    // Generate random array
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    int sum = 0;
    int minVal = arr[0];
    int maxVal = arr[0];

    double start = clock();

    // Parallel Reduction
    #pragma omp parallel for reduction(+:sum) reduction(min:minVal) reduction(max:maxVal)
    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (arr[i] < minVal)
            minVal = arr[i];

        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    double end = clock();

    double avg = (double)sum / n;

    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;

    cout << "Execution Time: " << end - start << " sec" << endl;

    return 0;
}