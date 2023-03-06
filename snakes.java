// USACO 2019 US Open Gold: Snakes
import java.util.*;
import java.io.*;

public class Snakes {

    public static int[] snakes;
    public static int N;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader("snakes.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("snakes.out")));

        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        int K = Integer.parseInt(st.nextToken());
        snakes = new int[N];
        st = new StringTokenizer(br.readLine());
        for(int i = 0; i<N; i++) snakes[i] = Integer.parseInt(st.nextToken());

        int[][] dp = new int[N+1][N];
        for(int i = 0; i<N; i++) {
            int min = Integer.MAX_VALUE/2;
            for(int j = 0; j<N; j++) {
                if(snakes[j]-snakes[i]<0) dp[j][i] = Integer.MAX_VALUE/2;
                else if(i>0){
                    if(dp[j][i-1] == Integer.MAX_VALUE/2) dp[j][i] = Integer.MAX_VALUE/2;
                    else {
                        dp[j][i] = snakes[j]-snakes[i];
                        if(i>0) dp[j][i] += dp[j][i-1];
                    }
                }
                else {
                    dp[j][i] = snakes[j]-snakes[i];
                    if(i>0) dp[j][i] += dp[j][i-1];
                }
                min = Math.min(min, dp[j][i]);
            }
            dp[N][i] = min;
        }

        for(int i = 0; i<K; i++) dp = iterate(dp);
        out.println(dp[N][N-1]);
        out.close();
        br.close();

    }

    public static int[][] iterate(int[][] dp) {
        int[][] next = new int[N+1][N];
        for(int i = 0; i<=N; i++) {
            next[i][0] = dp[i][0];
        }
        for(int i = 1; i<N; i++) {
            int min = Integer.MAX_VALUE;
            for(int j = 0; j<N; j++) {
                if(snakes[j]-snakes[i]<0) {
                    next[j][i] = Integer.MAX_VALUE/2;
                    continue;
                }
                else next[j][i] = Math.min(dp[j][i], Math.min(dp[N][i-1], next[j][i-1])+snakes[j]-snakes[i]);
                min = Math.min(min, next[j][i]);
            }
            next[N][i] = min;
        }
        return next;
    }
/*
    public static void printarray(int[][] dp) {
        for(int i = 0; i<=N; i++) {
            boolean yeet = false;
            for(int j = 0; j<N; j++) {
                if(dp[i][j] == Integer.MAX_VALUE/2) {
                    System.out.print("* ");
                    yeet = true;
                }
                else System.out.print(dp[i][j] + " ");
            }
            System.out.println();
        }
    }
*/
}
