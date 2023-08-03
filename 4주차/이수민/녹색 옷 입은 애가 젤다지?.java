import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}
	}

	static int[][] dp;
	static int[][] map;
	static int N;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int i = 1;

		while (true) {
			N = Integer.parseInt(br.readLine());
			if (N == 0)
				break;
			map = new int[N][N];
			dp = new int[N][N];

			for (int r = 0; r < N; r++) {
				StringTokenizer st = new StringTokenizer(br.readLine());
				for (int c = 0; c < N; c++) {
					map[r][c] = Integer.parseInt(st.nextToken());
					dp[r][c] = Integer.MAX_VALUE;
				}
			}
			dp[0][0] = map[0][0];
			que = new LinkedList<>();

			for (int r = 0; r < N; r++) {
				for (int c = 0; c < N; c++) {
					que.offer(new Point(r, c));
					bfs();

				}
			}

			System.out.println("Problem " + (i++) + ": " + dp[N - 1][N - 1]);
		}
	}

	static int[] dr = { 0, 1, 0, -1 };
	static int[] dc = { 1, 0, -1, 0 };
	static Queue<Point> que;

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				if (dp[nr][nc] > map[nr][nc] + dp[cur.r][cur.c]) {
					dp[nr][nc] = map[nr][nc] + dp[cur.r][cur.c];
					que.offer(new Point(nr, nc));

				}
			}
		}
	}

	private static void print() {
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				System.out.print(dp[r][c] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}
}
