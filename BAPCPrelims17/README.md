# 2017 Benelux Algorithm Programming Contest preliminaries 

[Link to contest (Kattis)](https://open.kattis.com/problem-sources/Benelux%20Algorithm%20Programming%20Contest%20%28BAPC%29%20preliminaries%202017)

(*) Problems with stars were more difficult.

## B: Booming Business*

- A bonsai tree consists of a single branch, with 0 or more smaller bonsai trees branching off from that branch. In graph-theoretic terms, a bonsai tree is a rooted tree that has a single edge (branch) coming out of it's root. The "height" of the tree is the length of the longest chain of branches from the root to a leaf node, and the "width" of the tree is the number of edges (branches) on the tree. 
- Count the number of bonsai trees with height $H \leq 300$ and weight $W \leq 300$. Note that two trees that only differ by the ordering of their children are considered different trees.  

### Solution

Often times, combinatorics problems on graphs/grids admit a dynamic programming solution, so we will attempt to use DP. Let $dp[h][w] = $ number of trees with height $h$ and weight $w$. For now, ignore the bonsai condition; we can make any tree a bonsai by attaching another edge to the root and rerooting that tree on the other vertex of that edge. 

There are a number of possible transitions: add branches one-by-one, attach extra branches to the leaves of a height $h-1$ tree to get height $h$ trees, or merge the roots of height $h-1$ trees to obtain trees of height $h$. The first one seems too complicated, and the second one requires extra information on the number of leaf nodes available at the time, so we will go with the third option.  

Suppose we know how many trees of height $\leq h-1$ exist for each possible weight $\leq W$. We attempt to attach some number of these trees by an edge connected to their root to a common root, forming a tree of height $h$. Importantly, a different ordering of the children of a node results in a different tree for our answer, so the number of ways to make a tree of height $h$ and weight $w$ is the unbounded knapsack problem on trees of height $\leq h-1$, with some modifications:

- We must have at least one tree of height $h-1$ among the trees we merge together. Additionally, compute another knapsack using only trees of height $< h-1$, and subtract it from the knapsack of height $\leq h-1$ trees. 
- We must add an edge when we add a tree to connect it with the new height $h$ root node, so a tree with weight $w$ actually has weight $w+1$ for purposes of the knapsack. 
- A tree of weight $0$ is allowed, but only at height $0$.

If we naively compute this for each $dp[h][w]$, this becomes $O(H^2W^2)$ since each knapsack takes $O(HW)$ time. We can speed this up by observing that the answer we wish to compute for some $dp[h][w]$ is part of the resulting knapsack computed for $dp[h][W]$. Therefore we only need to run the knapsack twice per height (for merging height $\leq h-1$ and height $< h-1$ trees respectively), bringing down the total complexity to $O(H^2W)$. 

Remember that earlier we decided that $dp[h][w]$ represents the number of trees, not the number of bonsai trees. We must add an extra edge to the root of height $h-1$ and weight $w-1$ trees to obtain bonsais of height $h$ and weight $w$. The answer is therefore $dp[H-1][W-1]$.  

## I: Intelligence Infection



## J: Journal Editing*



## K: Knight's Marathon