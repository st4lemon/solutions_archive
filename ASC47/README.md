# Andrew Stankevich Contest 47
[Link to problems (Codeforces)](https://codeforces.com/gym/100608)

(*) Problems with stars were more difficult.

## A: Ambitious Plan
- Given coordinate points in the form $(x, y)$ representing $n \leq 1500$ drones $m \leq 1500$ forts and $t \leq 1500$ towers, compute the number of ways to choose a drone, fort, and two towers such that the segment connecting the drone and the fort intersects the segment connecting the two towers (call this an "explosion"). You are also given that all drones satisfy $y > 0$ and all towers/forts satisfy $x < 0$.

### Solution

Choose a fort and two towers: the drones that cause an explosion given these selections are the drones that appear in between the two towers when viewed from the fort. This motivates a sweepline-like solution. For each fort, sort all drones and towers by their angle, and sweep in counterclockwise order to count the number of explosions. 

Suppose the point we are sweeping over is a tower. Then, for each other tower that we have seen so far, the amount of explosions created is the number of drones appearing between these two. We can maintain how many "possible explosions" can happen based upon the list of towers and drones currently seen so far, which can be maintained in O(1): track how many towers have been seen, and when we add a drone we add as many possible explosions as towers seen so far. 

There exists one more case; the two towers must appear within 180 degrees of each other in the sweepline in order to actually intersect the drone-fort segment (otherwise, the towers form a segment behind the fort). Before computing the answer, we remove points from the end of the sweepline that are further than 180 degrees behind our current point, and if they are towers we subtract from the possible explosions the number of explosions that tower is responsible for (which is the number of drones currently in the sweepline) and decrement the number of towers too. Knowing this, in order not to overcount explosions in our sweepline we first sweep the semicircle under the fort (which cannot have any explosions), then sweep 360 degrees around the fort through every point (which allows us to try every possible tower as a left tower for an explosion). 

Overall runtime: $O(N^2 \log N)$. 

## J: Jinxiety of a Polyomino*

- You are given an $H \leq 2000$ by $W \leq 2000$ grid filled with '#' and '.' characters. The '#' characters define a convex polyomino:
  - Polyomino: connected set of squares of a unit grid
  - Convex: any vertical/horizontal line intersects the polyomino in a contiguous segment
- Define the "jinxiety" of the polyomino as the minimal $k$ possible that it is possible to get from any square to any other square by a path that uses only two directions and changes direction at most $k$ times. Find the jinxiety of this convex polyomino. 


### Solution 

Naively, we can do this with an $O(N^4)$ BFS: Perform an 0-1 BFS from a starting square, and for each (square, direction) pair, either continue going straight at a cost of 0 or turn left or right at a cost of 1. Repeat this for each square, and the farthest distance we reach in the BFS is the answer. This can be improved in several ways:
- Because the polyomino is convex, if we are able to visit a single square in a row (column), then we can visit all squares in that row (column) within at most 1 extra move. We can speed up the previous 0-1 BFS by visiting whole rows and columns at a time, obtaining for each row/columm how long it takes to visit all squares within that row/column. 
  - From a starting square, *mark* it's starting row and column as distance 0. Then, the starting row can visit some other columns, and the starting column can visit some other rows. Initialize $k = 0$. 
  - For each of these new visitable rows/columns that have not been *marked*, *mark* them with distance $k + 1 = 1$, since it takes 1 more turn to visit everything in the new row/column. The exception is if all squares within the row/column are within columns/rows that have been processed in a previous iteration, in this case we mark it with distance $k = 0$ since it has already been visited within 0 moves. 
  - Then, continue for the new visitable rows/columns from the previous iteration, incrementing the distance $k$ per iteration. 
  - This is $O(N^3)$ since for each square we process every row and column exactly once, a major improvement from before but still not fast enough for $H = W = 2000$. 
- For a single square, we simulate all possible paths in the BFS. Any possible shortest path will only take moves in the direction of the destination, so these paths are of two forms: moving horizontally with the first move or vertically with the first move. A minimal path exists within the set of paths of either form, so between two squares there are only two possible paths we need to check. Instead of trying to calculate both the horizontal-first and vertical-first paths in a single BFS, instead compute them separately. 
  - From a starting square, *mark* it's starting row as distance 0 (this represents taking the initial horizontal move). This starting row can visit some other columns. Initialize $k = 0$. 
  - Continue the same *marking* process as above, now alternating between marking columns and marking rows. This generates the shortest distances from this square to every row/column given we start with a horizonal move. 
  - Repeat this for starting with a vertical move too. 
  - The farthest row/column distance from the square is $$\max_{\text{all rows/columns}}( \min(\text{dist(horizontal-start), dist(vertical-start)}))$$
  - This is still $O(N^3)$ but is simpler to compute that the last. Note also that this allows for $0$-distance horizontal moves, but if we do take such a move then the values it generates is simply overridden by the vertical-first move calculations. 
- Finally, notice that for all squares in the same row, the calculations for a horizontal-starting path are exactly the same; since we are allowing $0$-distance moves, the starting column within a row doesn't actually matter. We therefore do not need to recompute a horizontal-starting path for a single row multiple times for every starting column, and can instead compute it once for each row. Similar reasoning for columns. 
  - Compute row/column distances for every starting row/starting column. 
  - For a given row, *mark* it with distance $0$ (it is the starting row, and we are making a horizontal move at no cost), and compute the row/column distances like above. Repeat this for all columns. 
  - Then, for each square we retrieve the row/column distances from its starting row horizontal move and its starting column vertical move that were computed earlier. Compute the answer from the same formula as the previous algorithm. 
  - This is still $O(N^3)$ since calculating the answer requires $O(N)$ operations per square, but computing the row and column distances is now $O(N^2)$; $O(N)$ rows/columns and $O(N)$ time to compute. 

It then remains to compute the overall answer faster than $O(N^3)$. The answer is obtained by taking a global maximum across all squares; which we can decompose into taking a maximum value for each row across all its visitable columns, and then taking a global maximum from all the rows. We again use the property that the polyomino is convex, and note that the squares form a contiguous segment within each row.

- For a single row, this formula is $$\max_{\text{squares in current row}}\max_{\text{destination rows/columns}}( \min(\text{dist(horizontal-start), dist(vertical-start)}))$$ $$= \max_{\text{destination rows/columns}}\max_{\text{squares in current row}}( \min(\text{dist(horizontal-start), dist(vertical-start)}))$$ $$= \max_{\text{destination rows/columns}}\min(\text{dist(horizontal start)}, \max_{\text{squares in current row}}\text{dist(vertical-start)})$$
- The formula $\max_{\text{squares in current row}}\text{dist(vertical-start)})$ can be computed by range query: either compute one range query on vectors of length $H + W$, or compute $H+W$ range queries for each destination row/column on scalar values of that row/column. In either case, this results in $O(N^2 \log N)$ time to build the structure and $O(N \log N)$ time to query a range of columns for each row, which comes out to $O(N^2 \log N)$ time to compute. 
- After the range query, it takes another $O(N)$ time per row to compute the rowwise answer, for $O(N^2)$ overall to generate the final answer. 

The final runtime of this algorithm is $O(N^2 \log N)$, where with $N = H+W \leq 4000$ will run in time. 



