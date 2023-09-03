import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int num;
		int dist;

		public Point(int r, int c) {
			this.r = r;
			this.c = c;
		}

		public Point(int r, int c, int num, int dist) {
			this.r = r;
			this.c = c;
			this.num = num;
			this.dist = dist;
		}
	}

	static int[][] map;
	static boolean[][] v;
	static int N;
	static Queue<Point> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		N = Integer.parseInt(br.readLine());
		map = new int[N][N];

		for (int r = 0; r < N; r++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				if (map[r][c] == 1)
					map[r][c] = -1;
			}
		}

		que = new LinkedList<>();
		int cnt = 0;

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				if (map[r][c] == -1) {
					que.offer(new Point(r, c));
					map[r][c] = ++cnt;
					bfs(cnt);
				}

			}
		}
		min = Integer.MAX_VALUE;
		makeLegs();
		System.out.println(min);

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs(int cnt) {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || map[nr][nc] != -1)
					continue;

				que.offer(new Point(nr, nc));
				map[nr][nc] = cnt;

			}

		}

	}

	static int min;

	private static void makeLegs() {

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < N; c++) {
				v = new boolean[N][N];

				if (map[r][c] != 0) {
					v[r][c] = true;
					que.offer(new Point(r, c, map[r][c], 0));
					start();

				}

			}
		}

	}

	private static void start() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == 0) {
					que.offer(new Point(nr, nc, cur.num, cur.dist + 1));
					v[nr][nc] = true;
				} else if (map[nr][nc] != cur.num) {
					min = Math.min(cur.dist, min);
				}
			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < N;
	}

}
