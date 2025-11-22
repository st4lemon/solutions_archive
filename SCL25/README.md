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

- San Francisco is divided into two half-grids at a 45 degree angle to each other. 
- The horizontal axis is a street, Market Street. Streets below Market Street run north-south and east-west, while streets above Market Street are at a 45 degree angle to the coordinate axes. The point $(0, 0)$ lies on Market street. You can only travel along streets, and can only change streets where they meet (see picture in problemset). 
- Given two points, compute the shortest travel distance between them. 

### Solution

The two easy cases are if the two grid points lie on on the same side of Market Street. 
- If both points are below Market Street, then the closest distance is always the Manhattan distance. Observe that using any streets above Market Street to travel between two points below is always slower than just taking Market Street, therefore we can ignore the roads above Market Street in this case. 
- If both points are above Market Street, then the closest distance is usually the Manhattan distance, with one exception. 
  - If the points are close enough to Market Street, then it is faster to take Market Street. For example, suppose our points $(3, -1)$ and $(0, 2)$ are above Market Street. Then, the Manhattan distance is $6$, but the path $(3, -1) \to (1, -1) \to (0, 0) \to (0, 2)$ has distance $4 + \sqrt{2}$. 
  - We can find if this is the case by attempting to use the minimal-Manhattan distance path from $(x_1, y_1)$ to $(x_2, y_2)$ that goes as far south as possible. Assuming that the 45-degree streets continue past Market street, this minimal-Manhattan distnace path would turn the corner at $(x, y) = (\min\{x_1, x_2\}, \min\{y_1, y_2\})$ (example: $(3, -1)$ would turn the corner at $(0, -1)$ to go to $(0, 2)$). 
  - This path intersects the largest section of Market Street, and it is always better to take it when possible. The length of this Market Streetsection is $\sqrt{2} \cdot -(x+y)$, and the length of the Manhattan distance path that is cut off by this section is $2 \cdot -(x + y)$. 
  - So then, we simply check if $(x, y) = (\min\{x_1, x_2\}, \min\{y_1, y_2\})$ is below the line $x+y = 0$ to determine if Market Street cuts off this south-most path, then if it is we use the above calculations to determine how much distance we save by cutting across Market Street. 

The final case is if there is one point on either side of Market Street. However, for the same reason that we take Market Street in the second case above, it is never better to traverse horizontally above Market Street (by zig-zagging) because it always costs less to perform that traversal on Market Street itself. 

Any optimal path therefore has three parts to it: travel down to Market Street as fast as possible, then travel horizontally along Market Street, then go below Market Street. The most important part is the first; once we decide where our downwards path meets Market Street, then the distance to the second point is just the Manhattan distance in the grid below Market Street. 

- Consider a point $(x, y)$ above Market Street. Then, using only moves in the negative x- and y- directions, it takes $x+y$ moves to reach the line $x+y = 0$, and we can reach any lattice point on the line between $(-y, y)$ and $(x, -x)$. In the regular coordinate axes, this translates to the points $(-y\sqrt{2}, 0)$ and $(x \sqrt{2}, 0)$. 
- Then, for a point $(a, b)$ below Market Street, the two closest points from above Market Street are $(\sqrt{2} \lfloor a/\sqrt{2} \rfloor, 0)$ and $(\sqrt{2} \lceil a/\sqrt{2} \rceil, 0)$. 
- If at least one of the points lies within $(-y\sqrt{2}, 0)$ and $(x \sqrt{2}, 0)$, then it is possible to reach then just through downwards moves from above market street, and we should take the closer of such points.
- If neither lies within the interval, then we simply find the Manhattan distance to $(-y\sqrt{2}, 0)$ and $(x\sqrt{2}, 0)$ and take the minimum. 

This completes the final case.


## K: **Farthest City**

## L: TV Remotes

## M: **Two-for-One Crosswords**

