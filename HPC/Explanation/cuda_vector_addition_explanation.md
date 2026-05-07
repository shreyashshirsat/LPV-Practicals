# CUDA Vector Addition

## 0. Beginner Roadmap and HPC/CUDA Focus

If you are new to High Performance Computing and CUDA, understand this practical in this simple way:

- **CUDA** is used to run code on an NVIDIA GPU.
- CPU is called the **host**.
- GPU is called the **device**.
- A GPU has many small workers called threads.
- Vector addition is easy to parallelize because every element can be added independently.
- Each CUDA thread can calculate one output element.
- Data must be copied from CPU memory to GPU memory before the kernel runs.
- After the kernel finishes, the result must be copied back from GPU to CPU.

Subject focus:

This practical is from **High Performance Computing using GPU programming**. In the exam, first say: "This program should add two large vectors using CUDA, where each GPU thread computes one element of the result vector."

## 0A. Core Theory: What, Why, How, and When

### What is CUDA?

CUDA is a parallel programming platform by NVIDIA. It allows us to run code on the GPU.

A CPU has fewer powerful cores. A GPU has many smaller cores designed to perform many simple operations at the same time.

### What is Vector Addition?

Vector addition means adding two arrays element by element.

Example:

```text
A = [1, 2, 3]
B = [4, 5, 6]
C = [5, 7, 9]
```

Formula:

```text
C[i] = A[i] + B[i]
```

### Why is Vector Addition good for GPU?

Each output element is independent. Calculating `C[0]` does not depend on `C[1]`. Therefore, many GPU threads can calculate different elements at the same time.

### What is Host and Device?

In CUDA:

- **Host** means CPU.
- **Device** means GPU.
- Host memory means normal RAM.
- Device memory means GPU memory.

The CPU starts the program, but the GPU performs the parallel calculation.

### What is a Kernel?

A kernel is a function that runs on the GPU. It is written with `__global__`.

The CPU launches the kernel, and many GPU threads execute it.

### How does CUDA thread indexing work?

CUDA threads are grouped into blocks. Blocks are grouped into a grid.

To find which array element a thread should process, we calculate:

```cpp
int i = blockIdx.x * blockDim.x + threadIdx.x;
```

This gives a unique global index for each thread.

### Why is memory copy needed?

CPU and GPU have separate memory. The GPU cannot directly use normal CPU arrays in basic CUDA programs. So:

1. Copy input from CPU to GPU.
2. Run kernel on GPU.
3. Copy result from GPU back to CPU.

### When should CUDA be used?

Use CUDA when:

- Data is large.
- Same operation is repeated many times.
- Operations are independent.
- GPU is available.

For very small data, CPU may be faster because memory transfer overhead is high.

## 1. Which Practical This File Belongs To

This note belongs to the **CUDA Vector Addition** practical from the given HPC list.

Important file check:

- Required file: CUDA program for addition of two large vectors.
- Actual files present in `access`: `bfs.cpp`, `dfs.cpp`, `bubblesort.cpp`, `mergesort.cpp`, `mmas.cpp`.
- CUDA source file present: **No `.cu` file found**.
- Match status: **Missing source code**.

This Markdown file is therefore an exam-focused guide for what the CUDA vector addition program should contain.

## 2. Aim of the Practical

To write a CUDA C/C++ program that adds two large vectors in parallel using GPU threads.

## 3. Concept Used

Vector addition means:

```text
C[i] = A[i] + B[i]
```

for every index `i`.

In CUDA, each GPU thread can calculate one element of the result vector. This makes vector addition highly parallel.

## 4. Algorithm Explanation

1. Create two input vectors `A` and `B` on CPU.
2. Initialize them with values.
3. Allocate memory on GPU for `A`, `B`, and `C`.
4. Copy `A` and `B` from CPU memory to GPU memory.
5. Launch CUDA kernel.
6. Each GPU thread calculates one index:
   - Find global thread index.
   - If index is within range, calculate `C[i] = A[i] + B[i]`.
7. Copy result vector `C` back from GPU to CPU.
8. Print or verify result.
9. Free GPU memory.

## 5. Libraries and Header Files Used

A typical CUDA vector addition program uses:

