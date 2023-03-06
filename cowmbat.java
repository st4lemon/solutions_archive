// USACO December 2019 Gold: Moortal Cowmbat
import java.util.*;
import java.io.*;

public class cowmbat {

    public static int N, M, K;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader("cowmbat.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("cowmbat.out")));
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());

        int[][] cost = new int[M][M];
        int[] combo = new int[N];

        String line = br.readLine();
        for(int i = 0; i<N; i++) combo[i] = line.charAt(i)-97;

        for(int i = 0; i<M; i++) {
            st = new StringTokenizer(br.readLine());
            for(int j = 0; j<M; j++) {
                cost[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        for(int k = 0; k<M; k++) {
            for(int i = 0; i<M; i++) {
                for(int j = 0; j<M; j++) {
                    if(cost[i][j] > cost[i][k] + cost[k][j]) {
                        cost[i][j] = cost[i][k] + cost[k][j];
                    }
                }
            }
        }

        int[][] prefix = new int[N][M];
        for(int i = 0; i<N; i++) {
            for(int j = 0; j<M; j++) {
                if(i==0) prefix[i][j] = cost[combo[i]][j];
                else prefix[i][j] = prefix[i-1][j] + cost[combo[i]][j];
            }
        }
/*
        for(int i = 0; i<N; i++) {
            for(int j = 0; j<N; j++) System.out.print(cost[i][j]);
            System.out.println();
        }
*/
        int[][] dp = new int[N][M];
        for(int i = 0; i<N; i++) Arrays.fill(dp[i], Integer.MAX_VALUE/2);
        for(int i = 0; i<M; i++) {
            int num = 0;
            for(int j = 0; j<K; j++) {
                num += cost[combo[j]][i];
            }
            dp[K-1][i] = num;
        }

        //print(dp);

        for(int i = K-1; i<N-1; i++) {
            for(int j = 0; j<M; j++) {
                //add one number
                dp[i+1][j] = Math.min(dp[i+1][j], dp[i][j] + cost[combo[i+1]][j]);
                //change to new number
                if(i+K>=N) continue;
                for(int a = 0; a<M; a++) {
                    if(a==j) continue;
                    int num = prefix[i+K][a]-prefix[i][a];
                    dp[i+K][a] = Math.min(dp[i+K][a], dp[i][j] + num);
                    //System.out.println(i + " " + j + " " + a + " " + num);
                }
            }
            //System.out.println(i);
            //print(dp);
        }

        int ans = Integer.MAX_VALUE;
        for(int i = 0; i<M; i++) {
            ans = Math.min(ans, dp[N-1][i]);
        }
        pw.println(ans);
        pw.close();
        br.close();

    }

    public static void print(int[][] dp) {

        for(int i = 0; i<N; i++) {
            for(int j = 0; j<M; j++) {
                if(dp[i][j]==Integer.MAX_VALUE/2) System.out.print("- ");
                else System.out.print(dp[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();

    }

}
