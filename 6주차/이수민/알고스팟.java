import java.io.*;
import java.util.*;

public class Main {

	static class Point {
		int r;
		int c;
		int wall;

		public Point(int r, int c, int wall) {
			this.r = r;
			this.c = c;
			this.wall = wall;
		}
	}

	static int N, M;
	static int[][] map;
	static boolean[][] v;
	static Deque<Point> que;

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		StringTokenizer st = new StringTokenizer(br.readLine());
		M = Integer.parseInt(st.nextToken());
		N = Integer.parseInt(st.nextToken());
		map = new int[N][M];
		v = new boolean[N][M];

		for (int r = 0; r < N; r++) {
			char[] ch = br.readLine().toCharArray();
			for (int c = 0; c < M; c++) {
				map[r][c] = ch[c] - '0';
			}
		}
		que = new LinkedList<>();

		v[0][0] = true;
		min = Integer.MAX_VALUE;
		que.offer(new Point(0, 0, 0));
		bfs();

	}

	static int[] dr = { 0, 1, -1, 0 };
	static int[] dc = { 1, 0, 0, -1 };
	static int min;

	private static void bfs() {
		while (!que.isEmpty()) {
			Point cur = que.poll();
			if (cur.r == N - 1 && cur.c == M - 1) {
				System.out.println(cur.wall);
				return;
			}

			for (int d = 0; d < 4; d++) {
				int nr = cur.r + dr[d];
				int nc = cur.c + dc[d];

				if (!check(nr, nc) || v[nr][nc])
					continue;

				if (map[nr][nc] == 1) {
					que.offer(new Point(nr, nc, cur.wall + 1));
					v[nr][nc] = true;

				} else if (map[nr][nc] == 0) {
					que.addFirst(new Point(nr, nc, cur.wall));
					v[nr][nc] = true;
				}

			}

		}

	}

	private static boolean check(int nr, int nc) {
		return nr >= 0 && nr < N && nc >= 0 && nc < M;
	}
}
