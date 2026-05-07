# Bubble Sort and Merge Sort Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- Sorting means arranging data in increasing or decreasing order.
- **Sequential sorting** means one flow of execution performs the sorting.
- **Parallel sorting** means multiple CPU threads help perform parts of the sorting.
- **Performance comparison** means checking which version takes less time.
- OpenMP makes loops or independent sections run on multiple CPU threads.
- Bubble sort is simple but slow.
- Merge sort is faster because it uses divide and conquer.

Subject focus:

This practical is from **High Performance Computing** because it compares sequential and parallel algorithms. In the exam, first say: "This program compares sequential and OpenMP parallel versions of bubble sort and merge sort by measuring execution time."

## 0A. Core Theory: What, Why, How, and When

### What is an Algorithm Performance Comparison?

Performance comparison means running two or more approaches and measuring which one is faster.

In this practical, we compare:

- Sequential Bubble Sort.
- Parallel Bubble Sort.
- Sequential Merge Sort.
- Parallel Merge Sort.

### Why compare sequential and parallel algorithms?

Parallel code is not automatically faster. It has overhead from thread creation, synchronization, and memory access. We compare both versions to understand whether parallelization actually helps.

### What is Bubble Sort?

Bubble sort repeatedly compares adjacent elements and swaps them. It is easy to understand but slow for large data.

### What is Merge Sort?

Merge sort is a divide-and-conquer algorithm:

1. Divide array into two halves.
2. Sort each half.
3. Merge sorted halves.

It is much faster than bubble sort for large arrays.

### Why is Merge Sort good for parallelism?

The left half and right half are independent before merging. That means they can be sorted at the same time using different threads.

### What does OpenMP do here?

OpenMP is used in two ways:

- `parallel for` divides loop iterations among threads for bubble sort phases.
- `parallel sections` runs left and right merge sort branches in parallel.

### When is parallel sorting useful?

Parallel sorting is useful for large arrays where the time saved is greater than thread overhead. For small arrays, sequential sorting may be faster.

## 1. Which Practical This File Belongs To

This note mainly maps to `mergesort.cpp`, because that file contains:

- Sequential Bubble Sort
- Parallel Bubble Sort
- Sequential Merge Sort
- Parallel Merge Sort
- Time comparison for all four

It also relates to `bubblesort.cpp`, but `bubblesort.cpp` contains only sequential and parallel bubble sort, not merge sort.

Requirement check:

- Required: Bubble Sort and Merge Sort using OpenMP with sequential vs parallel performance comparison.
- Actual `mergesort.cpp`: Implements both sorting algorithms and compares time.
- Match status: **Matches the requirement**.

## 2. Aim of the Practical

To implement Bubble Sort and Merge Sort in both sequential and parallel forms using OpenMP, and compare their execution time.

## 3. Concept Used

Two sorting concepts are used:

- Bubble Sort: repeatedly compares adjacent elements and swaps them if they are in wrong order.
- Merge Sort: divides array into halves, sorts each half, and merges sorted halves.

OpenMP is used to parallelize:

- Bubble sort using odd-even phases.
- Merge sort using parallel sections.

## 4. Algorithm Explanation

Bubble Sort:

1. Start from first element.
2. Compare adjacent elements.
3. Swap if left element is greater than right element.
4. Repeat for all elements.
5. After each pass, one large element reaches correct position.

Parallel Bubble Sort in this code:

1. Uses odd-even transposition sort style.
2. Even phase compares pairs `(0,1), (2,3), (4,5)`.
3. Odd phase compares pairs `(1,2), (3,4), (5,6)`.
4. Each phase is parallelized because pairs do not overlap inside that phase.
5. Repeat for `n` passes.

Merge Sort:

1. Divide the array into two halves.
2. Recursively sort left half.
3. Recursively sort right half.
4. Merge both sorted halves.

Parallel Merge Sort:

1. Divide array into two halves.
2. Sort left and right halves in separate OpenMP sections.
3. Merge the sorted halves.
4. For small subarrays, use sequential merge sort to avoid parallel overhead.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Used for printing output.
- `#include <vector>`: Used for dynamic arrays.
- `#include <cstdlib>`: Used for `rand()` and `srand()`.
- `#include <ctime>`: Used for `time(0)` random seed.
- `#include <omp.h>`: Used for OpenMP directives.
- `#include <chrono>`: Used for accurate time measurement.

## 6. Complete Code Logic

