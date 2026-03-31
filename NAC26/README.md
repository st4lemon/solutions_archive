# ICPC North American Championship 2026

[Link to problems (QOJ)](https://qoj.ac/contest/3518)

(*) Problems with stars were more difficult.

## A: Acorn Quarrels

- There are $N \leq 10^5$ squirrels on a tree. The tree can be modeled as a graph-theoretic tree, where each squirrel is a node and each edge is a branch connecting two squirrels. Each squirrel has some unique index from 1 to $n$, and some number of acorns. 
- In ascending order of index, each squirrel steals one acorn from the neighboring squirrel with the most acorns. If there is a tie, the squirrel steals one acorn from all such maximal squirrels. 
- You want to distribute acorns such that each squirrel begins with at least $N$ acorns but no more than $2N-1$ acorns, and after this process occurs each squirrel has the same amount of acorns as it did originally. 

### Solution

- TBD

## B: Boss Rush

- There are $N \leq 3\cdot 10^5$ monsters. Each monster $i$ attacks every $D \leq 10^9$ seconds, and performs it's first attack at time $0 \leq f_i < D$. 
- To defeat a monster, you must parry it's attack by blocking at the same time as it's attack. After blocking, you must recover for $w \leq 10^9$ seconds before you can block again. Each parry only defeats one monster, and you do not care about how many unblocked attacks there are. 
- Determine the minimum amount of time it takes to defeat all bosses. 

### Solution

Consider a successful sequence of moves ending at time $T$. Note that all bosses share the same attack delay, so we can model this problem as $D$ nodes each representing a residue $\mod D$. Then for each boss, draw a directed edge from $f_i$ to $(f_i + W)\% D$. Then, for each second $t$ that we are able to block but choose not to, draw an edge from $t \% D$ to $(t+1) \% D$. Then, this graph forms a Eulerian trail starting at $0$ and ending at $T \% D$. We can identify if such a path exists if only 0 has an extra out-edge and exactly one other node has an extra in-edge, or if every node has equal amounts of edges going in and out, also while ensuring that the graph is fully connected. 

Then, we can binary search on the time it takes to defeat all monsters and construct this graph. Each pair of consecutive nodes $i-1, i$ has $\lfloor T/D \rfloor + [i \geq T \% D] - (\text{\# overlapping boss edges})$ directed edges between them. Then, we add the boss edges, and compute the in-degree and out-degree of each node. 

This is too slow for $D \leq 10^9$, but we can also coordinate compress the coordinates with the endpoints of the boss edges, since those are the only places where the in-degrees and out-degrees change. This brings graph construction down to $O(N)$ per case, so the total runtime is $O(N \log N)$. 


## C: Cable Pruning

- You have a connected graph with $N$ vertices and $N$ weighted edges. There are also $K$ coupled pairs of servers (one server can be part of multiple couplings). Determine the minimum cost of edges to keep each coupled pair connected. 

### Solution

Observe that the graph has exactly one cycle (a tree plus an edge). A coupled pair can either be connected solely through one of the trees that come off of the cycle, or through the cycle if they are in different trees. 

Observe also that the edges in the trees are fixed; for each edge we only keep it if we keep it in every configuration. We will add values to nodes so that we can use DFS to determine if an edge is needed. Root all trees at the cycle. Then:

- If both nodes are in the same tree, add 1 to each node and -2 to their LCA. 
- Otherwise, just add 1 to each node. This forms an interval on the cycle. 

Then, for each node we take the sum of it's subtree, including itself. If this sum is $> 0$, we must use the edge going to it's parent. If there now exist intervals on the cycle formed by this process, we must choose how to assign them as well. Each interval has two placements in which it can be in, which are opposites of each other. 

Observe that removing any edge determines the placement of each interval, because every edge is contained in exactly one of the two placements. So, we can try removing each edge and calculating the cost of the cycle edges with at least one interval passing through it. This value can be computed with a segtree counting the sum of the elements with no intervals passing through it, and a sweepline over the intervals. 

## D: Draw Your Deck

- You have a deck of $N \leq 1500$ cards, each with an integer value between $0$ and $K \leq 3$. The game is played by first drawing the top card. Then, in each subsequent turn, you can play one card of your choice from your hand, and draw cards from the top of the deck equal to the value of the card you just played. 
- Across all possible orderings of the deck, what is the probability that you can draw the entire deck?

### Solution

A deck cannot be drawn to the end if and only if for some value $i < N$, the sum of the first $i$ cards is less than $i$. This implies that if the sum of the first $i$ cards is at least $i$ for all $i < N$, then we can draw the entire deck. 

We can reframe this question by subtracting 1 from all card values. Then, the above condition is equivalent to having a prefix sum of $0$ for all $i < N$. Note that the $1$ (now $0$) cards do not affect this prefix sum, so we can just consider the $-1, 1,$ and $2$ cards for now. We can write a 3-dimensional dp that represents each state by the number of $-1, 1,$ and $2$ cards outside of the current prefix, where $dp[x][y][z] = $ probability that you reach this state following the rules. The transition is just subtracting 1 from $x, y,$ or $z$ and computing the respective probability that this transition occurs, as well as checking that the prefix sum still holds. The answer is then $dp[1][0][0] + dp[0][1][0] + dp[0][0][1]$, since if the first $N-1$ cards sum to $\geq N-1$, we will have drawn all $N$ cards. 

There is one special case when the cards `sum to $N-1$ (or to $-1$ after subtracting 1). We must enforce that the deck ends with a $0$, but earlier we ignored the $1$ cards. Helpfully, any sequence of $0, 2, 3$ satisfying the properties of the game will end with a 0, so it suffices to compute the number of ways to place the 1s such that none of them come at the end of this sequence. With stars and bars, this is ${n-1 \choose k} / {n \choose k} = \frac{n-k}{n}$. In this case, we multiply our answer by this value and we are done. 




## G: Gemstone Dowsing

- There are $N \leq 10^5$ gemstones buried underground. You have taken $N$ surface readings at location $x_i$ for $i \leq N$, which tell you which gemstone is the closest to that point by Euclidean distance. 
- You additionally already know the locations of $K \leq N-1$ gemstones underground. 
- Across all plausible configurations of gemstones satisfying the given constraints, for each unknown gemstone compute the lowest possible y-value it could achieve. 

### Solution

The condition that each gemstone is closest to its reading is equivalent to: Consider the semicircle centered at the reading point and passing through the gemstone; no other gemstone lies in the interior of this semicircle. We make two observations:
- The x-position of the gems must be in the same order as the readings. 
  - If they are not, then one gem must lie within the other's semicircle. 
- For an unknown gemstone, only the two known gemstones on its left and right matter. 
  - Consider an unknown gemstone $x$ and let $l$ and $r$ be the closest known gemstones on its left and right. WLOG let the reading of gemstone $y$ lie between $l$ and $x$, and consider all valid positions to place $x$. Then, place gemstone $y$ at the intersection of the semicircles of $l$ and $x$. This point is at least as close to the reading of $y$ as gemstones $x$ and $l$ are, and is at least as far as $x$ and $l$ are from their respective readings. 
  - If an intersection does not exist, then either neither semicircle covers the reading of $y$ and we can just put gemstone y at the location of the reading, or one semicircle covers $y$ and we can place it at $y = 0$ where that semicircle intersects the $x$-axis. 

The algorithm is then as follows. For each unknown gemstone $x$:
- Find the closest known gemstones on the left and the right. Take the minimum distance from the reading to the gemstones as the radius of the semicircle of $x$.
- If the lowest point of this semicircle lies outside of the left and right semicircles, place gemstone $x$ at that location. 
- Otherwise, exactly one semicrcle covers the top point of $x$, and the two semicircles both do not intersect some interval on the left or right half of the semicircle of $x$. Take the intersections of semicircles $l$ and $r$ with the semicircle of $x$, and choose the lowest point as the gemstone's best location. Save this as the answer, but do not place this gemstone so as to not affect other unknown gemstones. 



## H: Heist of the Century

- There is a safe with $N \leq 500$ dials on it, each of which can be set to any integer from $1$ to $2N$. You can submit queries where you submit a dial combination to the judge. Suppose your query is $[x_1, x_2, ..., x_n]$ and the actual combination is $[d_1, d_2, ..., d_n]$. Then, the judge will return $\max_{1 \leq i \leq n} |x_i-d_i|$. 
- Within $4N$ queries, submit the correct combination to the safe. 

### Solution

If the dial values range from $0$ to $2N$, then each dial would be symmetric around $N$. We can determine any $d_i$ in 2 queries: set all $x_j = N$, then make a query with $x_i = 0$ and one with $x_i = 2N$. If $d_i \neq N$, then exactly one of the queries returns a value $> N$. Otherwise, if both queries return $N$, then $d_i = N$. This requires $2N$ queries. 

For dial values ranging from $1$ to $2N$ instead, we can first identify all $d_i = 2N$ by querying $x_i = 1$ and $x_j = N$ for all $j \neq i$. If the query returns $2N - 1$, then $d_i = 2N$ and we set $x_i = 2N$ for all subsequent queries. Then, the range for each remaining dial is $1$ to $2N-1$, which is symmetric around $N$ and can be queried for as before. This takes $3N$ queries, plus 1 more to report the answer if not done already. 

## I: I Don't Miss Pennies

 - You have $N \leq 300\ 000$ items to purchase, and their costs are given in cents. However, transactions are rounded to the nearest nickel (5 cents). You can choose how to group items into transactions. Determine the optimal amount of cents you can save by grouping your purchases optimally. 

### Solution:

Organize all transactions into equivalence classes mod 5. Then, we can process transactions that are $0, 1, 2 \mod 5$ as-is, since we cannot gain money on these. Then, notice that combining two 3s or a 3 and a 4 decreases our cost by 5. Combining two 4s produces one 3, and does not save us any money. 

Greedily combine 4s until there are at least as many 3s as 4s. Then, combine 3s and 4s until no more 3s are left, then combine all 4s with each other. 

## J: Jelly Fusion

- There are $N \leq 300\ 000$ rectangles on a circular array. You may combine two adjacent jellies into one jelly that takes the maximum height and maximum width between the two jellies. This jelly replaces the two jellies in the array and can then be combined again with adjacent jellies. 
- Determine the largest sum of areas of the remaining jellies after performing zero or more combine operations. 

### Solution

For now, suppose that we are working with an array that is not circular. We discuss how to deal with the circular case later. 

Observe that we can combine any contiguous interval of jellies into one jelly that has height and width equal to the maximum height and maximum width of the jellies in the range. Then, any optimal interval we choose must either be a single jelly, or one endpoint has maximum height and the other endpoint has maximum width. 
- Suppose an endpoint has neither maximum height nor width. Then, we can remove this jelly from the interval and it does not change the size of the combined jelly, but now there is an extra jelly that can contribute to the final answer. 

Let $(h_i, w_i)$ be the height and width of the $i$-th jelly. Let $dp[i] =$ max sum of areas using jellies $[1, i]$. Then, this value is the largest of three possible values:
- $dp[i-1] + h_i \cdot w_i$
- $\max_{j < i} dp[j] + h_i \cdot w_{j+1}$
- $\max_{j < i} dp[j] + w_i \cdot h_{j+1}$

The lower two values can be expressed as the maximum of linear functions where the independent variables are $h_i$ and $w_i$ respectively. We can obtain these values in $O(\log N)$ with a Li-Chao tree or convex hull trick. Overall, this takes $O(N \log N)$ time. 

To perform this on a circular array, note that the jelly with maximum width (or height, does not matter) must be the endpoint of some interval. We can try putting this jelly at the start of the array then at the end of the array, and the maximum of these two answers is the answer for the full problem.


## K: Kindergarten Revisited

- You have $N \leq 100$ axis-aligned rectangles on an infinite sheet of paper that do not touch or intersect. Given a piece of paper, you can draw a line that does not go through any rectangle (but it can touch sides/corners) to cut the piece into two pieces of paper. Further cuts on each piece of paper do not affect the other piece. 
- Determine the minimum number of cuts needed to put each rectangle on its own sheet of paper, or decide that it is impossible. 

### Solution

Observations:
- Any cut increases the number of pieces by 1. Therefore, if the task is possible, we will make exactly $N-1$ cuts. 
- There are $\approx {4N \choose 2} \leq 8N^2$ possible cuts (choose 2 rectangular vertices). For a given piece of paper, we can apply the cut if it does not intersect any of the rectangles on that piece of paper. 
- A piece of paper can be represented by the set of rectangles on it.

When we make a cut, the set of rectangles on the resulting pieces is smaller than the original piece. Making any cut only increases the the number of possible cuts, therefore it is okay to greedily make any cut that splits the set of rectangles into two nonempty subsets. For each piece, we can check all $8N^2$ cuts, and for each cut it takes $O(N)$ time to check if the current set of rectangles intersects it. 

Overall, this is $O(N^4)$ but with a high constant. We can speed this up by representing the current piece with a bitset, and precomputing a bitset for each cut representing the rectangles it intersects. Then, determining if any rectangle intersects a cut is just a bitset AND operation. We then spend $O(N)$ per actual cut we make to divide the rectangles into two subsets, and verify that both pieces are nonempty. Note that there exists only $O(N)$ lines that split off one empty piece; these are the edges of the convex hull of the rectangles. Therefore, for each piece we spend $O(N^3/w + N^2)$ time splitting it. We make $N-1$ splits, so total runtime is $O(N^4/w)$. 

There exists an $O(N^2 \log N)$ solution, by maintaining a segment tree at each point maintaining intervals representing rectangles from the perspective of the point. When splitting rectangles, we remove each rectangle from all points in the opposite partition. We search for a valid cut by querying for an empty region in all of the segment trees in a single partition. Total runtime is $O(N \log N)$ per split (query $N$ times $O(\log N)$) and $O(N^2 \log N)$ amortized overall for the segment tree updates. 

## M: Maki Conveyor Belt

- There is a circular conveyor belt of length $N \leq 10^9$, $M \leq 10^5$ types of makis, and $K \leq \min(2 \cdot 10^5, N)$ plates on the conveyor belt. Alice and Bob are sitting at positions $p_A$ and $p_B$ along the conveyor belt. 
- Every second, the conveyor belt moves forward, moving plates at position $i$ to position $i+1$ (if $i=N$, the plate moves to $1$). At any time (including time 0), Alice and Bob can both choose to purchase makis off of the plate currently in front of them. Each plate carries some amount of one type of maki, and costs a certain amount per piece. 
- Alice and Bob both want to eat a certain amount of each kind of maki in the shortest amount of time possible. Compute how quickly Alice and Bob can eat all of the makis they want, as well as the minimum cost to achieve this minimum time. 

### Solution

We can binary search on the time that it takes to complete this task, because the amount of makis of each type available to Alice and Bob is a monotonically nondecreasing quantity. 

Then, suppose we fix the time $T$. Sort the plates by cost lowest to highest, because we will always prefer taking cheaper plates over more expensive ones. For each plate, decide if it is within Alice's range, Bob's range, or both. We greedily take plates under two conditions. Suppose Alice needs $A$ and Bob needs $B$ of some type of maki: 
- Take at most $A+B$ makis of that type in total.
- Take at most $A$ makis that Alice can reach but Bob cannot. Take at most $B$ makis that Bob can reach but Alice cannot.

After going through all plates, we succeed if for each maki type we have taken $A+B$ makis in total and the conditions above are satisfied.

