# ICPC North American Championship 2026

[Link to problems (QOJ)](https://qoj.ac/contest/3518)

(*) Problems with stars were more difficult.

## A: Acorn Quarrels


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



## I: I Don't Miss Pennies

## J: Jelly Fusion

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