The program creates a random array of size `50000`. It makes four copies of the same array so every algorithm sorts identical data. Then it runs sequential bubble sort, parallel bubble sort, sequential merge sort, and parallel merge sort. Execution time for each algorithm is measured using `high_resolution_clock` and printed in milliseconds.

## 7. Step-by-Step Code Explanation

`void generateArray(vector<int>& arr, int n)`

Fills the array with random values between `0` and `9999`.

`void bubbleSort(vector<int>& arr)`

Sequential bubble sort function.

`for (int i = 0; i < n; i++)`

Runs multiple passes.

`for (int j = 0; j < n - i - 1; j++)`

Compares adjacent elements.

`if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);`

Swaps adjacent elements if they are in wrong order.

`void parallelBubbleSort(vector<int>& arr)`

Parallel odd-even style bubble sort.

`#pragma omp parallel for`

Parallelizes the even and odd comparison loops.

Even phase:

```cpp
for (int j = 0; j < n - 1; j += 2)
```

Compares pairs starting from index 0.

Odd phase:

```cpp
for (int j = 1; j < n - 1; j += 2)
```

Compares pairs starting from index 1.

`void merge(vector<int>& arr, int l, int m, int r)`

Merges two sorted subarrays:

- Left subarray: `l` to `m`
- Right subarray: `m + 1` to `r`

`vector<int> temp(r - l + 1);`

Temporary array used during merging.

`while (i <= m && j <= r)`

Compares elements from both halves.

`void mergeSort(vector<int>& arr, int l, int r)`

Sequential recursive merge sort.

`if (l >= r) return;`

Base case: array of size 0 or 1 is already sorted.

`int m = (l + r) / 2;`

Finds middle index.

`mergeSort(arr, l, m);`

Sorts left half.

`mergeSort(arr, m + 1, r);`

Sorts right half.

`merge(arr, l, m, r);`

Merges sorted halves.

`void parallelMergeSort(vector<int>& arr, int l, int r)`

Parallel recursive merge sort.

`if (r - l < 1000)`

Uses sequential merge sort for small arrays to reduce overhead.

`#pragma omp parallel sections`

Creates parallel sections for left and right recursive calls.

`#pragma omp section`

Marks each independent section.

`auto start = high_resolution_clock::now();`

Records start time.

`duration_cast<milliseconds>(end - start).count()`

Calculates elapsed time in milliseconds.

## 8. Input and Output Explanation

Input:

- No user input.
- Array size is fixed as `n = 50000`.
- Random values are generated using `rand()`.

Output:

The program prints:

```text
Sequential Bubble Sort Time: ... ms
Parallel Bubble Sort Time: ... ms
Sequential Merge Sort Time: ... ms
Parallel Merge Sort Time: ... ms
```

It does not print the sorted array.

## 9. Parallelization Logic

Bubble sort parallelism:

- Comparisons are divided into even and odd phases.
- In one phase, compared pairs do not overlap.
- Therefore, multiple swaps can happen safely in parallel.

Merge sort parallelism:

- Left and right halves can be sorted independently.
- OpenMP sections run those two recursive calls in parallel.

## 10. OpenMP Explanation

Directives used:

`#pragma omp parallel for`

- Used in parallel bubble sort.
- Divides loop iterations among threads.
- Safe because compared pairs in the same phase do not overlap.

`#pragma omp parallel sections`

- Used in parallel merge sort.
- Creates a parallel region with multiple sections.

`#pragma omp section`

- Defines independent work.
- One section sorts left half.
- Another section sorts right half.

Race conditions:

- Bubble sort avoids race conditions by separating even and odd phases.
- Merge sort sections work on different parts of the array, so they do not write to same indexes.
- The merge step runs after sections complete.

Sequential vs parallel comparison:

- Same random data is copied into four arrays.
- Each algorithm sorts one copy.
- Time is measured separately.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Bubble Sort:

- Sequential: `O(n^2)`
- Parallel odd-even version: still `O(n^2)` total work, but comparisons in each phase can run in parallel.

Merge Sort:

- Sequential: `O(n log n)`
- Parallel: total work remains `O(n log n)`, but independent halves can be sorted simultaneously.

Merge sort is usually much faster than bubble sort for large arrays.

## 13. Space Complexity

Bubble Sort:

- `O(1)` extra space, ignoring array storage.

Merge Sort:

- `O(n)` extra space because temporary vectors are used during merging.

The program also stores four array copies, so total program memory is around `O(4n)`, simplified as `O(n)`.

## 14. Performance Measurement

Performance is measured using C++ `chrono`:

```cpp
auto start = high_resolution_clock::now();
...
auto end = high_resolution_clock::now();
```

Elapsed time:

```cpp
duration_cast<milliseconds>(end - start).count()
```

This gives time in milliseconds.

Important note:

For fair comparison, the code copies the same original array into `arr1`, `arr2`, `arr3`, and `arr4`.

## 15. Output Explanation

Example output:

```text
Sequential Bubble Sort Time: 9000 ms
Parallel Bubble Sort Time: 5000 ms
Sequential Merge Sort Time: 20 ms
Parallel Merge Sort Time: 15 ms
```

Actual values depend on CPU, compiler, number of threads, and random data.

Interpretation:

- Lower time means faster algorithm.
- Merge sort should usually be much faster than bubble sort.
- Parallel version may or may not be faster for small input because thread overhead exists.

## 16. Why This Practical Is Important

Sorting is a common operation in data processing, databases, search systems, and HPC workloads. This practical shows how parallelism can improve performance and also teaches that algorithm choice matters: merge sort is naturally more efficient than bubble sort.

## 17. Common Viva Questions and Answers

1. What is bubble sort?
   Answer: A sorting algorithm that repeatedly swaps adjacent elements.

2. What is merge sort?
   Answer: A divide-and-conquer sorting algorithm.

3. Which is faster for large data, bubble sort or merge sort?
   Answer: Merge sort.

4. What is the time complexity of bubble sort?
   Answer: `O(n^2)`.

5. What is the time complexity of merge sort?
   Answer: `O(n log n)`.

6. How is bubble sort parallelized here?
   Answer: Using odd-even phases with `parallel for`.

7. Why are even and odd phases needed?
   Answer: To avoid overlapping swaps.

8. What is odd-even transposition sort?
   Answer: A parallel version of bubble sort using alternating even and odd comparisons.

9. How is merge sort parallelized?
   Answer: Left and right halves are sorted in parallel sections.

10. Which OpenMP directive is used for bubble sort?
    Answer: `#pragma omp parallel for`.

11. Which directive is used for merge sort?
    Answer: `#pragma omp parallel sections` and `#pragma omp section`.

12. Why use a cutoff of 1000 in parallel merge sort?
    Answer: To avoid overhead for small subarrays.

13. What is a race condition?
    Answer: When multiple threads access and modify shared data unsafely.

14. Does parallel bubble sort use critical?
    Answer: No, it avoids conflicts using even and odd phases.

15. Does this code print sorted arrays?
    Answer: No, it prints only execution times.

16. How is time measured?
    Answer: Using `high_resolution_clock`.

17. Why are four array copies used?
    Answer: To ensure every algorithm sorts the same input.

18. Why may parallel code be slower sometimes?
    Answer: Thread creation and synchronization overhead.

19. What is divide and conquer?
    Answer: Breaking a problem into smaller parts, solving them, and combining results.

20. What is the role of `merge()`?
    Answer: It combines two sorted halves into one sorted range.

## 18. Examiner-Style Short Explanation

This program compares sequential and parallel versions of bubble sort and merge sort using OpenMP. Bubble sort is parallelized using odd-even phases, where non-overlapping adjacent pairs are compared in parallel. Merge sort is parallelized using OpenMP sections, where left and right halves are sorted simultaneously. The same random array is copied into four arrays for fair comparison, and execution time is measured using `chrono`. The practical demonstrates both parallel sorting and performance comparison.

## 19. Important Points to Remember

- Bubble sort is `O(n^2)`.
- Merge sort is `O(n log n)`.
- Parallel bubble uses even and odd phases.
- Parallel merge uses sections.
- Same input must be used for fair timing.
- Thread overhead can reduce speedup for small arrays.
- Merge sort is usually better than bubble sort.

## 20. Possible Errors and Fixes

- Error: OpenMP not working.
  Fix: Compile with `-fopenmp`.

- Error: Very slow bubble sort.
  Fix: Reduce `n` or use merge sort.

- Error: Stack or memory issue.
  Fix: Reduce array size or optimize temporary storage.

- Error: Parallel merge not much faster.
  Fix: Tune cutoff value and number of threads.

- Error: Wrong time unit confusion.
  Fix: Remember output is in milliseconds.

## 21. Code Improvements

- Print whether arrays are actually sorted.
- Use `omp_get_wtime()` for OpenMP timing.
- Add user input for array size.
- Add speedup calculation: sequential time divided by parallel time.
- Avoid nested parallel overhead in recursive merge sort.
- Use OpenMP tasks for a better parallel merge sort design.
