# Parallel Depth First Search Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- **HPC** focuses on making programs faster using parallel execution.
- **DFS** explores one path deeply before coming back.
- In parallel DFS, different branches of the graph can be explored by different threads.
- **OpenMP task** means a unit of work that can be picked up by any available thread.
- Because many threads share the same `visited` array, synchronization is needed.
- `critical` is used so only one thread updates shared data at a time.

Subject focus:

This practical is from **High Performance Computing** because it uses OpenMP tasks to explore recursive graph branches in parallel. In the exam, first say: "This program performs DFS on an undirected graph using OpenMP tasks for parallel recursive traversal."

## 0A. Core Theory: What, Why, How, and When

### What is DFS?

DFS stands for Depth First Search. It explores a graph by going as deep as possible along one path before backtracking.

Example:

```text
Start at 0
Go to 1
Go to 3
Backtrack
Go to 4
Backtrack
Go to 2
...
```

### Why use DFS?

DFS is useful for:

- Searching paths.
- Detecting cycles.
- Topological sorting.
- Solving mazes.
- Exploring connected components.
- Backtracking problems.

### How does DFS work normally?

DFS can be implemented using:

- Recursion.
- Stack.

The code uses recursion. Each recursive call explores one node and then recursively explores its unvisited neighbors.

### What is parallel DFS?

In parallel DFS, different branches of the graph can be explored by different threads.

For example, from node `0`, branches through node `1` and node `2` may be explored in parallel.

### Why use OpenMP tasks?

DFS is recursive and irregular. We do not always know in advance how many iterations or branches there will be. OpenMP `task` is useful for such recursive work because each branch can become a task.

### Why is synchronization needed?

All tasks share the `visited` array. If two tasks try to visit the same node at the same time, the output can become wrong. The code uses `critical` to safely check and update `visited`.

### When should parallel DFS be used?

Parallel DFS is useful for large search spaces with many independent branches. It may not help much for small graphs because task creation has overhead.

## 1. Which Practical This File Belongs To

This note is based on `dfs.cpp`. It belongs to the **Parallel Depth First Search using OpenMP** practical because it traverses an undirected graph using DFS and uses OpenMP tasks for parallel recursive exploration.

Requirement check:

- Required: Parallel DFS using OpenMP on a tree or undirected graph.
- Actual code: Uses undirected graph and OpenMP `parallel`, `single`, `task`, and `critical`.
- Match status: **Matches the practical requirement**.

## 2. Aim of the Practical

To design and implement Depth First Search traversal on an undirected graph using OpenMP parallel tasking.

## 3. Concept Used

Depth First Search, or DFS, is a graph traversal algorithm. It starts from a source node and explores as deep as possible before backtracking.

This code uses recursion and OpenMP tasks. Each unvisited neighbor can become a separate task.

## 4. Algorithm Explanation

1. Create an undirected graph using adjacency list.
2. Start DFS from node `0`.
3. Mark the start node as visited.
4. Print the current node.
5. For each neighbor:
   - Check if it is unvisited.
   - Mark it visited.
   - Create a new OpenMP task to explore that neighbor.
6. Recursive calls continue until all reachable nodes are visited.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Used for `cout`.
- `#include <vector>`: Used for adjacency list and visited array.
- `#include <omp.h>`: Provides OpenMP directives and parallel tasking support.

## 6. Complete Code Logic

The program defines a `Graph` class with vertices, adjacency list, and visited array. Edges are added as undirected edges. The `parallelDFS()` function starts an OpenMP parallel region. Inside it, a single thread starts the DFS using `dfsUtil()`. During DFS, unvisited neighbors are explored as OpenMP tasks, allowing multiple branches of the DFS tree to run in parallel.

## 7. Step-by-Step Code Explanation

`class Graph`

Defines the graph.

`int V;`

Stores number of vertices.

`vector<vector<int>> adj;`

Stores adjacency list.

`vector<bool> visited;`

Stores whether each vertex has already been visited.

`Graph(int V)`

Constructor initializes number of vertices, adjacency list, and visited array.

`void addEdge(int u, int v)`

Adds undirected edge between `u` and `v`.

`void dfsUtil(int node)`

Recursive helper function for DFS.

`#pragma omp critical cout << node << " ";`

Prints current node safely so multiple threads do not print at the same time.

`for (int neighbor : adj[node])`

Loops through all neighbors.

`bool go = false;`

This flag decides whether DFS should continue to that neighbor.

`#pragma omp critical`

Protects checking and updating `visited`.

`if (!visited[neighbor])`

Checks whether neighbor is not visited.

`visited[neighbor] = true;`

Marks neighbor visited before creating the task.

`go = true;`

Allows recursion for this neighbor.

`#pragma omp task`

Creates a parallel task for recursive DFS call.

`dfsUtil(neighbor);`

Explores the neighbor deeply.

`#pragma omp parallel`

Creates a team of threads.

`#pragma omp single`

Ensures only one thread starts the first DFS call. Other threads wait to execute tasks.

## 8. Input and Output Explanation

Input:

- No user input.
- Graph is hardcoded with 7 nodes.

Output:

Example:

```text
Parallel DFS: 0 1 3 4 2 5 6
```

Actual order may change because OpenMP tasks can execute in different order.

## 9. Parallelization Logic

Parallelism is applied using OpenMP tasks.

