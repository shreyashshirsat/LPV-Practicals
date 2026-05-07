# Bubble Sort Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- Bubble sort compares neighboring values and swaps them.
- Normal bubble sort has dependencies, so it is not directly safe to parallelize every comparison.
- The code uses **odd-even phases** to make safe parallel comparisons.
- In one phase, compared pairs do not overlap.
- Because pairs do not overlap, different threads can work at the same time.
- This shows a basic HPC idea: divide safe independent work among threads.

Subject focus:

This practical is from **High Performance Computing** because it uses OpenMP to parallelize part of a sorting algorithm and compares it with the sequential version. In the exam, first say: "This program implements sequential bubble sort and parallel odd-even bubble sort using OpenMP."

## 0A. Core Theory: What, Why, How, and When

### What is Sorting?

Sorting means arranging data in a particular order, usually ascending or descending.

Example:

```text
Before sorting: 5 2 8 1
After sorting:  1 2 5 8
```

### What is Bubble Sort?

Bubble sort is a simple sorting algorithm. It compares adjacent elements and swaps them if they are in wrong order. After each pass, the largest element moves toward the end.

### Why is Bubble Sort slow?

Bubble sort compares many pairs again and again. For `n` elements, it takes about `n^2` comparisons, so it becomes very slow for large arrays.

### Why study Bubble Sort in HPC?

Bubble sort is not used for high-performance real applications, but it is useful for learning parallel thinking. It shows that not every loop can be parallelized directly because some operations depend on previous operations.

### How does Odd-Even Parallel Bubble Sort work?

The algorithm splits comparisons into phases:

Even phase:

```text
(0,1), (2,3), (4,5)
```

Odd phase:

```text
(1,2), (3,4), (5,6)
```

Inside one phase, pairs do not share indexes. So multiple threads can compare and swap safely.

### Why not parallelize all adjacent comparisons at once?

Because overlapping pairs can conflict.

Example:

```text
(0,1) and (1,2)
```

Both use index `1`. If two threads modify index `1` at the same time, it creates a race condition.

### When do we use this?

Use this mainly for learning OpenMP and parallel synchronization concepts. For real sorting of large data, merge sort, quicksort, or library sorting functions are better.

## 1. Which Practical This File Belongs To

This note is based specifically on `bubblesort.cpp`. It belongs to the sorting practical because it implements:

- Sequential Bubble Sort
- Parallel Bubble Sort using OpenMP
- Time comparison between sequential and parallel bubble sort

Requirement check:

- Required practical: Bubble Sort and Merge Sort using OpenMP.
- Actual `bubblesort.cpp`: Contains only Bubble Sort, not Merge Sort.
- Match status: **Partially matches**. It correctly implements sequential and parallel bubble sort, but merge sort is missing from this file. Merge sort is present in `mergesort.cpp`.

## 2. Aim of the Practical

To implement Bubble Sort sequentially and in parallel using OpenMP and compare execution time.

## 3. Concept Used

Bubble Sort repeatedly compares adjacent elements and swaps them if they are in wrong order.

The parallel version uses odd-even transposition logic:

- Even phase compares `(0,1), (2,3), (4,5)`.
- Odd phase compares `(1,2), (3,4), (5,6)`.

Pairs in the same phase do not overlap, so they can be processed in parallel.

## 4. Algorithm Explanation

Sequential Bubble Sort:

1. Start from the beginning of the array.
2. Compare adjacent elements.
3. Swap if left value is greater than right value.
4. Repeat until the array becomes sorted.

Parallel Bubble Sort:

1. Repeat for `n` passes.
2. In even phase, compare even-index pairs in parallel.
3. In odd phase, compare odd-index pairs in parallel.
4. Continue until sorted.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Used for printing execution time.
- `#include <vector>`: Used for dynamic integer arrays.
- `#include <cstdlib>`: Used for `rand()` and `srand()`.
- `#include <ctime>`: Used for `time(0)` and `clock()`.
- `#include <omp.h>`: Used for OpenMP parallel loops.

## 6. Complete Code Logic

The program creates two arrays of size `5000`. It fills the first array with random values and copies it into the second array. The first array is sorted using sequential bubble sort and the second is sorted using parallel bubble sort. Time is measured for both and printed.

## 7. Step-by-Step Code Explanation

`void generateArray(vector<int>& arr, int n)`

Fills the array with random numbers.

`arr[i] = rand() % 10000;`

Generates values between `0` and `9999`.

`void bubbleSort(vector<int>& arr)`

Sequential bubble sort.

`int n = arr.size();`

Finds number of elements.

`for (int i = 0; i < n; i++)`

Outer loop controls passes.

`for (int j = 0; j < n - i - 1; j++)`

Inner loop compares adjacent values.

`if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);`

Swaps values if they are not in ascending order.

`void parallelBubbleSort(vector<int>& arr)`

Parallel version of bubble sort.

`#pragma omp parallel for`

Parallelizes pair comparisons.

Even phase:

```cpp
for (int j = 0; j < n - 1; j += 2)
```

Odd phase:

```cpp
for (int j = 1; j < n - 1; j += 2)
```

`int n = 5000;`

Sets array size.

`vector<int> arr1(n), arr2(n);`

Creates two arrays.

`arr2 = arr1;`

Copies same data for fair comparison.

`start = clock();`

Starts timing.

`end = clock();`

Ends timing.

