# Parallel Reduction Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- Reduction means combining many values into one final answer.
- Examples are sum, minimum, maximum, and average.
- In sequential execution, one thread checks all array elements.
- In parallel execution, many threads check different parts of the array.
- Each thread calculates a partial answer.
- OpenMP combines all partial answers safely using `reduction`.
- This avoids race conditions without manually using `critical`.

Subject focus:

This practical is from **High Performance Computing** because reduction operations are common in parallel data processing. In the exam, first say: "This program uses OpenMP reduction to calculate minimum, maximum, sum, and average of an array in parallel."

## 0A. Core Theory: What, Why, How, and When

### What is Reduction?

Reduction means combining many values into one final value.

Examples:

```text
Sum:     2 + 4 + 6 + 8 = 20
Minimum: min(2, 4, 6, 8) = 2
Maximum: max(2, 4, 6, 8) = 8
Average: 20 / 4 = 5
```

### Why is Reduction important in HPC?

Many scientific and data-processing problems need summary values:

- Total sales.
- Minimum temperature.
- Maximum speed.
- Average marks.
- Sum of pixels.

For very large data, doing this sequentially is slow. Parallel reduction allows multiple threads to process different parts of data.

### How does Parallel Reduction work?

Suppose an array has 10000 values and 4 threads:

- Thread 1 processes first part.
- Thread 2 processes second part.
- Thread 3 processes third part.
- Thread 4 processes fourth part.

Each thread calculates its own partial sum/min/max. At the end, OpenMP combines all partial results.

### Why not simply share one `sum` variable?

If all threads update the same `sum` at the same time, updates may be lost.

Example:

```text
Thread A reads sum = 10
Thread B reads sum = 10
Thread A writes 15
Thread B writes 18
```

The correct answer should include both updates, but one update may overwrite the other. This is a race condition.

### How does OpenMP reduction solve this?

OpenMP gives each thread a private copy of the reduction variable. After the loop, OpenMP safely combines private copies into the final result.

### When do we use reduction?

Use reduction when many values must be combined using operations like:

- Addition.
- Multiplication.
- Minimum.
- Maximum.
- Logical AND/OR.

## 1. Which Practical This File Belongs To

This note is based on `mmas.cpp`. It belongs to the **Parallel Reduction using OpenMP** practical because it calculates minimum, maximum, sum, and average using OpenMP reduction clauses.

Requirement check:

- Required: Implement Min, Max, Sum, and Average using Parallel Reduction and OpenMP.
- Actual code: Calculates min, max, sum, and average using `reduction`.
- Match status: **Matches the practical requirement**.

## 2. Aim of the Practical

To implement parallel reduction operations for finding minimum, maximum, sum, and average of an array using OpenMP.

## 3. Concept Used

Reduction is a parallel programming technique where multiple values are combined into one final result.

Examples:

- Sum: combine all elements using addition.
- Minimum: find smallest value.
- Maximum: find largest value.
- Average: sum divided by number of elements.

## 4. Algorithm Explanation

1. Create an array of size `10000`.
2. Fill it with random numbers from `0` to `999`.
3. Initialize `sum`, `minVal`, and `maxVal`.
4. Use OpenMP parallel for loop with reduction clauses.
5. Each thread calculates partial sum, partial minimum, and partial maximum.
6. OpenMP combines partial results into final values.
7. Calculate average as `sum / n`.
8. Print min, max, sum, average, and execution time.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Used for output.
- `#include <cstdlib>`: Used for `rand()` and `srand()`.
- `#include <ctime>`: Used for `time(0)` and `clock()`.
- `#include <omp.h>`: Used for OpenMP parallel loop and reduction.

## 6. Complete Code Logic

The program creates a random integer array of size `10000`. It initializes sum to 0 and min/max values to the first array element. Then it starts timing and runs a parallel loop. The OpenMP reduction clause safely combines values calculated by different threads. After the loop, average is calculated and results are printed.

## 7. Step-by-Step Code Explanation

`int n = 10000;`

Sets array size.

`int arr[n];`

Creates an integer array. Note: this is a variable-length array, accepted by some compilers but not standard C++.

`srand(time(0));`

Seeds random number generator using current time.

`arr[i] = rand() % 1000;`

Stores random values between `0` and `999`.

`int sum = 0;`

Initializes sum.

`int minVal = arr[0];`

Initializes minimum value.

`int maxVal = arr[0];`

Initializes maximum value.

`double start = clock();`

Starts timing.

`#pragma omp parallel for reduction(+:sum) reduction(min:minVal) reduction(max:maxVal)`

Parallelizes the loop and applies reductions for sum, min, and max.

`sum += arr[i];`

Each thread adds elements to its private sum. OpenMP combines them later.

`if (arr[i] < minVal) minVal = arr[i];`

Updates private minimum value.

`if (arr[i] > maxVal) maxVal = arr[i];`

Updates private maximum value.

`double avg = (double)sum / n;`

Calculates average after final sum is ready.

## 8. Input and Output Explanation

Input:

- No user input.
- Array is randomly generated.

Output:

```text
Minimum: ...
Maximum: ...
Sum: ...
Average: ...
Execution Time: ... sec
```

Because the array is random, values change on every run.

## 9. Parallelization Logic

The loop over array elements is parallelized. Different threads process different parts of the array.

Each thread calculates local partial results:

- partial sum
- partial min
- partial max

At the end, OpenMP combines all partial values into final values.

## 10. OpenMP Explanation

Directive used:

`#pragma omp parallel for reduction(+:sum) reduction(min:minVal) reduction(max:maxVal)`

Meaning:

- `parallel for`: divides loop iterations among threads.
- `reduction(+:sum)`: each thread gets a private sum and OpenMP adds all sums.
- `reduction(min:minVal)`: OpenMP finds final minimum from thread-local minima.
- `reduction(max:maxVal)`: OpenMP finds final maximum from thread-local maxima.

Race conditions:

- Without reduction, multiple threads would update `sum`, `minVal`, and `maxVal` at the same time.
- Reduction avoids race conditions automatically.

No `critical` is needed because reduction handles synchronization efficiently.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Sequential complexity:

```text
O(n)
```

Parallel complexity:

- Total work is still `O(n)`.
- With `p` threads, ideal time can approach `O(n / p)`.
- Final reduction combination adds small overhead.

## 13. Space Complexity

Space complexity:

```text
O(n)
```

Reason:

- Array of `n` elements is stored.
- OpenMP also creates private reduction variables per thread.

## 14. Performance Measurement

Time is measured using:

```cpp
double start = clock();
...
double end = clock();
```

Important note:

The code prints `end - start` as seconds, but `clock()` returns clock ticks, not direct seconds. Correct conversion should be:

```cpp
double time = (end - start) / CLOCKS_PER_SEC;
```

Better OpenMP timing:

```cpp
double start = omp_get_wtime();
...
double end = omp_get_wtime();
```

## 15. Output Explanation

Expected output:

- Minimum: smallest number in array.
- Maximum: largest number in array.
- Sum: total of all elements.
- Average: sum divided by `n`.
- Execution Time: time taken by reduction loop.

Since values are generated from `rand() % 1000`, minimum will usually be near `0` and maximum near `999`.

## 16. Why This Practical Is Important

Reduction is one of the most common operations in HPC. It is used in statistics, scientific computing, image processing, machine learning, numerical simulations, and data analytics.

## 17. Common Viva Questions and Answers

1. What is reduction?
   Answer: Combining multiple values into one final result.

2. Which operations are performed?
   Answer: Minimum, maximum, sum, and average.

3. Which OpenMP directive is used?
   Answer: `#pragma omp parallel for reduction(...)`.

4. What does `reduction(+:sum)` mean?
   Answer: Each thread computes private sum and OpenMP adds all sums.

5. What does `reduction(min:minVal)` mean?
   Answer: OpenMP finds minimum from thread-local minimum values.

6. What does `reduction(max:maxVal)` mean?
   Answer: OpenMP finds maximum from thread-local maximum values.

7. Why is reduction better than critical?
   Answer: It reduces synchronization overhead and avoids race conditions.

8. What is a race condition?
   Answer: Incorrect result caused by unsafe shared variable updates.

9. Is average directly reduced?
   Answer: No, average is calculated after sum is found.

10. What is the time complexity?
    Answer: `O(n)`.

11. What is the ideal parallel time?
    Answer: Approximately `O(n/p)` for `p` threads.

12. What is the array size?
    Answer: `10000`.

13. What range of values is generated?
    Answer: `0` to `999`.

14. Why initialize min and max with `arr[0]`?
    Answer: It gives valid initial comparison values from the array.

15. Does the program take user input?
    Answer: No.

16. What is wrong with timing output?
    Answer: `clock()` ticks are printed as seconds without dividing by `CLOCKS_PER_SEC`.

17. What timing function is better for OpenMP?
    Answer: `omp_get_wtime()`.

18. Is CUDA used here?
    Answer: No.

19. Does reduction create private variables?
    Answer: Yes, each thread gets private reduction variables.

20. How does OpenMP combine private values?
    Answer: It combines them automatically at the end of the loop.

## 18. Examiner-Style Short Explanation

This program demonstrates parallel reduction using OpenMP. It creates an array of 10000 random integers and calculates sum, minimum, maximum, and average. The loop is parallelized using `#pragma omp parallel for`, and reduction clauses are used for sum, min, and max. Each thread computes partial results, and OpenMP safely combines them into final results. Average is calculated after the final sum. This avoids race conditions and is more efficient than using critical sections.

## 19. Important Points to Remember

- Reduction combines many values into one.
- Sum, min, and max are reduced directly.
- Average is calculated from sum.
- Reduction avoids race conditions.
- `parallel for` divides loop iterations.
- `clock()` should be converted using `CLOCKS_PER_SEC`.
- `omp_get_wtime()` is better for OpenMP timing.

## 20. Possible Errors and Fixes

- Error: `omp.h` missing.
  Fix: Use OpenMP-supported compiler.

- Error: Reduction not working.
  Fix: Compile with `-fopenmp`.

- Error: Variable-length array not supported.
  Fix: Use `vector<int> arr(n);`.

- Error: Wrong execution time.
  Fix: Divide clock difference by `CLOCKS_PER_SEC`.

- Error: Integer overflow for large arrays.
  Fix: Use `long long sum`.

## 21. Code Improvements

- Use `vector<int>` instead of `int arr[n]`.
- Use `long long` for sum.
- Use `omp_get_wtime()` for timing.
- Add sequential version for comparison.
- Print number of threads.
- Allow user to enter array size.