DFS is recursive. Different branches of the DFS tree can be explored at the same time. When an unvisited neighbor is found, the code creates a task for it.

The visited array is shared, so `critical` is used to avoid two tasks visiting the same node.

## 10. OpenMP Explanation

Directives used:

`#pragma omp parallel`

- Creates multiple threads.
- Required so tasks can run on multiple threads.

`#pragma omp single`

- Ensures only one thread begins DFS from the start node.
- Other threads can execute tasks created by that thread.

`#pragma omp task`

- Creates a unit of work for exploring a neighbor.
- Tasks may run in parallel.

`#pragma omp critical`

- Protects printing.
- Protects `visited` check and update.

Race condition handling:

- The visited array is shared.
- If two threads check the same neighbor at the same time, both may visit it.
- Critical section ensures only one thread marks a node visited.

Performance comparison:

- The code does not include sequential DFS or timing.
- For comparison, add sequential DFS and use `omp_get_wtime()`.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Sequential DFS complexity:

```text
O(V + E)
```

Parallel DFS:

- The total work remains `O(V + E)`.
- Parallel tasks may reduce runtime by exploring branches at the same time.
- Speedup depends on graph shape and task overhead.

## 13. Space Complexity

Space complexity:

```text
O(V + E)
```

Reason:

- Adjacency list stores graph.
- Visited array stores status.
- Recursive calls and OpenMP tasks require additional stack/task memory.

## 14. Performance Measurement

This code does not measure execution time.

Suggested timing:

```cpp
double start = omp_get_wtime();
g.parallelDFS(0);
double end = omp_get_wtime();
cout << "Time: " << end - start;
```

For performance comparison, create a normal recursive DFS and compare sequential time with parallel time.

## 15. Output Explanation

The output is DFS traversal from node `0`.

DFS goes deep before visiting another branch. For the hardcoded tree, one possible output is:

```text
0 1 3 4 2 5 6
```

Because tasks run in parallel, order can differ.

## 16. Why This Practical Is Important

Parallel DFS is useful in graph search, artificial intelligence, maze solving, state-space exploration, connected component analysis, and large graph processing.

## 17. Common Viva Questions and Answers

1. What is DFS?
   Answer: DFS is a traversal algorithm that explores deeply before backtracking.

2. What is the main difference between BFS and DFS?
   Answer: BFS visits level by level, while DFS visits depth-wise.

3. Which OpenMP feature is used for parallel DFS?
   Answer: OpenMP tasks.

4. Why are tasks suitable for DFS?
   Answer: Recursive branches can be treated as independent tasks.

5. What does `#pragma omp parallel` do?
   Answer: It creates a team of threads.

6. What does `#pragma omp single` do?
   Answer: It allows only one thread to start DFS.

7. What does `#pragma omp task` do?
   Answer: It creates a task that can be executed by available threads.

8. Why is `critical` used?
   Answer: To protect shared output and visited array.

9. What is a race condition?
   Answer: Incorrect behavior caused by multiple threads accessing shared data at the same time.

10. Is the graph directed?
    Answer: No, it is undirected.

11. What is the time complexity of DFS?
    Answer: `O(V + E)`.

12. What is the space complexity?
    Answer: `O(V + E)` plus recursion/task overhead.

13. Can DFS output order change?
    Answer: Yes, parallel task scheduling can change order.

14. Why mark visited before creating task?
    Answer: To prevent another task from visiting the same node.

15. Does this code use a stack?
    Answer: It uses recursion, which internally uses the call stack.

16. Does this code measure performance?
    Answer: No.

17. How can timing be added?
    Answer: Use `omp_get_wtime()`.

18. What is the starting node?
    Answer: Node `0`.

19. What is the limitation of parallel DFS?
    Answer: Too many small tasks can create overhead.

20. How can this code be improved?
    Answer: Add task cutoff, timing, sequential DFS, and user input.

## 18. Examiner-Style Short Explanation

This program implements parallel DFS using OpenMP. The graph is stored as an adjacency list and is undirected. DFS starts from node 0 inside an OpenMP parallel region. A single thread begins the traversal, and recursive calls for unvisited neighbors are created as OpenMP tasks. Critical sections protect printing and the shared visited array to avoid race conditions. The code matches the Parallel DFS practical, though it does not include sequential comparison or timing.

## 19. Important Points to Remember

- DFS explores depth-wise.
- This code uses recursion.
- OpenMP tasks parallelize DFS branches.
- `parallel` creates threads.
- `single` starts DFS once.
- `task` creates recursive parallel work.
- `critical` protects shared data.
- Output order can change.

## 20. Possible Errors and Fixes

- Error: `omp.h` missing.
  Fix: Use a compiler with OpenMP support.

- Error: OpenMP pragmas ignored.
  Fix: Compile with `-fopenmp`.

- Error: Repeated nodes.
  Fix: Protect visited check and update.

- Error: Stack overflow on very large graph.
  Fix: Use iterative DFS or limit recursion depth.

- Error: Slow performance.
  Fix: Add task cutoff to avoid too many tiny tasks.

## 21. Code Improvements

- Add sequential DFS for comparison.
- Add execution time measurement.
- Add user input for graph.
- Add `#pragma omp taskwait` if exact completion control is needed before leaving a scope.
- Avoid printing inside parallel traversal while measuring time.
- Use larger graph to show meaningful speedup.
