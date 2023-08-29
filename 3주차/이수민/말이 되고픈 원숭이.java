import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int k;
		int dist;

		public Point(int r, int c, int k, int dist) {
			this.r = r;
			this.c = c;
			this.k = k;
			this.dist = dist;
		}
	}

	static int K;
	static int H, W;
	static int[][] map;
	static int[][][] v;
	static Queue<Point> que;
	static int ans;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		K = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine());
		W = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());

		map = new int[H][W];
		v = new int[H][W][K + 1];
		que = new LinkedList<>();
		ans = Integer.MAX_VALUE;

		for (int r = 0; r < H; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < W; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());

				for (int k = 0; k <= K; k++) {
					v[r][c][k] = Integer.MAX_VALUE;
				}
			}
		}

		que.offer(new Point(0, 0, 0, 0));
		v[0][0][0] = 0;

		bfs();

		for (int i = 0; i <= K; i++) {
			ans = Math.min(ans, v[H - 1][W - 1][i]);
		}
		System.out.println(ans == Integer.MAX_VALUE ? -1 : ans);

	}

	static int[] dr = { 0, -1, 1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	static int[] hr = { -2, -1, -2, -1, 2, 1, 2, 1 };
	static int[] hc = { -1, -2, 1, 2, -1, -2, 1, 2 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || map[nr][nc] == 1 || v[nr][nc][cur.k] <= cur.dist + 1)
					continue;

				v[nr][nc][cur.k] = cur.dist + 1;
				que.offer(new Point(nr, nc, cur.k, cur.dist + 1));
			}

			if (cur.k < K) {
				for (int d = 0; d < 8; d++) {
					int nr = cur.r + hr[d];
					int nc = cur.c + hc[d];

					if (!check(nr, nc) || map[nr][nc] == 1 || v[nr][nc][cur.k + 1] <= cur.dist + 1)
						continue;

					v[nr][nc][cur.k + 1] = cur.dist + 1;
					que.offer(new Point(nr, nc, cur.k + 1, cur.dist + 1));

				}

			}
		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < H && nc >= 0 && nc < W;
	}
}