- `#include <iostream>`: For printing output.
- `#include <cuda_runtime.h>`: For CUDA runtime functions such as `cudaMalloc`, `cudaMemcpy`, and `cudaFree`.

Sometimes only CUDA compiler support is enough and explicit CUDA runtime include may not be shown, but using it is clearer.

## 6. Complete Code Logic

Expected program flow:

1. Declare vector size `N`.
2. Allocate host arrays on CPU.
3. Fill input arrays.
4. Allocate device arrays on GPU.
5. Copy data from host to device.
6. Configure CUDA block size and grid size.
7. Launch kernel.
8. Copy output from device to host.
9. Display result.
10. Free allocated memory.

## 7. Step-by-Step Code Explanation

Typical kernel:

```cpp
__global__ void vectorAdd(int *A, int *B, int *C, int N) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < N) {
        C[i] = A[i] + B[i];
    }
}
```

`__global__`

Means this function runs on GPU and is called from CPU.

`blockIdx.x`

Index of the current block.

`blockDim.x`

Number of threads in one block.

`threadIdx.x`

Index of current thread inside its block.

`int i = blockIdx.x * blockDim.x + threadIdx.x;`

Calculates global thread index.

`if (i < N)`

Prevents extra threads from accessing invalid memory.

`C[i] = A[i] + B[i];`

Performs one vector addition.

Typical memory allocation:

```cpp
cudaMalloc(&d_A, N * sizeof(int));
cudaMalloc(&d_B, N * sizeof(int));
cudaMalloc(&d_C, N * sizeof(int));
```

Allocates memory on GPU.

Typical copy:

```cpp
cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
```

Copies input arrays from CPU to GPU.

Kernel launch:

```cpp
vectorAdd<<<blocks, threads>>>(d_A, d_B, d_C, N);
```

Runs the CUDA kernel.

Copy result:

```cpp
cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
```

Copies result from GPU to CPU.

Free memory:

```cpp
cudaFree(d_A);
cudaFree(d_B);
cudaFree(d_C);
```

Releases GPU memory.

## 8. Input and Output Explanation

Input:

- Usually two vectors `A` and `B`.
- Values may be hardcoded, randomly generated, or entered by user.

Output:

- Result vector `C`.

Example:

```text
A = [1, 2, 3]
B = [4, 5, 6]
C = [5, 7, 9]
```

## 9. Parallelization Logic

Each vector element is independent.

So:

- Thread 0 calculates `C[0]`
- Thread 1 calculates `C[1]`
- Thread 2 calculates `C[2]`

This is called data parallelism.

No synchronization is needed inside the kernel because each thread writes to a different index.

## 10. OpenMP Explanation

OpenMP is not used in CUDA vector addition. This practical uses GPU parallelism through CUDA.

## 11. CUDA Explanation

CPU responsibilities:

- Allocate host memory.
- Initialize vectors.
- Allocate GPU memory.
- Copy data to GPU.
- Launch kernel.
- Copy result back.
- Free memory.

GPU responsibilities:

- Run many threads.
- Each thread adds one vector element.

Kernel function:

- Runs on GPU.
- Contains code executed by each thread.

Thread ID calculation:

```cpp
int i = blockIdx.x * blockDim.x + threadIdx.x;
```

Blocks and grids:

- Threads are grouped into blocks.
- Blocks are grouped into a grid.

Typical configuration:

```cpp
int threads = 256;
int blocks = (N + threads - 1) / threads;
```

Device memory:

- Allocated using `cudaMalloc`.

Host memory:

- Normal CPU arrays or vectors.

Memory copy:

- Host to device: input data.
- Device to host: output data.

Why CUDA is useful:

- Large vectors have many independent additions.
- GPU can run thousands of threads.

## 12. Time Complexity

Sequential vector addition:

```text
O(n)
```

CUDA vector addition:

- Total work is still `O(n)`.
- With many GPU threads, practical runtime can be much lower.
- Ideal parallel time is close to `O(n / number_of_threads)`.

## 13. Space Complexity

Space complexity:

```text
O(n)
```

Memory used:

- Host vectors `A`, `B`, `C`.
- Device vectors `d_A`, `d_B`, `d_C`.

