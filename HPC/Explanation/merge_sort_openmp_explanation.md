# Merge Sort Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- Merge sort divides the array into two halves.
- The left half and right half can be sorted independently.
- Independent work is good for parallel computing.
- OpenMP `sections` allow two different code blocks to run at the same time.
- After both halves are sorted, they are merged.
- The goal is to reduce runtime compared with sequential merge sort.

Subject focus:

This practical is from **High Performance Computing** because it uses parallel execution to speed up a divide-and-conquer algorithm. In the exam, first say: "This program implements sequential and OpenMP parallel merge sort and compares their execution time."

## 0A. Core Theory: What, Why, How, and When

### What is Merge Sort?

Merge sort is a sorting algorithm based on divide and conquer.

Divide and conquer means:

1. Break a big problem into smaller problems.
2. Solve the smaller problems.
3. Combine the answers.

### How does Merge Sort work?

For an array:

```text
8 3 5 1
```

It divides:

```text
8 3    5 1
8  3   5  1
```

Then sorts and merges:

```text
3 8    1 5
1 3 5 8
```

### Why is Merge Sort efficient?

Merge sort divides the array into halves, so the number of levels is about `log n`. At each level, all elements are merged once. Therefore, time complexity is `O(n log n)`.

### Why is Merge Sort suitable for parallel computing?

The left half and right half can be sorted independently. Independent work is the main requirement for parallel execution.

### How does OpenMP parallel merge sort work?

The code uses OpenMP sections:

- One section sorts the left half.
- Another section sorts the right half.

After both sections finish, the merge step combines the two sorted halves.

### Why use a cutoff?

Creating threads for very small arrays can be slower than sorting normally. The cutoff says: if the part is small, use sequential merge sort.

### When should parallel merge sort be used?

Use it for large arrays where recursive halves are big enough to benefit from multiple CPU cores.

## 1. Which Practical This File Belongs To

This note focuses on the merge sort part of `mergesort.cpp`. It belongs to the **Merge Sort using OpenMP** practical because it implements both sequential and parallel merge sort and measures execution time.

Requirement check:

- Required: Sequential and parallel merge sort comparison using OpenMP.
- Actual code: Contains `mergeSort()` and `parallelMergeSort()` with timing.
- Match status: **Matches the requirement**.

## 2. Aim of the Practical

To implement merge sort sequentially and in parallel using OpenMP, then compare their execution time.

## 3. Concept Used

Merge sort is a divide-and-conquer algorithm. It divides the array into smaller halves, sorts each half, and merges the sorted halves.

Parallel merge sort uses the fact that left and right halves are independent before merging.

## 4. Algorithm Explanation

Sequential merge sort:

1. If the subarray has one or zero elements, return.
2. Find the middle index.
3. Recursively sort the left half.
4. Recursively sort the right half.
5. Merge both sorted halves.

Parallel merge sort:

1. If subarray is small, use sequential merge sort.
2. Otherwise, divide into two halves.
3. Sort left half in one OpenMP section.
4. Sort right half in another OpenMP section.
5. Merge both halves.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Output printing.
- `#include <vector>`: Dynamic array storage.
- `#include <cstdlib>`: Random number generation.
- `#include <ctime>`: Random seed.
- `#include <omp.h>`: OpenMP support.
- `#include <chrono>`: Time measurement.

## 6. Complete Code Logic

The code generates a random array of size `50000`. It copies the same data into `arr3` and `arr4`. `arr3` is sorted by sequential merge sort. `arr4` is sorted by parallel merge sort. Time is measured for both and printed in milliseconds.

## 7. Step-by-Step Code Explanation

`void merge(vector<int>& arr, int l, int m, int r)`

Merges two sorted parts of the array.

`vector<int> temp(r - l + 1);`

Temporary storage for merged output.

`int i = l, j = m + 1, k = 0;`

`i` points to left half, `j` points to right half, and `k` points to temp array.

`while (i <= m && j <= r)`

Runs while both halves still have elements.

`if (arr[i] <= arr[j])`

Chooses smaller value from left or right half.

`while (i <= m) temp[k++] = arr[i++];`

Copies remaining left-half elements.

`while (j <= r) temp[k++] = arr[j++];`

Copies remaining right-half elements.

`for (int i = l; i <= r; i++) arr[i] = temp[i - l];`

Copies merged result back into original array.

`void mergeSort(vector<int>& arr, int l, int r)`

Sequential recursive merge sort.

`if (l >= r) return;`

Base condition.

`int m = (l + r) / 2;`

Finds middle.

`mergeSort(arr, l, m);`

Sorts left half.

`mergeSort(arr, m + 1, r);`

Sorts right half.

`merge(arr, l, m, r);`

Merges sorted halves.

`void parallelMergeSort(vector<int>& arr, int l, int r)`

Parallel version.

`if (r - l < 1000)`

For small subarray, sequential merge sort is used.

`#pragma omp parallel sections`

Starts parallel sections.

`#pragma omp section`

Defines independent sorting tasks.

`parallelMergeSort(arr, l, m);`

Sorts left half.

`parallelMergeSort(arr, m + 1, r);`

Sorts right half.

## 8. Input and Output Explanation

Input:

- No user input.
- Random array of size `50000`.

Output:

Relevant merge sort output:

```text
Sequential Merge Sort Time: ... ms
Parallel Merge Sort Time: ... ms
```

The full file also prints bubble sort times.

## 9. Parallelization Logic

The main parallel idea is that the left and right halves are independent before merging.

OpenMP sections allow the left recursive call and right recursive call to run at the same time. After both sections complete, the merge operation combines them.

## 10. OpenMP Explanation

Directives used:

`#pragma omp parallel sections`

- Creates a parallel region.
- Allows different sections to run by different threads.

`#pragma omp section`

- Marks one independent block of code.
- One section sorts the left half.
- One section sorts the right half.

Race conditions:

- Left and right halves are separate array ranges.
- Therefore, they do not write to the same indexes.
- Merge happens after both sections complete.

Performance comparison:

- Sequential and parallel merge sorts are timed separately.
- Same original data is used through copied arrays.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Sequential merge sort:

```text
O(n log n)
```

Parallel merge sort:

- Total work remains `O(n log n)`.
- Parallel time can improve because left and right halves run together.
- Merging itself is still sequential in this code.

## 13. Space Complexity

Space complexity:

```text
O(n)
```

Reason:

- Temporary arrays are created during merge.
- Recursion also uses stack memory.

## 14. Performance Measurement

Time is measured using `chrono`:

```cpp
auto start = high_resolution_clock::now();
mergeSort(arr3, 0, n - 1);
auto end = high_resolution_clock::now();
```

Elapsed time is printed using:

```cpp
duration_cast<milliseconds>(end - start).count()
```

## 15. Output Explanation

Expected output:

```text
Sequential Merge Sort Time: number ms
Parallel Merge Sort Time: number ms
```

If parallel time is lower, parallel implementation is faster. If not, overhead may be high or input size may be too small.

## 16. Why This Practical Is Important

Merge sort is widely used because it has guaranteed `O(n log n)` time. Parallel merge sort is important in HPC because large arrays can be divided and processed by multiple cores.

## 17. Common Viva Questions and Answers

1. What is merge sort?
   Answer: A divide-and-conquer sorting algorithm.

2. What are the three main steps of merge sort?
   Answer: Divide, sort recursively, and merge.

3. What is the base case?
   Answer: When `l >= r`.

4. What is the role of `merge()`?
   Answer: It combines two sorted halves.

5. What is the time complexity?
   Answer: `O(n log n)`.

6. What is the space complexity?
   Answer: `O(n)`.

7. How is merge sort parallelized?
   Answer: Left and right halves are sorted in parallel.

8. Which OpenMP directive is used?
   Answer: `parallel sections` and `section`.

9. Why is cutoff value used?
   Answer: To avoid parallel overhead for small subarrays.

10. What is the cutoff in this code?
    Answer: Subarrays smaller than 1000 are sorted sequentially.

11. Does this code parallelize the merge step?
    Answer: No.

12. Why are left and right sections safe?
    Answer: They work on different array ranges.

13. What is thread overhead?
    Answer: Extra time required to create/manage threads.

14. What is divide and conquer?
    Answer: Solving a problem by dividing it into smaller subproblems.

15. Why use `chrono`?
    Answer: To measure execution time.

16. Why use same input for both versions?
    Answer: For fair performance comparison.

17. Is merge sort stable?
    Answer: Yes, if equal elements are copied from left first, as this code does.

18. Can parallel merge sort be slower?
    Answer: Yes, for small arrays or high overhead.

19. What does `duration_cast<milliseconds>` do?
    Answer: Converts elapsed time to milliseconds.

20. How can this code be improved?
    Answer: Use tasks, better cutoff, and sortedness verification.

## 18. Examiner-Style Short Explanation

This program implements sequential and parallel merge sort using OpenMP. Merge sort divides the array into two halves, recursively sorts each half, and merges the sorted halves. In the parallel version, OpenMP sections are used so the left and right halves can be sorted simultaneously. A cutoff is used so small subarrays are sorted sequentially to avoid thread overhead. Execution time is measured using `chrono`, allowing comparison between sequential and parallel merge sort.

## 19. Important Points to Remember

- Merge sort uses divide and conquer.
- Time complexity is `O(n log n)`.
- Extra space is `O(n)`.
- Left and right halves can be sorted in parallel.
- Merge step is sequential in this code.
- Cutoff avoids overhead.
- Timing is in milliseconds.

## 20. Possible Errors and Fixes

- Error: OpenMP not enabled.
  Fix: Compile with `-fopenmp`.

- Error: Parallel version slower.
  Fix: Increase input size or tune cutoff.

- Error: High memory usage.
  Fix: Reuse temporary array.

- Error: Wrong sorting result.
  Fix: Check merge boundaries `l`, `m`, and `r`.

- Error: Compiler issue with nested sections.
  Fix: Use OpenMP tasks instead of repeated parallel sections.

## 21. Code Improvements

- Add function to verify sorted array.
- Use OpenMP tasks for recursive parallelism.
- Add speedup calculation.
- Take array size from user.
- Use `omp_get_wtime()` for OpenMP timing.
- Avoid creating many temporary vectors repeatedly.
