import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dist;
		boolean flag;

		public Point(int r, int c, int dist, boolean flag) {
			this.r = r;
			this.c = c;
			this.dist = dist;
			this.flag = flag;
		}
	}

	static int[][] map;
	static int N, M;
	static int[][][] v;
	static Queue<Point> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[N][M];
		v = new int[N][M][2];

		for (int r = 0; r < N; r++) {
			char[] ch = br.readLine().toCharArray();

			for (int c = 0; c < M; c++) {
				map[r][c] = ch[c] - '0';
				v[r][c][0] = Integer.MAX_VALUE;
				v[r][c][1] = Integer.MAX_VALUE;

			}
		}
		que = new LinkedList<>();
		que.offer(new Point(0, 0, 1, false));
		v[0][0][0] = 1;
		v[0][0][1] = 1;
		answer = -1;

		bfs();
		System.out.println(answer);

	}

	static int answer;

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			if (cur.r == N - 1 && cur.c == M - 1) {
				answer = Math.min(v[cur.r][cur.c][0], v[cur.r][cur.c][1]);
				return;
			}

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				if (map[nr][nc] == 1 && !cur.flag && v[nr][nc][1] > cur.dist + 1) {
					v[nr][nc][1] = cur.dist + 1;
					que.offer(new Point(nr, nc, cur.dist + 1, true));

				} else if (map[nr][nc] == 0) {
					if (!cur.flag && v[nr][nc][0] > cur.dist + 1) {
						v[nr][nc][0] = cur.dist + 1;
						que.offer(new Point(nr, nc, cur.dist + 1, false));
					} else if (cur.flag && v[nr][nc][1] > cur.dist + 1) {
						v[nr][nc][1] = cur.dist + 1;
						que.offer(new Point(nr, nc, cur.dist + 1, true));
					}

				}

			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
