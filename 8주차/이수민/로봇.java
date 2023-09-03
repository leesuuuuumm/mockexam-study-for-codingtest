import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dir;
		int dist;

		public Point(int r, int c, int dir, int dist) {
			this.r = r;
			this.c = c;
			this.dir = dir;
			this.dist = dist;
		}
	}

	static int N, M;
	static int[][][] v;
	static int[][] map;
	static Queue<Point> que;
	static int er, ec, ed;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		map = new int[M][N];
		v = new int[M][N][4];

		que = new LinkedList<>();
		for (int r = 0; r < M; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < N; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());
				for (int d = 0; d < 4; d++) {
					v[r][c][d] = Integer.MAX_VALUE;
				}
			}
		}

		st = new StringTokenizer(br.readLine());
		int sr = Integer.parseInt(st.nextToken()) - 1;
		int sc = Integer.parseInt(st.nextToken()) - 1;
		int sd = Integer.parseInt(st.nextToken()) - 1;
		que.offer(new Point(sr, sc, sd, 0));
		v[sr][sc][sd] = 0;

		st = new StringTokenizer(br.readLine());
		int er = Integer.parseInt(st.nextToken()) - 1;
		int ec = Integer.parseInt(st.nextToken()) - 1;
		int ed = Integer.parseInt(st.nextToken()) - 1;

		bfs();

		System.out.println(v[er][ec][ed]);

	}

	static int[] dr = { 0, 0, 1, -1 };
	static int[] dc = { 1, -1, 0, 0 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			order1(cur);
			order2(cur);
		}

	}

	private static void order1(Point cur) {
		int nr = cur.r;
		int nc = cur.c;

		for (int k = 1; k <= 3; k++) {
			nr += dr[cur.dir];
			nc += dc[cur.dir];

			if (!check(nr, nc) || map[nr][nc] == 1)
				break;

			if (v[nr][nc][cur.dir] > cur.dist + 1) {
				que.offer(new Point(nr, nc, cur.dir, cur.dist + 1));
				v[nr][nc][cur.dir] = cur.dist + 1;
			}
		}
	}

	private static void order2(Point cur) {
		if (cur.dir == 0 || cur.dir == 1) {
			for (int d = 2; d <= 3; d++) {
				changeDir(cur, d);
			}
		} else {
			for (int d = 0; d <= 1; d++) {
				changeDir(cur, d);
			}
		}
	}

	private static void changeDir(Point cur, int d) {
		if (v[cur.r][cur.c][d] > cur.dist + 1) {
			v[cur.r][cur.c][d] = cur.dist + 1;
			que.offer(new Point(cur.r, cur.c, d, cur.dist + 1));
		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < M && nc >= 0 && nc < N;
	}

}
