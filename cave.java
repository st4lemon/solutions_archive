// USACO January 2020 Platinum: Cave Paintings
import java.util.*;
import java.io.*;

public class cave {

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader("cave.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cave.out")));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        char[][] map = new char[N][M];
        for(int i = 0; i<N; i++) {
            map[i] = br.readLine().toCharArray();
        }

        int[][] nums = new int[N][M]; // grouping
        long[][] vals = new long[N][M]; // ways
        int g = 1;

        for(int i = N-2; i>0; i--) {
            int par = -1;
            for(int j = 1; j<M-1; j++) {
                if(map[i][j]=='#') {
                    par = -1;
                    continue;
                }
                if(par == -1) {
                    par = 10000*i + j;
                    vals[i][j] = 1;
                }
                nums[i][j] = par;
                if(map[i+1][j]=='#') continue;
                int p = parent(i+1, j, nums);
                if(p==par) continue;
                nums[p/10000][p%10000] = par;
                vals[par/10000][par%10000] *= Math.abs(vals[p/10000][p%10000]);
                vals[par/10000][par%10000] %= 1000000007;
            }
            for(int j = 1; j<M-1; j++) {
                int p = parent(i, j, nums);
                if(vals[p/10000][p%10000]>0) {
                    vals[p/10000][p%10000]++;
                    vals[p/10000][p%10000]*=-1;
                }
            }
        }

        long ans = 1;
        for(int i = 1; i<N-1; i++) {
            for(int j = 1; j<M-1; j++) {
                int p = parent(i, j, nums);
                if (vals[p / 10000][p % 10000] < 0) {
                    vals[p / 10000][p % 10000] *= -1;
                    ans *= vals[p / 10000][p % 10000];
                    ans %= 1000000007;
                    //System.out.println(i + " " + ans);
                }
            }
        }
/*
        for(int i = 0; i<N; i++) {
            for(int j = 0; j<M; j++) System.out.print(vals[i][j] + " ");
            System.out.println();
        }

        for(int i = 0; i<N; i++) {
            for(int j = 0; j<M; j++) System.out.print(nums[i][j] + " ");
            System.out.println();
        }
*/
        out.println(ans);
        out.close();
        br.close();

    }

    public static int parent(int x, int y, int[][] u) {
        if(x==u[x][y]/10000 && y==u[x][y]%10000) return u[x][y];
        int val = parent(u[x][y]/10000, u[x][y]%10000, u);
        u[x][y] = val;
        return val;
    }

}
