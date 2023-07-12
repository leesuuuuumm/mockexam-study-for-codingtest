import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r1;
		int c1;
		int r2;
		int c2;
		int cnt;

		public Point(int r1, int c1, int r2, int c2, int cnt) {
			this.r1 = r1;
			this.c1 = c1;
			this.r2 = r2;
			this.c2 = c2;
			this.cnt = cnt;
		}
	}

	static int N, M;
	static char[][] map;
	static Queue<Point> que;
	static boolean[][][][] v;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		v = new boolean[N][M][N][M];

		map = new char[N][M];
		que = new LinkedList<>();
		int r1 = -1;
		int c1 = -1;
		for (int r = 0; r < N; r++) {
			map[r] = br.readLine().toCharArray();
			a: for (int c = 0; c < M; c++) {
				if (map[r][c] == 'o') {
					if (r1 == -1 && c1 == -1) {
						r1 = r;
						c1 = c;
					} else {
						que.offer(new Point(r1, c1, r, c, 0));
						v[r1][c1][r][c] = true;
						break a;
					}
				}
			}
		}

		System.out.println(bfs());
	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static int bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			if (cur.cnt > 10) {
				return -1;
			}
			for (int d = 0; d < 4; d++) {
				int nr1 = cur.r1 + dr[d];
				int nc1 = cur.c1 + dc[d];
				int nr2 = cur.r2 + dr[d];
				int nc2 = cur.c2 + dc[d];

				if ((nr1 < 0 || nr1 >= N || nc1 < 0 || nc1 >= M) && (nr2 < 0 || nr2 >= N || nc2 < 0 || nc2 >= M)) {
					continue;
				}

				if ((nr1 < 0 || nr1 >= N || nc1 < 0 || nc1 >= M) || (nr2 < 0 || nr2 >= N || nc2 < 0 || nc2 >= M)) {
					if (cur.cnt + 1 > 10) {
						return -1;
					}

					return cur.cnt + 1;
				}

				if (map[nr1][nc1] == '#') {
					nr1 = cur.r1;
					nc1 = cur.c1;
				}

				if (map[nr2][nc2] == '#') {
					nr2 = cur.r2;
					nc2 = cur.c2;
				}
				if (v[nr1][nc1][nr2][nc2] || nr1 == nr2 && nc1 == nc2) {
					continue;
				}
				v[nr1][nc1][nr2][nc2] = true;

				que.offer(new Point(nr1, nc1, nr2, nc2, cur.cnt + 1));

			}

		}
		return -1;
	}
}
