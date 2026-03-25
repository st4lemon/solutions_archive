# Makoto rng_58 Soejima Contest 4

[Link to problems (Codeforces)](https://codeforces.com/gym/100959)

(*) Problems with stars were more difficult.

## B: Airports*

- There are $N < 10^5$ airports on a coordinate plane. For some constant $D$, connect any pair of airports where the Manhattan distance between them is at least $D$. 
- Compute the maximum $D$ where the airports are connected. 

### Solution

Consider an airport at $(x_i, y_i)$. Then, the airports that are at least distance $D$ away lie in the region: 
$$\{y-y_i \leq x - x_i - D\} \cup \{y-y_i \geq x - x_i + D\} \\ \cup\ \{y - y_i \leq x_i - D - x \} \cup \{y - y_i \geq x_i + D - x \}.$$
These make up two sets of parallel lines. Consider the set $\{y-y_i \leq x - x_i - D\} \cup \{y-y_i \geq x - x_i + D\}$. If we sort all airports by $(y_i - x_i)$, the set excludes a contiguous interval of these airports (sorting by $(y_i + x_i)$ produces the same result with the other set of parallel lines). As we visit more airports, the interval of unreachable airports is the intersection of these intervals for each airport. Thus, the set of unreachable airports is always a contiguous interval, which shrinks as we visit more airports. 

For a fixed $D$, we can perform BFS and maintain two intervals of unvisited airports, one for each pair of parallel lines. When we visit an airport, construct the intervals for the current airport and $D$. For any airports in the current unvisited set that can now be visited, add them to the queue to visit them, and shrink the interval. We use a pair of left/right pointers to represent the intervals, and increment/decrement the respective pointers to shrink them. This routine runs in $O(N)$ time, assuming the two lists of sorted airports are provided. 

Binary search on $D$, using the above routine to check if the airports are fully connected. 

## I: Robots

- There are $N \leq 10^5$ robots on a grid, each facing in one of four cardinal directions. They remain stationary until they are touched by another robot, except for robot 1 which starts moving at time = 0. A moving robot moves 1 unit per second in the direction that it is facing. If a robot lands on the same grid space as a stationary robot, the stationary robot starts moving. Robots do not interact otherwise, and can occupy the same space. 
- Compute the positions of all robots after $T \leq 1e18$ seconds. 

### Solution

We can do a coordinate-compressed BFS to naively solve this problem in $O(n^3 \log n)$ time by keeping a visited grid for each robot. However, this is inefficient because robots will frequently retrace each other's paths. Also, moving robots do not interact with each other, so we only care if a robot is heading towards another stationary robot. 

Instead, construct a graph connecting each robot's starting space with the robots above, below, to the left, and to the right of it. Mark each edge with the direction that it approaches the space. At most $$4N$$ edges exist. Then, we can BFS by adding events of the form `(time, square, direction, robot)` to a priority_queue. When a robot visits a square, we find the next square along it's trajectory and add that event to the priority queue. This can be done in $O(n^2 \log n)$, with the worst case being robots on a horizontal line all facing left and right. 

Then, speed this up to $O(n \log n)$ by enforcing that each starting square is only visited once per direction. If a robot moves into a square that has already been visited while moving in the same direction, then it is simply retracing another robot's path and therefore no longer can start any robots. The `robot` field can also be dropped since we only need `(time, square, direction)` to compute the next square and time of arrival at that. square. We add one event per `(square, direction)` pair, so there are $O(N)$ events inserted into the priority_queue. 

Record the start time $s_i$ of each robot when it is first visited; then we can compute its final location in constant time by moving it $T-s_i$ spaces in the direction that it is facing. 

## L: String Modification

- You are given strings $s$ and $t$, where $1 \leq |s| \leq |t| \leq 5000$. In one operation, choose a character from $s$ and insert another character directly after the chosen character. The inserted character must be different from the chosen character. 
- Determine if he can convert $s$ to $t$ by repeating the operation zero or more times. 

### Solution

Let `dp1[i][j]` = we can convert `s[i:]` to `t[j:]` using the given operation, and `s[i] = t[j]`. Let `dp2[i][j]` = we can convert `s[i:]` to `t[k:]` for some $k \geq j$, where $s[i] = t[k]$. 
- `dp1[i][j] = true` if `s[i] == t[j]` and: 
  - `dp1[i+1][j+1]` if `s[i] == t[j+1]`, because `s[i+1]` must match `t[j+1]` since we cannot insert `t[j+1]` after `s[i]`. 
  - `dp2[i+1][j+1]` otherwise, since we can insert `t[j+1]` after `s[i]`. It does not matter what the characters after `t[j+1]` are: if they are equal to `t[j+1]`, we can append more copies of it after `s[i]`, and if they are not then we can apply our operation to copies of `t[j+1]`. 

Then, output YES if `dp1[0][0]` is true, since the first characters of $s$ and $t$ must match. 

