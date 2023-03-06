// 2023 Socal ICPC Regional: Color Tubes (Problem 7)
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1003

typedef pair<int, int> pii;

int N; //

vector<pii> instructions;

vector<pii> locationOf [MAXN]; // [color][index] = {xposition, height}
int tubes [MAXN][3]; // [xposition][height] = color

void print() {
    for(int i = 0; i<=N; i++) {
        cout << "        ";
        for(int j = 0; j<3; j++) {
            cout << tubes[i][j] << " ";
        }
        cout << endl;
    }
}

int nextZero(int after) {
    for(int i = after+1; i<=N; i++) {
        if(tubes[i][2]==0) return i;
    }
    return -1;
}

pair<int, int> findColor(int color, int after) {
    for(int i = 0; i<3; i++) {
        if(locationOf[color][i].first>after) {
            return locationOf[color][i];
        }
    }
    return {0, -1};
}

void move(int from, int to) { // move top ball from to
    instructions.push_back({from, to});
    int totop = -1;
    for(int i = 0; i<3; i++) {
        if(tubes[to][i]==0) {
            totop = i;
            break;
        }
    }

    int top = 2;
    for(int i = 2; i>=0; i--) {
        if(tubes[from][i]!=0) {
            top = i;
            break;
        }
    }

    int color = tubes[from][top];
    int ind = 0;
    for(int i = 0; i<3; i++) {
        if(locationOf[color][i].first==from && locationOf[color][i].second==top) {
            ind = i;
            break;
        }
    }

    tubes[to][totop] = color;
    tubes[from][top] = 0;

    locationOf[color][ind] = {to, totop};

    //print();
}

int main() {

    cin >> N;
    int a;
    for(int i = 0; i<=N; i++) {
        for(int j = 0; j<3; j++) {
            cin >> a;
            tubes[i][j] = a;
            locationOf[a].push_back({i, j});
        }
    }

    for(int i = 1; i<=N; i++) {
        // move zeroes to front
        while(tubes[0][0]!=0) {
            //cout << tubes[0][0] << " " << tubes[0][1] << " " << tubes[0][2] << endl;
            move(0, nextZero(0));
        }
        int color = tubes[i][0];

        //cout << i << " " << instructions.size() << endl;
        for(int h = 1; h<3; h++) { // insert at h
            if(tubes[i][h]==color) continue;
            //cout << h << "|" << color << endl;
            pair<int, int> ball = findColor(color, i);
            int height = ball.second;
            if(height==2) {
                for(int j = 2; j>=h; j--) {
                    if(tubes[i][j]!=0) move(i, 0);
                }
                move(ball.first, i);
            }
            else if(height==1) {
                for(int j = 2; j>=h; j--) {
                    if(tubes[i][j]!=0) move(i, 0);
                }
                move(ball.first, 0);
                move(ball.first, i);
            }
            else {
                if(h==2) {
                    if(tubes[i][2]!=0) move(i, 0);
                    move(ball.first, 0);
                    move(ball.first, 0);
                    move(ball.first, i);
                }
                else {
                    move(ball.first, 0);
                    move(ball.first, 0);
                    move(ball.first, 0);
                    move(i, ball.first);
                    move(i, ball.first);
                    move(0, i);
                }
            }
            while(tubes[0][0]!=0) {
                //cout << tubes[0][0] << " " << tubes[0][1] << " " << tubes[0][2] << endl;
                move(0, nextZero(0));
            }
        }

    }

    cout << instructions.size() << endl;
    for(pii next : instructions) {
        cout << next.first << " " << next.second << endl;
    }

}

/*
3
2 2 0
1 3 1
3 1 2
3 0 0

 */