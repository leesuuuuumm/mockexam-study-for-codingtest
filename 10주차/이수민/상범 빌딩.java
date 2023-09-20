import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int l;
		int r;
		int c;
		int time;

		public Point(int l, int r, int c, int time) {
			this.l = l;
			this.r = r;
			this.c = c;
			this.time = time;
		}
	}

	static int L, R, C;
	static char[][][] map;
	static boolean[][][] v;
	static Queue<Point> que;
	static int time;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			StringTokenizer st = new StringTokenizer(br.readLine());

			L = Integer.parseInt(st.nextToken());
			R = Integer.parseInt(st.nextToken());
			C = Integer.parseInt(st.nextToken());

			if (L == 0 && R == 0 && C == 0)
				return;

			map = new char[L][R][C];
			v = new boolean[L][R][C];

			que = new LinkedList<>();
			time = 0;

			for (int l = 0; l < L; l++) {
				for (int r = 0; r < R; r++) {
					map[l][r] = br.readLine().toCharArray();

					for (int c = 0; c < C; c++) {
						if (map[l][r][c] == 'S') {
							que.offer(new Point(l, r, c, 0));
							v[l][r][c] = true;
						}
					}
				}
				br.readLine();
			}

			time = -1;
			bfs();
			System.out.println(time == -1 ? "Trapped!" : "Escaped in " + time + " minute(s).");

		}
	}

	static int[] dl = { 0, 0, 0, 0, -1, 1 };
	static int[] dr = { -1, 1, 0, 0, 0, 0 };
	static int[] dc = { 0, 0, -1, 1, 0, 0 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			if (map[cur.l][cur.r][cur.c] == 'E') {
				time = cur.time;
				return;
			}
			for (int d = 0; d < 6; d++) {
				int nl = cur.l + dl[d];
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nl, nr, nc) || v[nl][nr][nc] || map[nl][nr][nc] == '#')
					continue;

				if (map[nl][nr][nc] == 'E') {
					time = cur.time + 1;
					return;
				}

				que.offer(new Point(nl, nr, nc, cur.time + 1));
				v[nl][nr][nc] = true;
			}
		}

	}

	private static boolean check(int nl, int nr, int nc) {
		return nl >= 0 && nl < L && nr >= 0 && nr < R && nc >= 0 && nc < C;
	}
}
