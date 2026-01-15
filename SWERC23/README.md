# 2023-2024 Southwestern Europe Regional Contest

[Link to contest (Codeforces)](https://codeforces.com/gym/104030)

(*) Problems with stars were more difficult.

## C: Metro Quiz*

- There are $M \leq 50$ metro lines, each which pass through some subset of $N \leq 18$ stations. There exists some optimal strategy for guessing metro lines by asking questions of the form "Does the line pass through station $n$?" which is replied to with yes or no. 
- Compute the expected number of guesses in an optimal strategy across all possible stations as answer, or output "not possible" if no strategy can guess every station. 

### Solution 

For now, let every state be represented by a length-50 bitstring, representing which lines are still possible solutions. Each station can also be a length-50 bitstring representing the lines that pass through it. 

From a single state $s$, we can compute it's expected value by trying every possible station. Let $K$ be the set of station bitstrings, and let $S$ be the solution. Then,  $$E[s] =1 + \min_{m \in K}\left(P(S \in s\land m) \cdot E[s \land m] + P(S \in (s - s\land m)) \cdot E[s - s\land m)\right) \\ = 1 + \min_{m \in K} \left( \frac{E[s \land m] \cdot popcount(s \land m) + E[s - s\land m] \cdot popcount(s - s\land m)}{popcount(s)}\right).$$

For ease of computation, let $dp[s] = E[s] \cdot popcount(s)$. Then, $$dp[s] = popcount(s) + \min_{m \in K}(dp[s \land m] + dp[s - s\land m])$$

However, a state space of $2^{50}$ is too large, so we must analyze the algorithm further. Note that for any possible solution, any subset of stations we guess corresponds to some subset of lines available, therefore there exists a many-to-one mapping $(\text{solution, stations}) \mapsto \text{reachable states}$ by the rules of this problem. Therefore, the upper bound on number of reachable states is $\leq M \cdot 2^N = 50 \cdot 2^{18} \approx 10^7$. Our DP can just be represented by a map, and with 5 seconds we can pass with an $O(MN 2^N)$ DP solution. 

## G: Favorite Dish*

- There are $N \leq 500\ 000$ dishes, each with a score for taste $t_i$ and plating $p_i$. There are also $M \leq 500\ 000$ diners, each with some preference for taste $T_i$ and plating $P_i$. 
- The score that a dish $i$ receives from diner $j$ is $(t_i T_j + p_iP_j)/(T_j + P_j)$. For each diner, determine their favorite dish. 

### Solution

For every dish, plot point $(t_i, p_i)$ on the plane. Then, for any given diner $j$, the favorite dish is the dish such that $(t_i, p_i) \cdot (T_j, P_j)$ is maximized; in other words, furthest in the direction of $T_j, P_j$. We can visualize a line passing through every point with slope $-P_j/T_j$&mdash;the furthest such line corresponds to the diner's favorite dish. 

This means that any possible favorite dish must have some line with negative slope passing through it where all other dishes lie below the line, which is equivalent to saying that all possible favorite dishes must lie on the upper-right quadrant of the convex hull.

We can do a two pointers-like solution:
- Compute the upper-right quadrant of the convex hull (these are the hull points between the highest and rightmost points). Sort the diners by $P_j/T_j$. 
- Start one pointer at the leftmost remaining hull point, and start the other pointer at the first diner.
- For each diner, while the current dish is less preferable than the next dish, move the dish pointer forwards. 

After handling collinear points (break ties by input order), the full solution runs in $O(N \log N)$ time.

## H: Break a leg!*

- You are given a simple polygon with $N \leq 100\ 000$ non-collinear vertices representing the top surface of a table. It is even thickness and density throughout. You must choose three of the vertices to place table legs of equal length, such that the center of gravity of the table lies in the triangle created by these three vertices. 
- Count the number of ways to select three legs such that this property holds.

### Solution 

There exist a variety of ways to find the center of mass. I chose to use a signed triangulation to compute $\int x\ dm$ and $\int y\ dm$ in a piecewise manner using integers where possible; you can also modify the shoelace formula to compute these quantities. 

Instead of counting triangles that contain the center of mass, we count triangles that do not have the center of mass in its interior. For each triangle, in order to prevent overcounting, we select the point that contains the ohter two points within a 180-degree CCW sector starting from that point. 

We then iterate over all $N$ points, maintaining a 180-degree sliding window that tracks how many points are in the window. From those points in the window, we can choose any two of them to make a triangle; they will form a positive-area triangle because no three points are collinear, and the primary point of the resulting triangle will be the current point. 

To obtain the answer, subtract the number of triangles found by this method from $N \choose 3$. A couple edge cases that may come up:

- A point lying exactly 180-degrees away from the current point should still be included in the window. 
- Since no three points are collinear, we can pick points with the same angle to be part of one triangle. 
- If the center of mass lies on a vertex, then this vertex can never appear in a triangle that contains the center of mass. Remove this point from the point set after computing the center of mass but before counting bad triangles. 
- Since $|x|, |y| \leq 10^6$, integer cross products are well-defined within 64-bit arithmetic. In a Python implementation, this is not a problem. 

