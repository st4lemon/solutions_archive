# Andrew Stankevich Contest 3 (ASC 3) 

[Link to problems (Codeforces)](https://codeforces.com/gym/100198)

(*) Problems with stars were more difficult.

## A: Areas

- Given a set of $N \leq 80$ lines on the plane, count the number of finite faces and print their areas in non-decreasing order. 

### Solution

Draw a large bounding box around all of the line intersections. Then, any face with a vertex on the bounding box must have an edge on the bounding box, and is an infinite face. We maintain a list of faces in the plane and iteratively add lines. For each line, we check if it intersects each face, and if it does then we partition the face and add both faces to the list. At the end, find the areas of faces without points on the bounding box. This can be done with a standard polygon cut algorithm.

The number of intersections of $N$ lines is $N \choose 2$, and the number of edges is $N^2$ (including infinite edges). Therefore, the number of faces on the plane is roughly $(N+1) \choose 2$, so we can indeed store them all. Then, for each line we add, we run polygonCut on all $O(N^2)$ faces active at the time. The best upper bound on runtime is $O(N^2)$ per line, since polygonCut checks every polygon edge for an intersection, and each edge is in exactly 2 faces. Overall, this is $O(N^3)$ which is more than fast enough. 

## F: Weird Dissimilarity

- You are given an alphabet $\Sigma$ of up to 200 characters, and two strings $s$ and $t$ ($|s|, |t| \leq 2000$). You are also given a matrix $d$ that computes the "dissimilarity" function $d(a, b) \to \mathbb{N}$ for all $a, b \in \Sigma$. Then, for length $n$ strings $\alpha$ and $\beta$, $dist(\alpha, \beta) = \sum_{i=0}^{n-1}d(\alpha[i], \beta[i])$. 
- Generate two strings $\alpha$ and $\beta$ of the same length such that they have the minimum *distance* among all pairs of strings such that $\alpha$ contains $s$ as a subsequence and $\beta$ contains $t$ as a subsequence. 

### Solution

Dynamic programming on subsequence length: Let `dp[i][j] = min cost to generate two strings taking i chars from s and j chars from t as subsequences`. Then, there are three transitions we can take to reach$(i, j)$:

- `dp[i-1][j]`: append `s[i-1]` to $\alpha$ and choose the lowest-cost character to append to $\beta$, adding this minimjum cost
- `dp[i][j-1]`: append `t[j-1]` to $\beta$ and choose the lowest-cost character to append to $\alpha$, adding this minimum cost.
- `dp[i-1][j-1]`: append `s[i-1]` to $\alpha$ and `t[j-1]` to $\beta$, and add cost `(s[i-1], t[j-1])`  

Precompute these minimal transitions in $O(|\Sigma|^2)$, then each transition takes $O(1)$ time. Additionally store the optimal transitions for each state, and to generate $\alpha$ and $\beta$ we can walk backwards along these optimal transitions from `dp[|s|][|t|]` to `dp[0][0]`. The memory is rather tight to store $O(N^2)$ states, so be efficient with storing the transitions. 

## G: PLCool

- Problem description is long, omitted.

### Solution

If we know the value of each operand already when we process a print statement, the problem simply boils down to writing a recursive expression parser, which is a standard problem found online. The problem helpfully guarantees that the value of any expression found during the process of computing an expression is within $\pm 10^9$, so this can be done easily in any language.

In order to find the values of each operand, we maintain a DSU structure based on the define functions. Each define draws a directed edge from the first operand to the second. Additionally, if an undefined operand appears there is a default value we can give it. So we come up with the following definition of values:

- If the parent of $x$ is itself, it is a parent node in the DSU and is "undefined" and has a default value. 
- If the parent of $x$ is not itself, it takes the value of it's parent. 

So then, when `define x y` is called, first if `y` is undefined we assign it a default value. Then, if `x` has a parent other than itself we ignore this call, otherwise set the parent of `x` to `y`. We can then use standard tricks like path compression and union-by-size to optimize. Since there are a small number of print statements and an even smaller number of operands per print statement, just using path compression is okay; the upper bound on number of edge traversals we make is bounded by $ \times (30000\text{ operands}) \times (2000 \text{ prints}) \leq 4\cdot 10^7$, which is still an overestimate.

### I: Two Cylinders

- You are given two cylinders whose axes intersect and are perpendicular. They have infinite height and have radius $R_1$ and $R_2$ respectively. Output the volume of the intersection of the cylinders. 

### Solution

Let $r$ be the smaller of the two radiuses and $R$ be the larger. The integral we are looking for is simply $\int_{-r}^r (2\sqrt{R^2 - x^2})(2\sqrt{r^2-x^2}) dx$. One can compute this easily using any rapidly-converging integral approximation function, such as Simpson's Rule with step size $10^{-5}$. 
