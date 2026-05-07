# Parallel Breadth First Search Using OpenMP

## 0. Beginner Roadmap and HPC Focus

If you are new to High Performance Computing, understand this practical in this simple way:

- **HPC** means solving problems faster by using more computing power.
- A normal program often runs mostly on one CPU core.
- A parallel program divides work among multiple CPU cores or threads.
- **OpenMP** helps us write parallel programs in C/C++ using simple `#pragma` directives.
- **Thread** means a smaller worker inside a program.
- **Race condition** means two or more threads try to update shared data at the same time and may create wrong output.
- **Synchronization** means controlling threads so shared data stays correct.

Subject focus:

This practical is from **High Performance Computing** because it parallelizes graph traversal using CPU threads. In the exam, first say: "This program performs BFS traversal on an undirected graph and uses OpenMP to process nodes at the same BFS level in parallel."

## 0A. Core Theory: What, Why, How, and When

### What is a Graph?

A graph is a data structure made of:

- **Vertices/nodes**: points in the graph.
- **Edges**: connections between nodes.

Example:

```text
0 connected to 1 and 2
1 connected to 3 and 4
2 connected to 5 and 6
```

This can represent networks, maps, social connections, computer networks, and trees.

### What is BFS?

BFS stands for Breadth First Search. It visits nodes level by level.

If BFS starts from node `0`, it first visits:

1. Start node.
2. All direct neighbors.
3. Neighbors of those neighbors.
4. Continues level by level.

### Why use BFS?

BFS is useful when we want shortest path in an unweighted graph. It is also used in searching, networking, web crawling, and AI.

### How does BFS work normally?

Sequential BFS usually uses a queue:

1. Insert start node into queue.
2. Remove one node from queue.
3. Visit its unvisited neighbors.
4. Insert neighbors into queue.
5. Repeat until queue is empty.

### How is BFS parallelized?

At one BFS level, many nodes can be processed independently. This group of nodes is called the **frontier**.

Example:

```text
Level 0: 0
Level 1: 1, 2
Level 2: 3, 4, 5, 6
```

Nodes `1` and `2` can be processed at the same time. Nodes `3`, `4`, `5`, and `6` can also be processed at the same time.

### Why is synchronization needed?

Multiple threads may try to:

- Print output at the same time.
- Mark the same node as visited.
- Add nodes into the same `next` vector.

This can cause race conditions. So `critical` is used to make sensitive operations safe.

### When should parallel BFS be used?

Use parallel BFS for large graphs where each level has many nodes. For very small graphs, parallel BFS may be slower because creating and managing threads takes extra time.

## 1. Which Practical This File Belongs To

This note is based on `bfs.cpp`. It belongs to the **Parallel Breadth First Search using OpenMP** practical because it creates an undirected graph and traverses it level by level using a parallel BFS function.

Requirement check:

- Required: Parallel BFS using OpenMP on a tree or undirected graph.
- Actual code: Uses an undirected graph with 7 vertices and `#pragma omp parallel for`.
- Match status: **Matches the practical requirement**.

## 2. Aim of the Practical

To design and implement Breadth First Search traversal on an undirected graph using OpenMP parallelization.

## 3. Concept Used

Breadth First Search, or BFS, is a graph traversal algorithm. It starts from a source node and visits all directly connected nodes first, then moves to the next level.

The code uses a `frontier` list to store the current level of nodes and a `next` list to store nodes of the next level.

## 4. Algorithm Explanation

1. Create a graph using an adjacency list.
2. Insert edges into the graph.
3. Start BFS from vertex `0`.
4. Mark the start vertex as visited.
5. Put the start vertex into the `frontier`.
6. While the frontier is not empty:
   - Process all nodes in the current frontier.
   - Print each current node.
   - Check all neighbors of each current node.
   - If a neighbor is not visited, mark it visited and add it to `next`.
7. After processing the current level, assign `frontier = next`.
8. Repeat until all reachable nodes are visited.

## 5. Libraries and Header Files Used

- `#include <iostream>`: Used for input/output, mainly `cout`.
- `#include <vector>`: Used to store adjacency lists, visited array, frontier, and next frontier.
- `#include <omp.h>`: Provides OpenMP support and allows use of OpenMP directives.

