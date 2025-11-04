# 2025 Nordic Collegiate Programming Contest
[Link to problems (Codeforces)](https://codeforces.com/gym/106124)

**Problems in bold were more difficult.**

## B: Bohemian Bookshelf

- You are given a set of $N \leq 100$ books, each with a height and a width. They are placed on a bookshelf with height $130 \leq H \leq 350$ and width $300 \leq W \leq 900$. The books can either be placed upright on the left side of the bookshelf, or placed sideways in a horizontal stack. The width of the horizontal stack plus the widths of the upright books must not exceed the width of the bookshelf, and the height of the stack and height of the upright books must not exceed the height of the bookshelf. Additionally, the books in the stack must be placed in nondecreasing order of height from the bottom up, and there must be at least one book in the stack and one book upright. 
- Determine an arrangement of books in the bookshelf, or output that it is impossible. 

### Solution

The amount of space we have to place upright books is solely dependent on the tallest book sideways on the stack. Moreover, supposing that we fix what this tallest book is, it is always good to make the tallest stack possible, because this minimizes the total width of the upright books and therefore admits the stack in the most bookshelves possible. 

This motivates a knapsack solution: For every possible stack width (of which there are $N$ of them), compute a knapsack to determine the tallest stack we can create using books of height less than the current stack width. Then, given this stack we determine if the upright books fit horizontally and vertically in the shelf, and if they fit we can output it as our answer. We can easily retrieve the books in the stack by memorizing the knapsack transitions and backtracking at the end of the knapsack. 

The only edge case is if all of the books fit in a single stack and we do not need an upright book to fit everything; then we just need to pick the book with the smallest width and make it an upright book before we check if the books fit in the shelf. 

## G: Gotta Trade Some of 'Em

- You are given an undirected graph with $N \leq 100000$ kids and $M \leq 200000$ edges representing friendships between kids. There are also $k \leq 100000$ different game variants. 
- Each kid owns one of the $k$ variants, and each variant contains Pokemon that can only be caught in that variant. Other variants can only obtain these exclusive Pokemon by trading with a game variant that contains that Pokemon, or trading with a kid that obtains the exclusive Pokemon through a list of other trades. 
- Assume that there are enough copies of the exclusive Pokemons in each version so that trades are always possible, and that trades can only happen between friendships. Assign each kid a variant of the game such that everyone can obtain all the exclusive pokemon, or report that this isn't possible. 

### Solution

Clearly, a kid can obtain the exclusive pokemon of a different variant that they own if and only if it is in the same connected component as that other variant. To see if it's possible, compute the size of each connected component. If all components are size $\geq k$, then greedily assign each kid an unseen game variant, such that every component contain every variant. 

## I: Instagraph

- You are given a directed graph with $N \leq 200000$ vertices and $M \leq 1000000$ edges. An edge $u \to v$ means that $u$ follows $v$. For each vertex $v$, it's *celebrity centrality* is the largest subset of vertices that all follow $v$ such that $v$ does not follow any vertex in the subset. Compute the maximum *celebrity centrality* across all vertices. 

### Solution

Iterate through all of the edges. For each vertex, we maintain the number of vertices that follow it that it doesn't follow back based upon the edges we have seen so far. 

The algorithm is simple: when we see an edge $a \to b$, then if $a$ does not contain $b$ within it's set of followers then we add $a$ to $b$'s set of followers. Otherwise, remove $b$ from $a$'s set of followers; they now follow each other. The answer is just the maximum size of all the followers sets. 

## **J: Jump**

- You are given two integers $N \leq 300000$ and $E \leq 10^9$. A singer is on stage and a song is playing, with a *beat* playing every $N$ milliseconds. The singer starts with energy level $E$, and is continually jumping starting with his first jump at time 0. If the singer jumps with energy level $E$, he takes $E$ milliseconds to land on the ground again. 
- When the singer is jumping, he loses 1 energy when he lands on the ground. However, if he lands on the ground at the same time as a beat plays, then he gains 1 energy instead. If he hits the ground and his energy decreases to 0, then he stops. Calculate how many milliseconds it takes for the singer to stop jumping, or if he never stops then output "infinity". 

### Solution

Suppose we have just jumped from a beat with energy $e$. Then the amount of jumps before we land on another beat is determined solely by the value of $e\ \%\ N$, unless $e$ is small enough that we reach 0 before the next beat. Observe also that no matter the starting value of $e$, we will reach another beat witin $2N$ moves. For each $e\ \%\ N$, we can naively compute in $O(N^2)$ time how long it takes to reach the next beat; this can be sped up with a prefix sum-like method to $O(N)$ (maintain a prefix sum of the jump distance starting from an energy with $e\ \%\ N = 0$, and decreasing by 1). Let this array be $d$, with $d[i]$ = jumps to next beat starting with energy $e$ such that $e\ \%\ N = i$. 

Assume for now that the singer does not jump infinitely, we will define a naive algorithm to determine the number of jumps necessary to reach 0. Start with energy $E$, then take $d[E\ \%\ N]$ jumps and subtract that number from the energy; which brings us to the next beat. Increment the energy by 2 (since we add 1 energy instead of subtracting 1 when hitting the beat), and set $E$ to this new energy level. Repeat until you reach 0, keeping track of how many seconds have passed (which is the sum of a decreasing arithmetic sequence starting at $E$). Observe that if a cycle does not exist, then we never repeat an energy level on a beat; otherwise there will be a cycle (we can repeat the same modulo energy level as long as the latter energy is lower than the former). 

Before determining how to speed this up, we first answer the question of how cycles can be detected. Observe that the change in energy level is almost always negative from beat to beat, and it is only positive if the change is +1, which happens when $E = N$. Then, afterwards $E+1 \% N = 1$ so we cannot increase our energy level again (unless $N = 1$ which is a special case). In this case, our jumps go: 

- Jump with energy $E$, hit a beat, new energy is $E+1$. 
- Jump with energy $E+1$, we are 1 ms after the beat, new energy is $E$
- Jump with energy $E$, we are still 1 ms after, new energy is $E-1$
- Jump with energy $E-1$, we now hit a beat and the new energy is $E$. 

This cycle repeats; so if we ever increase in energy we will repeat this 2-beat cycle. Any other cycles cannot have a beat-to-beat increase in energy, so the only other possible cycle is if the energy stays the same between two consecutive beats that we hit, which happens when $N = 2E-1$ (jump $E$, then $E-1$ which hits a beat and raises energy back to $E$). So if there is an infinite cycle, every other beat we hit is guaranteed to be the same. 

We then extend the iterative solution to work for $E \leq 10^9$. We use binary lifting to determine when we have reached 0. Define $bn[k][i]$ = decrease in energy level (before adding 2) starting on a beat from energy $E\ \%\ N = i$ after hitting $2^k$ beats. After $2^k$ beats from $i\ \%\ N$, the next energy level we start jumping from is $bn[k][i] - 2$ levels lower than our current energy level, so the new energy level is $(i - (bn[k][i]-2)) \% N$. The recurrence is then as follows: $$bn[k+1][i] = bn[k][i] -2 + bn[k][(i - (bn[k][i] - 2)) \% N]$$  

We can then retrieve the "path taken" by our singer by computing further layers of the binary lifting until $bn[k][E\ \%\ N] > E$, or we detect a cycle has occurred (which happens when $bn[k][E\ \%\ N] = bn[k-1][E\ \%\ N]$, or when $N = 1$). Finally, in order of decreasing $k$, if $bn[k][E\ \%\ N] <= E$, then we take those $2^k$ beats and set $E -= bn[k][E\ \%\ N]$. 

However, this only retrieves how many beats it takes to reach the end, not how many seconds. Along with bn, keep track of two more values for a given $[k][i]$: the number of jumps we've made so far (which is initialized with $bn[0]$ and uses the same recurrence but does not subtract 2 since we do not "subtract" a jump ever), and the number of seconds elapsed so far; which can be initialized with arithmetic sequences and merged naively in the binary lifting. I found it easier to do a complimentary-counting way of tracking seconds, then subtracting the number obtained from this binary-lift counting from $E \cdot (\text{total jumps})$; essentially you can calculate it given the number of jumps for each $bn[k][i]$ and the actual decrease in energy cause by $bn[k][i]$. See code for details. 

Overall this runs in $O(N)$ to compute $d$, then $bn$ (and the other auxiliary arrays) takes $O(N \log E)$ time to compute since our path to 0 never repeats an energy level on a beat, and is strictkly decreasing if there is no cycle. Finally, computing the answer is just an $O(\log E)$ walk in $bn$, for an $O(N \log E)$ runtime overall. 

## K: km/h

- You are given $N \leq 100$ speed limit signs, which each are either an integer or '/' representing a derestriction of the previous speed limit. There exists a global national speed limit on all roads, which we know is a multiple of 10 and strictly greater than all speed limit signs, but we don't know what this limit is. 
- Based on these rules and the order in which you see the speed limits, determine the maximum speed you can go while abiding by the law. 

### Solution
The problem asks us to maintain the lowest possible national speed limit for every prefix of the input, and for a derestriction we assume the lowest possible national speed limit based on the seen speed limit signss applies and set our speed as such. This value is simply the smallest multiple of 10 greater than all speed limit signs seen so far; we can maintain this with a simple formula: for speed limit s, the national speed limit from this point onwards must be at least $10 * (\lfloor s / 10 \rfloor + 1)$. 
