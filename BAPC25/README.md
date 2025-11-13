# 2025 Benelux Algorithm Programming Contest
[Link to problems (Codeforces)](https://codeforces.com/gym/106160)

**Problems in bold were more difficult.**

## B: Boggle Sort

- You are given 16 dice with letters written on each face, and you are given the initial orientation of the dice. With one operation, you can rotate any dice such that one of the faces previously on its side is now facing up. Following this, it takes two operations to rotate the bottom face to the top. Compute the minimum number of operations needed such that the dice form a non-decreasing lexicographical sequence. 
- Note additionally that 'Q' does not exist on a face alone, and is actually 'Qu' in the game. The string 'QuT' is not in lexicographical order, but 'QuU' is. 

### Solution

Use dynamic programming. We use an $(N+1)$ by $26$ state table, and let $dp[i][c] = $ min number of operations to put dice 1 through i in nondecreasing lexicographical order such that $c$ is currently the face-up character on dice $i$. The transition can be computed in $O(26)$ by checking $dp[i-1][k]$ for all $k \leq c$, and adding the corresponding number of moves to flip dice $i$ to $c$. 

We deal with the 'Qu' face as follows: we still check all $dp[i-1][k]$ for all $k \leq$ 'q', but then we update $dp[i][$'u'$]$ instead. This maintains the proper lexicographical ordering. 


## C: Coherency

- You have $N \leq 200\ 000$ models, placed on a board represented by a 2D coordinate plane. Each model is centered at a location $(x, y)$ described in millimeters above and to the right of the bottom-left corner, with $0 \leq x, y \leq 10^8$. Each model also has a base diameter $d \in \{25, 28, 32, 40, 50, 65, 80, 90, 100, 130, 160\}$, and no two models overlap (although they can touch). 
- A collection of such models forms a *coherent* unit if between any pair of models, there is an unbroken chain of models that have a Euclidean distance of no more than 2 inches (50.8 mm) between the edges of their bases. Furthermore, if there are seven or more models, then each model must be within two inches of *two* other models.
- Determine if the given collection of models is *coherent*. 

### Solution

Suppose we had a graph with an edge between models if they are within 2 inches of each other. Then, the problem only requires us to compute the degree of every node and decide if the graph is connected, which is simple. However, computing this naively requires $O(N^2)$ computations to calculate all the edges. 

We can actually bound the number of edges in the following way: Between any two "connected" models, there can be a distance of at most $160/2 + 50.8 + 160/2 = 210.8$ between them. Therefore, for a given model we need only check within a $411.6 \times 411.6$ box to find other possibly-connected models. If we pack diameter 25 balls in a grid-like pattern in this box, we can only fit $\sim 260$ other models. Since every edge is counted twice when counting this way, we can upper bound the number of edges at $130 \cdot N \leq 2.6 \cdot 10^7$. Given 10 seconds, this is okay. 

We can compute these edges through a sweepline-like solution now. Sort all models by $x$-position, and maintain a sliding window of width $210.8$, stored in a set sorted by $y$-position. We then iterate over models in order of increasing $x$-position, move the sliding window forward so the right side of the window touches the model center, and query for points within 210.8 units above or below the current model. For every point we draw an edge between models that we determine are within 2 inches of each other (alternatively, use DSU and count degrees of each node), and after computing all edges we can decide if the models are coherent. 


## **E: Excruciating Elevators**



## I: Intermill Logistics



## **L: Linguistic Labyrinth**



