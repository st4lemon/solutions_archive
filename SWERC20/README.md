# 2020-2021 Southwestern Europe Regional Contest

[Link to contest (Codeforces)](https://codeforces.com/gym/103081)

(*) Problems with stars were more difficult.

## C: Safe Distance

- You are given an $X \leq 1000000$ by $Y \leq 1000000$ grid. Alice starts at $(0, 0)$ and wishes to reach $(X, Y)$. However, there are $N$ other people in the room with $x$ and $y$-coordinates given. Find the maximum distance such that there exists a path from $(0, 0)$ to $(X, Y)$ that does not come within $d$ distance from any other person. 

### Solution

Fix a distance $d$, then this induces a graph between people in the room, with an edge between two people if they are $2d$ units apart. Also add point for the four corners, and make an edge between a corner and a person if the person is within $d$ units of either wall corresponding to the corner. Then, a path exists from $(0, 0)$ to $(X, Y)$ if and only if there is no person within $d$ units of $(0, 0)$ or $(X, Y)$ and there exists some face of the graph that contains both $(0, 0)$ and $(X, Y)$ (it's not really a planar graph but we would still see a contiguous connected polygon if a path exists). The answer is then the minimum $d$ such that no path exists, because Alice would be able to take a path that's exactly $d$ units away from anyone else. 

Turns out that we don't actually have to try finding a face; a face connecting $(0, 0)$ and $(X, Y)$ exists if and only if there is no connected path dividing them, which happens if a path from the top-left corner to the bottom-right corner exists. We just have to find the smallest $d$ such that a path exists. 

We instead build the graph by drawing an edge for every pair of points; between two people which are distance $k$ apart we give the edge weight $k/2$, and between a person and a corner we look at the vertical and horizontal distance to the two bounding edges defining the corner and assign the weight to be the minimum of the two distances. An edge here means that we can travel between these two points if $d$ is at least the edge weight. 

Then, we want to find the path from the top left corner to the bottom left corner with minimal maximum edge weight. This can be computed using Prim's algorithm starting from the top left corner, and continuing until we either reach the bottom left corner or until we exceed the smallest distance of any point to $(0, 0)$ or $(X, Y)$ (because the origin or destination is always within that smallest distance of another person). With $N$ vertices and $O(N^2)$ edges, the algorithm runs in $O(N^2 \log N)$ time.  

## **F: Mentors**

- There are $N \leq 2021$ members, each with a unique rank in $[1, N]$. Each member has a mentor which has a higher rank than it (except for the rank $N$ member, they cannot have a mentor). Each mentor can have up to two mentees. We are also given $R \leq 2021$ and $M \leq 10^9$; compute the number of possible mentor assignments such that the member with rank $R$ does not mentor anybody, and output the answer mod $M$. 

### Solution

Use dynamic programming. Let the state be $dp[i][j] =$ number of ways to arrange mentorships of ranks $[1, i]$ such that there are $j$ members without mentors. Then, to transition to rank $i+1$, we can choose to take 0, 1, or 2 new mentees, and then $i+1$ does not have a mentor either. The transition for $dp[i+1][k]$ is the sum of:

- $dp[i][k-1]$  (take 0 mentees)
- $dp[i][k] * k$ (take 1 mentee, there are $k$ to choose from)
- $dp[i][k+1] * {k+1 \choose 2}$ (take 2 mentees, there are $k \choose 2$ ways to select them)

The exception is for $i = R$, then we force it to take 0 mentees. The final answer will be at $dp[N][1]$, since the rank $N$ person will not have a mentor. 

## L: Restaurants

- There are $N \leq 50\ 000$ customers and $M \leq 10\ 000$ restaurants, numbered $1$ to $N$ and $1$ to $M$ respectively. Each customer makes a reservation to some subset of restaurants, and it ranks its reservations in order of its preference. Each restaurant has a fixed capacity and it also ranks the reservations it receives in order of their preference. 
- Assign customers to restaurants such that:
  - No restaurant accepts more customers than its capacity
  - A customer is given a table in at most one restaurant 
  - There does not exist a restaurant and a customer such that the restaurant has space or would prefer the customer over one of its accepted customers, and the customer does not have a reservation or would prefer the restaurant over it's current restaurant. 

Importantly, the total number of reservations is bounded by $1\ 000\ 000$. 

### Solution

This is a variant of the Stable Matching problem, with the only difference being that restaurants can accept multiple customers instead of just one. The algorithm is executed in rounds, described as follows:

- Every unassigned customer requests the highest restaurant on its reservation list that it has not requested before. The customer is now temporarily assigned to the restaurant.
- Every restaurant that now has too many customers assigned to it will repeatedly unassign its least-preferred customer until it is under capacity. 

Continue executing rounds until either every customer is temporarily assigned or is out of reservations to request. This temporary assignment is now the answer. With an efficient implementation that only checks unassigned customers for new requests, and only checks the capacity of restaurants that have been requested that same round, the algorithm runs in $O((\text{reservations}) * \log N)$. 

## **M: Fantasmagorie**