Total memory is roughly six arrays of size `n`.

## 14. Performance Measurement

A correct CUDA program can measure time using:

- CPU timers for total time.
- CUDA events for GPU kernel time.

CUDA event example:

```cpp
cudaEventRecord(start);
vectorAdd<<<blocks, threads>>>(d_A, d_B, d_C, N);
cudaEventRecord(stop);
cudaEventSynchronize(stop);
cudaEventElapsedTime(&ms, start, stop);
```

For fair performance comparison, compare:

- Sequential CPU vector addition time.
- CUDA kernel time.
- Total CUDA time including memory transfer.

## 15. Output Explanation

Expected output should show correct addition.

Example:

```text
Vector addition completed successfully
C[0] = 3
C[1] = 5
C[2] = 7
```

For large vectors, usually only first few values are printed.

## 16. Why This Practical Is Important

Vector addition is the simplest CUDA program and teaches the basic GPU programming flow: host memory, device memory, kernel launch, thread indexing, and memory copy. These ideas are used in larger HPC problems.

## 17. Common Viva Questions and Answers

1. What is CUDA?
   Answer: CUDA is NVIDIA's platform for GPU programming.

2. What is a kernel?
   Answer: A function that runs on the GPU.

3. What does `__global__` mean?
   Answer: The function runs on GPU and is called from CPU.

4. What is host?
   Answer: CPU and its memory.

5. What is device?
   Answer: GPU and its memory.

6. What does `cudaMalloc` do?
   Answer: Allocates memory on GPU.

7. What does `cudaMemcpy` do?
   Answer: Copies data between CPU and GPU memory.

8. What does `cudaFree` do?
   Answer: Frees GPU memory.

9. How is thread index calculated?
   Answer: `blockIdx.x * blockDim.x + threadIdx.x`.

10. Why check `i < N`?
    Answer: To avoid out-of-bounds memory access.

11. What is a block?
    Answer: A group of CUDA threads.

12. What is a grid?
    Answer: A group of CUDA blocks.

13. Why use `(N + threads - 1) / threads`?
    Answer: To create enough blocks for all elements.

14. Does each thread compute the whole vector?
    Answer: No, each thread usually computes one element.

15. Is synchronization needed for vector addition?
    Answer: No, because each thread writes to a different output index.

16. What is data parallelism?
    Answer: Applying the same operation to many independent data items.

17. What compiler is used for CUDA?
    Answer: `nvcc`.

18. What file extension is commonly used?
    Answer: `.cu`.

19. What is memory transfer overhead?
    Answer: Time spent copying data between CPU and GPU.

20. Why is GPU faster for large vectors?
    Answer: Many elements can be processed simultaneously by many threads.

## 18. Examiner-Style Short Explanation

CUDA vector addition adds two arrays using GPU parallelism. The CPU initializes input vectors, allocates GPU memory using `cudaMalloc`, copies data to the GPU using `cudaMemcpy`, and launches a kernel. Inside the kernel, each thread calculates its global index and adds one pair of elements. The result is copied back to CPU memory and GPU memory is freed. The CUDA source file is missing in the current directory, but this is the expected logic for the practical.

## 19. Important Points to Remember

- CUDA runs code on GPU.
- CPU is host, GPU is device.
- Kernel runs on GPU.
- Each thread handles one vector element.
- Use `cudaMalloc`, `cudaMemcpy`, and `cudaFree`.
- Use bounds check `if (i < N)`.
- Compile CUDA code with `nvcc`.

## 20. Possible Errors and Fixes

- Error: `nvcc` not found.
  Fix: Install NVIDIA CUDA Toolkit.

- Error: No CUDA-capable device.
  Fix: Run on a system with NVIDIA GPU.

- Error: Illegal memory access.
  Fix: Check thread index bounds with `if (i < N)`.

- Error: Wrong result.
  Fix: Check memory copy directions.

- Error: Missing `.cu` file.
  Fix: Create a CUDA source file for vector addition.

## 21. Code Improvements

- Add CPU sequential version for comparison.
- Use CUDA events for accurate kernel timing.
- Check return values of CUDA API calls.
- Use large `N` to show GPU benefit.
- Print only first few elements for large vectors.
- Add result verification.
