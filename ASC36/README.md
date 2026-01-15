# Andrew Stankevich Contest 36 (ASC 36) 

[Link to problems (Codeforces)](https://codeforces.com/gym/100430)

(*) Problems with stars were more difficult.

## A: Chip Installation

- There are $N \leq 50\ 000$ wires. You are given the description of $2N$ sockets arranged in a ring, and each wire uniquely has two sockets that it can be connected to. Each wire also has a color, and two wires of the same color cannot be connected next to each other. 
- Determine a way to connect every wire into one of its sockets, so that no two wires in adjacent sockets have the same color. 

### Solution

Suppose two sockets $a$ and $b$ are adjacent to each other have the same color. If I plug a wire into socket $a$, then socket $b$ cannot have a wire, therefore the wire associated with socket $b$ must be plugged into its other socket. 

We can then reframe the entire problem as 2SAT. Formally, let there be a variable $x_i$ for every wire $i$. Assign one of the sockets $x_i$ and one of the sockets $\overline{x_i}$. 
 - For any two adjacent sockets $a$ and $b$ with the same color, add the constraints $a \to \bar{b}$ and $b \to \bar{a}$. 

Then, any satisfying assignment to the 2SAT expression corresponds with some assignment of wires to sockets, such that every wire is connected to at least one of its sockets.

## D: GridBagLayout

- Statement omitted for brevity. 

### Solution 

Although the sample input can look intimidating to properly parse, note that there are only 2 real types of expressions: "add component" (which is always the same string) and "set parameter" (which is 3 tokens, beginning with gbc.(parameter name)). Some basic string processing is enough for this. 

Aside from that, we can mostly just implement the statement. Maintain the previously-placed object, as well as a large-enough boolean grid to specify if a component occupies that location (since we have $\leq 50$ components and each has $\leq 50$ width/height, a $3000 \times 3000$ grid works). For each box, find it's upper-left corner, then use width/height to determine the bottom left corner. For width/height = REMAINDER, just fill up the row/column to the end of the grid.

Additionally, in order to determine when a row/column has no free spaces (for relative gridx/gridy), maintain the count of unoccupied cells in each row and column as we update the grid. Then, a row (or column) has no free spaces if this count is $0$. We can naively loop over each box to perform this update because there are only $50$ components. 

## E: Hot Potato Routing*

- There are $N \leq 100$ network nodes, each with a list of $l_i \leq 8$ destination nodes $a_{i, 0}, a_{i, 1}, ..., a_{i, l_i-1}$. There are also $P \leq 100$ packets to be delivered, each with an appearance time, a starting node, and a target node. Packets move as follows:
    - At the appearance time, the packet enters the network and arrives at the starting node $i$. 
    - At time $t$, a packet at node $i$ to node $a_{i, t \% l_i}$, arriving at time $t+1$. 
    - If two packets would arrive at the same node at the same time, they are both discarded.
    - If a packet successfully arrives at it's target node at any time, it is successfully delivered and is then removed from the network.
- Determine the largest subset of packets that can be sent and successfully delivered. 

### Solution

Observe that the network graph is periodic mod $\text{lcm}(8, 7, ..., 2, 1) = 840$. For any single packet, there are $840N$ states that it could be in, of which $840(N-1)$ of them are not at it's target node. Therefore, if the packet travels for more than $840N$ time steps it must be in a cycle that does not contain it's target node. 

We first use this observation to identify all packets that can reach their target node, as well as the ending time when they reach their target. Since all of the packets arrive at $t \leq 1000$, we have enough time to simulate $N$ moves for $840N + 1000$ time steps. We can choose the subset of packets while performing this simulation.
 - If two packets reach the same node at the same time, we can retroactively choose one of them to be removed from the subset (as if it never existed). At the collision point, all future moves both packets make (up until they reach their targets) will be exactly the same, so we can greedily choose the one with an earlier ending time because it will cause less collisions with other packets. 
 - Furthermore, if the packet we chose to continue eventually is also removed due to another collision, we can be sure that the removed packet would also reach the same collision and would also be removed. 

The algorithm is simply to simulate the network for $840N + 1000$ steps and handle collisions as described above. If a packet reaches its target without being removed, we add it to the answer set. 


## G: Magic Potions
 
- You have $N \leq 100\ 000$ types of substances, numbered $1...N$, and $1 \leq a_i \leq 10^9$ bottles of substance $i$. A potion is made by combining two different substances, and is described by the substances that compose it. 
- You want to make the maximum number of potions possible, but among the ways to maximize potion count you also want to maximize the number of $1+2$ potions, then maximize the number of $1+3$ potions, up to $1+N$ potions, then the $2+3$ potions, etc (lexicographical order). 
- Determine the lexicographically minimal set of potions that maximizes the number of potions made. 

### Solution

Suppose we are making the potions one by one, and for now assume we have an even quantity of substances in total. Let $t$ be the remaining number of unused substances. 

Since we seek to minimize lexicographical ordering of our chosen set, it is always best to combine the two lowest-numbered potions at any time. We can keep doing this until there exists some potion type such that $a_i = t/2$(*), at which point we must use all other potions to match with this one. 

To speed this up, we can make this into a two-pointers solution that makes as many potions of one type as possible before moving on. If we are making a potion with substances $x$ and $y$, we either use up all of substance $x$ or $y$, or we use up enough so that $t/2 = a_z$ for some $z \neq x, y$ and then move on to matching bottles of type $z$ with everything else. This is guaranteed to be the correct solution for even $t$; match any more bottles that are not type $z$ and we would be leftover with too many type $z$ bottles to match together. 

For the case of odd $t$, we can leave one bottle unmatched so we amend the condition (*) to $a_z = \lceil t/2 \rceil$. If we were to use $\lfloor t/2 \rfloor$ instead, all bottles of type $z$ would be matched, but this diverges from the lexicographically-minimal bottle sequence one potion earlier than if we used $\lceil t/2 \rceil$, so this strategy of leaving one bottle of type $z$ unmatched is optimal. 

## H: Restoring Permutations

- A permutation has a *descent* at position $i$ if $a_i > a_{i+1}$. A permutation has a *fixed point* at position $i$ if $a_i = i$. 
- Consider the following process:
  - Create a permutation with $2n$ elements such that there are exactly $n$ descents, all at odd positions (1-indexed), and that there are exactly $n$ fixed points
  - Delete all fixed points in the permutation
  - Re-index the remaining numbers by their relative order to create a new permutation of length $n$
- Given this resulting permutation, reconstruct the original permutation. 

### Solution

The two conditions given imply that in the original permutation, exactly one of $2i$ and $2i-1$ are a fixed point for $i \in [1, n]$. They cannot both be fixed points because then we would not have a descent, and at least one must be a fixed point or else we will not have $n$ fixed points overall. A consequence of this is that exactly one of $2i$ and $2i-1$ will be left over after deleting all fixed points. Since we don't know yet which of the two is the fixed point, let $f_i$ denote the fixed point and $l_i$ denote the leftover value out of $2i$ and $2i-1$. 

Let $p = p_1p_2...p_n$ be the given permutation. Then, note that $i<j \implies l_i < l_j$. This means we can arrange these $l_i$ in their correct order based on $p$. So then, in positions $2i$ and $2i-1$ we have the elements $l_{p_i}, f_i$ in some order. But also, $i<j \implies f_i < l_j, l_i < f_j$ as well, so the values of $l_{p_i}$ and $f_i$ are related by $p_i$ and $i$, irrespective of which elements were chosen as fixed points. We then put the greater of $l_{p_i}$ and $f_i$ in position $2i-1$, and the lesser in position $2i$.

After performing this last operation, we now know the locations of all the fixed points, which is equal to their value. This then determines which values are leftover, which we can now assign to all $l_i$. The only case where a permutation is impossible to construct is if $p_i = i$ at any point, because either choice of fixed point does not make a descent.



## I: Roads*

- Given $N$ points on the plane and the degree of each node, connect the points with segments such that no two segments cross, each node has a number of segments incident to it equal to it's degree, and the graph forms a tree.

### Solution

We use divide and conquer, using halfplane partitions passing through points to split the plane into several convex regions. The algorithm is as follows:

 - Identify the highest degree point $p$ in the current set; let the degree of $p$ be $k$. Sort all other points by angle around this point. Use angular sweepline to maintain a 180-degree sliding window of points around $p$. There are $N$ such windows that matter (one for each line passing through any point and $p$). 
 - Let $S$ be the set of points in the window and $k = |S|$. Then, if $\sum_{s \in S} deg[s] < 2k < \sum_{s \in S} deg[s] + deg[p]$, we can partition the problem along a line passing through $p$. For now, I claim that a partition satisfying this inequality always exists (*).
     - Subproblem 1: $S$ plus point $p$, but in this subproblem assign $deg[p] = 2k - \sum_{s \in S} deg[s]$
     - Subproblem 2: All remaining points plus point $p$, but in this subproblem assign $deg[p]=\sum_{s\in S}deg[s]+deg[p]-2k$.
     - In the sample input, an example of this partition is as follows (given as a list of {node, degree} pairs):
         - $(1, 1), (2, 1), (5, 2)$
         - $(2, 1), (4, 3), (6, 1), (7, 1), (5, 2)$. 
     - The partition is through node $5$ which originally has degree 4, and we assign 2 "degrees" to each partition $P$ so that $\sum_{s \in P} deg[s] = 2|P| - 2$, and it is possible to make a tree.
 - Base case: 2 nodes of degree 1, which we connect with an edge.

This subdivision divides the point set through $p$ and decides the number of edges connected to $p$ from either side so that both subdivisions can make a tree. Furthermore, edges from one partition cannot intersect the other because the partitioned regions are convex and disjoint, so the subproblems are independent. 

The divide-and-conquer tree is a binary tree with $n-1$ leaves, so we perform $n-1$ partition operations. Each partition takes $O(n \log n)$ time for sorting and $O(n)$ for sweepline, so overall this algorithm runs in $O(n^2 \log n)$. time. 

### Proof of claim (*):

The inequality can be simplified to $0 < 2k - \sum_{s \in S} deg[s] < deg[p]$. We can treat $2k - \sum_{s \in S} deg[s]$ as a periodic function $f(\theta)$ with respect to the angle of the partition line. 

Consider an arbitrary partition line at angle $\theta$. If $0 <f(\theta) < deg[p]$ then we are done, otherwise WLOG suppose that $f(\theta) \leq 0$. Then, the other partition has $N - k - 1$ points, and has degree sum $2(N - 1) - \sum_{s \in S} deg[s] - deg[p]$. Then, 
$$2(N-k-1) - (2(N-1) - \sum_{s \in S} deg[s] - deg[p])$$
$$= -2k + \sum_{s \in S} deg[s] + deg[p]$$
$$= -f(\theta) + deg[p] \geq deg[p]$$

Thus, $f(\theta + \pi) \geq deg[p]$, so at some point $f$ crosses over from $\leq 0$ to $\geq deg[p]$. Additionally, since $deg[p] \geq max_{s \in S} deg[s]$, the quantity $2k - \sum_{s \in S} deg[s]$ can only change by $\pm (deg[p] - 2)$ between consecutive partitions. The interval $0 < x < deg[p]$ has size $deg[p]-1$, therefore if $f$ crosses over the interval at some point in $(\theta, \theta+\pi)$, then some partition must fall within the interval. 