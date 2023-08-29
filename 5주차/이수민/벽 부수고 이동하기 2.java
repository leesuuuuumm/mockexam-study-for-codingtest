import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dist;
		int wall;

		public Point(int r, int c, int dist, int wall) {
			this.r = r;
			this.c = c;
			this.dist = dist;
			this.wall = wall;
		}
	}

	static int[][] map;
	static int[][][] v;
	static int N, M, K;
	static Queue<Point> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());

		map = new int[N][M];
		v = new int[N][M][K + 1];
		for (int r = 0; r < N; r++) {
			char[] ch = br.readLine().toCharArray();

			for (int c = 0; c < M; c++) {
				map[r][c] = ch[c] - '0';

				for (int k = 0; k <= K; k++) {
					v[r][c][k] = Integer.MAX_VALUE;

				}
			}

		}

		int ans = Integer.MAX_VALUE;
		que = new LinkedList<>();

		que.offer(new Point(0, 0, 1, 0));
		v[0][0][0] = 1;

		bfs();

		for (int i = 0; i <= K; i++) {
			ans = Math.min(ans, v[N - 1][M - 1][i]);
		}
		System.out.println(ans == Integer.MAX_VALUE ? -1 : ans);

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				if (map[nr][nc] == 0 && v[nr][nc][cur.wall] > cur.dist + 1) {
					v[nr][nc][cur.wall] = cur.dist + 1;
					que.offer(new Point(nr, nc, cur.dist + 1, cur.wall));
				}

				if (map[nr][nc] == 1 && cur.wall < K && v[nr][nc][cur.wall + 1] > cur.dist + 1) {
					v[nr][nc][cur.wall + 1] = cur.dist + 1;
					que.offer(new Point(nr, nc, cur.dist + 1, cur.wall + 1));
				}

			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
