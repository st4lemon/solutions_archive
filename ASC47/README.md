# Andrew Stankevich Contest 47
[Link to problems (Codeforces)](https://codeforces.com/gym/100608)

## A: Ambitious Plan
- Given coordinate points in the form $(x, y)$ representing $n \leq 1500$ drones $m \leq 1500$ forts and $t \leq 1500$ towers, compute the number of ways to choose a drone, fort, and two towers such that the segment connecting the drone and the fort intersects the segment connecting the two towers (call this an "explosion"). You are also given that all drones satisfy $y > 0$ and all towers/forts satisfy $x < 0$.

### Solution

Choose a fort and two towers: the drones that cause an explosion given these selections are the drones that appear in between the two towers when viewed from the fort. This motivates a sweepline-like solution. For each fort, sort all drones and towers by their angle, and sweep in counterclockwise order to count the number of explosions. 

Suppose the point we are sweeping over is a tower. Then, for each other tower that we have seen so far, the amount of explosions created is the number of drones appearing between these two. We can maintain how many "possible explosions" can happen based upon the list of towers and drones currently seen so far, which can be maintained in O(1): track how many towers have been seen, and when we add a drone we add as many possible explosions as towers seen so far. 

There exists one more case; the two towers must appear within 180 degrees of each other in the sweepline in order to actually intersect the drone-fort segment (otherwise, the towers form a segment behind the fort). Before computing the answer, we remove points from the end of the sweepline that are further than 180 degrees behind our current point, and if they are towers we subtract from the possible explosions the number of explosions that tower is responsible for (which is the number of drones currently in the sweepline) and decrement the number of towers too. Knowing this, in order not to overcount explosions in our sweepline we first sweep the semicircle under the fort (which cannot have any explosions), then sweep 360 degrees around the fort through every point (which allows us to try every possible tower as a left tower for an explosion). 

Overall runtime: $O(N^2 \log N)$. 

## J: Jinxiety of a Polyomino

- You are given an $H \leq 2000$ by $W \leq 2000$ grid filled with '#' and '.' characters. The '#' characters define a convex polyomino:
  - Polyomino: connected set of squares of a unit grid
  - Convex: any vertical/horizontal line intersects the polyomino in a contiguous segment
- Define the "jinxiety" of the polyomino as the minimal $k$ possible that it is possible to get from any square to any other square by a path that uses only two directions and changes direction at most $k$ times. Find the jinxiety of this convex polyomino. 

### Solution

It appears to be too slow to do a naive BFS from each square (or even from each row or column), so we must get a bit creative. Let the "distance" be the number of turns required to reach a square, and observe the following:

- For every row (or column), if we are able to visit a single cell within it then we can reach the rest of the row (or column) within a single move. 
- Between any two pair of squares, the directions that one can take to reach the second square from the first is fixed. There are then two possible ways to reach it: starting with a horizontal move or starting with a vertical move. 
- Between all squares within a single row (or column), if we force them to make a horizontal (or vertical) move first then their shortest-distances to other squares are very similar (only being different because a square cannot move to itself horizontally, but other squares in the row can). 
  - In the latter case, we don't actually care about the zero-distance horizontal (or vertical) move since we'd rather take the vertical (or horizontal) move in this case. 

The solution attempts to simulate taking these two paths in the second observation, using the first and third observation to speed things up significantly. We compute two matrices of size $O(H(H+W))$ and $O(W(H+W))$ representing:

- r[i][j]: given a starting row and ending row/column, and taking the first move to be a horizontal move, how many turns does it take to reach all squares in this row/column (represents paths starting with horizontal moves)
- c[i][j]: given a starting column and ending row/column, and taking the first move to be a vertical move, how many turns does it take to reach all squares in this row/column (represents paths starting with vertical moves)

Then, the farthest distance from a single square can be computed by taking its row and column and using those as the starting row and starting columns. Then, for a given row/column, the shortest distance to reach all squares in this row/column is the minimum of that of the horizontal-starting and vertical-starting paths. 

It then remains to actually calculate these matrices. For each row and each column, compute its left/right (similarly upper/lower) bound on the polyomino; all points between these bounds are points in the polyomino. Suppose we are computing a horizontal-starting path for some row r:

- Maintain left/right and upper/lower bounds on columns and rows that we have currently visited. Initialize the left/right bounds to that of the current row, and the upper/lower bound to a single value - the current row. "Mark" the row as distance 0. 
- Repeat the following process. Let dist = distance of the previous iteration (initially 0)
  - Currently, either some rows are in our bounds and unmarked, or some cols are in bounds and unmarked. WLOG suppose there are currently unmarked rows in bounds. 
  - For each unmarked row, check if it can reach any columns out of the left/right bounds. If so, mark it with dist + 1. Otherwise, mark it with dist. 
  - Using all rows marked in this iteration and the old left/right, calculate the new left/right bounds. 
  - Search for any columns that are now in bounds and unmarked. They will be processed in the next iterations. Increment distance by 1 and start from the top of the loop, now searching through columns. 
  - On the other hand, if no new columns are added to the bounds, we are done. 

Finally, it is still too slow to compute the answer for each square; we must make $O(N+M)$ minimum comparisons between the horizontal-starting and vertical-starting paths. We instead speed this up by constructing a range query (segment-tree, sparse table, etc) on the columns matrix so that we can obtain the maximum distances from a set of columns. In a segment tree this merge operation looks like taking two row/column distances vectors and computing a new row/column distances vector using an element-wise maximum operation. Then, for each row we take its row/column distances and do an element-wise minimum with the range-queried distance vector representing the columns within the row left/right bounds. Taking another maximum across all the row distance vectors and taking the greatest element then gives us the answer. 