## 6. Complete Code Logic

The program defines a `Graph` class. The graph stores number of vertices and an adjacency list. The `addEdge()` function adds undirected edges. The `parallelBFS()` function performs BFS using two vectors: `frontier` for current level and `next` for next level.

In `main()`, a graph of 7 vertices is created. Edges are added like a tree:

```text
        0
      /   \
     1     2
    / \   / \
   3   4 5   6
```

Then BFS starts from vertex `0`.

## 7. Step-by-Step Code Explanation

`class Graph`

Defines a graph data structure.

`int V;`

Stores number of vertices.

`vector<vector<int>> adj;`

Stores adjacency list. For each vertex, it stores connected neighbors.

`Graph(int V)`

Constructor. It receives number of vertices and resizes adjacency list.

`void addEdge(int u, int v)`

Adds an edge between `u` and `v`.

`adj[u].push_back(v);`

Adds `v` as neighbor of `u`.

`adj[v].push_back(u);`

Adds `u` as neighbor of `v`, so the graph is undirected.

`vector<bool> visited(V, false);`

Keeps track of visited vertices.

`vector<int> frontier, next;`

`frontier` stores current BFS level. `next` stores the next BFS level.

`frontier.push_back(start);`

Adds starting node to the frontier.

`visited[start] = true;`

Marks starting node as visited.

`while (!frontier.empty())`

Continues BFS while there are nodes to process.

`next.clear();`

Clears next level before processing current level.

`#pragma omp parallel for`

Parallelizes the loop over current frontier nodes.

`int node = frontier[i];`

Gets the current node.

`#pragma omp critical cout << node << " ";`

Ensures only one thread prints at a time.

`for (int neighbor : adj[node])`

Visits all neighbors of current node.

`if (!visited[neighbor])`

Checks if neighbor has not already been visited.

`#pragma omp critical`

Protects the visited check and insertion into `next`.

`next.push_back(neighbor);`

Adds neighbor to next frontier.

`frontier = next;`

Moves to the next BFS level.

## 8. Input and Output Explanation

Input:

- No user input is taken.
- The graph is hardcoded in `main()`.

Output:

The program prints BFS traversal, for example:

```text
Parallel BFS: 0 1 2 3 4 5 6
```

Because of parallel execution, order inside the same BFS level may change. For example, `1 2` may appear as `2 1`.

## 9. Parallelization Logic

Parallelism is applied to nodes in the current BFS frontier.

At each BFS level, multiple nodes can be processed at the same time because their neighbors can be checked independently. The code uses `#pragma omp parallel for` for this.

Shared data like `cout`, `visited`, and `next` can cause race conditions, so critical sections are used.

## 10. OpenMP Explanation

OpenMP directive used:

`#pragma omp parallel for`

- Creates multiple threads.
- Divides loop iterations among threads.
- Each thread processes one or more frontier nodes.

`#pragma omp critical`

- Allows only one thread to execute the protected block at a time.
- Used while printing.
- Used while checking/updating `visited` and `next`.

Race condition handling:

- Without `critical`, two threads may visit the same neighbor and push it twice.
- The code checks `visited[neighbor]` again inside the critical section to avoid duplicate insertion.

Performance comparison:

- This code does not compare sequential and parallel BFS time.
- It only shows parallel BFS traversal.

## 11. CUDA Explanation

CUDA is not used in this file. This is an OpenMP CPU program.

## 12. Time Complexity

Sequential BFS time complexity:

```text
O(V + E)
```

where `V` is number of vertices and `E` is number of edges.

Parallel BFS expected improvement:

- Nodes at the same level can be processed in parallel.
- Actual speedup depends on graph structure.
- Small graphs may not show speedup due to thread overhead and critical sections.

## 13. Space Complexity

Space complexity:

```text
O(V + E)
```

Reason:

- Adjacency list stores graph edges.
- `visited` stores visited status for each vertex.
- `frontier` and `next` store current and next level nodes.

## 14. Performance Measurement

This code does not measure execution time.

To measure performance, use `omp_get_wtime()` before and after BFS:

```cpp
double start = omp_get_wtime();
g.parallelBFS(0);
double end = omp_get_wtime();
cout << "Time: " << end - start;
```

For proper comparison, also implement sequential BFS and compare both times.

## 15. Output Explanation

Expected traversal for the hardcoded tree:

```text
0 1 2 3 4 5 6
```

Meaning:

- `0` is visited first.
- `1` and `2` are visited next.
- `3`, `4`, `5`, and `6` are visited last.

Due to parallel execution, same-level order may vary.

## 16. Why This Practical Is Important

Parallel BFS is important in graph analytics, social networks, web crawling, routing, search engines, and AI search problems. In HPC, large graphs can have millions of vertices, so processing frontier nodes in parallel can reduce runtime.

## 17. Common Viva Questions and Answers

1. What is BFS?
   Answer: BFS is a graph traversal algorithm that visits nodes level by level.

2. What data structure is commonly used in sequential BFS?
   Answer: Queue.

3. What does this code use instead of a queue?
   Answer: It uses `frontier` and `next` vectors.

4. What is a frontier?
   Answer: The set of nodes at the current BFS level.

5. Why is BFS suitable for parallelization?
   Answer: Nodes at the same level can be processed independently.

6. Which OpenMP directive is used for parallelism?
   Answer: `#pragma omp parallel for`.

7. Why is `critical` used while printing?
   Answer: To prevent multiple threads from writing to `cout` at the same time.

8. Why is `critical` used for `visited` and `next`?
   Answer: To avoid race conditions and duplicate visits.

9. What is a race condition?
   Answer: A situation where multiple threads access shared data at the same time and produce incorrect results.

10. Is the graph directed or undirected?
    Answer: Undirected, because edges are added both ways.

11. What is the time complexity of BFS?
    Answer: `O(V + E)`.

12. What is the space complexity of BFS?
    Answer: `O(V + E)`.

13. Does BFS always give shortest path in an unweighted graph?
    Answer: Yes, BFS finds shortest path by number of edges.

14. Can output order change in parallel BFS?
    Answer: Yes, order among nodes at the same level can change.

15. Does this code measure performance?
    Answer: No.

16. How can performance be measured?
    Answer: Using `omp_get_wtime()`.

17. Why is the second visited check inside critical needed?
    Answer: Because another thread may mark the neighbor visited before this thread enters critical section.

18. What is the starting node?
    Answer: Node `0`.

19. What is the main limitation of this code?
    Answer: Critical sections reduce parallel speedup.

20. How can the code be improved?
    Answer: Add sequential BFS, timing, user input, and better thread-safe frontier handling.

## 18. Examiner-Style Short Explanation

This program implements parallel BFS using OpenMP. The graph is stored using an adjacency list. BFS starts from node 0 and processes nodes level by level using a frontier vector. The loop over frontier nodes is parallelized with `#pragma omp parallel for`, so multiple nodes at the same level can be processed simultaneously. Critical sections are used to safely print nodes and update the shared visited array and next frontier. The code matches the Parallel BFS practical, but it does not include timing or comparison with sequential BFS.

## 19. Important Points to Remember

- BFS visits level by level.
- This code uses an undirected graph.
- `frontier` stores current level.
- `next` stores next level.
- `parallel for` divides frontier nodes among threads.
- `critical` avoids race conditions.
- Output order within same level may change.
- Time complexity remains `O(V + E)`, but parallelism can reduce runtime for large graphs.

## 20. Possible Errors and Fixes

- Error: `omp.h` not found.
  Fix: Install compiler with OpenMP support.

- Error: OpenMP directives ignored.
  Fix: Compile with `-fopenmp` in GCC.

- Error: Duplicate nodes in output.
  Fix: Protect visited check and update using critical section.

- Error: Slow parallel execution.
  Fix: Use larger graph and reduce critical section usage.

- Error: Invalid vertex index.
  Fix: Ensure edges use vertices from `0` to `V-1`.

## 21. Code Improvements

- Add sequential BFS for comparison.
- Measure time using `omp_get_wtime()`.
- Take graph input from user.
- Print number of threads used.
- Avoid printing inside parallel loop for better performance.
- Use thread-local next frontier vectors and merge them after the parallel region.
