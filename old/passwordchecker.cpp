// LeetCode #420. Strong Password Checker
#include <bits/stdc++.h>

using namespace std;

/*
 * find all the long streaks of characters, and solve those as you go
 * count the amount of adjustments needed for upper/lower and digits and length
 * use length at the end as a bounding condition
 *      when length < 6 prioritize adding for digits
 *      when length >=6 prioritize swapping
 *
 */

class Solution {
public:
    vector<int> checkTriples(string s) { // returns length of longest streak
        char c = s[0];
        int count = 1;
        vector<int> ret;
        for(int i = 1; i<s.length(); i++) {
            if(s[i]==c) {
                count++;
            }
            else {
                if(count>=3) ret.push_back(count);
                c = s[i];
                count = 1;
            }
        }
        if(count>=3) ret.push_back(count);
        return ret;
    }

    int checkLength(string s) {
        if(s.length()<6) return 6-s.length();
        else if(s.length()>20) return 20-s.length();
        else return 0;
    }

    int checkCase(string s) {
        bool digit = false;
        bool upper = false;
        bool lower = false;

        for(int i = 0; i<s.length(); i++) {
            if(islower(s[i])) lower = true;
            if(isupper(s[i])) upper = true;
            if(isdigit(s[i])) digit = true;
        }

        int ret = 0;
        if(!digit) ret++;
        if(!upper) ret++;
        if(!lower) ret++;
        return ret;
    }

    int strongPasswordChecker(string password) {

        vector<int> triples = checkTriples(password);
        int cases = checkCase(password);
        int length = checkLength(password);
/*
        cout << cases << " " << length << endl;
        for(int a : triples) {
            cout << a << " ";
        }
        cout << endl;
*/
        if(length>0) {
            int ans = max(cases, length);
            if(triples.size()==0) {
                return ans;
            }
            else {
                if(triples[0]==5) ans = max(ans, 2);
                else ans = max(1, ans);
                return ans;
            }
        }
        else {
            int ans = 0;
            int length = password.length();
            for(int i = 0; i<cases; i++) { //  swap out things in triples for case changes
                int ind = 0; // find the highest mod 3 (lowest mod 3 can be deleted in shortening moves
                for(int j = 1; j<triples.size(); j++) {
                    if(triples[j]%3>triples[ind]%3) {
                        ind = j;
                    }
                }
                if(triples.size()==0) { // just swap a random one
                    ans++;
                }
                else { // swap something in a triple
                    ans++;
                    triples[ind] -= 3;
                    if(triples[ind]<3) triples.erase(triples.begin()+ind);
                }
            }

            while(length>20) {
                length--;
                ans++;
                if(triples.size()==0) continue;
                int ind = 0;
                for(int i = 1; i<triples.size(); i++) {
                    if(triples[ind]%3>triples[i]%3) {
                        ind = i;
                    }
                }
                triples[ind]--;
                if(triples[ind]<3) triples.erase(triples.begin()+ind);
            }

            for(int i = 0; i<triples.size(); i++) {
                ans += triples[i]/3;
            }

            return ans;

        }

    }

};