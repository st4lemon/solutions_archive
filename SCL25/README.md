# 2025 Southern California Regional Contest

[Link to problems (ICPC)](http://socalcontest.org/history/2025/SCICPC-ProblemSet-2025-2026.pdf)

(*) Problems with stars were more difficult.

## B: Rubik's Cube

- There is a Rubik's cube with six $3 \times 3$ faces, with an arbitrary coloring of red, white, blue, green, orange, and yellow squares (not necessarily an equal amount of each color). 
- You are given the coloring of the front face of the cube. You can query the cube by specifying a 90-degree turn of one of its faces, and the resulting front face of the cube will be returned to you. 
- Determine in 100 moves or less what the original color of every square was. Note that it is impossible to determine the center piece of any face except the front face, so those do not need to be determined. 

### Solution

Repeating $UD'$ 4 times and then $LR'$ 4 times gets us all squares on the back face, and 6 of the 8 squares on the up, down, left, and right faces. We can then extract the remaining 4 squares on the left/right faces by performing $LR'$ so that now rotating the up and down faces will reveal those 4 squares: $UD'$ gets us the two on the right, then $U'DU'D$ from that point gets us the two on the left. Reset the cube with $UD'L'R$ and repeat the procedure similarly for the up and down faces.

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

The final case is if there is one point on either side of Market Street. However, for the same reason that we take Market Street in the second case above, it is never better to traverse horizontally above Market Street (by zig-zagging) because it always costs less to move horizontally on Market Street itself. 

Any optimal path therefore has three parts to it: travel down to Market Street as fast as possible, then travel horizontally along Market Street, then go below Market Street. The most important part is the first; once we decide where our downwards path meets Market Street, then the distance to the second point is just the Manhattan distance in the grid below Market Street. 

- Consider a point $(x, y)$ above Market Street. Then, using only moves in the negative x- and y- directions, it takes $x+y$ moves to reach the line $x+y = 0$, and we can reach any lattice point on the line between $(-y, y)$ and $(x, -x)$. In the regular coordinate axes, this translates to the points $(-y\sqrt{2}, 0)$ and $(x \sqrt{2}, 0)$. 
- Then, for a point $(a, b)$ below Market Street, the two closest points from above Market Street are $(\sqrt{2} \lfloor a/\sqrt{2} \rfloor, 0)$ and $(\sqrt{2} \lceil a/\sqrt{2} \rceil, 0)$. 
- If at least one of the points lies within $(-y\sqrt{2}, 0)$ and $(x \sqrt{2}, 0)$, then it is possible to reach then just through downwards moves from above market street, and we should take the closer of such points.
- If neither lies within the interval, then we simply find the Manhattan distance to $(-y\sqrt{2}, 0)$ and $(x\sqrt{2}, 0)$ and take the minimum. 

This completes the final case.


## K: Farthest City*

## L: TV Remotes

- There are an infinite number of TVs placed on a number line, with one at each integer coordinate. You have $N \leq 10^5$ remotes, each centered at some x-coordinate $-10^9 \leq x_i \leq 10^9$ and with some range $r_i \leq 10^9$. A remote can send a single signal to one TV within the range $[x_i - r_i, x_i + r_i]$. 
- Initially, all TVs are off. Sending a signal to a TV that is off turns it on, and sending a signal to a TV that is on turns it off. If all remotes send exactly one signal, what is the minimum number of TVs that can be on after all signals are completed?

### Solution

Since TVs can be toggled off, we can match remotes that can reach the same TV since aiming them both at the same TV turns it on then off again, minimizing the contribution. It then remains to compute a maximal matching of remotes, which can be done with a line sweep algorithm on intervals. 
- For each remote $(x_i, r_i)$, add a "start" event at $x_i - r_i$ and an "end" event at $x_i + r_i$. Sweep over events in ascending x-position, putting start events first if a start and end event occur at the same location. Maintain a sorted set of <endpoint, indej> pairs, sorted by greatest endpoint and then by index. 
- When we reach a start point, push the corresponding <endpoint, index> pair into the set. Any index in the set represents a remote that is currently "active" and is unmatched. 
- When we reach an end point, we first check if the remote is still in the set. If it is, then we must attempt to match it with another active remote. Remove the remote from the set, and then if the set is nonempty we match it with the smallest-endpoint active remote, also removing it from the set. 
  - This greedy choice is always best because an active interval with a later endpoint has more possible matches than one earlier. 
- However, if the set is empty then the remote cannot be matched, so we add 1 to the answer instead of matching it. 


## M: Two-for-One Crosswords*

- You have an $R \leq 10^3$ by $C \leq 10^3$ grid of characters, each of which are '.' representing a white space or '#' representing a filled black space. This represent a crossword puzzle, and any maximal set of consecutive vertical or consecutive horizontal white spaces is a slot where a word can go. Slots are ordered by their top-left most square, ordered top-to-bottom then left-to-right, and if there is a tie then the horizontal slot comes first. 
- Each slot has two possible words that fit in the slot, which are given to you in input. Count the number of ways to choose a word for each slot such that you obtain a valid crossword puzzle (that is, two slots that intersect at a square agree on the letter appearing there). 

### Solution

We can somewhat model the crossword as a 2-SAT formula, where each slot can have one of two values (words) and each square that is in two slots enforces a constraint on the slots because that square can only have a single letter, therefore the two slots must choose words sharing a letter. Before even thinking of how to count the number of solutions (since standard 2-SAT algorithms only output a valid configuration), let's attempt to build a 2-SAT instance from the grid. 

Consider two slots that intersect in a square. Then, each slot has two word choices, therefore two choices of letters to put in that square. With the constraint that the letters chosen for each slot must be the same, we can go through every case and build a 2-SAT-like graph. Let the two slots be $x$ and $y$; for each slot we add two vertices $x_1, x_2$ representing the choice of taking the first word or second word respectively (similarly to how 2-SAT has vertices for $x$ and $\bar{x}$).

- $a/a \mid a/a$ (all letters are the same)
  - No matter what word is chosen, this square will match. No constraints are added. 
- $a/a \mid a/b$ (one slot has the same letters, second slot has one matching letter)
  - The choice of the first slot is irrelevant in this square, but we know that we must choose $a$ for the second slot. Fix $y_1$ to be selected. If it is $a/a \mid b/a$, then we fix $y_2$ instead. 
- $a/b \mid a/b$ (both slots have the same choices)
  - In this case, if one slot chooses $a$ then the other must choose $a$, and if one chooses $b$ then the other must choose $b$. Add the edges $x_1 \to y_1, y_1 \to x_1, x_2 \to y_2, y_2 \to x_2$. If it is $a/b \mid b_a$ instead, add $x_1 \to y_2, y_2 \to x_1, x_2 \to y_1, y_1 \to x_2$. 
- $a/b \mid a/c$ (slots share one choice)
  - In order to match, both slots must pick the first word to match the letter $a$. Fix $x_1$ and $y_1$ to be selected. 
- Any other combination indicates that $x$ and $y$ do not share any choices, therefore no valid crossword exists because there is a square that is unsatisfiable. 

The result is a graph with $2S$ vertices ($S$ = number of slots), with an edge from $x_j$ to $y_k$ if choosing word $j$ in slot $x$ means we must choose word $k$ in slot $y$. We observe that this is slightly different than a standard 2-SAT graph; every edge $a \to b$ has a matching edge $b \to a$ in the graph. We can therefore treat all edges as undirected. 

Then, we can make the following observations:
- For some slot $x$, if $x_1$ and $x_2$ are in the same component, then no valid crossword exists. This basically means choosing word 1 implies we must choose word 2 in the same slot, a contradiction. 
- The only place where we add edges is in the $a/b \mid a/b$ case, where if we add the $x_1 - y_1$ edge, we also add the $x_2 - y_2$ edge (and for each $x_2 - y_1$ we add $x_1 - y_2$). Therefore, the "opposite" edge always exists in the graph. 
- Since we always add opposite edges for each edge, if a component has no contradictions (from the first bullet point), then every vertex is disconnected from its same-slot counterpart, and all of the opposite edges of edges in the component must exist, therefore an opposite component disconnected from the current component must exist. 

Finally, a configuration of words on a crossword is a choice of one word for each slot. With our graph structure, if we pick a word for a slot, we must also pick all the words in slots corresponding to all nodes in the same connected component. We must count the number of configurations that satisfy the constraints we fixed before (see cases $a/a \mid a/b$ and $a/b \mid a/c$). 
- First, check that no constraints contradict one another. We can do this by marking all components that must be chosen. Then, for each slot i both word 1 and word 2 are in marked components, then they must both be chosen which contradicts choosing only one word, therefore no valid crossword exists. 
- Then, if no contradictions arise then a valid crossword now exists. Consider each pair of opposite components: if one of them has a fixed word within it then it must be chosen; otherwise if both components are unconstrained then we may pick either one. 

The answer is then $2^C$, where $C = $ number of pairs of unconstrained components. 
