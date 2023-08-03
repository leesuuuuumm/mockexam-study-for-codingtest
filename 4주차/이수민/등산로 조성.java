import java.io.*;
import java.util.*;
 
public class Solution {
    static class Point {
        int r;
        int c;
 
        public Point(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
 
    static int[][] map;
    static int N;
    static int K;
    static ArrayList<Point> list;
    static boolean flag;
    static boolean[][] v;
 
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());
        for (int t = 1; t <= T; t++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            N = Integer.parseInt(st.nextToken());
            K = Integer.parseInt(st.nextToken());
            int max = 0;
            v = new boolean[N][N];
            map = new int[N][N];
            hikingTrail = 0;
            list = new ArrayList<>();
 
            for (int r = 0; r < N; r++) {
                st = new StringTokenizer(br.readLine());
                for (int c = 0; c < N; c++) {
                    map[r][c] = Integer.parseInt(st.nextToken());
                    max = Math.max(max, map[r][c]);
                }
            }
 
            for (int r = 0; r < N; r++) {
                for (int c = 0; c < N; c++) {
                    if (map[r][c] == max) {
                        list.add(new Point(r, c));
                    }
                }
            }
 
            for (int i = 0; i < list.size(); i++) {
                flag = false;
                v[list.get(i).r][list.get(i).c] = true;
                dfs(list.get(i), 1);
                v[list.get(i).r][list.get(i).c] = false;
            }
            System.out.println("#" + t + " " + hikingTrail);
 
        }
    }
 
    static int[] dr = { 1, 0, -1, 0 };
    static int[] dc = { 0, -1, 0, 1 };
    static int hikingTrail;
 
    private static void dfs(Point cur, int cnt) {
 
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
 
            if (!check(nr, nc))
                continue;
 
            if (v[nr][nc] || flag && map[nr][nc] >= map[cur.r][cur.c]) {
                hikingTrail = Math.max(hikingTrail, cnt);
                // System.out.println();
                continue;
            }
 
            if (!flag && map[nr][nc] >= map[cur.r][cur.c]) {
                for (int k = 1; k <= K; k++) {
                    if(map[nr][nc]-k>=map[cur.r][cur.c]) continue;
                    map[nr][nc] -= k;
                    v[nr][nc] = true;
                    flag = true;
                    // System.out.println(nr + " " + nc + " " + (cnt + 1));
 
                    dfs(new Point(nr, nc), cnt + 1);
                    v[nr][nc] = false;
                    map[nr][nc] += k;
                    flag = false;
                }
            }
 
            if (map[nr][nc] < map[cur.r][cur.c]) {
                v[nr][nc] = true;
                // System.out.println("ㄹㅇㅁㄴㄻㅇㄴㄻㅇㄴㄹㅇㄴ");
 
                // System.out.println(nr + " " + nc + " " + (cnt + 1));
                dfs(new Point(nr, nc), cnt + 1);
                v[nr][nc] = false;
            }
 
        }
 
    }
 
    private static boolean check(int nr, int nc) {
        return nr >= 0 && nr < N && nc >= 0 && nc < N;
    }
 
}
