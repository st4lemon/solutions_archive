/*

https://codeforces.com/gym/104945/problem/G
2023-2024 ICPC Southwestern European Regional Contest (SWERC 2023) #G: Favourite dish

The Olympic Village dining hall serves N dishes (1 <= N <= 500000), each with a score on its taste and its plating (integers from 1 to 1000000). There are M people (1 <= M <= 500000) who each have a weight on taste and a weight on plating (also integers from 1 to 1000000). A person's final score on a dish is the weighted average of the dish's scores on taste and plating. 

The chefs at the Olympics want to provide everyone with their favourite dish. Calculate everyone's favorite dish. If multiple dishes tie for the highest score as a person's favorite, choose the one with the smallest number. 


Solution: Convex Hull + Two Pointers

Trying every pair of dishes and people is far too slow for this problem. Since we need to output a favorite dish for every person, we need to find a fast way to identify every person's favorite dish. 

One observation we can make is the following: suppose we plot every dish on an xy-coordinate plane, with taste on the x-axis and plating on the y-axis. Then, some dishes can never be a favorite of any person. Some examples of such a case are as follows; Denote (x, y) as a dish with taste x and plating y:
 - For a <= x and b <= y, given dishes (x, y) and (a, b), no diner will ever choose (a, b) over (x, y)
 - Suppose we have dishes (x, y+5), (x+5, y) and (x+1, y+1). No matter what, (x+1, y+1) will never be chosen as a favorite dish since the other two dishes exist. 

This follows from modeling the dishes on the coordinate plane: for a specific diner, which dish is their favorite plate? Denote T as the diner's weight on taste, and P as the weight on plating. We can model the score for any dish (x, y) as S(x, y) = Tx + Py; which is just the equation of a line in the first quadrant. We can call such a line a "level line of value S(x, y)", and every point (dish) lies on exactly one of these lines with its score being equal to the value of the level line. A dish can only every be considered a favorite dish if, for some set of level lines defined by the diners, it obtains the maximum score among all dishes.

We can find this set in O(N log N) using a convex hull algorithm; first sort points by their taste decreasing and as we sweep from right to left, we continuously take points that make left turns (collinear points are allowed, we will see why later). Visualizing with level lines, we can see that for any set of three points in order, if the middle one forms a right turn with the other two points then at least one of the outer points will always have a higher score than the middle point. Thus, a convex hull is a sufficient model for this. It returns a list of dishes sorted by taste decreasing (and plating increasing) that are all candidates to be favorite dishes. 

It then remains to match diners to dishes. For any diner, as we iterate over dishes by taste decreasing, the score will initially increase with each successive dish until we reach the maximum score, and then it will decrease. This structure leads us to a ternary search solution, which finds the global maximum of a convex function. 

My solution actually implements a two pointers method to find this (I didn't come up with the ternary search solution until now). If we sort the diners by their ratio between taste and plating preference (i.e. the slope of the level lines corresponding to their preference), their set of favorite dishes forms a monotonic list. (Why? Consider the line segments before and after the point: their slopes indicate the range at which this dish is the best dish, and the slopes consistently become flatter as we decrease in taste. Thus, flatter slope = lower taste dish) Therefore, if we sort the diners by their "slope", the current diner's favorite dish will either be the same as the previous diner's favorite, or it will come after the current dish on the hull (to the "left"). Thus, if we know the previous diner's favorite dish, we compare it and the next dish on the convex hull. If that works, then we can compare the next dish, and so on. We never have to repeat dishes, so this search becomes O(N) amortized. 

There is a small hiccup here, though. What if there are multiple favorite dishes for a single diner? In the convex hull, this is represented by a set of collinear dishes on the coordinate plane. If we are able to detect such a case, it helps to have some way to precompute which dish the diner should pick ahead of time. 

For the ternary search solution, for each point we can mark some events that indicate "if this dish is chosen with a specific slope, instead output this lower-indexed dish". Each dish will store up to two of these values, which is okay. Then, for each range of collinear dishes, we can iterate across it to find the minimum index dish, and do another pass to set the values we need. 

For my solution, I chose instead to calculate this online: if we run into a situation where two adjacent dishes on the hull have the same score for the current diner, we know that the first of the two dishes is the start of a collinear range of dishes (since otherwise the previous pair would have had the same score). Then, we binary search for the end of the collinear range; all collinear dishes have the same score, and all dishes coming after have a lower score. We then do the same as above and immediately jump to the minimum index dish, doing some extra scorekeeping for when the "slope" of the current diner changes. 

*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pt {
    ll x;
    ll y;
    int ind;
};

ll cross(pt one, pt two) {
    return one.x * two.y - two.x * one.y;
}

istream& operator>>(istream& is, pt& p) {
    is >> p.x >> p.y;
    return is;
}

struct cmp {
    bool operator()(const pt& one, const pt& two) {
        if(one.x == two.x) return one.y < two.y;
        return one.x > two.x;
    }
};


struct comp {
    bool operator()(const pt& one, const pt& two) {
        if(one.x * one.y == 0 && two.x * two.y == 0) {
            return one.y < two.y;
        }
        return one.x * two.y > one.y * two.x;
    }
};

ostream& operator<<(ostream& os, pt& p) {
    os << p.x << " " << p.y;
    return os;
}

pt operator-(pt one, pt two) {
    pt ret;
    ret.x = one.x - two.x;
    ret.y = one.y - two.y;
    return ret;
}

ll score(pt dish, ll x, ll y) {
    return x * dish.x + y * dish.y;
}



int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<pt> dishes(N);
    vector<pt> diners(M);

    for(int i = 0; i<N; i++) {
        cin >> dishes[i];
        dishes[i].ind = i;
    }

    for(int i = 0; i<M; i++) {
        cin >> diners[i];
        diners[i].ind = i;
    }

    sort(dishes.begin(), dishes.end(), cmp());
    sort(diners.begin(), diners.end(), comp());
    /*
    cout << "dishes\n";
    for(auto p : dishes) {
        cout << p << '\n';
    }
    cout << "diners\n";
    for(auto p : diners) {
        cout << p << '\n';
    }

    cout << '\n';
    */
    vector<pt> hull;

    for(int i = 0; i<N; i++) {
        while(hull.size() >= 2) {
            int n = hull.size();
            if(cross(hull[n-1]-dishes[i], hull[n-2]-dishes[i]) > 0) {
                hull.pop_back();
            }
            else break;
        }
        hull.push_back(dishes[i]);
    }

    // for(auto p : hull) cout << p << '\n';

    vector<int> ans(M, 0);
    int curr = 0;
    int next = 1;
    bool checked = false;
    for(int i = 0; i<M; i++) {
        if(i > 0) {
            if(diners[i].x * diners[i-1].y != diners[i-1].x * diners[i].y) {
                checked = false;
                curr = next - 1;
            }
        }
        while(curr < hull.size()-1) {
            ll s1 = score(hull[curr+1], diners[i].x, diners[i].y);
            ll s2 = score(hull[curr], diners[i].x, diners[i].y);
            if(s1 > s2) {
                curr = next;
                next = curr + 1;
                checked = false;
            }
            else if (s1 == s2 && !checked) {
                int low = curr;
                int high = hull.size()-1;
                while (low < high) {
                    int m = (low + high + 1) / 2;
                    if(score(hull[m], diners[i].x, diners[i].y) == s1) {
                        low = m;
                    }
                    else high = m-1;
                }
                // cout << curr << " " << low << '\n';
                int best = curr;
                for(int k = curr+1; k<= low; k++) {
                    if(hull[k].ind < hull[best].ind) {
                        best = k;
                    }
                }
                curr = best;
                next = low + 1;
                checked = true;
                break;
            }
            else {
                break;
            }
        }
        ans[diners[i].ind] = hull[curr].ind+1;
    }

    for(int a : ans) cout << a << '\n';


}
