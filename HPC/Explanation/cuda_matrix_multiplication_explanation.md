# CUDA Matrix Multiplication

## 0. Beginner Roadmap and HPC/CUDA Focus

If you are new to High Performance Computing and CUDA, understand this practical in this simple way:

- Matrix multiplication produces a new matrix from two input matrices.
- Each output cell can be calculated independently.
- This independence makes matrix multiplication suitable for GPU parallelism.
- In CUDA, each GPU thread can calculate one output cell.
- A 2D grid of CUDA threads matches the 2D structure of a matrix.
- CPU prepares data and launches the kernel.
- GPU performs the heavy calculation.
- Result is copied back from GPU memory to CPU memory.

Subject focus:

This practical is from **High Performance Computing using GPU programming**. In the exam, first say: "This program should multiply two matrices using CUDA, where each GPU thread computes one element of the output matrix."

## 0A. Core Theory: What, Why, How, and When

### What is Matrix Multiplication?

Matrix multiplication combines two matrices to produce a third matrix.

For each output cell:

```text
C[row][col] = sum of A[row][k] * B[k][col]
```

Example:

```text
C[0][0] = A[0][0]*B[0][0] + A[0][1]*B[1][0] + ...
```

### Why is Matrix Multiplication important?

Matrix multiplication is used in:

- Deep learning.
- Computer graphics.
- Scientific simulations.
- Image processing.
- Engineering calculations.
- Data analytics.

It is one of the most important operations in high performance computing.

### Why use CUDA for Matrix Multiplication?

Matrix multiplication has many output cells. Each output cell can be calculated independently, so many GPU threads can work at the same time.

For example:

- Thread 1 computes `C[0][0]`.
- Thread 2 computes `C[0][1]`.
- Thread 3 computes `C[1][0]`.

### What is a 2D Grid?

Matrices are two-dimensional, so CUDA often uses 2D blocks and 2D grids.

Thread indexing:

```cpp
row = blockIdx.y * blockDim.y + threadIdx.y;
col = blockIdx.x * blockDim.x + threadIdx.x;
```

This maps one thread to one matrix cell.

### What is Host and Device?

- Host: CPU side.
- Device: GPU side.

The CPU prepares matrices and launches the kernel. The GPU performs multiplication.

### What is Device Memory?

CUDA programs usually allocate separate memory on GPU using `cudaMalloc`. Input matrices are copied from CPU to GPU before calculation, and result matrix is copied back after calculation.

### Why is bounds checking needed?

The grid may create more threads than needed. Extra threads must not access invalid matrix positions. That is why CUDA kernels use:

```cpp
if (row < N && col < N)
```

### When should CUDA matrix multiplication be used?

Use CUDA when matrices are large enough that GPU parallelism gives more benefit than memory transfer cost. For small matrices, CPU may be enough.

## 1. Which Practical This File Belongs To

This note belongs to the **CUDA Matrix Multiplication** practical from the given HPC list.

Important file check:

- Required file: CUDA C program for matrix multiplication.
- Actual files present in `access`: `bfs.cpp`, `dfs.cpp`, `bubblesort.cpp`, `mergesort.cpp`, `mmas.cpp`.
- CUDA source file present: **No `.cu` file found**.
- Match status: **Missing source code**.

This Markdown file is an exam-focused guide for what the CUDA matrix multiplication program should contain.

## 2. Aim of the Practical

To write a CUDA C/C++ program that multiplies two matrices using GPU parallelism.

## 3. Concept Used

Matrix multiplication computes:

```text
C[row][col] = sum of A[row][k] * B[k][col]
```

Each output element can be calculated independently, so CUDA can assign one GPU thread to one output matrix element.

## 4. Algorithm Explanation

1. Create matrix `A` and matrix `B` on CPU.
2. Initialize both matrices.
3. Allocate GPU memory for `A`, `B`, and `C`.
4. Copy `A` and `B` from CPU to GPU.
5. Launch CUDA kernel.
6. Each thread calculates one element of matrix `C`.
7. Copy result matrix `C` back from GPU to CPU.
8. Print or verify result.
9. Free GPU memory.

