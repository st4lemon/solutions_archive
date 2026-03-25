# Andrew Stankevich Contest 46 (ASC 46) 

[Link to problems (Codeforces)](https://codeforces.com/gym/100524)

(*) Problems with stars were more difficult.

## A: Astronomy Problem

- There are $N \leq 3000$ planets represented as integer points $(x_i, y_i)$ on a 2D grid. You are given $m \leq 3000$ manuscripts, each with three integers $a_i, b_i, c_i$. 
- You are at $p = (0, 0)$. For each manuscript $i$, find the number of pairs of planets $x, y$ such that:
  - $dist(p, x) = \sqrt{a_i}$
  - $dist(p, y) = \sqrt{b_i}$
  - $dist(x, y) = \sqrt{c_i}$

### Solution

For each pair of points, precompute the distance between them and the distances to the origin. We can store the frequency of each triple in a map, and lookup the answer for each manuscript. 

## D: Dichromatic Trees*

- A red-black tree is a binary tree which colors each node red or black. It has the condition that any path from the root to a leaf has the same number of black vertices. This number of black vertices is called the "black height". 
- You are given $k \leq 131072$ integer values of $n_i$, and one integer $h \leq 16$. For each $n_i$, find the number of red-black trees with $n_i$ vertices and black height $h$. Output the answer mod $258\ 280\ 327$. 

### Solution

Let $dp[h][r/b][n]$ = number of red-black trees with $n$ vertices, root color red or black, and black height $h$. This dp can be solved with: 

$$\begin{align*}dp[h][b][n] &= \sum_{i + j = n-1} (dp[h-1][r][i] + dp[h-1][b][i]) \cdot (dp[h-1][r][j] + dp[h-1][b][j]) \\ 
dp[h][r][n] &= \sum_{i+j = n-1} dp[h][b][i] \cdot dp[h][b][j]
\end{align*}$$ 

These recurrences can be rewritten as convolutions. 

$$\begin{align*}
    dp[h][b] &= (dp[h-1][b] + dp[h-1][r]) * (dp[h-1][b] + dp[h-1][r]) << 1\\ 
    dp[h][r] &= dp[h][b] * dp[h][b] << 1,
\end{align*}$$

where $vec << 1$ denotes shifting all elements 1 index higher and setting $vec[0] = 0$. We precompute this dp for $n \leq 131072$ and $h \leq 16$ using an FFT template supporting modular arithmetic. This runs in $O(kh \log k)$. 

## F: Figure Skating

- Given some rules defining good/romantic/energetic/tragic sequences of figure skating jumps, count the number of good sequences of length $n \leq 10^9$. 

### Solution

Let our state be defined by whether we are currently in a good/romantic/energetic/tragic sequence. The sequence rules then define a transition function that inputs the current sequence type and a jump type, and outputs a set of states that we could now be in. This defines a transition matrix.

Note that the only sequence that can end is a good sequence, and good sequences can end at any time. Use matrix exponentiation to compute transitions up to $n$, and output how many length-$n$ good-to-good sequences there are.

