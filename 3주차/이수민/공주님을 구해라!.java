import java.io.*;
import java.util.*;

public class Main {
	static class Point {
		int r;
		int c;
		int dist;
		boolean sword;

		public Point(int r, int c, int dist, boolean sword) {
			this.r = r;
			this.c = c;
			this.dist = dist;
			this.sword = sword;
		}

	}

	static int[][] map;
	static int[][][] v;

	static int N, M, T;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		T = Integer.parseInt(st.nextToken());

		map = new int[N][M];

		for (int r = 0; r < N; r++) {
			st = new StringTokenizer(br.readLine());
			for (int c = 0; c < M; c++) {
				map[r][c] = Integer.parseInt(st.nextToken());

			}
		}

		v = new int[N][M][2];
		que = new LinkedList<>();

		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				v[r][c][0] = Integer.MAX_VALUE;
				v[r][c][1] = Integer.MAX_VALUE;
			}
		}

		que.offer(new Point(0, 0, 0, false));
		v[0][0][0] = 0;
		v[0][0][1] = 0;
		time = 0;

		bfs();
		System.out.println(time == 0 ? "Fail" : time);

	}

	static int time;

	static Queue<Point> que;
	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();

			if (cur.dist > T)
				break;
			if (cur.r == N - 1 && cur.c == M - 1) {
				time = Math.min(v[N - 1][M - 1][0], v[N - 1][M - 1][1]);
				return;

			}

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc))
					continue;

				if (map[nr][nc] == 2 && v[nr][nc][0] > cur.dist + 1) {
					que.offer(new Point(nr, nc, cur.dist + 1, true));
					v[nr][nc][0] = cur.dist + 1;
				}
				// v[][][0]: 벽 안뚫은애 , [1]: 벽 뚫은 애

				// 벽을 만나면
				else if (map[nr][nc] == 1) {
					if (cur.sword && v[nr][nc][1] > cur.dist + 1) {
						que.offer(new Point(nr, nc, cur.dist + 1, true));
						v[nr][nc][1] = cur.dist + 1;

					}
				}
				// 그냥 땅일 경우
				else if (map[nr][nc] == 0) {
					if (!cur.sword && v[nr][nc][0] > cur.dist + 1) {
						que.offer(new Point(nr, nc, cur.dist + 1, false));
						v[nr][nc][0] = cur.dist + 1;
					} else if (cur.sword && v[nr][nc][1] > cur.dist + 1) {
						que.offer(new Point(nr, nc, cur.dist + 1, true));
						v[nr][nc][1] = cur.dist + 1;
					}
				}

			}

		}
	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
