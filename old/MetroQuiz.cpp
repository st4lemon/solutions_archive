/* https://codeforces.com/gym/104945/problem/C

2023-2024 ICPC Southwestern European Regional Contest (SWERC 2023)

Problem C: Metro Quiz

You are given the map of the M (1 <= M <= 50) metro lines (numbered 1 to M), featuring a total of N (1 <= N <= 18) metro stations (numbered from 0 to N-1) and indicating, for each line, those stations at which the line stops. Player A and Player B play a game using this map. Player A thinks of a metro line uniformly at random that player B will need to guess. For each guess, player B can ask whether the line stops at a metro station of her choice, and player A answers truthfully. After enough questions, player B will typically know with certainty which metro line player A had in mind. Of course, player B wants to minimise the number of questions she needs to ask. 

Please compute the expected number of questions that player B needs to find the answer, in the optimal strategy. If it is not always possible for player B to know which line player A had in mind with certainty, output not possible. 

*/

/*

Solution: Subset DP / DFS with memorization

Let the state space be all possible subsets of metro lines (although this = 2^50 and large, this is actually okay for now); each one of these represents a unique game state. For a given game state, we want to determine what is the best station to guess that minimizes our expected number of guesses. Suppose our current subset of metro lines is S and we want to try picking station m, which divides S into U and ~U (depending on the response from player A). Then, if we know the expected number of guesses from U and ~U, then we can easily calculate the expected number of guesses from S. This leads to a solution using DFS with memorization: start with the set of all metro stations, and for each state try guessing every possible station. Some notes about my implementation:

 - Since each line has equal probability of being chosen, the game transitions to U or ~U with probability weighted on the size of these subsets. I instead get around this by letting dp[U] = (# expected guesses)*(size of U), so the value in the dp table is proportional to the size of the game state it represents. This allows us to simply add together two dp values when doing our DFS
 - How is it possible that this runs in time? Turns out, the set of possible game states is upper bounded by the total number of subsets of stations. Each game state is reachable by guessing some subset of stations (irrespective of order); therefore the total number of states is bounded by 2^N = 2^18. 
 - In order to save a factor of M in calculating the resulting game state after guessing a station, I store each station as a bitmask with the i-th bit set to 1 if the i-th metro line passes through that station. Taking the bitwise AND of a station and a game state gives the new game state if player A answers yes, and doing a simple subtraction obtains the state where player A says no.

Total runtime: O(N * 2^N) 
 

*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 1LL<<18

typedef long long ll;

ll N, M;
ll station[18] = {0};

unordered_map<ll, ll> dp;

ll dfs(ll mask) {
	if(dp.count(mask)) return dp[mask];
	int cnt = __builtin_popcountll(mask);
	ll best = 50*50;
	for(int m = 0; m<N; m++) {
		ll num = station[m] & mask;
		if(num == 0 || num == mask) continue;
		best = min(best, dfs(num) + dfs(mask - num));
	}
	dp[mask] = best+cnt;
	// cout << bitset<5>(mask) << ": " << best + cnt << '\n';
	return best + cnt;
}


int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N >> M;
	
	for(int i = 0; i<M; i++) {
		int k;
		cin >> k;
		for(int j = 0; j<k; j++) {
			int l;
			cin >> l;
			station[l] |= 1LL<<i;
		}
	}
	
	for(ll i = 1; i< 1LL<<M; i *= 2) {
		dp[i] = 0;
	}
		
	double ans = dfs((1LL<<M) - 1);
	if(ans >= 50*50) {
		cout << "not possible" << '\n';
		return 0;
	}
	cout << fixed << setprecision(8) << ans/M << '\n';
	
}
