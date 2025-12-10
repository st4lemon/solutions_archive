//
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

unordered_map<string, string> par;
unordered_map<string, ll> pval;

string pa(string& c) {
    if(par[c] != c) {
        par[c] = pa(par[c]);
    }
    return par[c];
}



bool isdigit(string& s) {
    for(char& c : s) {
        if(isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

void define(string& c, string& p) {
//    cerr << "defining " << c << " -> " << p << endl;
    if(par.find(p)==par.end()) {
//        cerr << "adding p=" << p << endl;
        par[p] = p;
        if(isdigit(p)) {
//            cerr << "define " << c << " " << p << endl;
            pval[p] = stoll(p);
        }
        else {
            pval[p] = 0;
        }
    }
    if(par.find(c) != par.end()) {
//        cerr << "already found c=" << c << endl;
        if(pa(c) != c) {
//            cerr << "already defined c=" << c << endl;
            return;
        }
        if(pa(c) == pa(p)) {
//            cerr << "cyclical assignment" << endl;
            return;
        }
    }

    par[c] = pa(p);
    pval[c] = pval[pa(c)];
}

ll binpow(ll n, ll k) {
    if(k == 1) return n;
    if(k == 1) return 1;
    ll ret = binpow(n, k/2);
    ret *= ret;
    if(k%2 == 1) ret *= n;
    return ret;
}

ll exp3(string& s, int& i);

ll exp0(string& s, int& i) {
    if(s[i] == '(') {
        i++;
        ll ret = exp3(s, i);
        i++;
        return ret;
    }
    ll neg = 1;
    while(i < s.length()) {
        if(s[i] == '+') {
            i++;
        }
        else if(s[i] == '-') {
            i++;
            neg *= -1;
        }
        else {
            break;
        }
    }
    int sind = i;
    while(i < s.length() && isalnum(s[i]) != 0) {
        i++;
    }
    string val = s.substr(sind, i-sind);
    if(par.find(val) == par.end()) {
        par[val] = val;
        if(isdigit(val)) {
//            cerr << "exp0def " << i << " " <<  val << endl;
            pval[val] = stoll(val);
        }
        else {
            pval[val] = 0;
        }
    }
//    cerr << "exp0 " << i << " " << val << " " << pa(val) << " " << neg * pval[pa(val)] << endl;
    return neg * pval[pa(val)];
}

ll exp1(string& s, int& i) {
    vector<ll> terms;
    terms.push_back(exp0(s, i));
    while(i < s.length() && s[i] == '^') {
        i++;
        terms.push_back(exp0(s, i));
    }
    while(terms.size() > 1) {
        ll b = terms.back();
        terms.pop_back();
        terms.back() = binpow(terms.back(), b);
    }
//    cerr << "exp1 " << i << " " << terms[0] << endl;
    return terms[0];
}

ll exp2(string& s, int& i) {
    vector<ll> terms;
    vector<char> op;
    terms.push_back(exp1(s, i));
    while(i < s.length() && (s[i] == '*' || s[i] == '/' || s[i] == '%')) {
        op.push_back(s[i]);
        i++;
        terms.push_back(exp1(s, i));
    }
    ll val = terms[0];
    int ind = 1;
    while(ind < terms.size()) {
        if(op[ind-1] == '*') {
            val *= terms[ind];
        }
        else if(op[ind-1] == '/') {
            int sgn = val * terms[ind] > 0 ? 1 : -1;
            val = sgn * (abs(val) / abs(terms[ind]));
        }
        else {
            int sgn = val * terms[ind] > 0 ? 1 : -1;
            val = sgn * (abs(val) % abs(terms[ind]));
        }
        ind++;
    }
//    cerr << "exp2 " << i << " " << val << endl;
    return val;
}

ll exp3(string& s, int& i) {
    ll val = exp2(s, i);
    while(i < s.length()) {
        ll sgn = s[i] == '+' ? 1 : -1;
        if(sgn == -1 && s[i] != '-') {
            break;
        }
        i++;
        val += sgn * exp2(s, i);
    }
//    cerr << "exp3 " << i << " " << val << endl;
    return val;
}

void lower(string& s) {
    for(char& c : s) {
        c = tolower(static_cast<unsigned char>(c));
    }
}

ll exp(string& s) {
    int i = 0;
    lower(s);
//    cerr << s << endl << endl;
    return exp3(s, i);
}

int main() {

    cin.tie(0)->sync_with_stdio(0);

    freopen("plcool.in", "r", stdin);
    freopen("plcool.out", "w", stdout);

    string s;
    while(getline(cin, s)) {
        stringstream ss(s);
        ss >> s;
        if(s == "print") {
            stringstream sss;
            while(ss >> s) {
                sss << s;
            };
            s = sss.str();
            cout << exp(s) << endl;
        }
        else if(s == "define") {
            string s1, s2;
            ss >> s1 >> s2;
            lower(s1);
            lower(s2);
            define(s1, s2);
        }
    }

}