## 5. Libraries and Header Files Used

A typical CUDA matrix multiplication program uses:

- `#include <iostream>`: For printing matrices and messages.
- `#include <cuda_runtime.h>`: For CUDA runtime functions.

For timing, it may also use CUDA events or C++ timing libraries.

## 6. Complete Code Logic

Expected program flow:

1. Define matrix dimensions.
2. Allocate host memory.
3. Initialize input matrices.
4. Allocate device memory with `cudaMalloc`.
5. Copy input matrices to device using `cudaMemcpy`.
6. Configure 2D block and 2D grid.
7. Launch matrix multiplication kernel.
8. Copy result back to host.
9. Print result or verify correctness.
10. Free device memory.

## 7. Step-by-Step Code Explanation

Typical kernel:

```cpp
__global__ void matrixMul(int *A, int *B, int *C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        int sum = 0;
        for (int k = 0; k < N; k++) {
            sum += A[row * N + k] * B[k * N + col];
        }
        C[row * N + col] = sum;
    }
}
```

`__global__`

Marks the function as a CUDA kernel.

`row`

Global row index calculated using block and thread indexes.

`col`

Global column index calculated using block and thread indexes.

`if (row < N && col < N)`

Prevents invalid memory access.

`for (int k = 0; k < N; k++)`

Computes dot product of one row of `A` and one column of `B`.

`C[row * N + col]`

Stores result in flattened 1D memory.

Typical block/grid setup:

```cpp
dim3 threads(16, 16);
dim3 blocks((N + 15) / 16, (N + 15) / 16);
matrixMul<<<blocks, threads>>>(d_A, d_B, d_C, N);
```

`dim3`

CUDA type used for 2D or 3D block/grid dimensions.

## 8. Input and Output Explanation

Input:

- Matrix `A`
- Matrix `B`

Values may be hardcoded, randomly generated, or entered by user.

Output:

- Matrix `C`, where `C = A x B`.

Example:

```text
A = [1 2]
    [3 4]

B = [5 6]
    [7 8]

C = [19 22]
    [43 50]
```

## 9. Parallelization Logic

Each output matrix cell is independent.

For example:

- One thread computes `C[0][0]`.
- Another thread computes `C[0][1]`.
- Another thread computes `C[1][0]`.

This makes matrix multiplication suitable for GPU parallelism.

## 10. OpenMP Explanation

OpenMP is not used in CUDA matrix multiplication. This practical uses CUDA GPU programming.

## 11. CUDA Explanation

CPU responsibilities:

- Initialize matrices.
- Allocate device memory.
- Copy data to GPU.
- Launch kernel.
- Copy result back.
- Free memory.

GPU responsibilities:

- Run many threads.
- Each thread computes one output element.

Kernel:

- Calculates one `row` and `col`.
- Performs dot product.
- Stores result.

Thread indexing:

```cpp
row = blockIdx.y * blockDim.y + threadIdx.y;
col = blockIdx.x * blockDim.x + threadIdx.x;
```

Blocks and grids:

- A 2D block such as `16 x 16` has 256 threads.
- A 2D grid covers all rows and columns.

Device memory:

- Allocated using `cudaMalloc`.

Host-device transfer:

- `cudaMemcpyHostToDevice` copies input matrices to GPU.
- `cudaMemcpyDeviceToHost` copies result back.

Why CUDA is useful:

- Matrix multiplication has many independent output elements.
- GPUs are designed for massive parallel arithmetic.

## 12. Time Complexity

Sequential matrix multiplication:

```text
O(n^3)
```

Reason:

- For every output cell, loop over `n` elements.
- There are `n x n` output cells.

CUDA version:

- Total arithmetic work remains `O(n^3)`.
- Many output cells are computed in parallel.
- Practical runtime can be much lower on GPU.

## 13. Space Complexity

Space complexity:

```text
O(n^2)
```

Reason:

- Matrix `A`: `n x n`
- Matrix `B`: `n x n`
- Matrix `C`: `n x n`
- Device copies also require GPU memory.

## 14. Performance Measurement

