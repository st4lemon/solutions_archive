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

- There is a building with $10^6$ floors, which are numbered $0, 1, ..., 10^6$ with $0$ representing the ground floor. There are $N \leq 35$ jobs on floors $f_1, f_2, ..., f_N$ that you must complete next month in that order, each requiring some amount of time to complete given in seconds. 
- The only way to move up and down floors is by elevators. Initially all elevators are stopped, but you can choose to start them at any time, and once an elevator is started it moves between $0$ and $10^6$ indefinitely. Since you have a month before the jobs must be started, you can pick any starting configuration of the elevators. 
- You start on floor 0. Time starts when you get on an elevator at floor $0$ and ends when you complete the final job. What is the minimum possible completion time?

### Solution

We must prove a some lemmas before coming to the solution. Consider an elevator configuration with the minimum possible completion time and the sequence of elevators we take defined by that configuration, and define an elevator's "position" as the time elapsed since the last time that elevator was at floor $0$. This becomes helpful because now every position-direction pair is represented as an integer from $0$ to $2\cdot10^6$. 

- Let a "crossing" occur from $e_1$ to $e_2$ when in the elevator sequence derived from the configuration, we get off of elevator $e_1$ and the next elevator we ride is elevator $e_2$. Let this crossing be a "perfect crossing" at job $j$ when $e_1$ arrives at the floor of job $j$, then $e_2$ arrives exactly when job $j$ is completed.
- Lemma 1: For a fixed configuration, a minimum sequence exists where crossings only occur at jobs. 
  - Suppose a minimum sequence has a crossing between $e_1$ and $e_2$ after the completion of job $j$ but before job $j+1$. $e_2$ must be moving in the opposite direction of $e_1$ when it dropped us off; otherwise the crossing is not useful and we would just stay on $e_1$. Then, $e_2$ goes backwards on the same path until we pass job $j$ again, before eventually reaching job $j+1$ (if $j+1$ was on this path, then $e_1$ would just drop us off there before the crossing would occur). However, it is equivalent to just wait at $f_j$ until $e_2$ arrives. 
- Lemma 2: For any elevator $e$, we can increase it's starting position by some nonnegative integer to obtain a configuration where there is a perfect crossing to $e$.  
  - Consider every job $j$ where we take elevator $e$ after finishing the job, but we don't take $e$ to arrive at the job. Then, we wait for some non-negative time $t_j$ after each one of these jobs for $e$ to arrive. Let $t$ be the minimum wait time of all such $t_j$; then adding $t$ to the starting position of $e$ and taking the same sequence of elevators will cause it to arrive exactly on time when some job finishes (the end time of the job is still the same, but now $e$ arrives earlier). 
  - This reduces the number of meaningful configurations; we need only consider sequences of elevators where each elevator used has some "perfect crossing" to it, since we can always transform configurations without perfect crossings to equivalent ones that have them, through the above process.
- Lemma 3: Suppose we use all 4 elevators at some point. For a given elevator configuration and sequence, construct a directed graph with 4 vertices representing the elevators, and an edge from elevator $e_i$ to $e_j$ if there is a perfect crossing from $e_i$ to $e_j$. Then, there must exist an equivalent configuration such that its graph admits a directed spanning tree rooted at the elevator starting from floor $0$. 
  - Let $e_1, e_2, e_3, e_4$ be the 4 elevators, and let $e_1$ be the elevator starting at floor $0$. Suppose such a directed spanning tree rooted at $e_1$ does not exist; then there is some set of elevators reachable from $e_1$ and some set of elevators that are not reachable in the graph. Then, in the elevator sequence that we take, there are some number of crossings from the reachable subset to the unreachable subset, and using the same process from Lemma 1 we can increment the starting positions of the unreachable elevators until some perfect crossing from a reachable to an unreachable elevator exists. Continue this process until all elevators are reachable from $e_1$. 
  - A similar proof holds for if we use $<4$ elevators; make one node per elevator, and such a directed spanning tree must exist. 
- Lemma 4: For a perfect crossing from $e_1$ to $e_2$ at job $j$, we can determine the relative difference in starting positions of $e_1$ and $e_2$ based only upon $f_j$ and the time it takes to complete $j$. 
  - $e_1$ must have come from $f_{j-1}$ prior to arriving at $f_j$, so we know the position $p_1$ of $e_1$ when it reaches $f_j$. Then, the job takes some amount of time $t_j$ to complete, so once $e_2$ arrives at $f_j$, elevator $e_1$ is at $p_1 + t_j$. $e_2$ can either be moving up or moving down, so there are two possible positions it could be at. Later on, we will be able to choose which direction the elevator is moving, so WLOG suppose $e_2$ is moving up at this perfect crossing. Then, it is at position $f_j$, so $e_2$ is $f_j - (p_1 + t_j)$ units ahead of $e_1$. 


The result of these lemmas is that if we know the DST representing perfect crossings, and we know where these perfect crossings occur, and the direction that the elevator takes after leaving a perfect crossing, then we have determined the starting points of the elevators. We can simply try all of them.

The algorithm then is as follows:
- Choose one of the unlabeled DSTs with 4 nodes, of which there are $\leq 3!$. 
    - We assume all 4 elevators might be used; less elevators may be used if some other elevator always happens to arrive first after each job. 
    - Each of these DSTs have 3 edges.
- For each edge, choose one of $n$ floors where that perfect crossing occurs, and the direction that the outgoing elevator moves in. This fixes the starting position of each elevator. For $3$ edges, this is $O((2n)^3)$. 
- Simulate the sequence of elevators greedily in $O(n)$; after finishing job $j$, take the elevator that gets you to job $j+1$ the fastest.
- Return the shortest time used to complete all jobs over all possible configurations. 

The total runtime is $\leq 3! \cdot (2n)^3 \cdot n \approx 48n^4$, and with $n \leq 35$ this runs in time.


## I: Intermill Logistics

- There are $N \leq 10^5$ mills, each which can process $p \leq 10^9$ kilograms of wheat per hour and is located $t \leq 10^9$ hours away. You have $w \leq 10^9$ kilograms of wheat to process, and you have enough transport vehicles to send wheat to each of the mills simultaneously and to bring the processed flour back. How long does it take to process all the wheat?

### Solution

It is optimal for the transport vehicles to leave for every mill at the same time, and arrive back at the same time. Consider a single mill in an optimal milling scheme that takes time $T$; if the mill is milling at time $x$, then it is also milling at time $T-x$. This means the timeline of work for every mill is symmetric along $x = T/2$, so we can instead ask the question: Suppose that the transport vehicles do not need to return; how long does it take to mill $W/2$ kilograms of wheat? This helps us find what $T/2$ is, which gives us $T$. 

something something sweepline solution works here. thanks!


## **L: Linguistic Labyrinth**



