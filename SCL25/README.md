# 2025 Southern California Regional Contest

[Link to problems (ICPC)](http://socalcontest.org/history/2025/SCICPC-ProblemSet-2025-2026.pdf)

**Problems in bold were more difficult**

## B: Rubik's Cube

## F: Fractal Painting

- You are given 3 points $(x_0, y_0), (x_1, y_1), (x_2, y_2)$ with each x- and y- coordinate being an integer between $-10^4$ and $10^4$. All points are distinct and neither of them are $(0, 0)$. We define a fractal painting recursively based upon these points: 
  - The first segment is from $(0, 0)$ to $(x_0, y_0)$ (call this segment $A$), and the next two branch off from $A$: $(x_0, y_0)$ to $(x_1, y_1)$ and $(x_0, y_0)$ to $(x_2, y_2)$ (called $B$ and $C$ respectively). 
  - Then, $B$ and $C$ branch off as well. For segment $B$, we attach segment $D$ and $E$ to $x_1$ such that $BDE$ is congruent to $ABC$.
- The fractal goes on infinitely; determine if there exists a bounding box that encloses the entire fractal. 

### Solution 

The fractal is essentially an infinite binary tree rooted at $(0, 0)$, and obviously it is impossible to traverse it. We instead must determine analytically if it is bounded or not. For each segment of the fractal, we can define its left and right child as the two segments that branch off from it ($B$'s left and right children are $D$ and $E$ respectively). Since each subfractal is congruent to the original fractal, if we were to traverse the tree then taking the left child always multiplies our segment length by a fixed ratio, and also turns us by a fixed angle. 

From this we can decide a couple simple cases. If we always take the left child, then the segment lengths form an infinite geometric series. This is the same if we always take the right child. 
- If either child is longer than the parent segment, the fractal is unbounded. 
  - We can keep taking this longer child, and the segment lengths can grow infinitely. 
- If both children are shorter than the parent segment, the fractal is bounded. 
  - Suppose the parent is $l$ times the length of the left child, and $r$ times the length of the right child. Then, for some sequence of moves $\{a_n\}_{n \in \N}$ where $a_k = $ either $l$ or $r$, $$\sum_{n=1}^\infty \prod_{i=1}^n \frac{1}{a_i} \leq \sum_{n=1}^\infty \frac{1}{(\min \{l, r\})^n}$$
  and since $l, r > 1$, then $\frac{1}{(\min \{l, r\})} < 1$, and the geometric series is bounded and any point in the fractal must be at most $\sum_{n=1}^\infty \frac{1}{(\min \{l, r\})^n}$ units away from $0, 0$. 

The only cases that remains are both children are the same length as the parent, or one child is the same length and one is shorter. 
- If one child is the same length, then it depends. 
  - Suppose the left child is the same length, and the right child is shorter than the parent. Then, repeatedly taking the left child is like repeatedly turning right; essentially we are going in a big circle. We can leave the circle by turning right at some point, but now the segment size decreases. So this fractal becomes a large series of circles that touch at vertices and are decreasing in size. For the same reason as above, this is bounded. 
  - There is one exception: if the left child goes in the same direction as the parent, then we can go infinitely in one direction. In this case the fractal is unbounded.
- If both children are the same length, then it turns out the fractal is not bounded. 
  - If the children turn in opposite directions, then we can alternate going left and going right to zigzag in one direction. 
  - If the children both turn in the same direction, then suppose we want to move in any direction. On moves going outwards, take the wider turn. On moves going backwards, take the sharper turn. This forms an infinite spiral moving in some direction. 

This covers all the cases: the fractal is bounded if both children are shorter, or if one child is the same length and not collinear with the parent and the second child is shorter. 

## I: Penniless in America

## J: San Francisco Distances

## K: **Farthest City**

## L: TV Remotes

## M: **Two-for-One Crosswords**