Performance can be measured using CUDA events:

```cpp
cudaEventRecord(start);
matrixMul<<<blocks, threads>>>(d_A, d_B, d_C, N);
cudaEventRecord(stop);
cudaEventSynchronize(stop);
cudaEventElapsedTime(&ms, start, stop);
```

Compare:

- CPU sequential matrix multiplication.
- GPU kernel time.
- GPU total time including memory transfers.

## 15. Output Explanation

Expected output:

- Result matrix `C`.
- For large matrices, usually only part of matrix or verification message is printed.

Correctness check:

- Compare CUDA result with CPU result for small matrix.

## 16. Why This Practical Is Important

Matrix multiplication is a core operation in scientific computing, graphics, simulations, machine learning, neural networks, and image processing. CUDA matrix multiplication teaches GPU thread indexing, 2D grids, and memory transfer.

## 17. Common Viva Questions and Answers

1. What is matrix multiplication?
   Answer: Multiplying rows of first matrix with columns of second matrix.

2. What is CUDA?
   Answer: NVIDIA platform for GPU programming.

3. What is a kernel?
   Answer: A GPU function launched from CPU.

4. What does `__global__` mean?
   Answer: Function runs on GPU and is called from CPU.

5. What does each thread compute?
   Answer: Usually one output matrix element.

6. How is row index calculated?
   Answer: `blockIdx.y * blockDim.y + threadIdx.y`.

7. How is column index calculated?
   Answer: `blockIdx.x * blockDim.x + threadIdx.x`.

8. Why use 2D grid?
   Answer: Matrix output is two-dimensional.

9. What is `dim3`?
   Answer: CUDA type for specifying block and grid dimensions.

10. Why use bounds check?
    Answer: To prevent threads outside matrix size from accessing invalid memory.

11. What is host memory?
    Answer: CPU memory.

12. What is device memory?
    Answer: GPU memory.

13. What does `cudaMalloc` do?
    Answer: Allocates GPU memory.

14. What does `cudaMemcpy` do?
    Answer: Copies data between CPU and GPU.

15. What does `cudaFree` do?
    Answer: Frees GPU memory.

16. What is the time complexity of sequential matrix multiplication?
    Answer: `O(n^3)`.

17. What is the space complexity?
    Answer: `O(n^2)`.

18. Why is GPU useful for matrix multiplication?
    Answer: Many output cells can be computed in parallel.

19. What compiler is used?
    Answer: `nvcc`.

20. What file extension is used for CUDA?
    Answer: `.cu`.

## 18. Examiner-Style Short Explanation

CUDA matrix multiplication multiplies two matrices using GPU threads. The CPU allocates and initializes matrices, copies them to GPU memory using `cudaMemcpy`, and launches a CUDA kernel. In the kernel, each thread calculates its row and column index and computes one output element by taking the dot product of a row of matrix A and a column of matrix B. The result is copied back to CPU memory and GPU memory is freed. The actual CUDA source file is missing in this directory, but this is the required logic for the practical.

## 19. Important Points to Remember

- Matrix multiplication is `O(n^3)` sequentially.
- Each CUDA thread can compute one output cell.
- Use 2D grid and 2D blocks.
- Use `cudaMalloc`, `cudaMemcpy`, and `cudaFree`.
- Use bounds check for row and column.
- Compile with `nvcc`.
- For large matrices, GPU gives better performance.

## 20. Possible Errors and Fixes

- Error: `nvcc` not found.
  Fix: Install CUDA Toolkit.

- Error: No NVIDIA GPU.
  Fix: Run on CUDA-capable system.

- Error: Wrong matrix result.
  Fix: Check row-major indexing formula.

- Error: Illegal memory access.
  Fix: Add row and column bounds check.

- Error: Missing `.cu` file.
  Fix: Create CUDA matrix multiplication source file.

## 21. Code Improvements

- Add CPU version for comparison.
- Use CUDA events for timing.
- Check all CUDA API errors.
- Use shared memory tiled matrix multiplication for better performance.
- Verify GPU result using CPU result.
- Print only small matrices or sample output for large matrices.
