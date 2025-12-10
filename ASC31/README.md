# Andrew Stankevich Contest 31 (ASC 31) 

[Link to problems (Codeforces)](https://codeforces.com/gym/100357)

(*) Problems with stars were more difficult.

## C: Convex Hull*

- There are $n$ ($3 \leq n \leq 10$) lines on a plane, each moving a constant speed of $v_i$ ($|v| \geq 0.01$) perpendicular to itself. At any point in time, there exists a convex hull of the pairwise intersections of all the lines. 
- From time 0 to time $T \leq 100$, compute the average area of this convex hull. 

### Solution

At any point in time, there are $n \choose 2$ intersections on the plane, each defined by a pair of lines. Each intersection also has a constant velocity vector, so we can instead consider $m \leq 45$ points moving with constant velocity. 

Observations:
- The set of points on the convex hull changes only if three points are collinear. A hull point can only leave the hull by passing through the line connecting it's neighbors on the hull, and a point can only enter the hull by passing through some line segment defined by adjacent hull points. 
- Any set of three points $x, y, z$ can only be collinear at two points in time. Since the points have constant velocity $a, b, c$, at time $t$ they are at positions $x+at, y+bt, z+ct$. Solving $[(y+bt)-(x+at)] \times [(z+ct)-(x+at)] = 0$ (cross product) produces a quadratic formula, so there are two roots that we can solve for in constant time. 

Therefore, the number of times the point set of the convex hull changes is bounded above by $2{m \choose 3} = O(m^3)$. Then, given a convex hull with moving points as well as a time interval $[a, b]$ where the points on the hull don't change, the area function $A(t)$ is quadratic with respect to time (try to see why; hint is to consider the area swept by adjacent hull points). 

We can then easily compute $\int_a^b A(t)\ dt$ using numerical methods (interpolation or quadratures) for all adjacent events $a$ and $b$, and then sum them to obtain $\int_0^T A(t)\ dt$. Dividing this quantity by $T$ produces the answer. 



