# ICPC North American Championship 2026

[Link to problems (QOJ)](https://qoj.ac/contest/3518)

(*) Problems with stars were more difficult.

## A: Acorn Quarrels

## B: Boss Rush

## C: Cable Pruning

## D: Draw Your Deck

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