## 8. Input and Output Explanation

Input:

- No user input.
- Random array of size `5000`.

Output:

```text
Sequential Bubble Sort Time: ... sec
Parallel Bubble Sort Time: ... sec
```

Important note:

The code prints `end - start` as seconds, but `clock()` returns clock ticks. The correct time in seconds is:

```cpp
(end - start) / CLOCKS_PER_SEC
```

## 9. Parallelization Logic

Parallelism is applied during even and odd phases.

In the even phase, pairs do not overlap, so multiple swaps are safe. In the odd phase, pairs also do not overlap. This avoids race conditions without needing `critical`.

## 10. OpenMP Explanation

Directive used:

`#pragma omp parallel for`

- Creates multiple threads.
- Splits loop iterations among threads.
- Used separately for even phase and odd phase.

Race condition handling:

- Same-phase pairs do not share array positions.
- Therefore, no two threads write to same element in the same phase.

Sequential and parallel comparison:

- `arr1` is sorted sequentially.
- `arr2` is sorted in parallel.
- Both start from identical data.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Sequential bubble sort:

```text
O(n^2)
```

Parallel bubble sort:

- Total work remains `O(n^2)`.
- Comparisons in each phase can be divided among threads.
- Speedup is limited because phases still run one after another.

## 13. Space Complexity

Bubble sort extra space:

```text
O(1)
```

Program space:

- Two arrays of size `n`, so total array storage is `O(n)`.

## 14. Performance Measurement

The program uses:

```cpp
clock()
```

Problem:

`clock()` returns CPU clock ticks, not seconds directly.

Better options:

- Use `(end - start) / CLOCKS_PER_SEC`.
- Use `omp_get_wtime()` for OpenMP programs.
- Use `chrono` as done in `mergesort.cpp`.

## 15. Output Explanation

The output compares sequential and parallel bubble sort time.

If parallel time is lower, parallel version is faster. If it is higher, thread overhead is more than the benefit.

The program does not print the sorted array, so correctness is not visibly verified.

## 16. Why This Practical Is Important

This practical teaches basic parallel loop execution and shows how an algorithm must be modified before it can be parallelized safely. Normal bubble sort has dependency between adjacent comparisons, so the code uses odd-even phases.

## 17. Common Viva Questions and Answers

1. What is bubble sort?
   Answer: A sorting algorithm that swaps adjacent elements if they are in wrong order.

2. What is the time complexity of bubble sort?
   Answer: `O(n^2)`.

3. Is bubble sort efficient for large arrays?
   Answer: No.

4. What is parallel bubble sort here based on?
   Answer: Odd-even transposition sort.

5. Why use even and odd phases?
   Answer: To avoid overlapping swaps.

6. Which OpenMP directive is used?
   Answer: `#pragma omp parallel for`.

7. Why is `critical` not used?
   Answer: Pairs in the same phase do not write to the same indexes.

8. What is a race condition?
   Answer: Unsafe simultaneous access to shared data by multiple threads.

9. What does `arr2 = arr1` do?
   Answer: Copies the original array for fair comparison.

10. What is the array size?
    Answer: `5000`.

11. What range of random values is used?
    Answer: `0` to `9999`.

12. What does `srand(time(0))` do?
    Answer: Seeds random number generator using current time.

13. What does `clock()` return?
    Answer: CPU clock ticks.

14. Is the time printed correctly as seconds?
    Answer: Not exactly. It should be divided by `CLOCKS_PER_SEC`.

15. Does this file implement merge sort?
    Answer: No.

16. Where is merge sort implemented?
    Answer: In `mergesort.cpp`.

17. Can parallel bubble sort be slower?
    Answer: Yes, because thread overhead can be high.

18. Why is same input needed?
    Answer: For fair timing comparison.

19. Does this code verify sorted output?
    Answer: No.

20. How can it be improved?
    Answer: Add sortedness check, proper timing, and speedup calculation.

## 18. Examiner-Style Short Explanation

This program compares sequential and parallel bubble sort using OpenMP. It generates a random array, copies it, sorts one copy sequentially, and sorts the other using odd-even parallel bubble sort. The even phase and odd phase are separately parallelized using `#pragma omp parallel for`. Since compared pairs do not overlap inside one phase, race conditions are avoided. The file partially matches the sorting practical because it does not include merge sort; merge sort is implemented in `mergesort.cpp`.

## 19. Important Points to Remember

- Bubble sort compares adjacent elements.
- Parallel version uses odd-even phases.
- Same-phase pairs do not overlap.
- `parallel for` divides comparisons among threads.
- Time printing has a unit issue.
- Merge sort is not present in this file.

## 20. Possible Errors and Fixes

- Error: `omp.h` missing.
  Fix: Use compiler with OpenMP support.

- Error: OpenMP not active.
  Fix: Compile with `-fopenmp`.

- Error: Time looks too large.
  Fix: Divide by `CLOCKS_PER_SEC`.

- Error: Parallel version slower.
  Fix: Use larger input or better sorting algorithm.

- Error: Cannot confirm sorting.
  Fix: Add a function to check sorted order.

## 21. Code Improvements

- Add merge sort or refer clearly to `mergesort.cpp`.
- Use `omp_get_wtime()` or `chrono`.
- Print speedup.
- Verify sorted array.
- Let user enter array size.
- Use `long long` or `double` correctly for time values.
